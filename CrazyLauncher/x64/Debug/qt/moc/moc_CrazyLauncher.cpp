/****************************************************************************
** Meta object code from reading C++ file 'CrazyLauncher.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../CrazyLauncher.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CrazyLauncher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
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
struct qt_meta_tag_ZN2Cl13CrazyLauncherE_t {};
} // unnamed namespace

template <> constexpr inline auto Cl::CrazyLauncher::qt_create_metaobjectdata<qt_meta_tag_ZN2Cl13CrazyLauncherE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Cl::CrazyLauncher",
        "CreateAddWindow",
        "",
        "CreateEditWindow",
        "OnCloseUtilityWindow",
        "OnProjectAdded",
        "Project",
        "project",
        "OnProjectEdited",
        "Project*",
        "baseProjectEdited",
        "OnRemoveProject",
        "LaunchProject"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'CreateAddWindow'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'CreateEditWindow'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'OnCloseUtilityWindow'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'OnProjectAdded'
        QtMocHelpers::SlotData<void(const Project &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Slot 'OnProjectEdited'
        QtMocHelpers::SlotData<void(Project *)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Slot 'OnRemoveProject'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'LaunchProject'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CrazyLauncher, qt_meta_tag_ZN2Cl13CrazyLauncherE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Cl::CrazyLauncher::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2Cl13CrazyLauncherE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2Cl13CrazyLauncherE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN2Cl13CrazyLauncherE_t>.metaTypes,
    nullptr
} };

void Cl::CrazyLauncher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CrazyLauncher *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->CreateAddWindow(); break;
        case 1: _t->CreateEditWindow(); break;
        case 2: _t->OnCloseUtilityWindow(); break;
        case 3: _t->OnProjectAdded((*reinterpret_cast<std::add_pointer_t<Project>>(_a[1]))); break;
        case 4: _t->OnProjectEdited((*reinterpret_cast<std::add_pointer_t<Project*>>(_a[1]))); break;
        case 5: _t->OnRemoveProject(); break;
        case 6: _t->LaunchProject(); break;
        default: ;
        }
    }
}

const QMetaObject *Cl::CrazyLauncher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Cl::CrazyLauncher::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN2Cl13CrazyLauncherE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Cl::CrazyLauncher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
