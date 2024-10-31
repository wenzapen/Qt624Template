import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 400
    height: 400
    title: "Using SVG Path Data in QML"

    PathView {
        anchors.centerIn: parent
        width: 200
        height: 200
        model: 1  // Just one item for demonstration
        delegate: Rectangle {
            width: 20
            height: 20
            color: "blue"
        }

        path: Path {
            PathSvg {
                path: "M10 10 L90 10 L90 90 L10 90 Z" // Example SVG path data (square)
            }
        }
    }
}
