import QtQuick 2.10
import QtQuick.Layouts 1.10
import QtQuick.Controls 2.12 as QQC2
import Qt.labs.folderlistmodel 2.15 as FLM
import org.kde.kirigami 2.15 as Kirigami
import org.kde.kije 1.0

DocApp {
    actions: [
        Action {
            identifier: "foo"
        }
    ]
    menubar: [
        Action {
            text: "Lukin"
        },
        Action {
            text: "File"
        },
        EditAction { }
    ]
    viewDelegate: Page {
        actions: ["foo", "bar"]

        Rectangle {
            color: "black"
            anchors.fill: parent
        }

        id: view

        Window.win.state: []

        property var backStack: []
        property var forwardStack: []

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

        GridView {
            anchors {
                fill: parent
                margins: Kirigami.Units.largeSpacing
            }
            model: FLM.FolderListModel {
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
                            view.clickGoTo(filePath)
                        } else {
                            Qt.openUrlExternally(filePath)
                        }
                    }
                }
            }
        }
    }
}
