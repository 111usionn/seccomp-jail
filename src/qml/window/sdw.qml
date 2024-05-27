import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import FluentUI 1.0
import "../component"

FluWindow {
    title:"Detail"
    width: 500
    height: 600
    fixSize: true
    launchMode: FluWindowType.Standard
    property int pid_
    property int argNumber: select_arg.currentIndex
    property var addrs: []
    property var ctrl
    onInitArgument:
        (argument)=>{
            pid_ = argument.pid
            addrs = argument.addrs
            ctrl = argument.ctrl
        }
    FluFrame {
        id: frame1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 5
        height: 60
        FluComboBox {
            id: select_arg
            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 10
            }
            editable: false
            model: ListModel {
                ListElement {name: "arg1";}
                ListElement {name: "arg2";}
                ListElement {name: "arg3";}
                ListElement {name: "arg4";}
                ListElement {name: "arg5";}
                ListElement {name: "arg6";}
            }
            textRole: "name"
        }
        FluTextBox {
            id: input_length
            width: 100
            placeholderText: qsTr("Length")
            cleanEnabled: true
            anchors {
                verticalCenter: parent.verticalCenter
                left: select_arg.right
                leftMargin: 10
            }
            text: "4"
        }
        FluFilledButton {
            text: qsTr("Peek")
            anchors {
                verticalCenter: parent.verticalCenter
                left: input_length.right
                leftMargin: 10
            }
            onClicked: {
                ctrl.getCommand(pid_, 0, 0, addrs[0], addrs[1], addrs[2], addrs[3], addrs[4], addrs[5], 0, argNumber, 4, Number(input_length.text))
            }
        }
    }
    FluMultilineTextBox{
        id: display_info
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: frame1.bottom
        anchors.margins: 5
        disableColor: FluTheme.dark ?  Qt.rgba(255/255,255/255,255/255,1) : Qt.rgba(27/255,27/255,27/255,1)
        disabled: true
        anchors.fill: parent
    }
    Connections {
        target: ctrl
        function onShowPeekData(pid, num, data, strData) {
            if(pid == pid_)
            {
                if(num == 0) {
                    display_info.text = ""
                }
                display_info.text += data + "(" + strData + ")" + '\n'
            }
        }
    }
}
