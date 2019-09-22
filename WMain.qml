import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 1.4 as C1
import QtQuick.Dialogs 1.2

Window
{
    id: root
    visible: true
    width: 640
    height: 480
    title: UICom.AppName

    Material.theme: Material.System
    Material.accent: Material.LightBlue

    Component.onCompleted: {
        x = Screen.width  / 2 - width  / 2
        y = Screen.height / 2 - height / 2
    }


    FileDialog {
        id: dlgOpenFile
        title: "Open .log"
        folder: "file:/var/log" //warning: not native path format!
        selectExisting: true
        sidebarVisible: false
        nameFilters: ["Log files (*.log)"]
        onAccepted: {
            root.title = root.title + " : " + fileUrl;

            if ( !UICom.processLog(fileUrl) ) {
                btnOpen.icon.color = "#ffffff";
                alert(qsTr("UI: cant open file"));
            }

        }
        onRejected: {
            root.title = UICom.AppName;
            btnOpen.icon.color = "#ffffff";
        }
    }

    ToolBar {
        id: toolBar
        opacity: 1

        anchors {
            left: parent.left
            right: parent.right
        }

        leftPadding: 8
        antialiasing: true

        Material.background: Material.Blue
        Material.elevation: 6

        Flow {
            id: toolsFlow
            layoutDirection: Qt.LeftToRight
            flow: Flow.LeftToRight
            spacing: 5
            anchors.fill: parent

            Row {
                id: tool1
                height: parent.height -1
                clip: false

                ToolButton {
                    id: btnOpen
                    text: ".Log"
                    highlighted: false
                    transformOrigin: Item.Center
                    flat: false
                    icon.source: "qrc:/icons/open-folder.svg"
                    icon.color: "#ffffff"

                    onClicked: {
                        icon.color = "#000000";
                        dlgOpenFile.open();
                    }
                }
                ToolSeparator {}
            }
            Row {
                id: tool2
                anchors {
                    leftMargin: tool1.width
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                    top: parent.top
                }

                TextField {
                    id: textField
                    text: qsTr("")
                    rightPadding: 6
                    bottomPadding: 6
                    anchors.fill: parent
                    placeholderText: "type to search.."
                    Material.accent: Material.Grey
                    background: null
                }
            }
        }

        Menu
        {
            title: qsTr("Help")
        }


    }

    C1.TreeView {
        id: tree
        flickableItem.interactive: false
        sortIndicatorVisible: true
        sortIndicatorColumn: 0
        anchors{
            right: parent.right
            left: parent.left
            bottom: parent.bottom
            top: toolBar.bottom
        }

        model: logmodel

        Connections {
            target: UICom
            onChangedData: {

                var names = logmodel.ColumnNames;

                while (tree.columnCount > 0)
                    tree.removeColumn(0);

                for (var j = 0; j < names.length; j++)
                    tree.addColumn(Qt.createQmlObject (
                                       'import QtQuick 2.0; import QtQuick.Controls 1.4;'+
                                       'TableViewColumn {title:"'+names[j]+
                                       '"; role: title}', tree) );

            }
        }
    }
}


/*##^##
Designer {
    D{i:10;anchors_height:200;anchors_width:200;anchors_x:110;anchors_y:153}
}
##^##*/
