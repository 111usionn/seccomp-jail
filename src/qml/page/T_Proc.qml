import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import FluentUI 1.0
import "../component"

FluScrollablePage{
    launchMode: FluPageType.SingleTask
    title: qsTr("Trace")

    function getAllNumbers(str) {
      const regex = /\d+/g;
      return str.match(regex);
    }

    Component{
        id:com_page
        FluFrame{
            property int targetpid: argument
            property int argc
            padding: 10
            ColumnLayout {
                FluText {
                    text: qsTr("syscall number and argc")
                }
                RowLayout {
                    FluTextBox {
                        id: proc_input_nr
                        width: 1000
                        placeholderText: qsTr("nr")
                        cleanEnabled: true
                    }
                    FluComboBox {
                        editable: false
                        model: ListModel {
                            ListElement {name: "0";}
                            ListElement {name: "1";}
                            ListElement {name: "2";}
                            ListElement {name: "3";}
                            ListElement {name: "4";}
                            ListElement {name: "5";}
                            ListElement {name: "6";}
                        }
                        textRole: "name"
                        onActivated: function(index){
                            argc = index
                        }
                    }
                    FluFilledButton {
                        text: qsTr("Execute")
                        onClicked: {
                            controller.startInject(targetpid, Number(proc_input_nr.text), Number(proc_input_arg1.text), Number(proc_input_arg2.text),
                            Number(proc_input_arg3.text), Number(proc_input_arg4.text), Number(proc_input_arg5.text), Number(proc_input_arg6.text), argc)
                        }
                    }
                    FluButton {
                        text: qsTr("Clear")
                        onClicked: {
                            proc_input_arg1.text = proc_input_arg2.text = proc_input_arg3.text = proc_input_arg4.text = proc_input_arg5.text = proc_input_arg6.text = ""
                        }
                    }
                }
                RowLayout {
                    FluText {
                        text: qsTr("arg1:")
                    }
                    FluTextBox{
                        id: proc_input_arg1
                        Layout.preferredWidth: 200
                        placeholderText: qsTr("arg1")
                        cleanEnabled: true
                    }
                    FluText {
                        text: qsTr("arg2:")
                    }
                    FluTextBox{
                        id: proc_input_arg2
                        Layout.preferredWidth: 200
                        placeholderText: qsTr("arg2")
                        cleanEnabled: true
                    }
                    FluText {
                        text: qsTr("arg3:")
                    }
                    FluTextBox{
                        id: proc_input_arg3
                        Layout.preferredWidth: 200
                        placeholderText: qsTr("arg3")
                        cleanEnabled: true
                    }
                }
                RowLayout {
                    FluText {
                        text: qsTr("arg4:")
                    }
                    FluTextBox{
                        id: proc_input_arg4
                        Layout.preferredWidth: 200
                        placeholderText: qsTr("arg4")
                        cleanEnabled: true
                    }
                    FluText {
                        text: qsTr("arg5:")
                    }
                    FluTextBox{
                        id: proc_input_arg5
                        Layout.preferredWidth: 200
                        placeholderText: qsTr("arg5")
                        cleanEnabled: true
                    }
                    FluText {
                        text: qsTr("arg6:")
                    }
                    FluTextBox{
                        id: proc_input_arg6
                        Layout.preferredWidth: 200
                        placeholderText: qsTr("arg6")
                        cleanEnabled: true
                    }
                }
            }
        }
    }

    function newTab(pid){
        tab_view.appendTab("qrc:/example/res/image/favicon.ico",qsTr("Pid: ")+pid,com_page,pid)
    }

    FluFrame{
        Layout.fillWidth: true
        Layout.preferredHeight: 36+multiine_textbox.height
        padding: 10
        Layout.topMargin: 20

        FluMultilineTextBox{
            id: multiine_textbox
            disableColor: FluTheme.dark ?  Qt.rgba(255/255,255/255,255/255,1) : Qt.rgba(27/255,27/255,27/255,1)
            disabled: true
            font.family: 'Noto Sans Mono'
            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.left
                right: parent.right
            }
            onTextChanged: {
                var pids = getAllNumbers(text)
                listmodel_select_pid.clear()
                for(var i = 0; i < pids.length; i++)
                {
                    listmodel_select_pid.append({"name":pids[i],"val":Number(pids[i])})
                }
            }
        }
    }

    FluFrame{
        Layout.fillWidth: true
        Layout.topMargin: 15
        Layout.preferredHeight: 250
        padding: 10
        FluTabView{
            id:tab_view
            tabWidthBehavior: FluTabViewType.SizeToContent
            closeButtonVisibility: FluTabViewType.Always
            onNewPressed:{
                pop_filter.showPopup()
            }
        }
    }

    ListModel {
        id: listmodel_select_pid
    }

    FluMenu{
        id:pop_filter
        width: 200
        height: 89

        contentItem: Item{

            onVisibleChanged: {
                if(visible){
                    sel_pid.currentIndex = 0
                }
            }

            FluComboBox {
                id: sel_pid
                anchors{
                    left: parent.left
                    right: parent.right
                    top: parent.top
                    leftMargin: 10
                    rightMargin: 10
                    topMargin: 10
                }
                editable: false
                model: listmodel_select_pid
                textRole: "name"
                valueRole: "val"
            }

            FluButton{
                text: qsTr("Create")
                anchors{
                    bottom: parent.bottom
                    right: parent.right
                    bottomMargin: 10
                    rightMargin: 10
                }
                onClicked: {
                    newTab(sel_pid.currentValue)
                    pop_filter.close()
                }
            }

        }

        function showPopup(){
            pop_filter.popup()
        }

    }

    Connections {
        target: controller
        function onQmlDrawProcTree(tree) {
            multiine_textbox.text = tree
        }
    }
}
