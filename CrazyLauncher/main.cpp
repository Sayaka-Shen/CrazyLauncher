#include "CrazyLauncher.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("CrazyLauncher");

    Cl::CrazyLauncher window;
    window.show();
    return app.exec();
}
