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

    viewDelegate: Page {
        Rectangle {
            color: "black"
            anchors.fill: parent
        }

        onWriteState: (state) => state.text = foo.text
        onRestoreState: (state) => {
            if (state.text) foo.text = state.text
        }

        QQC2.TextField {
            id: foo
        }
    }
}
