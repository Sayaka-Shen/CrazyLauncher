#include "CrazyLauncher.h"
#include "widget/MainWidget.h"

namespace Cl
{
	CrazyLauncher::CrazyLauncher(QWidget* parent) : QMainWindow(parent), m_mainWidget(InitMainWidget(this))
	{
		setWindowIcon(QIcon(":/new/prefix1/LogoCrazyLauncher.ico"));
	}

	CrazyLauncher::~CrazyLauncher() {}
	
	MainWidget* CrazyLauncher::InitMainWidget(QWidget* parent)
	{
		m_mainWidget = new MainWidget(parent);
		setCentralWidget(m_mainWidget);

		return m_mainWidget;
	}
}