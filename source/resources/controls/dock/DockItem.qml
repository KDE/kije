import QtQuick 2.12
import QtQuick.Window 2.12
import org.kde.kirigami 2.12 as Kirigami
import org.kde.kijetesantakalu.private 1.0

Item {
    id: __dockRoot

    property int dockingStyle: DockItem.DockingStyle.DockedInWindow
    default property alias children: __contentItem.children

    enum DockingStyle {
        FloatingOwnWindow,
        FloatingInnerWindow,
        DockedInWindow
    }

    property Item item: Item {
        id: __contentItem
        implicitWidth: childrenRect.width
        implicitHeight: childrenRect.height
        parent: {
            switch (__dockRoot.dockingStyle) {
                case DockItem.DockingStyle.DockedInWindow:
                    return __dockRoot.parent
                case DockItem.DockingStyle.FloatingOwnWindow:
                    return __ownWindowContentItem
                case DockItem.DockingStyle.FloatingInnerWindow:
                    return __innerWindow
            }
        }
    }
    property Item innerWindow: Kirigami.ShadowedRectangle {
        id: __innerWindow
        parent: {
            if (__dockRoot.dockingStyle == DockItem.DockingStyle.FloatingInnerWindow)
                return DockPrivate.rootItem(__dockRoot.parent)
            else
                return null
        }
        shadow {
            color: Qt.rgba(0,0,0,0.3)
            size: 32
        }
        height: childrenRect.height
        width: childrenRect.width
        DragHandler {}
    }
    property Window ownWindow: Window {
        id: __ownWindow
        visible: __dockRoot.dockingStyle == DockItem.DockingStyle.FloatingOwnWindow
        flags: Qt.Window | Qt.CustomizeWindowHint | Qt.WindowTitleHint | Qt.Tool | Qt.WindowCloseButtonHint | Qt.WindowStaysOnTopHint
        height: __ownWindowContentItem.height
        width: __ownWindowContentItem.width
        minimumHeight: height
        minimumWidth: width
        maximumHeight: height
        maximumWidth: width
        Item {
            id: __ownWindowContentItem
            implicitWidth: childrenRect.width
            implicitHeight: childrenRect.height
        }
    }
}