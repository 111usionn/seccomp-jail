import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs
import FluentUI 1.0
import "../component"

FluContentPage{
    id: rules_root
    launchMode: FluPageType.SingleTask
    title: qsTr("Rules")
    property var json
    property string rule_path: ""
    property var dataSource : []
    property string nameKeyword: ""
    function jsonLength(obj) {
        var size = 0, key
        var array = []
        for(key in obj) {
            if(obj.hasOwnProperty(key)) {
                size++;
            }
        }
        return size;
    }
    function getRuleName(num) {
        switch(num) {
            case 0:
                return "Allow"
            case 1:
                return "Abort"
            case 2:
                return "Notify"
            case 3:
                return "Allow forever"
            case 4:
                return "Abort forever"
        }
    }
    onNameKeywordChanged: {
        table_view.filter(function(item){
            if(item.name.includes(nameKeyword)){
                return true
            }
            return false
        })
    }
    FluContentDialog{
        id: rules_dialog_create_rule
        property int default_rule_type: 0
        title: qsTr("Create New Rules")
        message: qsTr("Please select a default rule")
        negativeText: qsTr("Cancel")
        contentDelegate: Component{
            Item{
                implicitWidth: parent.width
                implicitHeight: 30
                x: 20
                FluComboBox{
                    editable: false
                    model: ListModel {
                        ListElement {name: "all allow"; val: 0}
                        ListElement {name: "all abort"; val: 1}
                        ListElement {name: "all notify"; val: 2}
                        ListElement {name: "all allow forever"; val: 3}
                        ListElement {name: "all abort forever"; val: 4}
                    }
                    textRole: "name"
                    valueRole: "val"
                    onActivated: function(index){
                        rules_dialog_create_rule.default_rule_type = valueAt(index)
                    }
                }
            }
        }
        onNegativeClicked: {
            showError(qsTr("Canceled"))
        }
        positiveText: qsTr("Create")
        onPositiveClicked: {
            controller.createDefaultRule(default_rule_type)
            showSuccess(qsTr("Created"))
        }
    }

    FluFrame{
        id: rules_frame_control
        padding: 10
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: 50
        Row {
            anchors{
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            spacing: (parent.width - 10 - rules_btn_select_rule.width - rules_btn_create_default_rule.width - rules_btn_load_rule.width - rules_btn_save.width - rules_btn_saveAs.width) / 4
            FluButton {
                id: rules_btn_select_rule
                text: qsTr("Select rule")
                onClicked: {
                    var dialog = Qt.createQmlObject("import QtQuick.Dialogs; FileDialog {nameFilters: [ \"JSON (*.json)\"] }", parent);
                    dialog.title = qsTr("Save");
                    dialog.fileMode = FileDialog.OpenFile
                    dialog.accepted.connect(function() {
                        rule_path = dialog.selectedFile;
                    });
                    dialog.open();
                }
            }

            FluButton {
                id: rules_btn_load_rule
                text: qsTr("Load rule")
                onClicked: {
                    var ruleExist = controller.setRule(rule_path)
                    /*if(!ruleExist)//empty path
                    {

                    }
                    else
                    {
                        current_rule_path_text.text = rule_path.text
                    }*/
                }
            }

            FluButton {
                id: rules_btn_create_default_rule
                text: qsTr("Create rule")
                onClicked: {
                    rules_dialog_create_rule.open()
                }
            }

            FluButton {
                id: rules_btn_save
                text: qsTr("Save")
                onClicked: {
                    if(controller.haveCurrentRule()) {
                        controller.saveCurrentRule();
                    }
                }
            }

            FluButton {
                id: rules_btn_saveAs
                text: qsTr("Save As")
                onClicked: {
                    var dialog = Qt.createQmlObject("import QtQuick.Dialogs; FileDialog {nameFilters: [ \"JSON (*.json)\"] }", parent);
                    dialog.title = qsTr("Save As");
                    dialog.fileMode = FileDialog.SaveFile
                    dialog.accepted.connect(function() {
                        if(controller.haveCurrentRule()) {
                            controller.saveCurrentRule(dialog.fileUrl);
                        }
                    });
                    dialog.open();
                }
            }
        }
    }

    FluPagination{
        id:gagination
        anchors{
            bottom: parent.bottom
            left: parent.left
        }
        pageCurrent: 1
        itemCount: 10000
        pageButtonCount: 7
        __itemPerPage: 50
        previousText: qsTr("<Previous")
        nextText: qsTr("Next>")
        onRequestPage:
            (page,count)=> {
                table_view.closeEditor()
                loadData(page,count)
                table_view.resetPosition()
            }
    }

    ListModel {
        id: list_changeto
        ListElement {name: "allow"; val: 0}
        ListElement {name: "abort"; val: 1}
        ListElement {name: "notify"; val: 2}
        ListElement {name: "allow forever"; val: 3}
        ListElement {name: "abort forever"; val: 4}
    }
    Component{
        id:com_changeto
        Item{
            RowLayout{
                anchors.centerIn: parent
                FluComboBox{
                    id: rule_selecter
                    editable: false
                    model: list_changeto
                    textRole: "name"
                    valueRole: "val"
                }
                FluFilledButton{
                    text: qsTr("Update")
                    onClicked: {
                        var obj = table_view.getRow(row)
                        var reval = controller.updateRule(obj.nr, rule_selecter.currentValue)
                        if(reval == 1) {
                            showSuccess(qsTr("Updated"))
                        }
                        else {
                            showError(qsTr("Failed, this is a force enabled syscall"))
                        }
                    }
                }
            }
        }
    }

    FluMenu{
        id:pop_filter
        width: 200
        height: 89

        contentItem: Item{

            onVisibleChanged: {
                if(visible){
                    name_filter_text.text = rules_root.nameKeyword
                    name_filter_text.cursorPosition = name_filter_text.text.length
                    name_filter_text.forceActiveFocus()
                }
            }

            FluTextBox{
                id:name_filter_text
                anchors{
                    left: parent.left
                    right: parent.right
                    top: parent.top
                    leftMargin: 10
                    rightMargin: 10
                    topMargin: 10
                }
                iconSource: FluentIcons.Search
            }

            FluButton{
                text: qsTr("Search")
                anchors{
                    bottom: parent.bottom
                    right: parent.right
                    bottomMargin: 10
                    rightMargin: 10
                }
                onClicked: {
                    rules_root.nameKeyword = name_filter_text.text
                    pop_filter.close()
                }
            }

        }

        function showPopup(){
            table_view.closeEditor()
            pop_filter.popup()
        }

    }

    Component{
        id:com_column_filter_name
        Item{
            FluText{
                text: qsTr("Name")
                anchors.centerIn: parent
            }
            FluIconButton{
                width: 20
                height: 20
                iconSize: 12
                verticalPadding:0
                horizontalPadding:0
                iconSource: FluentIcons.Filter
                iconColor: {
                    if("" !== rules_root.nameKeyword){
                        return FluTheme.primaryColor
                    }
                    return FluTheme.dark ?  Qt.rgba(1,1,1,1) : Qt.rgba(0,0,0,1)
                }
                anchors{
                    right: parent.right
                    rightMargin: 3
                    verticalCenter: parent.verticalCenter
                }
                onClicked: {
                    pop_filter.showPopup()
                }
            }
        }
    }

    FluTableView{
        id:table_view
        anchors{
            left: parent.left
            right: parent.right
            top: rules_frame_control.bottom
            bottom: gagination.top
        }
        anchors.topMargin: 5
        columnSource:[
            {
                title: qsTr("nr"),
                dataIndex: 'nr',
                width:150,
                minimumWidth:100,
                maximumWidth:200
            },
            {
                title: table_view.customItem(com_column_filter_name,{title:qsTr("Name")}),
                dataIndex: 'name',
                readOnly: true,
                width:200,
                minimumWidth:100,
                maximumWidth:300
            },
            {
                title: qsTr("status"),
                dataIndex: 'status',
                width:200,
                minimumWidth:150,
                maximumWidth:300,
            },
            {
                title: qsTr("Change to"),
                dataIndex: 'combobox',
                width:300,
                minimumWidth:300,
                maximumWidth:300,
            }
        ]
    }

    function getObject(num){
        return {
            nr: num,
            name: controller.qmlFSN(num),
            status: getRuleName(json[num]),
            combobox: table_view.customItem(com_changeto),
            _minimumHeight:50,
            _key:FluTools.uuid()
        }
    }

    function loadData(page){
        const dataSource = []
        for(var i= 50 * (page - 1);i<Math.min(50 * (page - 1) + 50, jsonLength(json));i++){
            dataSource.push(getObject(i))
        }
        rules_root.dataSource = dataSource
        table_view.dataSource = rules_root.dataSource
    }

    Connections {
        target: controller
        function onCurrentRuleChanged() {
            json = JSON.parse(controller.getCurrentJson())
            gagination.itemCount = jsonLength(json)
            loadData(gagination.pageCurrent)
        }
        function onIsTracingchanged(isTracing) {
            if(isTracing)
            {
                list_changeto.remove(3, 2)
            }
            else
            {
                list_changeto.append({"name": "allow forever", "val": 3})
                list_changeto.append({"name": "abort forever", "val": 4})
            }
        }
    }
}
