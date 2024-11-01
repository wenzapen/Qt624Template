FFMpeg 推流命令：
ffmpeg -re -i input_video.mp4 -c:v copy -c:a copy -f rtsp rtsp://localhost:8554/mystream

mainWindow->invoke(openFile)->Hurricane(openFile)->emit signal(signalOpenFile)
->FrameController slot(openFile) -> emit signal(signalDecoderOpenFile)->demuxer slot(openFile)
:create DecodeDispatcher -> emit signal(openFileResult) -> frameController emit(openFileResult)
->hurricane slotOpenFileResult -> emit signal(slotOpenFileResult) -> hurricane(qml) onOpenfileResult
->invoke mainWindow.start -> hurricane.start -> emit signal(signalStart)  -> frameController slot start
->   invoke  m_demuxer->start() && m_playback->start();
