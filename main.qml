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

    //打开文件

    //音视频是否在播放
    property bool isPlay: false


    signal openFile(string path)
    signal start()
    signal stop()

    Rectangle{
        color: "black"
        anchors.fill: parent
        HurricanePlayer{
            id: videoArea
            clip: true
            anchors.fill: parent
            MouseArea{
                anchors.fill: parent
                propagateComposedEvents: true
                cursorShape: "PointingHandCursor"
                onClicked: {
                    if(mainWindow.isPlay){
                        mainWindow.isPlay=false
                        mainWindow.stop()
                    }
                    else{
                        mainWindow.isPlay=true
                        mainWindow.start()
                    }
                }
            }
            Component.onCompleted: {

                mainWindow.start.connect(videoArea.start)
                mainWindow.stop.connect(videoArea.pause)
                // mainWindow.openFile.connect(videoArea.openFile)
                delayTimer.start()

                }
            onOpenFileResult: (result)=> {
                if(result == YT20PlayerNS.FAILED)
                {
                }
                else if(result == YT20PlayerNS.VIDEO)
                {
                    mainWindow.start()
                }
                else if(result == YT20PlayerNS.AUDIO){
                    mainWindow.start()
                }
            }

            Timer {
                id: delayTimer
                interval: 2000  // 2 seconds in milliseconds
                repeat: false   // Only run once
                onTriggered: {
                    console.log("2 seconds have passed, executing operation")
                    videoArea.openFile("../../../test2.mp4")
                    // 在这里执行你的操作
                }
            }

        }


    }


}
