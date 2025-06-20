/****************************************************************************
** Meta object code from reading C++ file 'SlicePlugin.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SlicePlugin.h"
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SlicePlugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN11SlicePluginE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN11SlicePluginE = QtMocHelpers::stringData(
    "SlicePlugin"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN11SlicePluginE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject SlicePlugin::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN11SlicePluginE.offsetsAndSizes,
    qt_meta_data_ZN11SlicePluginE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN11SlicePluginE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SlicePlugin, std::true_type>
    >,
    nullptr
} };

void SlicePlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SlicePlugin *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *SlicePlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SlicePlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN11SlicePluginE.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IPluginInterface"))
        return static_cast< IPluginInterface*>(this);
    if (!strcmp(_clname, "com.myide.plugins.IPluginInterface"))
        return static_cast< IPluginInterface*>(this);
    return QObject::qt_metacast(_clname);
}

int SlicePlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}

#ifdef QT_MOC_EXPORT_PLUGIN_V2
static constexpr unsigned char qt_pluginMetaDataV2_SlicePlugin[] = {
    0xbf, 
    // "IID"
    0x02,  0x78,  0x22,  'c',  'o',  'm',  '.',  'm', 
    'y',  'i',  'd',  'e',  '.',  'p',  'l',  'u', 
    'g',  'i',  'n',  's',  '.',  'I',  'P',  'l', 
    'u',  'g',  'i',  'n',  'I',  'n',  't',  'e', 
    'r',  'f',  'a',  'c',  'e', 
    // "className"
    0x03,  0x6b,  'S',  'l',  'i',  'c',  'e',  'P', 
    'l',  'u',  'g',  'i',  'n', 
    // "MetaData"
    0x04,  0xa2,  0x63,  'I',  'I',  'D',  0x78,  0x22, 
    'c',  'o',  'm',  '.',  'm',  'y',  'i',  'd', 
    'e',  '.',  'p',  'l',  'u',  'g',  'i',  'n', 
    's',  '.',  'I',  'P',  'l',  'u',  'g',  'i', 
    'n',  'I',  'n',  't',  'e',  'r',  'f',  'a', 
    'c',  'e',  0x68,  'M',  'e',  't',  'a',  'D', 
    'a',  't',  'a',  0xa4,  0x66,  'A',  'u',  't', 
    'h',  'o',  'r',  0x68,  'Y',  'o',  'u',  'r', 
    'N',  'a',  'm',  'e',  0x6b,  'D',  'e',  's', 
    'c',  'r',  'i',  'p',  't',  'i',  'o',  'n', 
    0x78,  0x46,  uchar('\xd0'), uchar('\x9f'), uchar('\xd0'), uchar('\xbb'), uchar('\xd0'), uchar('\xb0'),
    uchar('\xd0'), uchar('\xb3'), uchar('\xd0'), uchar('\xb8'), uchar('\xd0'), uchar('\xbd'), ' ',  uchar('\xd0'),
    uchar('\xb4'), uchar('\xd0'), uchar('\xbb'), uchar('\xd1'), uchar('\x8f'), ' ',  uchar('\xd0'), uchar('\xb2'),
    uchar('\xd1'), uchar('\x8b'), uchar('\xd1'), uchar('\x80'), uchar('\xd0'), uchar('\xb5'), uchar('\xd0'), uchar('\xb7'),
    uchar('\xd0'), uchar('\xba'), uchar('\xd0'), uchar('\xb8'), ' ',  uchar('\xd0'), uchar('\xbf'), uchar('\xd0'),
    uchar('\xb5'), uchar('\xd1'), uchar('\x80'), uchar('\xd0'), uchar('\xb2'), uchar('\xd1'), uchar('\x8b'), uchar('\xd1'),
    uchar('\x85'), ' ',  '1',  '0',  ' ',  uchar('\xd1'), uchar('\x81'), uchar('\xd1'),
    uchar('\x82'), uchar('\xd1'), uchar('\x80'), uchar('\xd0'), uchar('\xbe'), uchar('\xd0'), uchar('\xba'), ' ', 
    uchar('\xd0'), uchar('\xba'), uchar('\xd0'), uchar('\xbe'), uchar('\xd0'), uchar('\xb4'), uchar('\xd0'), uchar('\xb0'),
    0x64,  'N',  'a',  'm',  'e',  0x6b,  'S',  'l', 
    'i',  'c',  'e',  'P',  'l',  'u',  'g',  'i', 
    'n',  0x67,  'V',  'e',  'r',  's',  'i',  'o', 
    'n',  0x63,  '1',  '.',  '0', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN_V2(SlicePlugin, SlicePlugin, qt_pluginMetaDataV2_SlicePlugin)
#else
QT_PLUGIN_METADATA_SECTION
Q_CONSTINIT static constexpr unsigned char qt_pluginMetaData_SlicePlugin[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x78,  0x22,  'c',  'o',  'm',  '.',  'm', 
    'y',  'i',  'd',  'e',  '.',  'p',  'l',  'u', 
    'g',  'i',  'n',  's',  '.',  'I',  'P',  'l', 
    'u',  'g',  'i',  'n',  'I',  'n',  't',  'e', 
    'r',  'f',  'a',  'c',  'e', 
    // "className"
    0x03,  0x6b,  'S',  'l',  'i',  'c',  'e',  'P', 
    'l',  'u',  'g',  'i',  'n', 
    // "MetaData"
    0x04,  0xa2,  0x63,  'I',  'I',  'D',  0x78,  0x22, 
    'c',  'o',  'm',  '.',  'm',  'y',  'i',  'd', 
    'e',  '.',  'p',  'l',  'u',  'g',  'i',  'n', 
    's',  '.',  'I',  'P',  'l',  'u',  'g',  'i', 
    'n',  'I',  'n',  't',  'e',  'r',  'f',  'a', 
    'c',  'e',  0x68,  'M',  'e',  't',  'a',  'D', 
    'a',  't',  'a',  0xa4,  0x66,  'A',  'u',  't', 
    'h',  'o',  'r',  0x68,  'Y',  'o',  'u',  'r', 
    'N',  'a',  'm',  'e',  0x6b,  'D',  'e',  's', 
    'c',  'r',  'i',  'p',  't',  'i',  'o',  'n', 
    0x78,  0x46,  uchar('\xd0'), uchar('\x9f'), uchar('\xd0'), uchar('\xbb'), uchar('\xd0'), uchar('\xb0'),
    uchar('\xd0'), uchar('\xb3'), uchar('\xd0'), uchar('\xb8'), uchar('\xd0'), uchar('\xbd'), ' ',  uchar('\xd0'),
    uchar('\xb4'), uchar('\xd0'), uchar('\xbb'), uchar('\xd1'), uchar('\x8f'), ' ',  uchar('\xd0'), uchar('\xb2'),
    uchar('\xd1'), uchar('\x8b'), uchar('\xd1'), uchar('\x80'), uchar('\xd0'), uchar('\xb5'), uchar('\xd0'), uchar('\xb7'),
    uchar('\xd0'), uchar('\xba'), uchar('\xd0'), uchar('\xb8'), ' ',  uchar('\xd0'), uchar('\xbf'), uchar('\xd0'),
    uchar('\xb5'), uchar('\xd1'), uchar('\x80'), uchar('\xd0'), uchar('\xb2'), uchar('\xd1'), uchar('\x8b'), uchar('\xd1'),
    uchar('\x85'), ' ',  '1',  '0',  ' ',  uchar('\xd1'), uchar('\x81'), uchar('\xd1'),
    uchar('\x82'), uchar('\xd1'), uchar('\x80'), uchar('\xd0'), uchar('\xbe'), uchar('\xd0'), uchar('\xba'), ' ', 
    uchar('\xd0'), uchar('\xba'), uchar('\xd0'), uchar('\xbe'), uchar('\xd0'), uchar('\xb4'), uchar('\xd0'), uchar('\xb0'),
    0x64,  'N',  'a',  'm',  'e',  0x6b,  'S',  'l', 
    'i',  'c',  'e',  'P',  'l',  'u',  'g',  'i', 
    'n',  0x67,  'V',  'e',  'r',  's',  'i',  'o', 
    'n',  0x63,  '1',  '.',  '0', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(SlicePlugin, SlicePlugin)
#endif  // QT_MOC_EXPORT_PLUGIN_V2

QT_WARNING_POP
