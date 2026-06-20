#include "CrazyLauncher.h"

//#include <QtWidgets/QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QSize>
#include <QFile>
#include <QTextStream>

int main(int argc, char* argv[])
{
	/*
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
	*/

	QGuiApplication app(argc, argv);
	QCoreApplication::setApplicationName("CrazyLauncher");

	QQmlApplicationEngine engine;
	engine.connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { qDebug("Qml Failed to load"); QCoreApplication::exit(-1); }, Qt::QueuedConnection);
	engine.loadFromModule("CrazyLauncher", "Main");

    return app.exec();
}
