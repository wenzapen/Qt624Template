/****************************************************************************
** Meta object code from reading C++ file 'framecontroller.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../framecontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'framecontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FrameController_t {
    const uint offsetsAndSize[64];
    char stringdata0[411];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_FrameController_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_FrameController_t qt_meta_stringdata_FrameController = {
    {
QT_MOC_LITERAL(0, 15), // "FrameController"
QT_MOC_LITERAL(16, 21), // "signalDecoderOpenFile"
QT_MOC_LITERAL(38, 0), // ""
QT_MOC_LITERAL(39, 11), // "std::string"
QT_MOC_LITERAL(51, 4), // "path"
QT_MOC_LITERAL(56, 17), // "signalDecoderSeek"
QT_MOC_LITERAL(74, 3), // "pos"
QT_MOC_LITERAL(78, 27), // "signalPositionChangedBySeek"
QT_MOC_LITERAL(106, 14), // "signalSetTrack"
QT_MOC_LITERAL(121, 1), // "i"
QT_MOC_LITERAL(123, 21), // "signalDecoderSetTrack"
QT_MOC_LITERAL(145, 14), // "signalBackward"
QT_MOC_LITERAL(160, 13), // "signalForward"
QT_MOC_LITERAL(174, 31), // "signalAudioOutputDevicesChanged"
QT_MOC_LITERAL(206, 20), // "signalDeviceSwitched"
QT_MOC_LITERAL(227, 14), // "openFileResult"
QT_MOC_LITERAL(242, 30), // "YT20Player::OpenFileResultType"
QT_MOC_LITERAL(273, 6), // "result"
QT_MOC_LITERAL(280, 20), // "playbackStateChanged"
QT_MOC_LITERAL(301, 9), // "isPlaying"
QT_MOC_LITERAL(311, 12), // "resourcesEnd"
QT_MOC_LITERAL(324, 10), // "setPicture"
QT_MOC_LITERAL(335, 13), // "VideoFrameRef"
QT_MOC_LITERAL(349, 3), // "pic"
QT_MOC_LITERAL(353, 12), // "initOnThread"
QT_MOC_LITERAL(366, 8), // "openFile"
QT_MOC_LITERAL(375, 5), // "pause"
QT_MOC_LITERAL(381, 4), // "stop"
QT_MOC_LITERAL(386, 5), // "close"
QT_MOC_LITERAL(392, 5), // "start"
QT_MOC_LITERAL(398, 4), // "seek"
QT_MOC_LITERAL(403, 7) // "seekPos"

    },
    "FrameController\0signalDecoderOpenFile\0"
    "\0std::string\0path\0signalDecoderSeek\0"
    "pos\0signalPositionChangedBySeek\0"
    "signalSetTrack\0i\0signalDecoderSetTrack\0"
    "signalBackward\0signalForward\0"
    "signalAudioOutputDevicesChanged\0"
    "signalDeviceSwitched\0openFileResult\0"
    "YT20Player::OpenFileResultType\0result\0"
    "playbackStateChanged\0isPlaying\0"
    "resourcesEnd\0setPicture\0VideoFrameRef\0"
    "pic\0initOnThread\0openFile\0pause\0stop\0"
    "close\0start\0seek\0seekPos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FrameController[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  134,    2, 0x06,    1 /* Public */,
       5,    1,  137,    2, 0x06,    3 /* Public */,
       7,    0,  140,    2, 0x06,    5 /* Public */,
       8,    1,  141,    2, 0x06,    6 /* Public */,
      10,    1,  144,    2, 0x06,    8 /* Public */,
      11,    0,  147,    2, 0x06,   10 /* Public */,
      12,    0,  148,    2, 0x06,   11 /* Public */,
      13,    0,  149,    2, 0x06,   12 /* Public */,
      14,    0,  150,    2, 0x06,   13 /* Public */,
      15,    1,  151,    2, 0x06,   14 /* Public */,
      18,    1,  154,    2, 0x06,   16 /* Public */,
      20,    0,  157,    2, 0x06,   18 /* Public */,
      21,    1,  158,    2, 0x06,   19 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      24,    0,  161,    2, 0x08,   21 /* Private */,
      25,    1,  162,    2, 0x0a,   22 /* Public */,
      26,    0,  165,    2, 0x0a,   24 /* Public */,
      27,    0,  166,    2, 0x0a,   25 /* Public */,
      28,    0,  167,    2, 0x0a,   26 /* Public */,
      29,    0,  168,    2, 0x0a,   27 /* Public */,
      30,    1,  169,    2, 0x0a,   28 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QReal,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal,   31,

       0        // eod
};

void FrameController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FrameController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signalDecoderOpenFile((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 1: _t->signalDecoderSeek((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        case 2: _t->signalPositionChangedBySeek(); break;
        case 3: _t->signalSetTrack((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->signalDecoderSetTrack((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->signalBackward(); break;
        case 6: _t->signalForward(); break;
        case 7: _t->signalAudioOutputDevicesChanged(); break;
        case 8: _t->signalDeviceSwitched(); break;
        case 9: _t->openFileResult((*reinterpret_cast< std::add_pointer_t<YT20Player::OpenFileResultType>>(_a[1]))); break;
        case 10: _t->playbackStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 11: _t->resourcesEnd(); break;
        case 12: _t->setPicture((*reinterpret_cast< std::add_pointer_t<VideoFrameRef>>(_a[1]))); break;
        case 13: _t->initOnThread(); break;
        case 14: _t->openFile((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->pause(); break;
        case 16: _t->stop(); break;
        case 17: _t->close(); break;
        case 18: _t->start(); break;
        case 19: _t->seek((*reinterpret_cast< std::add_pointer_t<qreal>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FrameController::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameController::signalDecoderOpenFile)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FrameController::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameController::signalDecoderSeek)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FrameController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameController::signalPositionChangedBySeek)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FrameController::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameController::signalSetTrack)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FrameController::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameController::signalDecoderSetTrack)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FrameController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameController::signalBackward)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (FrameController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameController::signalForward)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (FrameController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameController::signalAudioOutputDevicesChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (FrameController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameController::signalDeviceSwitched)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (FrameController::*)(YT20Player::OpenFileResultType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameController::openFileResult)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (FrameController::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameController::playbackStateChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (FrameController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameController::resourcesEnd)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (FrameController::*)(VideoFrameRef );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FrameController::setPicture)) {
                *result = 12;
                return;
            }
        }
    }
}

const QMetaObject FrameController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_FrameController.offsetsAndSize,
    qt_meta_data_FrameController,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_FrameController_t
, QtPrivate::TypeAndForceComplete<FrameController, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<std::string, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qreal, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<YT20Player::OpenFileResultType, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<VideoFrameRef, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qreal, std::false_type>


>,
    nullptr
} };


const QMetaObject *FrameController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FrameController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FrameController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FrameController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void FrameController::signalDecoderOpenFile(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FrameController::signalDecoderSeek(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FrameController::signalPositionChangedBySeek()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void FrameController::signalSetTrack(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FrameController::signalDecoderSetTrack(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FrameController::signalBackward()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void FrameController::signalForward()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void FrameController::signalAudioOutputDevicesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void FrameController::signalDeviceSwitched()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void FrameController::openFileResult(YT20Player::OpenFileResultType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void FrameController::playbackStateChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void FrameController::resourcesEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void FrameController::setPicture(VideoFrameRef _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
