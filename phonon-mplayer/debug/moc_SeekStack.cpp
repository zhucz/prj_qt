/****************************************************************************
** Meta object code from reading C++ file 'SeekStack.h'
**
** Created: Sat Mar 6 21:20:47 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SeekStack.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SeekStack.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Phonon__MPlayer__SeekStack[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x08,
      38,   27,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Phonon__MPlayer__SeekStack[] = {
    "Phonon::MPlayer::SeekStack\0\0popSeek()\0"
    "reconnectTickSignal()\0"
};

const QMetaObject Phonon::MPlayer::SeekStack::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Phonon__MPlayer__SeekStack,
      qt_meta_data_Phonon__MPlayer__SeekStack, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Phonon::MPlayer::SeekStack::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Phonon::MPlayer::SeekStack::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Phonon::MPlayer::SeekStack::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Phonon__MPlayer__SeekStack))
        return static_cast<void*>(const_cast< SeekStack*>(this));
    return QObject::qt_metacast(_clname);
}

int Phonon::MPlayer::SeekStack::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: popSeek(); break;
        case 1: reconnectTickSignal(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
