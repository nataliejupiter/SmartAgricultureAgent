/****************************************************************************
** Meta object code from reading C++ file 'wet_page.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../wet_page.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wet_page.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
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

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSwet_pageENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSwet_pageENDCLASS = QtMocHelpers::stringData(
    "wet_page",
    "on_pushButton_3_clicked",
    "",
    "on_high_limit_add_clicked",
    "on_high_limit_minus_clicked",
    "on_low_limit_add_clicked",
    "on_low_limit_minus_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSwet_pageENDCLASS_t {
    uint offsetsAndSizes[14];
    char stringdata0[9];
    char stringdata1[24];
    char stringdata2[1];
    char stringdata3[26];
    char stringdata4[28];
    char stringdata5[25];
    char stringdata6[27];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSwet_pageENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSwet_pageENDCLASS_t qt_meta_stringdata_CLASSwet_pageENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "wet_page"
        QT_MOC_LITERAL(9, 23),  // "on_pushButton_3_clicked"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 25),  // "on_high_limit_add_clicked"
        QT_MOC_LITERAL(60, 27),  // "on_high_limit_minus_clicked"
        QT_MOC_LITERAL(88, 24),  // "on_low_limit_add_clicked"
        QT_MOC_LITERAL(113, 26)   // "on_low_limit_minus_clicked"
    },
    "wet_page",
    "on_pushButton_3_clicked",
    "",
    "on_high_limit_add_clicked",
    "on_high_limit_minus_clicked",
    "on_low_limit_add_clicked",
    "on_low_limit_minus_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSwet_pageENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x08,    1 /* Private */,
       3,    0,   45,    2, 0x08,    2 /* Private */,
       4,    0,   46,    2, 0x08,    3 /* Private */,
       5,    0,   47,    2, 0x08,    4 /* Private */,
       6,    0,   48,    2, 0x08,    5 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject wet_page::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSwet_pageENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSwet_pageENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSwet_pageENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<wet_page, std::true_type>,
        // method 'on_pushButton_3_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_high_limit_add_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_high_limit_minus_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_low_limit_add_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_low_limit_minus_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void wet_page::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<wet_page *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton_3_clicked(); break;
        case 1: _t->on_high_limit_add_clicked(); break;
        case 2: _t->on_high_limit_minus_clicked(); break;
        case 3: _t->on_low_limit_add_clicked(); break;
        case 4: _t->on_low_limit_minus_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *wet_page::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *wet_page::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSwet_pageENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int wet_page::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
