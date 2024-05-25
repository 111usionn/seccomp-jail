pragma Singleton

import QtQuick 2.15
import FluentUI 1.0

FluObject{

    property var navigationView
    property var paneItemMenu

    function rename(item, newName){
        if(newName && newName.trim().length>0){
            item.title = newName;
        }
    }

    FluPaneItem{
        id:item_home
        count: 0
        title: qsTr("Trace")
        menuDelegate: paneItemMenu
        infoBadge: FluBadge{
            count: item_home.count
        }
        icon: FluentIcons.Home
        url: "qrc:/qml/page/T_Home.qml"
        onTap: {
            if(navigationView.getCurrentUrl()){
                item_home.count = 0
            }
            navigationView.push(url)
        }
    }

    FluPaneItem{
        id:item_rules
        count: 0
        title: qsTr("Rules")
        menuDelegate: paneItemMenu
        infoBadge: FluBadge{
            count: item_rules.count
        }
        icon: FluentIcons.CheckboxComposite
        url: "qrc:/qml/page/T_Rules.qml"
        onTap: {
            if(navigationView.getCurrentUrl()){
                item_rules.count = 0
            }
            navigationView.push(url)
        }
    }

    FluPaneItem{
        id:item_proc
        count: 0
        title: qsTr("Process Tree & Inject")
        menuDelegate: paneItemMenu
        infoBadge: FluBadge{
            count: item_proc.count
        }
        icon: FluentIcons.AllApps
        url: "qrc:/qml/page/T_Proc.qml"
        onTap: {
            if(navigationView.getCurrentUrl()){
                item_proc.count = 0
            }
            navigationView.push(url)
        }
    }

    FluPaneItem{
        id:item_logs
        count: 0
        title: qsTr("Logs")
        menuDelegate: paneItemMenu
        infoBadge: FluBadge{
            count: item_logs.count
        }
        icon: FluentIcons.ButtonMenu
        url: "qrc:/qml/page/T_Logs.qml"
        onTap: {
            if(navigationView.getCurrentUrl()){
                item_logs.count = 0
            }
            navigationView.push(url)
        }
    }

    function getRecentlyAddedData(){
        var arr = []
        var items = navigationView.getItems();
        for(var i=0;i<items.length;i++){
            var item = items[i]
            if(item instanceof FluPaneItem && item.extra && item.extra.recentlyAdded){
                arr.push(item)
            }
        }
        arr.sort(function(o1,o2){ return o2.extra.order-o1.extra.order })
        return arr
    }

    function getRecentlyUpdatedData(){
        var arr = []
        var items = navigationView.getItems();
        for(var i=0;i<items.length;i++){
            var item = items[i]
            if(item instanceof FluPaneItem && item.extra && item.extra.recentlyUpdated){
                arr.push(item)
            }
        }
        return arr
    }

    function getSearchData(){
        if(!navigationView){
            return
        }
        var arr = []
        var items = navigationView.getItems();
        for(var i=0;i<items.length;i++){
            var item = items[i]
            if(item instanceof FluPaneItem){
                if (item.parent instanceof FluPaneItemExpander)
                {
                    arr.push({title:`${item.parent.title} -> ${item.title}`,key:item.key})
                }
                else
                    arr.push({title:item.title,key:item.key})
            }
        }
        return arr
    }

    function startPageByItem(data){
        navigationView.startPageByItem(data)
    }

}
