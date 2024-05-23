import QtQuick 2.0
import Sailfish.Silica 1.0

Rectangle {

    property var parcelData
    property alias isVisible: summaryCard.visible

    id: summaryCard
    anchors.horizontalCenter: parent.horizontalCenter
    radius: 10
    height: 300
    width: parent.width - (2* Theme.horizontalPageMargin)

    Column{
        anchors.left: parent.left
        anchors.right: parent.right

        Label {
            text: parcelDetails === undefined ? "" : "" + parcelDetails.title
            width: parent.width - Theme.horizontalPageMargin
            topPadding: Theme.horizontalPageMargin
            leftPadding: Theme.horizontalPageMargin
        }
        Label {
            text: parcelDetails === undefined ? "" : "Вес: "+parcelDetails.weight + "г."
            width: parent.width - Theme.horizontalPageMargin
            leftPadding: Theme.horizontalPageMargin
        }
        Label {
            text: parcelDetails === undefined ? "" : "От кого: "+parcelDetails.sender
            width: parent.width - Theme.horizontalPageMargin
            leftPadding: Theme.horizontalPageMargin
        }
        Label {
            text: parcelDetails === undefined ? "" : "Кому: "+parcelDetails.recipient
            width: parent.width - Theme.horizontalPageMargin
            leftPadding: Theme.horizontalPageMargin
        }
        Label {
            text: parcelDetails === undefined ? "" : "Добавлено: "+parcelDetails.acceptanceDate
            width: parent.width - Theme.horizontalPageMargin
            leftPadding: Theme.horizontalPageMargin
        }
    }
}
