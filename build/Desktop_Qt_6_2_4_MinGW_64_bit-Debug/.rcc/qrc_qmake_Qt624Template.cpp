/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 6.2.4
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

static const unsigned char qt_resource_data[] = {
  // C:/D/QT/Qt624Template/build/Desktop_Qt_6_2_4_MinGW_64_bit-Debug/Qt624Template/qmldir
  0x0,0x0,0x0,0x82,
  0x6d,
  0x6f,0x64,0x75,0x6c,0x65,0x20,0x51,0x74,0x36,0x32,0x34,0x54,0x65,0x6d,0x70,0x6c,
  0x61,0x74,0x65,0xd,0xa,0x74,0x79,0x70,0x65,0x69,0x6e,0x66,0x6f,0x20,0x61,0x70,
  0x70,0x51,0x74,0x36,0x32,0x34,0x54,0x65,0x6d,0x70,0x6c,0x61,0x74,0x65,0x2e,0x71,
  0x6d,0x6c,0x74,0x79,0x70,0x65,0x73,0xd,0xa,0x70,0x72,0x65,0x66,0x65,0x72,0x20,
  0x3a,0x2f,0x51,0x74,0x36,0x32,0x34,0x54,0x65,0x6d,0x70,0x6c,0x61,0x74,0x65,0x2f,
  0xd,0xa,0x43,0x75,0x73,0x74,0x6f,0x6d,0x52,0x61,0x64,0x69,0x6f,0x42,0x75,0x74,
  0x74,0x6f,0x6e,0x20,0x31,0x2e,0x30,0x20,0x43,0x75,0x73,0x74,0x6f,0x6d,0x52,0x61,
  0x64,0x69,0x6f,0x42,0x75,0x74,0x74,0x6f,0x6e,0x2e,0x71,0x6d,0x6c,0xd,0xa,0xd,
  0xa,
  
};

static const unsigned char qt_resource_name[] = {
  // Qt624Template
  0x0,0xd,
  0xc,0xb5,0x9a,0x85,
  0x0,0x51,
  0x0,0x74,0x0,0x36,0x0,0x32,0x0,0x34,0x0,0x54,0x0,0x65,0x0,0x6d,0x0,0x70,0x0,0x6c,0x0,0x61,0x0,0x74,0x0,0x65,
    // qmldir
  0x0,0x6,
  0x7,0x84,0x2b,0x2,
  0x0,0x71,
  0x0,0x6d,0x0,0x6c,0x0,0x64,0x0,0x69,0x0,0x72,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/Qt624Template
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x2,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/Qt624Template/qmldir
  0x0,0x0,0x0,0x20,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,
0x0,0x0,0x1,0x92,0xe2,0x43,0xf0,0x14,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#ifdef QT_NAMESPACE
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_qmake_Qt624Template)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_qmake_Qt624Template)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qmake_Qt624Template)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qmake_Qt624Template)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_qmake_Qt624Template)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qmake_Qt624Template)(); }
   } dummy;
}
