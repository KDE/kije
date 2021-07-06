import QtQuick 2.15
import Qt.labs.folderlistmodel 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.12 as Kirigami
import org.kde.kije 1.0 as Kije

Kije.ApplicationWindow {
    id: appy
    title: "Lukin"

    toolbar {
        defaultActions: ["left", "right", "path", "up"]
        potentialActions: [
            Kije.Action {
                identifier: "left"
                text: "Back"
                displayName: "Go Backwards"
                enabled: appy.backStack.length > 0
                defaultShortcut: "Ctrl+A"

                onTriggered: appy.clickBack()
            },
            Kije.Action {
                identifier: "right"
                text: "Forward"
                displayName: "Go Forwards"
                enabled: appy.forwardStack.length > 0
                defaultShortcut: "Ctrl+D"

                onTriggered: appy.clickForward()
            },
            Kije.Action {
                identifier: "up"
                text: "Up"
                displayName: "Go Up"
                defaultShortcut: "Ctrl+W"

                onTriggered: appy.clickGoTo(folderModel.parentFolder)
            },
            Kije.Action {
                identifier: "path"
                displayName: "Path Bar"
                displayComponent: QQC2.Frame {
                    Layout.fillWidth: true

                    RowLayout {
                        Repeater {
                            model: (folderModel.folder + "").split("//")[1].split("/")
                            QQC2.Button {
                                text: modelData
                                onClicked: {
                                    appy.clickGoTo("file://" + (folderModel.folder + "").split("//")[1].split("/").slice(0, index+1).join("/"))
                                }
                            }
                        }
                    }
                }
            }
        ]
    }

    property var backStack: []
    property var forwardStack: []

    onSaveState: (obj) => {
        obj["backStack"] = this.backStack
        obj["forwardStack"] = this.forwardStack
        obj["location"] = folderModel.folder
    }
    onRestoreState: (obj) => {
        this.backStack = obj["backStack"] || []
        this.forwardStack = obj["forwardStack"] || []
        if (obj["location"]) {
            folderModel.folder = obj["location"]
        }
    }

    function clickGoTo(folder) {
        backStack = backStack.concat([folderModel.folder])
        forwardStack = []
        folderModel.folder = folder
    }
    function clickBack() {
        let item = backStack
        let goTo = item.pop()

        backStack = item
        forwardStack = forwardStack.concat([goTo])
        folderModel.folder = goTo
    }
    function clickForward() {
        let item = forwardStack
        let goTo = item.pop()

        forwardStack = item
        backStack = backStack.concat([goTo])

        folderModel.folder = goTo
    }

    stack.initialItem: Item {
        GridView {
            anchors {
                fill: parent
                margins: Kirigami.Units.largeSpacing
            }
            model: FolderListModel {
                id: folderModel

                showDirsFirst: true
            }

            delegate: Item {
                implicitWidth: Kirigami.Units.gridUnit * 5
                implicitHeight: Kirigami.Units.gridUnit * 5
                ColumnLayout {
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        right: parent.right
                    }
                    Kirigami.Icon {
                        source: fileIsDir ? "system-file-manager" : "text-x-katefilelist"

                        Layout.preferredHeight: Kirigami.Units.iconSizes.large
                        Layout.preferredWidth: Layout.preferredHeight
                        Layout.alignment: Qt.AlignHCenter
                    }
                    QQC2.Label {
                        text: fileBaseName
                        horizontalAlignment: Text.AlignHCenter
                        wrapMode: Text.Wrap
                        elide: Text.ElideRight
                        maximumLineCount: 2

                        Layout.fillWidth: true
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (fileIsDir) {
                            appy.clickGoTo(filePath)
                        } else {
                            Qt.openUrlExternally(filePath)
                        }
                    }
                }
            }
        }
    }

}