import QtQuick 2.0
import Sailfish.Silica 1.0

ListItem {
    width: parent.width - (2* Theme.horizontalPageMargin)
    contentHeight: Theme.itemSizeExtraLarge
    x: Theme.horizontalPageMargin

    property alias date: rowDate.text
    property alias description: rowStatus.text
    property alias optionalData: rowPoint.text

    Label {
        id: rowDate
        truncationMode: TruncationMode.Fade
    }
    Label {
        id: rowStatus
        anchors.top: rowDate.bottom
        truncationMode: TruncationMode.Fade
        width: parent.width - Theme.horizontalPageMargin
        //wrapMode: Label.WordWrap
    }
    Label {
        id: rowPoint
        anchors.top: rowStatus.bottom
        truncationMode: TruncationMode.Fade
    }
    Rectangle{
        anchors.top: rowPoint.bottom
        height: 1
        width: parent.width
        color: Theme.highlightColor
    }
}
