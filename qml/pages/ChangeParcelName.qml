import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {

    property string nameValue

    DialogHeader {
        acceptText: qsTr("Изменить название")
        cancelText: qsTr("Отмена")
    }
    TextField {
        id: nameField
        anchors.centerIn: parent
        width: parent.width
        placeholderText: qsTr("Введите название для посылки")
        label: qsTr("")
        EnterKey.enabled: !errorHighlight
        validator: RegExpValidator{
            regExp: /^.{3,32}$/
        }
    }
    onDone: if (result == DialogResult.Accepted)
                nameValue = nameField.text
}
