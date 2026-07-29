#include "windows/CrazyLauncher.h"

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
    window.show();

    return app.exec();
}
