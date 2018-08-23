/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ImageProcessor/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[26];
    char stringdata0[324];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "loadandShowImg"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "toGrayscale"
QT_MOC_LITERAL(4, 39, 8), // "drawHist"
QT_MOC_LITERAL(5, 48, 3), // "Mat"
QT_MOC_LITERAL(6, 52, 4), // "Mat&"
QT_MOC_LITERAL(7, 57, 5), // "image"
QT_MOC_LITERAL(8, 63, 12), // "drawGrayHist"
QT_MOC_LITERAL(9, 76, 13), // "drawGammaHist"
QT_MOC_LITERAL(10, 90, 5), // "gamma"
QT_MOC_LITERAL(11, 96, 12), // "negativeHist"
QT_MOC_LITERAL(12, 109, 12), // "contrastHist"
QT_MOC_LITERAL(13, 122, 10), // "brightness"
QT_MOC_LITERAL(14, 133, 8), // "contrast"
QT_MOC_LITERAL(15, 142, 11), // "orderDither"
QT_MOC_LITERAL(16, 154, 5), // "msize"
QT_MOC_LITERAL(17, 160, 15), // "on_show_clicked"
QT_MOC_LITERAL(18, 176, 16), // "on_reset_clicked"
QT_MOC_LITERAL(19, 193, 15), // "on_gray_clicked"
QT_MOC_LITERAL(20, 209, 19), // "on_histgray_clicked"
QT_MOC_LITERAL(21, 229, 20), // "on_histgamma_clicked"
QT_MOC_LITERAL(22, 250, 19), // "on_negative_clicked"
QT_MOC_LITERAL(23, 270, 19), // "on_contrast_clicked"
QT_MOC_LITERAL(24, 290, 15), // "on_quit_clicked"
QT_MOC_LITERAL(25, 306, 17) // "on_dither_clicked"

    },
    "MainWindow\0loadandShowImg\0\0toGrayscale\0"
    "drawHist\0Mat\0Mat&\0image\0drawGrayHist\0"
    "drawGammaHist\0gamma\0negativeHist\0"
    "contrastHist\0brightness\0contrast\0"
    "orderDither\0msize\0on_show_clicked\0"
    "on_reset_clicked\0on_gray_clicked\0"
    "on_histgray_clicked\0on_histgamma_clicked\0"
    "on_negative_clicked\0on_contrast_clicked\0"
    "on_quit_clicked\0on_dither_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x0a /* Public */,
       3,    0,  100,    2, 0x0a /* Public */,
       4,    1,  101,    2, 0x0a /* Public */,
       8,    0,  104,    2, 0x0a /* Public */,
       9,    1,  105,    2, 0x0a /* Public */,
      11,    0,  108,    2, 0x0a /* Public */,
      12,    2,  109,    2, 0x0a /* Public */,
      15,    1,  114,    2, 0x0a /* Public */,
      17,    0,  117,    2, 0x0a /* Public */,
      18,    0,  118,    2, 0x0a /* Public */,
      19,    0,  119,    2, 0x0a /* Public */,
      20,    0,  120,    2, 0x0a /* Public */,
      21,    0,  121,    2, 0x0a /* Public */,
      22,    0,  122,    2, 0x0a /* Public */,
      23,    0,  123,    2, 0x08 /* Private */,
      24,    0,  124,    2, 0x08 /* Private */,
      25,    0,  125,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 5, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   13,   14,
    QMetaType::Void, QMetaType::Int,   16,
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

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loadandShowImg(); break;
        case 1: _t->toGrayscale(); break;
        case 2: { Mat _r = _t->drawHist((*reinterpret_cast< Mat(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Mat*>(_a[0]) = _r; }  break;
        case 3: _t->drawGrayHist(); break;
        case 4: _t->drawGammaHist((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->negativeHist(); break;
        case 6: _t->contrastHist((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 7: _t->orderDither((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_show_clicked(); break;
        case 9: _t->on_reset_clicked(); break;
        case 10: _t->on_gray_clicked(); break;
        case 11: _t->on_histgray_clicked(); break;
        case 12: _t->on_histgamma_clicked(); break;
        case 13: _t->on_negative_clicked(); break;
        case 14: _t->on_contrast_clicked(); break;
        case 15: _t->on_quit_clicked(); break;
        case 16: _t->on_dither_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
