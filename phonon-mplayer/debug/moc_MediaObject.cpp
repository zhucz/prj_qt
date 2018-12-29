/****************************************************************************
** Meta object code from reading C++ file 'MediaObject.h'
**
** Created: Sat Mar 6 21:20:43 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MediaObject.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MediaObject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Phonon__MPlayer__MediaObject[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   29,   29,   29, 0x05,
      60,   46,   29,   29, 0x05,
      88,   78,   29,   29, 0x05,
     122,   29,   29,   29, 0x05,
     142,  133,   29,   29, 0x05,
     173,  164,   29,   29, 0x05,
     227,  217,   29,   29, 0x05,
     267,  256,   29,   29, 0x05,
     307,  289,   29,   29, 0x05,
     354,  349,   29,   29, 0x05,
     380,  367,   29,   29, 0x05,

 // slots: signature, parameters, type, tag, flags
     405,   29,   29,   29, 0x08,
     425,   29,   29,   29, 0x08,
     449,  439,   29,   29, 0x08,
     477,  289,   29,   29, 0x08,
     527,   29,   29,   29, 0x08,
     558,  546,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Phonon__MPlayer__MediaObject[] = {
    "Phonon::MPlayer::MediaObject\0\0"
    "aboutToFinish()\0percentFilled\0"
    "bufferStatus(int)\0newSource\0"
    "currentSourceChanged(MediaSource)\0"
    "finished()\0hasVideo\0hasVideoChanged(bool)\0"
    "metaData\0metaDataChanged(QMultiMap<QString,QString>)\0"
    "msecToEnd\0prefinishMarkReached(qint32)\0"
    "isSeekable\0seekableChanged(bool)\0"
    "newState,oldState\0"
    "stateChanged(Phonon::State,Phonon::State)\0"
    "time\0tick(qint64)\0newTotalTime\0"
    "totalTimeChanged(qint64)\0loadMediaInternal()\0"
    "mediaLoaded()\0mediaData\0"
    "mediaDataChanged(MediaData)\0"
    "stateChangedInternal(Phonon::State,Phonon::State)\0"
    "endOfFileReached()\0currentTime\0"
    "tickInternal(qint64)\0"
};

const QMetaObject Phonon::MPlayer::MediaObject::staticMetaObject = {
    { &MediaController::staticMetaObject, qt_meta_stringdata_Phonon__MPlayer__MediaObject,
      qt_meta_data_Phonon__MPlayer__MediaObject, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Phonon::MPlayer::MediaObject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Phonon::MPlayer::MediaObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Phonon::MPlayer::MediaObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Phonon__MPlayer__MediaObject))
        return static_cast<void*>(const_cast< MediaObject*>(this));
    if (!strcmp(_clname, "MediaObjectInterface"))
        return static_cast< MediaObjectInterface*>(const_cast< MediaObject*>(this));
    if (!strcmp(_clname, "MediaObjectInterface3.phonon.kde.org"))
        return static_cast< Phonon::MediaObjectInterface*>(const_cast< MediaObject*>(this));
    if (!strcmp(_clname, "AddonInterface0.2.phonon.kde.org"))
        return static_cast< Phonon::AddonInterface*>(const_cast< MediaObject*>(this));
    return MediaController::qt_metacast(_clname);
}

int Phonon::MPlayer::MediaObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MediaController::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: aboutToFinish(); break;
        case 1: bufferStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: currentSourceChanged((*reinterpret_cast< const MediaSource(*)>(_a[1]))); break;
        case 3: finished(); break;
        case 4: hasVideoChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: metaDataChanged((*reinterpret_cast< const QMultiMap<QString,QString>(*)>(_a[1]))); break;
        case 6: prefinishMarkReached((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 7: seekableChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: stateChanged((*reinterpret_cast< Phonon::State(*)>(_a[1])),(*reinterpret_cast< Phonon::State(*)>(_a[2]))); break;
        case 9: tick((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 10: totalTimeChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 11: loadMediaInternal(); break;
        case 12: mediaLoaded(); break;
        case 13: mediaDataChanged((*reinterpret_cast< const MediaData(*)>(_a[1]))); break;
        case 14: stateChangedInternal((*reinterpret_cast< Phonon::State(*)>(_a[1])),(*reinterpret_cast< Phonon::State(*)>(_a[2]))); break;
        case 15: endOfFileReached(); break;
        case 16: tickInternal((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void Phonon::MPlayer::MediaObject::aboutToFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Phonon::MPlayer::MediaObject::bufferStatus(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Phonon::MPlayer::MediaObject::currentSourceChanged(const MediaSource & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Phonon::MPlayer::MediaObject::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Phonon::MPlayer::MediaObject::hasVideoChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Phonon::MPlayer::MediaObject::metaDataChanged(const QMultiMap<QString,QString> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Phonon::MPlayer::MediaObject::prefinishMarkReached(qint32 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Phonon::MPlayer::MediaObject::seekableChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Phonon::MPlayer::MediaObject::stateChanged(Phonon::State _t1, Phonon::State _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Phonon::MPlayer::MediaObject::tick(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Phonon::MPlayer::MediaObject::totalTimeChanged(qint64 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_END_MOC_NAMESPACE
