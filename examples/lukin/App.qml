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
        actions: ["foo", "bar"]
    }
}
