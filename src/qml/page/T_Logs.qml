import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import FluentUI 1.0
import ClipBoard 1.0
import "../component"

FluContentPage{
    launchMode: FluPageType.SingleTask
    title: qsTr("Logs")

    Component{
        id:com_option
        Item {
            RowLayout {
                anchors.centerIn: parent
                FluButton{
                    text: qsTr("Delete")
                    onClicked: {
                        table_view.closeEditor()
                        table_view.removeRow(row)
                    }
                }
                FluFilledButton{
                    text: qsTr("Copy")
                    onClicked: {
                        var obj = table_view.getRow(row)
                        clipboard.setClipBoard(obj.logs)
                        showSuccess("Copy to clipboard")
                    }
                }
            }
        }
    }

    FluTableView{
        id:table_view
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
        anchors.topMargin: 5
        columnSource:[
            {
                title: qsTr("Log"),
                dataIndex: 'logs',
                width:parent.width - 180,
                minimumWidth:parent.width - 180,
                maximumWidth:parent.width - 180
            },
            {
                title: qsTr("Optios"),
                dataIndex: 'action',
                width:150,
                minimumWidth:150,
                maximumWidth:150
            }
        ]
    }
    function getObject(log){
        return {
            logs: log,
            action: table_view.customItem(com_option),
            _minimumHeight:50,
            _key:FluTools.uuid()
        }
    }

    ClipBoard {
        id: clipboard
    }

    Connections {
        target: controller
        function onShowLog(log) {
            table_view.appendRow(getObject(log))
        }
    }
}
