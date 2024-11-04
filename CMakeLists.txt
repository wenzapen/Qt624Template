cmake_minimum_required(VERSION 3.16)

project(Qt624Template VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick Multimedia)
if (WIN32)
    # 请将下面的路径更改为你系统上 FFmpeg 的实际安装路径
    set(FFMPEG_INCLUDE_DIR "C:/D/ffmpeg/include")
    set(FFMPEG_LIB_DIR "C:/D/ffmpeg/lib")
    set(FFMPEG_LIBS "avformat;avcodec;avutil;swscale;swresample;avdevice;avfilter;postproc")  # 根据需要修改
else()
    set(FFMPEG_INCLUDE_DIR "/usr/local/ffmpeg/include")
    set(FFMPEG_LIB_DIR "/usr/local/ffmpeg/lib")
    set(FFMPEG_LIBS "avformat;avcodec;avutil;swscale;swresample;avdevice;avfilter;postproc")
endif()


#portaudio
# if (WIN32)
#     # 请将下面的路径更改为你系统上 portaudio 的实际安装路径
#     set(PORTAUDIO_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/portaudio/win32/include")
#     set(PORTAUDIO_LIB_DIR "${CMAKE_SOURCE_DIR}/external/portaudio/win32/")
#     set(PORTAUDIO_LIBS "libportaudio.a")  # 根据需要修改
# else()
#     set(PORTAUDIO_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/portaudio/win32/include")
#     set(PORTAUDIO_LIB_DIR "${CMAKE_SOURCE_DIR}/external/portaudio/win32")
#     set(PORTAUDIO_LIBS "libportaudio.a")
# endif()


if(WIN32)
    set(PORTAUDIO_LIB_PATH "${CMAKE_SOURCE_DIR}/external/portaudio/lib/win/libportaudio.a")
elseif(UNIX)
    set(PORTAUDIO_LIB_PATH "${CMAKE_SOURCE_DIR}/external/portaudio/lib/unix/libportaudio.a")
endif()

if (UNIX)
    find_package(ALSA REQUIRED)
endif()

# add_subdirectory(external/portaudio)
add_subdirectory(external/sonic)
add_subdirectory(external/rwqueue)
add_subdirectory(external/concurrentqueue)



# include_directories(${FFMPEG_INCLUDE_DIR}})
link_directories(${FFMPEG_LIB_DIR})

qt_add_executable(appQt624Template
    main.cpp
    # external/portaudio/src/common/pa_ringbuffer.c
)

qt_add_qml_module(appQt624Template
    URI Qt624Template
    VERSION 1.0
    QML_FILES

        QML_FILES CustomRadioButton.qml
        QML_FILES main.qml
        SOURCES fireworks.h
        SOURCES hurricane.h
        SOURCES framecontroller.h
        SOURCES demuxer.h
        SOURCES dispatcher.h
        SOURCES twinsqueue.h
        SOURCES frame.h
        SOURCES helper.h
        SOURCES playback.h
        SOURCES audiosink.h
        SOURCES audioformat.h
        SOURCES hotplug.h
        SOURCES decoders.h
        SOURCES forward.h
        SOURCES yt20player.h
        SOURCES platform.h
        SOURCES renderer.h
        SOURCES updatevalue.h
        SOURCES virtual.h
        SOURCES backward.h
        RESOURCES shader/fragment.fsh
        RESOURCES shader/vertex.vsh
        RESOURCES ReadMe.md
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQt624Template PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQt624Template
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 添加 PortAudio 头文件目录
target_include_directories(appQt624Template PRIVATE

    ${CMAKE_CURRENT_SOURCE_DIR}/external/sonic/
    ${CMAKE_CURRENT_SOURCE_DIR}/external/rwqueue
    ${CMAKE_CURRENT_SOURCE_DIR}/external/concurrentqueue
    ${FFMPEG_INCLUDE_DIR}
)

if(WIN32)
    target_include_directories(appQt624Template PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external/portaudio/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/portaudio/src/common)
elseif(UNIX)
    target_include_directories(appQt624Template PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external/portaudio/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/portaudio/src/common)
endif()

target_link_libraries(appQt624Template
    PRIVATE Qt6::Quick
    Qt6::Multimedia
    ${FFMPEG_LIBS}
    ${PORTAUDIO_LIB_PATH}
    sonic
    rwqueue
    concurrentqueue


)

if(WIN32)
    target_link_libraries(appQt624Template PRIVATE
        winmm
        SetupAPI
    )
endif()

if(UNIX)
    target_link_libraries(appQt624Template
        PRIVATE ${ALSA_LIBRARIES}
    )
    target_include_directories(appQt624Template PRIVATE ${ALSA_INCLUDE_DIRS})
endif()



include(GNUInstallDirs)
install(TARGETS appQt624Template
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# 添加 windeployqt 自动部署功能
if(WIN32)
    # 查找 Qt 安装路径
    get_target_property(QT_BIN_DIR Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(QT_BIN_DIR ${QT_BIN_DIR} DIRECTORY)

    # 添加部署命令
    add_custom_command(TARGET appQt624Template POST_BUILD
        COMMAND "${QT_BIN_DIR}/windeployqt.exe" --qmldir "${CMAKE_SOURCE_DIR}" "$<TARGET_FILE:appQt624Template>"
        COMMENT "Running windeployqt to bundle Qt dependencies."
    )
endif()
