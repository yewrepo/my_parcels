import QtQuick 2.0
import Sailfish.Silica 1.0

ListItem {
    width: parent.width - (2* Theme.horizontalPageMargin)
    contentHeight: Theme.itemSizeExtraLarge
    x: Theme.horizontalPageMargin

    property alias barcode: number.text
    property alias userCaption: userCaption.text
    property alias iconSource: serviceIcon.source
    property bool isNewStatus

    property string lastStatusText
    property bool noLastStatus: lastStatusText.length == 0

    Row{
        id: topRow
        Label {
            id: number
            visible: text.length >0
            truncationMode: TruncationMode.Fade
            style: isNewStatus ? "Outline" : "Normal"
            leftPadding: 8
            rightPadding: 12
            topPadding: 8
        }
        Icon{
            id: statusChangeIcon
            source: "../icons/newMark.svg"
            color: palette.highlightColor
            visible: isNewStatus
        }
    }
    Label {
        id: userCaption
        visible: text.length >0
        anchors.top: topRow.bottom
        truncationMode: TruncationMode.Fade
        leftPadding: 8
    }
    Label {
        id: lastStatus
        visible: text.length >0
        text: noLastStatus ? "Нет информации" : lastStatusText
        color: (lastStatusText.length == 0) ? Theme.highlightDimmerColor : Theme.highlightColor
        anchors.top: userCaption.bottom
        truncationMode: TruncationMode.Fade
        leftPadding: 8
        bottomPadding: 8
    }
    Image {
        id: serviceIcon
        fillMode: Image.Pad
        source: ""
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }
}
