import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import FluentUI 1.0

FluLauncher {
    id: app
    Component.onCompleted: {
        FluApp.init(app)
        FluApp.windowIcon = "qrc:/logo.ico"
        FluApp.useSystemAppBar = false
        FluTheme.animationEnabled = true
        FluRouter.routes = {
            "/":"qrc:/main.qml",
            "/syscallDetailWindow":"qrc:/qml/window/sdw.qml"
        }
        FluRouter.navigate("/")
    }
}
