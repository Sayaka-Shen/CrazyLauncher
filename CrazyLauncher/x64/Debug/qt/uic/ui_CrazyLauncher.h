/********************************************************************************
** Form generated from reading UI file 'CrazyLauncher.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CRAZYLAUNCHER_H
#define UI_CRAZYLAUNCHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CrazyLauncherClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CrazyLauncherClass)
    {
        if (CrazyLauncherClass->objectName().isEmpty())
            CrazyLauncherClass->setObjectName("CrazyLauncherClass");
        CrazyLauncherClass->resize(600, 400);
        menuBar = new QMenuBar(CrazyLauncherClass);
        menuBar->setObjectName("menuBar");
        CrazyLauncherClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CrazyLauncherClass);
        mainToolBar->setObjectName("mainToolBar");
        CrazyLauncherClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CrazyLauncherClass);
        centralWidget->setObjectName("centralWidget");
        CrazyLauncherClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CrazyLauncherClass);
        statusBar->setObjectName("statusBar");
        CrazyLauncherClass->setStatusBar(statusBar);

        retranslateUi(CrazyLauncherClass);

        QMetaObject::connectSlotsByName(CrazyLauncherClass);
    } // setupUi

    void retranslateUi(QMainWindow *CrazyLauncherClass)
    {
        CrazyLauncherClass->setWindowTitle(QCoreApplication::translate("CrazyLauncherClass", "CrazyLauncher", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CrazyLauncherClass: public Ui_CrazyLauncherClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CRAZYLAUNCHER_H
