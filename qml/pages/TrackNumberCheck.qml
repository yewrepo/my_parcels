import QtQuick 2.0
import Sailfish.Silica 1.0

import ru.yewrepo.myparcels 1.0
import "../views"

Page {

    property var barcode
    property int postService: PostService.RU_POCHTA
    property string userCaption: ""
    property var serviceComboBoxLink

    property int state: -1
    property int error: -1
    property var parcelDetails
    property var serviceList: checkBarcodeViewModel.servicePostList

    objectName: "checkerPage"
    allowedOrientations: Orientation.All

    BusyIndicator {
        size: BusyIndicatorSize.Large
        anchors.centerIn: parent
        running: isLoadingState()
    }

    SilicaFlickable {
        anchors.fill: parent

        PageHeader {
            id: header
            objectName: "pageHeader"
            title: hasStartupBarcode() ? qsTr("Отслеживание") : qsTr("Добавление трек-номера")
        }

        ViewPlaceholder {
            enabled: isErrorState()
            text: qsTr("Ошибка")
            hintText: qsTr(getErrorTypeText())
        }

        TextField {
            id: trackField
            text: barcode === undefined ? "" : barcode
            anchors.top: header.bottom
            width: parent.width
            hideLabelOnEmptyField: false
            placeholderText: qsTr("")
            label: qsTr("Трек-номер")
            EnterKey.enabled: !errorHighlight
            enabled: !hasStartupBarcode()

            inputMethodHints: Qt.ImhPreferUppercase
            font.capitalization: Font.AllUppercase
            textRightMargin: {
                if (!hasStartupBarcode()){
                    Theme.horizontalPageMargin + sendButton.width + Theme.paddingLarge
                }else{
                    Theme.horizontalPageMargin
                }
            }
            validator: RegExpValidator{
                regExp: /^.{3,32}$/
            }
            labelComponent: Row {
                spacing: Theme.paddingSmall
                width: parent.width

                MiniComboBox {
                    id: serviceComboBox

                    menu: ContextMenu {
                        id: serviceComboBoxMenu
                        Repeater {
                            model: serviceList
                            MenuItem {
                                text: "" + serviceList[index].caption
                                onClicked: {
                                    checkBarcodeViewModel.setSelectedService(serviceList[index].postService)
                                }
                            }
                        }
                    }
                }

                Component.onCompleted: {
                    serviceComboBoxLink = serviceComboBox
                }
            }
            SecondaryButton {
                id: sendButton
                parent: trackField
                width: Theme.iconSizeMedium + 2 * Theme.paddingSmall
                height: width
                anchors{
                    right: parent.right
                    rightMargin: Theme.horizontalPageMargin
                }
                y: trackField.contentItem.y + trackField.contentItem.height - height/2
                icon.source: "image://theme/icon-m-send"
                enabled: (!trackField.errorHighlight && trackField.text.length > 0)
                visible: !hasStartupBarcode()
                onClicked: {
                    refreshTrackData(trackField.text.toUpperCase())
                }
            }
        }

        Row {
            id: realBarcodeRow
            anchors.horizontalCenter: parent.horizontalCenter
            height: hasRealbarcode() ? realBarcode.height : 0
            visible: hasRealbarcode()
            anchors{
                top: trackField.bottom
                right: parent.right
                rightMargin: Theme.horizontalPageMargin
            }
            Label {
                id: realBarcode
                text: getRealBarcodeText()
                color: Theme.highlightColor
                truncationMode: TruncationMode.Fade
                font.pixelSize: Theme.fontSizeExtraSmall
            }
        }

        Label {
            id: captionLabel
            text: userCaption
            leftPadding: Theme.horizontalPageMargin
            rightPadding: Theme.horizontalPageMargin + captionButton.width + Theme.paddingLarge
            topPadding: captionButton.height/4
            visible: isSuccessState()
            anchors{
                top: realBarcodeRow.bottom
                left: parent.left
                right: parent.right
            }

            SecondaryButton {
                id: captionButton
                icon.source: "image://theme/icon-m-edit"
                width: Theme.iconSizeMedium + 2 * Theme.paddingSmall
                height: width
                anchors{
                    right: parent.right
                    rightMargin: Theme.horizontalPageMargin
                }
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("ChangeParcelName.qml"))
                    dialog.accepted.connect(
                                function() {
                                    userCaption = dialog.nameValue
                                    checkBarcodeViewModel.changeCaption(userCaption)
                                })
                }
            }
        }

        Row {
            id: additionalInfoRow
            height: isPochtaRuAndNotLoading() ? additionalInfoButton.height : 0
            visible: isPochtaRuAndNotLoading()
            anchors {
                top: captionLabel.bottom;
                topMargin: Theme.paddingLarge
                horizontalCenter: parent.horizontalCenter
            }

            SecondaryButton {
                id: additionalInfoButton
                text: qsTr("Информация")
                onClicked: detailsPanel.open = !detailsPanel.open
            }
        }

        SectionHeader {
            id: historySection
            anchors.top: additionalInfoRow.bottom
            topPadding: Theme.paddingLarge
            text: qsTr("История перемещений")
            visible: isSuccessState()
        }

        SilicaListView{
            clip: true
            model: listModel
            visible: isSuccessState()
            anchors{
                top: historySection.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }

            delegate:
                TrackingHistoryView{
                date: model.time
                description: model.description
                optionalData: model.optionalData
                onClicked: {
                    Notices.show(model.description, Notice.Long, Notice.Bottom)
                }
            }

            ViewPlaceholder {
                enabled: listModel.count === 0 && isSuccessState()
                text: qsTr("Нет данных о перемещении")
            }

            VerticalScrollDecorator {}
        }
    }

    DockedPanel {
        id: detailsPanel
        width: parent.width
        height: 400
        dock: Dock.Bottom

        PochtaRuDetailsView{
            id: dockerDetails
            parcelData: parcelDetails
            anchors.centerIn: parent
            isVisible: isPochtaRuAndNotLoading()
        }
    }

    ListModel {
        id: listModel

        function updateList() {
            console.log("updateList")
            listModel.clear()
            for (var index = 0; index < parcelDetails.historyItemList.length; index++) {
                listModel.append(parcelDetails.historyItemList[index])
            }
            console.log("list count: "+listModel.count)
        }
    }

    function hasRealbarcode(){
        return parcelDetails !== undefined && parcelDetails.realBarcode !== ""
    }

    function isPochtaRuAndNotLoading(){
        return isPochtaRu() && isSuccessState()
    }

    function isPochtaRu(){
        return parcelDetails !== undefined && parcelDetails.postService == PostService.RU_POCHTA
    }

    function isLoadingState(){
        return state === LoadingStatus.LOADING;
    }

    function isSuccessState(){
        return state === LoadingStatus.SUCCESS;
    }

    function isErrorState(){
        return state === LoadingStatus.ERROR;
    }

    function hasStartupBarcode(){
        return barcode !== undefined
    }

    function getErrorTypeText(){
        switch(error){
        case ErrorType.EMPTY_RESPONSE:
            return "Сервис вернул пустой ответ"
        case ErrorType.NETWORK:
            return "Возникла сетевая ошибка"
        case ErrorType.WRONG_SERVICE:
            return "Выбран неправильный сервис"
        default:
            return "Возможно неправильный трек-номер"
        }
    }

    function getRealBarcodeText(){
        if (parcelDetails !== undefined){
            return parcelDetails.barcode + " ⤑ " + parcelDetails.realBarcode
        }
        return ""
    }

    function getPostServiceIndex(){
        for (var i = 0; i < serviceList.length; i++) {
            if (postService === serviceList[i].postService){
                console.log("getPostServiceIndex " + i)
                return i
            }
        }
        return 0
    }

    function refreshTrackData(barcode){
        checkBarcodeViewModel.setBarcode(barcode)
        checkBarcodeViewModel.checkBarcode(!hasStartupBarcode())
    }

    Component.onCompleted: {
        checkBarcodeViewModel.setSelectedService(postService)
        if (hasStartupBarcode()) {
            serviceComboBoxLink.currentIndex = getPostServiceIndex()
            refreshTrackData(barcode)
        }
    }

    Connections{
        target: checkBarcodeViewModel
        onGotDetails: {
            console.log("onGotDetails by " + details.barcode)

            dockerDetails.parcelData = checkBarcodeViewModel.parcelDetails

            parcelDetails = details
            if (!hasStartupBarcode()){
                userCaption = parcelDetails.title
            }
            listModel.updateList()
        }
        onGotLoadingState: {
            state = loadingState;
            error = errorType
        }
        onGotNotification: {
            Notices.show(message, Notice.Long, Notice.Center)
        }
    }
}
