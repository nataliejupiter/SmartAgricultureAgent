/****************************************************************************
** Meta object code from reading C++ file 'mainmonitor.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainmonitor.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qabstractbarseries.h>
#include <QtCharts/qvbarmodelmapper.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCharts/qcandlestickseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainmonitor.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSmainMonitorENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSmainMonitorENDCLASS = QtMocHelpers::stringData(
    "mainMonitor",
    "serial_readyRead",
    "",
    "SerialHistoricalDatePage",
    "SerialSetPage",
    "TemperatureSetPage",
    "WetParameterSetPage",
    "WaterLevelSetPage",
    "AboutusPage",
    "PHSetPage",
    "SerialTimeout_Event",
    "PictureReflesh",
    "on_pushButton_abnormal_clicked",
    "on_Button_Button_waterlevel_licked",
    "on_Button_temperature_clicked",
    "on_Button_waterlevel_clicked",
    "on_Button_wet_clicked",
    "drawingline",
    "on_Button_start_clicked",
    "on_Button_sendPicture_clicked",
    "on_Button_ph_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSmainMonitorENDCLASS_t {
    uint offsetsAndSizes[42];
    char stringdata0[12];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[25];
    char stringdata4[14];
    char stringdata5[19];
    char stringdata6[20];
    char stringdata7[18];
    char stringdata8[12];
    char stringdata9[10];
    char stringdata10[20];
    char stringdata11[15];
    char stringdata12[31];
    char stringdata13[35];
    char stringdata14[30];
    char stringdata15[29];
    char stringdata16[22];
    char stringdata17[12];
    char stringdata18[24];
    char stringdata19[30];
    char stringdata20[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSmainMonitorENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSmainMonitorENDCLASS_t qt_meta_stringdata_CLASSmainMonitorENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "mainMonitor"
        QT_MOC_LITERAL(12, 16),  // "serial_readyRead"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 24),  // "SerialHistoricalDatePage"
        QT_MOC_LITERAL(55, 13),  // "SerialSetPage"
        QT_MOC_LITERAL(69, 18),  // "TemperatureSetPage"
        QT_MOC_LITERAL(88, 19),  // "WetParameterSetPage"
        QT_MOC_LITERAL(108, 17),  // "WaterLevelSetPage"
        QT_MOC_LITERAL(126, 11),  // "AboutusPage"
        QT_MOC_LITERAL(138, 9),  // "PHSetPage"
        QT_MOC_LITERAL(148, 19),  // "SerialTimeout_Event"
        QT_MOC_LITERAL(168, 14),  // "PictureReflesh"
        QT_MOC_LITERAL(183, 30),  // "on_pushButton_abnormal_clicked"
        QT_MOC_LITERAL(214, 34),  // "on_Button_Button_waterlevel_l..."
        QT_MOC_LITERAL(249, 29),  // "on_Button_temperature_clicked"
        QT_MOC_LITERAL(279, 28),  // "on_Button_waterlevel_clicked"
        QT_MOC_LITERAL(308, 21),  // "on_Button_wet_clicked"
        QT_MOC_LITERAL(330, 11),  // "drawingline"
        QT_MOC_LITERAL(342, 23),  // "on_Button_start_clicked"
        QT_MOC_LITERAL(366, 29),  // "on_Button_sendPicture_clicked"
        QT_MOC_LITERAL(396, 20)   // "on_Button_ph_clicked"
    },
    "mainMonitor",
    "serial_readyRead",
    "",
    "SerialHistoricalDatePage",
    "SerialSetPage",
    "TemperatureSetPage",
    "WetParameterSetPage",
    "WaterLevelSetPage",
    "AboutusPage",
    "PHSetPage",
    "SerialTimeout_Event",
    "PictureReflesh",
    "on_pushButton_abnormal_clicked",
    "on_Button_Button_waterlevel_licked",
    "on_Button_temperature_clicked",
    "on_Button_waterlevel_clicked",
    "on_Button_wet_clicked",
    "drawingline",
    "on_Button_start_clicked",
    "on_Button_sendPicture_clicked",
    "on_Button_ph_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSmainMonitorENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  128,    2, 0x0a,    1 /* Public */,
       3,    0,  129,    2, 0x08,    2 /* Private */,
       4,    0,  130,    2, 0x08,    3 /* Private */,
       5,    0,  131,    2, 0x08,    4 /* Private */,
       6,    0,  132,    2, 0x08,    5 /* Private */,
       7,    0,  133,    2, 0x08,    6 /* Private */,
       8,    0,  134,    2, 0x08,    7 /* Private */,
       9,    0,  135,    2, 0x08,    8 /* Private */,
      10,    0,  136,    2, 0x08,    9 /* Private */,
      11,    0,  137,    2, 0x08,   10 /* Private */,
      12,    0,  138,    2, 0x08,   11 /* Private */,
      13,    0,  139,    2, 0x08,   12 /* Private */,
      14,    0,  140,    2, 0x08,   13 /* Private */,
      15,    0,  141,    2, 0x08,   14 /* Private */,
      16,    0,  142,    2, 0x08,   15 /* Private */,
      17,    0,  143,    2, 0x08,   16 /* Private */,
      18,    0,  144,    2, 0x08,   17 /* Private */,
      19,    0,  145,    2, 0x08,   18 /* Private */,
      20,    0,  146,    2, 0x08,   19 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject mainMonitor::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSmainMonitorENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSmainMonitorENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSmainMonitorENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<mainMonitor, std::true_type>,
        // method 'serial_readyRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SerialHistoricalDatePage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SerialSetPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'TemperatureSetPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'WetParameterSetPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'WaterLevelSetPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'AboutusPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'PHSetPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SerialTimeout_Event'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'PictureReflesh'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_abnormal_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Button_Button_waterlevel_licked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Button_temperature_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Button_waterlevel_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Button_wet_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'drawingline'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Button_start_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Button_sendPicture_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Button_ph_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void mainMonitor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<mainMonitor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->serial_readyRead(); break;
        case 1: _t->SerialHistoricalDatePage(); break;
        case 2: _t->SerialSetPage(); break;
        case 3: _t->TemperatureSetPage(); break;
        case 4: _t->WetParameterSetPage(); break;
        case 5: _t->WaterLevelSetPage(); break;
        case 6: _t->AboutusPage(); break;
        case 7: _t->PHSetPage(); break;
        case 8: _t->SerialTimeout_Event(); break;
        case 9: _t->PictureReflesh(); break;
        case 10: _t->on_pushButton_abnormal_clicked(); break;
        case 11: _t->on_Button_Button_waterlevel_licked(); break;
        case 12: _t->on_Button_temperature_clicked(); break;
        case 13: _t->on_Button_waterlevel_clicked(); break;
        case 14: _t->on_Button_wet_clicked(); break;
        case 15: _t->drawingline(); break;
        case 16: _t->on_Button_start_clicked(); break;
        case 17: _t->on_Button_sendPicture_clicked(); break;
        case 18: _t->on_Button_ph_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *mainMonitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mainMonitor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSmainMonitorENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int mainMonitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
    }
    return _id;
}
QT_WARNING_POP
