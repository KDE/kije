import QtQuick 2.10
import QtQuick.Controls 2.12 as QQC2
import org.kde.kije 1.0

DocApp {
    actions: [
        Action {
            identifier: "foo"
        }
    ]
    menubar: [
        Action {
            text: "SimpleEdit"
        },
        Action {
            text: "File"
        },
        EditAction { }
    ]

    property Window win: Window {
        id: win

        identifier: "foo"

        color: "green"
        width: 200
        height: 200
        visible: true

        state: [foo.text]

        QQC2.TextField {
            id: foo
            text: win.state[0]
        }
    }
}
