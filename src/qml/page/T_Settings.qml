import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs
import FluentUI 1.0
import "../component"

FluScrollablePage {
    id: settings_root
    launchMode: FluPageType.SingleInstance
    title: qsTr("Settings")
    FluFrame{
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 50
        padding: 10
        FluCheckBox{
            id: cb_stop_mode
            text: qsTr("All-stop mode")
            checked: false
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                controller.changeStopMode(checked)
            }
        }
    }
    Connections {
        target: controller
        function onIsTracingchanged(val) {
            cb_stop_mode.enabled = !val
        }
    }
}
