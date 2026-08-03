#pragma once
#include <QtWidgets/QMainWindow>

class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QString;
class QListWidgetItem;

namespace Cl
{
	class MainWidget;

	class CrazyLauncher : public QMainWindow
	{
		Q_OBJECT

	public:
		CrazyLauncher(QWidget* parent = nullptr);
		~CrazyLauncher();

	private:
		MainWidget* m_mainWidget;
		MainWidget* InitMainWidget(QWidget* parent);
	};
}


