#include "CrazyLauncher.h"
#include "widget/MainWidget.h"

namespace Cl
{
	CrazyLauncher::CrazyLauncher(QWidget* parent) : QMainWindow(parent), m_mainWidget(InitMainWidget(this))
	{
		setWindowIcon(QIcon(":/resources/LogoCrazyLauncher.ico"));
		setMinimumSize(1600, 900);
	}

	CrazyLauncher::~CrazyLauncher() {}
	
	MainWidget* CrazyLauncher::InitMainWidget(QWidget* parent)
	{
		m_mainWidget = new MainWidget(parent);
		setCentralWidget(m_mainWidget);

		return m_mainWidget;
	}
}