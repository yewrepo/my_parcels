/*******************************************************************************
**
** Copyright (C) 2022 ru.yewrepo.rupochta
**
** This file is part of the Отслеживание посылок Почты России project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

import QtQuick 2.0
import Sailfish.Silica 1.0

import ru.yewrepo.myparcels 1.0
import "../views"

Page {
    id: root
    objectName: "mainPage"
    allowedOrientations: Orientation.All

    property int parcelsCount: 0

    SilicaListView {
        anchors.fill: parent
        header: PageHeader {
            objectName: "pageHeader"
            title: qsTrId("Мои посылки")
            extraContent.children: [
                IconButton {
                    objectName: "aboutButton"
                    icon.source: "image://theme/icon-m-refresh"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        barcodeListViewModel.refreshAll()
                    }
                }
            ]
        }
        model: trackNumbersModel
        delegate: TrackNumberView {

            property var code : model.barcodeNumber
            property var postService : model.postService

            barcode: code
            userCaption: ""+ model.userCaption
            lastStatusText: model.lastStatus
            isNewStatus: model.isNewStatus
            iconSource: getIconSource(postService)

            onClicked: {
                barcodeListViewModel.setStatusChecked(code)
                console.log("postService: " + postService)
                pageStack.push(
                            Qt.resolvedUrl("TrackNumberCheck.qml"),
                            {barcode: code, userCaption: userCaption, postService: postService})
            }

            menu: Component {
                ContextMenu {
                    MenuItem {
                        text: qsTr("Удалить")
                        onClicked: {
                            trackNumbersModel.removeItem(index)
                            barcodeListViewModel.removeParcel(code)
                        }
                    }
                }
            }

            ListView.onRemove: animateRemoval()
        }

        VerticalScrollDecorator { }

        PullDownMenu {
            MenuItem {
                text: qsTr("О программе")
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
                }
            }
            MenuItem {
                text: qsTr("Добавить трек-номер")
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("TrackNumberCheck.qml"))
                }
            }
        }

        ViewPlaceholder {
            id: emptyPlaceHolder
            text: qsTr("Нет посылок")
        }

        Component.onCompleted: {
            barcodeListViewModel.fetchAll()
        }
    }

    function getIconSource(postService){
        switch(postService){
        case PostService.RU_POCHTA:
            return "../png/icon_rp.png"
        case PostService.GLOBAL_CAINIAO:
            return "../png/icon_cng.png"
        default:
            return "../png/icon_cn.png"
        }
    }

    DockedPanel {
        id: loadingPanel
        open: false
        width: page.isPortrait ? parent.width : Theme.itemSizeExtraLarge + Theme.paddingLarge
        height: page.isPortrait ? Theme.itemSizeExtraLarge + Theme.paddingLarge : parent.height

        dock: page.isPortrait ? Dock.Bottom : Dock.Right

        BusyIndicator {
            size: BusyIndicatorSize.Large
            anchors.centerIn: parent
            running: loadingPanel.expanded
        }
    }

    Connections{
        target: barcodeListViewModel

        onStoredListChanged: {
            console.log("onStoredListChanged")
            barcodeListViewModel.fetchAll()
        }

        onFetchStoredBarcodes: {
            trackNumbersModel.clear()
            emptyPlaceHolder.enabled = list.length === 0
            parcelsCount = list.length
            console.log("get stored: "+list.length)
            for (var index = 0; index < list.length; index++) {
                trackNumbersModel.addItem(list[index]);
            }
        }

        onLoadingCallback: {
            console.log("onLoadingCallback: "+loadingState)
            loadingPanel.open = loadingState === LoadingStatus.LOADING
            if (loadingState === LoadingStatus.ERROR){
                Notices.show("ERROR", Notice.Long, Notice.Center)
            }
        }
    }
}
