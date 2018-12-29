/****************************************************************************
** Meta object code from reading C++ file 'AudioOutput.h'
**
** Created: Sat Mar 6 21:20:34 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../AudioOutput.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AudioOutput.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Phonon__MPlayer__AudioOutput[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      37,   30,   29,   29, 0x05,
      58,   29,   29,   29, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_Phonon__MPlayer__AudioOutput[] = {
    "Phonon::MPlayer::AudioOutput\0\0volume\0"
    "volumeChanged(qreal)\0audioDeviceFailed()\0"
};

const QMetaObject Phonon::MPlayer::AudioOutput::staticMetaObject = {
    { &SinkNode::staticMetaObject, qt_meta_stringdata_Phonon__MPlayer__AudioOutput,
      qt_meta_data_Phonon__MPlayer__AudioOutput, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Phonon::MPlayer::AudioOutput::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Phonon::MPlayer::AudioOutput::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Phonon::MPlayer::AudioOutput::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Phonon__MPlayer__AudioOutput))
        return static_cast<void*>(const_cast< AudioOutput*>(this));
    if (!strcmp(_clname, "AudioOutputInterface"))
        return static_cast< AudioOutputInterface*>(const_cast< AudioOutput*>(this));
    if (!strcmp(_clname, "AudioOutputInterface2.phonon.kde.org"))
        return static_cast< Phonon::AudioOutputInterface*>(const_cast< AudioOutput*>(this));
    return SinkNode::qt_metacast(_clname);
}

int Phonon::MPlayer::AudioOutput::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SinkNode::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: volumeChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: audioDeviceFailed(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Phonon::MPlayer::AudioOutput::volumeChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Phonon::MPlayer::AudioOutput::audioDeviceFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
