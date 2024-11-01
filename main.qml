import QtQuick
import QtQuick.Controls
import QtMultimedia
import HurricanePlayer 1.0
import yt20player.ns 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 600

    // 打开文件

    // 音视频是否在播放
    property bool isPlay: false
    property bool isFullScreen: false  // 新增属性，用于跟踪是否全屏

    signal openFile(string path)
    signal start()
    signal stop()

    Rectangle {
        color: "black"
        anchors.fill: parent
        HurricanePlayer {
            id: videoArea
            clip: true
            anchors.fill: parent

            MouseArea {
                anchors.fill: parent
                propagateComposedEvents: true
                cursorShape: "PointingHandCursor"

                // 单击事件切换播放和暂停
                // onClicked: {
                //     if (mainWindow.isPlay) {
                //         mainWindow.isPlay = false
                //         mainWindow.stop()
                //     } else {
                //         mainWindow.isPlay = true
                //         mainWindow.start()
                //     }
                // }

                // 双击事件切换全屏和窗口模式
                onDoubleClicked: {
                    if (mainWindow.isFullScreen) {
                        mainWindow.visibility = Window.Windowed
                        mainWindow.isFullScreen = false
                    } else {
                        mainWindow.visibility = Window.FullScreen
                        mainWindow.isFullScreen = true
                    }
                }
            }

            Component.onCompleted: {
                // mainWindow.start.connect(videoArea.start)
                // mainWindow.stop.connect(videoArea.pause)
                // mainWindow.openFile.connect(videoArea.openFile)
                delayTimer.start()
            }

            onOpenFileResult: (result) => {
                if (result == YT20PlayerNS.FAILED) {
                    // 错误处理
                } else if (result == YT20PlayerNS.VIDEO || result == YT20PlayerNS.AUDIO) {
                    start()
                }
            }

            Timer {
                id: delayTimer
                interval: 2000  // 2秒
                repeat: false   // 只运行一次
                onTriggered: {
                    console.log("2 seconds have passed, executing operation")
                    videoArea.openFile("../../../test2.mp4")
                }
            }
        }
    }
}
