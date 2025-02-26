/****************************************************************************
** Meta object code from reading C++ file 'frame_parser.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../frame_parser.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frame_parser.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN11FrameParserE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN11FrameParserE = QtMocHelpers::stringData(
    "FrameParser",
    "newDataParsed",
    "",
    "string",
    "ID",
    "time",
    "packet_count",
    "mode",
    "state",
    "altitude",
    "temperature",
    "pressure",
    "voltage",
    "gyro_r",
    "gyro_p",
    "gyro_y",
    "accel_r",
    "accel_p",
    "accel_y",
    "mag_r",
    "mag_p",
    "mag_y",
    "auto_gyro_rotation_rate",
    "gps_time",
    "gps_altitude",
    "gps_latitude",
    "gps_longitude",
    "gps_stats",
    "cmd_echo",
    "readSerialData"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN11FrameParserE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,   25,   26,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      29,    0,   77,    2, 0x08,   27 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Double, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double, 0x80000000 | 3, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int, 0x80000000 | 3,    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,   24,   25,   26,   27,   28,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject FrameParser::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN11FrameParserE.offsetsAndSizes,
    qt_meta_data_ZN11FrameParserE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN11FrameParserE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FrameParser, std::true_type>,
        // method 'newDataParsed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<string, std::false_type>,
        QtPrivate::TypeAndForceComplete<string, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<string, std::false_type>,
        QtPrivate::TypeAndForceComplete<string, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<string, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<string, std::false_type>,
        // method 'readSerialData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void FrameParser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<FrameParser *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->newDataParsed((*reinterpret_cast< std::add_pointer_t<string>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[9])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[10])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[11])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[12])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[13])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[14])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[15])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[16])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[17])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[18])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[19])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[20])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[21])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[22])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[23])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[24])),(*reinterpret_cast< std::add_pointer_t<string>>(_a[25]))); break;
        case 1: _t->readSerialData(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (FrameParser::*)(string , string , double , string , string , double , double , double , double , double , double , double , double , double , double , double , double , double , double , string , double , double , double , int , string );
            if (_q_method_type _q_method = &FrameParser::newDataParsed; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *FrameParser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FrameParser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN11FrameParserE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FrameParser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FrameParser::newDataParsed(string _t1, string _t2, double _t3, string _t4, string _t5, double _t6, double _t7, double _t8, double _t9, double _t10, double _t11, double _t12, double _t13, double _t14, double _t15, double _t16, double _t17, double _t18, double _t19, string _t20, double _t21, double _t22, double _t23, int _t24, string _t25)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t8))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t9))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t10))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t11))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t12))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t13))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t14))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t15))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t16))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t17))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t18))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t19))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t20))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t21))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t22))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t23))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t24))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t25))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
