import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQml 2.15
import Qt.labs.platform 1.1
import QtQuick.Dialogs
import FluentUI 1.0
import seccompjail 1.0
import Controller 1.0
import "qml/page"
import "qml/global"
import "qml/component"
FluWindow {
    id: window
    width: 1150
    height: 480
    minimumWidth: 600
    minimumHeight: 240
    title: "seccomp-jail"
    launchMode: FluWindowType.SingleTask
    fitsAppBarWindows: true
    appBar: FluAppBar {
        id: appbar
        width: window.width
        height: 30
        showDark: true
        darkClickListener:(button)=>handleDarkChanged(button)
        closeClickListener: ()=>{dialog_close.open()}
        darkText: qsTr("Dark Mode")
    }
    Component.onDestruction: {
        FluRouter.exit()
    }
    Component{
        id: com_reveal
        CircularReveal{
            id: reveal
            target: window.contentItem
            anchors.fill: parent
            onAnimationFinished:{
                //动画结束后释放资源
                loader_reveal.sourceComponent = undefined
            }
            onImageChanged: {
                changeDark()
            }
        }
    }
    FluLoader{
        id:loader_reveal
        anchors.fill: parent
    }
    function distance(x1,y1,x2,y2){
        return Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
    }
    function handleDarkChanged(button){
        if(!FluTheme.animationEnabled || window.fitsAppBarWindows === false){
            changeDark()
        }else{
            if(loader_reveal.sourceComponent){
                return
            }
            loader_reveal.sourceComponent = com_reveal
            var target = window.contentItem
            var pos = button.mapToItem(target,0,0)
            var mouseX = pos.x
            var mouseY = pos.y
            var radius = Math.max(distance(mouseX,mouseY,0,0),distance(mouseX,mouseY,target.width,0),distance(mouseX,mouseY,0,target.height),distance(mouseX,mouseY,target.width,target.height))
            var reveal = loader_reveal.item
            reveal.start(reveal.width*Screen.devicePixelRatio,reveal.height*Screen.devicePixelRatio,Qt.point(mouseX,mouseY),radius)
        }
    }
    function changeDark(){
        if(FluTheme.dark){
            FluTheme.darkMode = FluThemeType.Light
        }else{
            FluTheme.darkMode = FluThemeType.Dark
        }
    }
    /*Column{
        anchors.centerIn: parent
        spacing: 15
        Image{
            width: 60
            height: 60
            source: "qrc:/logo.ico"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        FluText{
            text: qsTr("Welcome to FluentUI")
            anchors.horizontalCenter: parent.horizontalCenter
            font: FluTextStyle.Title
        }
        FluFilledButton{
            text: qsTr("Learn FluentUI")
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                Qt.openUrlExternally("https://space.bilibili.com/275661059")
            }
        }
    }

    Row{
        anchors{
            bottom: parent.bottom
            bottomMargin: 14
            horizontalCenter: parent.horizontalCenter
        }
        FluText{
            text: qsTr("Author's WeChat ID: ")
        }
        FluText{
            text: "FluentUI"
            color: FluTheme.fontSecondaryColor
        }
    }*/
    Component{
        id: nav_item_right_menu
        FluMenu{
            width: 186
            FluMenuItem{
                text: qsTr("Open in Separate Window")
                font: FluTextStyle.Caption
                onClicked: {
                    FluRouter.navigate("/pageWindow",{title:modelData.title,url:modelData.url})
                }
            }
        }
    }
    Flipable{
        id:flipable
        anchors.fill: parent
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
        back: Item{
            anchors.fill: flipable
            visible: flipable.flipAngle !== 0
            Row{
                id:layout_back_buttons
                z:8
                anchors{
                    top: parent.top
                    left: parent.left
                    topMargin: FluTools.isMacos() ? 20 : 5
                    leftMargin: 5
                }
                FluIconButton{
                    iconSource: FluentIcons.ChromeBack
                    width: 30
                    height: 30
                    iconSize: 13
                    onClicked: {
                        flipable.flipped = false
                    }
                }
                FluIconButton{
                    iconSource: FluentIcons.Sync
                    width: 30
                    height: 30
                    iconSize: 13
                    onClicked: {
                        loader.reload()
                    }
                }
                Component.onCompleted: {
                    window.setHitTestVisible(layout_back_buttons)
                }
            }
            FluRemoteLoader{
                id:loader
                lazy: true
                anchors.fill: parent
                source: "https://zhu-zichu.gitee.io/Qt_174_LieflatPage.qml"
            }
        }
        front: Item{
            id:page_front
            visible: flipable.flipAngle !== 180
            anchors.fill: flipable
            FluNavigationView{
                property int clickCount: 0
                id:nav_view
                width: parent.width
                height: parent.height
                z:999
                //Stack模式，每次切换都会将页面压入栈中，随着栈的页面增多，消耗的内存也越多，内存消耗多就会卡顿，这时候就需要按返回将页面pop掉，释放内存。该模式可以配合FluPage中的launchMode属性，设置页面的启动模式
                //                pageMode: FluNavigationViewType.Stack
                //NoStack模式，每次切换都会销毁之前的页面然后创建一个新的页面，只需消耗少量内存
                pageMode: FluNavigationViewType.Stack
                items: ItemsOriginal
                footerItems:ItemsFooter
                topPadding:{
                    if(window.useSystemAppBar){
                        return 0
                    }
                    return FluTools.isMacos() ? 20 : 0
                }
                displayMode: GlobalModel.displayMode
                logo: "qrc:/example/res/image/favicon.ico"
                title:"seccomp-jail"
                onLogoClicked:{
                    clickCount += 1
                    showSuccess("%1:%2".arg(qsTr("Click Time")).arg(clickCount))
                    if(clickCount === 5){
                        loader.reload()
                        flipable.flipped = true
                        clickCount = 0
                    }
                }
                autoSuggestBox:FluAutoSuggestBox{
                    iconSource: FluentIcons.Search
                    items: ItemsOriginal.getSearchData()
                    placeholderText: qsTr("Search")
                    onItemClicked:
                        (data)=>{
                            ItemsOriginal.startPageByItem(data)
                        }
                }
                Component.onCompleted: {
                    ItemsOriginal.navigationView = nav_view
                    ItemsOriginal.paneItemMenu = nav_item_right_menu
                    ItemsFooter.navigationView = nav_view
                    ItemsFooter.paneItemMenu = nav_item_right_menu
                    window.setHitTestVisible(nav_view.buttonMenu)
                    window.setHitTestVisible(nav_view.buttonBack)
                    window.setHitTestVisible(nav_view.imageLogo)
                    setCurrentIndex(3)
                    setCurrentIndex(2)
                    setCurrentIndex(0)
                }
            }
        }
    }
    FluContentDialog{
        id: dialog_close
        title: qsTr("Quit")
        message: qsTr("Are you sure you want to exit the program?")
        negativeText: qsTr("Minimize")
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.NeutralButton | FluContentDialogType.PositiveButton
        onNegativeClicked: {
            system_tray.showMessage(qsTr("Friendly Reminder"),qsTr("FluentUI is hidden from the tray, click on the tray to activate the window again"));
            timer_window_hide_delay.restart()
        }
        positiveText: qsTr("Quit")
        neutralText: qsTr("Cancel")
        onPositiveClicked:{
            FluRouter.exit(0)
        }
    }
    Controller{
        id: controller
    }
}
