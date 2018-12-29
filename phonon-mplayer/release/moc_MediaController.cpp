/****************************************************************************
** Meta object code from reading C++ file 'MediaController.h'
**
** Created: Sat Mar 6 21:19:55 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MediaController.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MediaController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Phonon__MPlayer__MediaController[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      52,   34,   33,   33, 0x05,
      98,   82,   33,   33, 0x05,
     142,  126,   33,   33, 0x05,
     182,  170,   33,   33, 0x05,
     214,  200,   33,   33, 0x05,
     246,  234,   33,   33, 0x05,

 // slots: signature, parameters, type, tag, flags
     274,  264,   33,   33, 0x08,
     314,  297,   33,   33, 0x08,
     353,  336,   33,   33, 0x08,
     413,  398,   33,   33, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Phonon__MPlayer__MediaController[] = {
    "Phonon::MPlayer::MediaController\0\0"
    "availableChapters\0availableChaptersChanged(int)\0"
    "availableTitles\0availableTitlesChanged(int)\0"
    "availableAngles\0availableAnglesChanged(int)\0"
    "angleNumber\0angleChanged(int)\0"
    "chapterNumber\0chapterChanged(int)\0"
    "titleNumber\0titleChanged(int)\0id,length\0"
    "titleAdded(int,qint64)\0titleId,chapters\0"
    "chapterAdded(int,int)\0id,title,from,to\0"
    "mkvChapterAdded(int,QString,QString,QString)\0"
    "titleId,angles\0angleAdded(int,int)\0"
};

const QMetaObject Phonon::MPlayer::MediaController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Phonon__MPlayer__MediaController,
      qt_meta_data_Phonon__MPlayer__MediaController, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Phonon::MPlayer::MediaController::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Phonon::MPlayer::MediaController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Phonon::MPlayer::MediaController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Phonon__MPlayer__MediaController))
        return static_cast<void*>(const_cast< MediaController*>(this));
    if (!strcmp(_clname, "AddonInterface"))
        return static_cast< AddonInterface*>(const_cast< MediaController*>(this));
    return QObject::qt_metacast(_clname);
}

int Phonon::MPlayer::MediaController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: availableChaptersChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: availableTitlesChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: availableAnglesChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: angleChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: chapterChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: titleChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: titleAdded((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 7: chapterAdded((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: mkvChapterAdded((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 9: angleAdded((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Phonon::MPlayer::MediaController::availableChaptersChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Phonon::MPlayer::MediaController::availableTitlesChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Phonon::MPlayer::MediaController::availableAnglesChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Phonon::MPlayer::MediaController::angleChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Phonon::MPlayer::MediaController::chapterChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Phonon::MPlayer::MediaController::titleChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
