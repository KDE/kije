import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15 as QQC2
import org.kde.kirigami 2.12 as Kirigami
import org.kde.kije 1.0 as Kije

Kirigami.ApplicationWindow {
    Kije.Router {
        location: "/users/mu/delete"

        Kije.Route {
            path: "/users/:user_id"

            component: Rectangle {
                color: "green"
            }

            Kije.Route {
                path: "/delete"

                component: Rectangle {
                    color: "cyan"

                    QQC2.Label {
                        anchors.centerIn: parent
                        text: $router.params.user_id
                    }
                }
            }
        }
    }

    Kije.RouterSlot {
        anchors.fill: parent

        Kije.RouterSlot {
            anchors.fill: parent
            anchors.margins: 50
        }
    }

    Component.onCompleted: print($router)
}
