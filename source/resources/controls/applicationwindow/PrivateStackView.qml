import QtQuick 2.12
import org.kde.kirigami 2.12
import QtQuick.Controls 2.13 as QQC2

QQC2.StackView {
    popEnter: Transition {
        OpacityAnimator {
            from: 0
            to: 1
            duration: Units.longDuration
            easing.type: Easing.InOutCubic
        }
    }
    popExit: Transition {
        ParallelAnimation {
            OpacityAnimator {
                from: 1
                to: 0
                duration: Units.longDuration
                easing.type: Easing.InOutCubic
            }
            YAnimator {
                from: 0
                to: height/2
                duration: Units.longDuration
                easing.type: Easing.InCubic
            }
        }
    }

    pushEnter: Transition {
        ParallelAnimation {
            PropertyAnimation {
                property: "opacity"
                from: 0
                to: 1
                duration: Units.longDuration
                easing.type: Easing.InOutCubic
            }
            YAnimator {
                from: height/2
                to: 0
                duration: Units.longDuration
                easing.type: Easing.OutCubic
            }
        }
    }

    pushExit: Transition {
        OpacityAnimator {
            from: 1
            to: 0
            duration: Units.longDuration
            easing.type: Easing.InOutCubic
        }
    }

    replaceEnter: Transition {
        ParallelAnimation {
            OpacityAnimator {
                from: 0
                to: 1
                duration: Units.longDuration
                easing.type: Easing.InOutCubic
            }
            YAnimator {
                from: height/2
                to: 0
                duration: Units.longDuration
                easing.type: Easing.OutCubic
            }
        }
    }

    replaceExit: Transition {
        ParallelAnimation {
            OpacityAnimator {
                from: 1
                to: 0
                duration: Units.longDuration
                easing.type: Easing.InCubic
            }
            YAnimator {
                from: 0
                to: -height/2
                duration: Units.longDuration
                easing.type: Easing.InOutCubic
            }
        }
    }
}