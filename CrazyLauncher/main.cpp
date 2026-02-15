#include "CrazyLauncher.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CrazyLauncher window;
    window.show();
    return app.exec();
}
