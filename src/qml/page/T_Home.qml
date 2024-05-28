import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import FluentUI 1.0
import "../component"

FluContentPage{
    id: hp
    launchMode: FluPageType.SingleTask
    title: qsTr("Trace")

    Flipable {
        id:flipable
        property bool flipped: false
        property real flipAngle: 0
        transform: Rotation {
            id: rotation
            origin.x: flipable.width/2
            origin.y: flipable.height/2
            axis { x: 0; y: 1; z: 0 }
            angle: flipable.flipAngle

        }
        states: State {
            PropertyChanges { target: flipable; flipAngle: 180 }
            when: flipable.flipped
        }
        transitions: Transition {
            NumberAnimation { target: flipable; property: "flipAngle"; duration: 1000 ; easing.type: Easing.OutCubic}
        }
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: 60

        front: FluFrame{
            id: home_frame_input
            visible: flipable.flipAngle !== 180
            anchors.fill: flipable
            padding: 10
            FluTextBox{
                id: home_textbox_program
                width: 400
                placeholderText: qsTr("Path of program")
                cleanEnabled: true
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                }
                text: "mkdir"
            }

            FluTextBox{
                id: home_textbox_args
                placeholderText: qsTr("Args")
                cleanEnabled: true
                width: home_textbox_program.width * 0.5
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: home_textbox_program.right
                    leftMargin: 10
                }
                text: "mkdir test"
            }

            FluFilledButton{
                id: home_btn_start
                text: qsTr("Trace")
                enabled: true
                anchors{
                    verticalCenter: parent.verticalCenter
                    right: home_btn_stop.left
                    rightMargin: 10
                }
                onClicked: {
                    controller.startTrace(home_textbox_program.text, home_textbox_args.text)
                    enabled = false
                    home_btn_stop.enabled = true
                    home_btn_to_remote.enabled = false
                }
            }

            FluButton{
                id: home_btn_stop
                enabled: false
                text: qsTr("Stop")
                anchors{
                    verticalCenter: parent.verticalCenter
                    right: home_btn_to_remote.left
                    rightMargin: 10
                }
                onClicked: {
                    controller.stopTrace()
                    enabled = false
                    home_btn_start.enabled = true
                    home_btn_to_remote.enabled = true
                }
            }

            FluButton{
                id: home_btn_to_remote
                text: qsTr("Remote")
                anchors{
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                }
                onClicked: {
                    flipable.flipped = !flipable.flipped
                }
            }
        }
        back: FluFrame{
            id: home_frame_input_remote
            padding: 10
            anchors.fill: flipable
            FluTextBox{
                id: home_textbox_program_remote
                width: 400
                placeholderText: qsTr("Path of program")
                cleanEnabled: true
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                }
                text: "mkdir"
            }

            FluTextBox{
                id: home_textbox_args_remote
                placeholderText: qsTr("Args")
                cleanEnabled: true
                width: home_textbox_program.width * 0.7
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: home_textbox_program_remote.right
                    leftMargin: 10
                }
                text: "mkdir test"
            }

            FluFilledButton{
                id: home_btn_start_remote
                text: qsTr("Trace")
                enabled: true
                anchors{
                    verticalCenter: parent.verticalCenter
                    right: home_btn_stop_remote.left
                    rightMargin: 10
                }
                onClicked: {
                    controller.startTrace(home_textbox_program_remote.text, home_textbox_args_remote.text)
                    enabled = false
                    home_btn_stop.enabled = true
                    home_btn_to_local.enabled = false
                }
            }

            FluButton{
                id: home_btn_stop_remote
                enabled: false
                text: qsTr("Stop")
                anchors{
                    verticalCenter: parent.verticalCenter
                    right: home_btn_to_local.left
                    rightMargin: 10
                }
                onClicked: {
                    controller.stopTrace()
                    enabled = false
                    home_btn_start_local.enabled = true
                }
            }

            FluButton{
                id: home_btn_to_local
                text: qsTr("Local")
                anchors{
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                }
                onClicked: {
                    flipable.flipped = !flipable.flipped
                }
            }
        }
    }

    Component{
        id:com_column_filter_name
        Item{
            FluText{
                text: qsTr("Name")
                anchors.centerIn: parent
            }
        }
    }

    function getmask(origdata, data) {
        if(Number(origdata) != Number(data)) {
            return 1
        }
        return 0
    }
    Timer {
        id: removelater
        property int targetrow
        interval: 150
        running: false
        onTriggered: {
            table_view.closeEditor()
            table_view.removeRow(targetrow)
            console.log("del row")
        }
    }
    Component{
        id:com_option
        Item {
            FluDropDownButton{
                anchors.centerIn: parent
                width: parent.width * 0.8
                height: parent.height * 0.8
                text: qsTr("Select an action")
                FluMenuItem{
                    text: qsTr("Pass")
                    onClicked: {
                        var obj = table_view.getRow(row)
                        var orig_data = [obj.orig_nr, obj.orig_arg1, obj.orig_arg2, obj.orig_arg3, obj.orig_arg4, obj.orig_arg5, obj.orig_arg6]
                        var new_data = [obj.nr, obj.arg1, obj.arg2, obj.arg3, obj.arg4, obj.arg5, obj.arg6]
                        var mask = 0
                        for(let i=0; i<7; i++) {
                            mask += (getmask(orig_data[i], new_data[i]) << i)
                        }
                        controller.getCommand(Number(obj.pid), Number(obj.status), Number(obj.nr), obj.arg1, obj.arg2, obj.arg3, obj.arg4, obj.arg5, obj.arg6, mask, 1, 0, 0)
                        removelater.targetrow = row
                        removelater.restart()
                    }
                }
                FluMenuItem{
                    text: qsTr("Abort")
                    onClicked: {
                        var obj = table_view.getRow(row)
                        controller.getCommand(Number(obj.pid), Number(obj.status), Number(obj.nr), obj.arg1, obj.arg2, obj.arg3, obj.arg4, obj.arg5, obj.arg6, 0, 0, 0, 0)
                        removelater.targetrow = row
                        removelater.restart()
                    }
                }
                FluMenuItem{
                    text: qsTr("Pass and add to rules")
                    onClicked: {
                        var obj = table_view.getRow(row)
                        controller.updateRule(Number(obj.orig_nr), 0)
                        var orig_data = [obj.orig_nr, obj.orig_arg1, obj.orig_arg2, obj.orig_arg3, obj.orig_arg4, obj.orig_arg5, obj.orig_arg6]
                        var new_data = [obj.nr, obj.arg1, obj.arg2, obj.arg3, obj.arg4, obj.arg5, obj.arg6]
                        var mask = 0
                        for(let i=0; i<7; i++) {
                            mask += (getmask(orig_data[i], new_data[i]) << i)
                        }
                        controller.getCommand(Number(obj.pid), Number(obj.status), Number(obj.nr), obj.arg1, obj.arg2, obj.arg3, obj.arg4, obj.arg5, obj.arg6, mask, 1, 0, 2)
                        removelater.targetrow = row
                        removelater.restart()
                    }
                }
                FluMenuItem{
                    text: qsTr("Abort and add to rules")
                    onClicked: {
                        var obj = table_view.getRow(row)
                        controller.updateRule(Number(obj.orig_nr), 1)
                        controller.getCommand(Number(obj.pid), Number(obj.status),  Number(obj.nr), obj.arg1, obj.arg2, obj.arg3, obj.arg4, obj.arg5, obj.arg6, 0, 0, 0, 0)
                        removelater.targetrow = row
                        removelater.restart()
                    }
                }
                FluMenuItem{
                    text: qsTr("More...")
                    onClicked: {
                        var obj = table_view.getRow(row)
                        FluRouter.navigate("/syscallDetailWindow", {"pid": Number(obj.pid), "addrs": [obj.arg1, obj.arg2, obj.arg3, obj.arg4, obj.arg5, obj.arg6], "ctrl": controller})
                    }
                }
            }
        }
    }

    Component{
        id:com_textbox
        FluTextBox {
            id: textbox
            anchors.fill: parent
            focus: true
            onCommit: {
                editTextChaged(textbox.text)
                table_view.closeEditor()
            }
        }
    }

    FluTableView{
        id:table_view
        anchors{
            left: parent.left
            right: parent.right
            top: flipable.bottom
            bottom: parent.bottom
        }
        anchors.topMargin: 5
        columnSource:[
            {
                title: qsTr("pid"),
                dataIndex: 'pid',
                width:70,
                minimumWidth:70,
                maximumWidth:70
            },
            {
                title: qsTr("nr"),
                dataIndex: 'nr',
                width:70,
                minimumWidth:70,
                maximumWidth:70
            },
            {
                title: qsTr("syscall"),
                dataIndex: 'syscall',
                width:80,
                minimumWidth:80,
                maximumWidth:200
            },
            {
                title: qsTr("arg1"),
                dataIndex: 'arg1',
                width:80,
                editDelegate: com_textbox,
                minimumWidth:80,
                maximumWidth:150,
                editMultiline: true
            },
            {
                title: qsTr("arg2"),
                dataIndex: 'arg2',
                width:80,
                minimumWidth:80,
                maximumWidth:150,
                editMultiline: true
            },
            {
                title: qsTr("arg3"),
                dataIndex: 'arg3',
                width:80,
                minimumWidth:80,
                maximumWidth:150,
                editMultiline: true
            },
            {
                title: qsTr("arg4"),
                dataIndex: 'arg4',
                width:80,
                minimumWidth:80,
                maximumWidth:150,
                editMultiline: true
            },
            {
                title: qsTr("arg5"),
                dataIndex: 'arg5',
                width:80,
                minimumWidth:80,
                maximumWidth:150,
                editMultiline: true
            },
            {
                title: qsTr("arg6"),
                dataIndex: 'arg6',
                width:80,
                minimumWidth:80,
                maximumWidth:150,
                editMultiline: true
            },
            {
                title: qsTr("Options"),
                dataIndex: 'action',
                width:200,
                minimumWidth:200,
                maximumWidth:200
            }
        ]
    }
    function getObject(pid, status, name, nr, arg1, arg2, arg3, arg4, arg5, arg6){
        return {
            pid: pid,
            nr: nr,
            syscall: name,
            arg1: arg1,
            arg2: arg2,
            arg3: arg3,
            arg4: arg4,
            arg5: arg5,
            arg6: arg6,
            status: status,
            action: table_view.customItem(com_option),
            orig_nr: nr,
            orig_arg1: arg1,
            orig_arg2: arg2,
            orig_arg3: arg3,
            orig_arg4: arg4,
            orig_arg5: arg5,
            orig_arg6: arg6,
            _minimumHeight:50,
            _key:FluTools.uuid()
        }
    }

    Connections {
        target: controller
        function onShowSyscall(pid, status, name, nr, arg1, arg2, arg3, arg4, arg5, arg6) {
            table_view.appendRow(getObject(pid, status, name, nr, arg1, arg2, arg3, arg4, arg5, arg6))
        }
        function onIsTracingchanged(val) {
            if(val == 0) {
                home_btn_start.enabled = true
                home_btn_start_remote.enabled = true
                home_btn_stop.enabled = false
                home_btn_stop_remote.enabled = false
                home_btn_to_local.enabled = true
                home_btn_to_remote.enabled = true
            }
        }
    }
}
