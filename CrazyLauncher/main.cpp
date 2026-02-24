#include "CrazyLauncher.h"

#include <QtWidgets/QApplication>
#include <QSize>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("CrazyLauncher");

    QFile file(":/new/prefix1/style.css");
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream styleStream(&file);
		app.setStyleSheet(styleStream.readAll());
    }

    Cl::CrazyLauncher window;
    window.setMaximumSize(QSize(600, 380));
    window.setMinimumSize(QSize(600, 380));
    window.show();

    return app.exec();
}
