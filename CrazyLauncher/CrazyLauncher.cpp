#include "CrazyLauncher.h"
#include "ProjectView.h"
#include "DescriptionView.h"
#include "SettingsView.h"
#include "ProjectManager.h"
#include "AddWindow.h"
#include "EditWindow.h"
#include "ProjectWidgetItem.h"
#include "Project.h"

#include <QListWidget>
#include <QVBoxLayout>
#include <QSettings>

namespace Cl
{
	CrazyLauncher::CrazyLauncher(QWidget* parent)
		: QMainWindow(parent)
	{
		// Parent for all widgets
		m_centralWidget = new QWidget(this);
		setCentralWidget(m_centralWidget);

		CreateLayout();
		CreateUI();
		CreateController();
		SetupLayout();
		SetupConnections();
	}

	CrazyLauncher::~CrazyLauncher() {}

	void CrazyLauncher::CreateController()
	{
		m_projectManager = new ProjectManager(this);
	}

	void CrazyLauncher::CreateLayout()
	{
		m_mainLayout = new QVBoxLayout(m_centralWidget);
		m_centralLayout = new QHBoxLayout(m_centralWidget);
		m_footerLayout = new QHBoxLayout(m_centralWidget);
	}

	void CrazyLauncher::CreateUI()
	{
		m_projectView = new ProjectView(m_centralWidget);
		m_descView = new DescriptionView(m_centralWidget);
		m_settingView = new SettingsView(m_centralWidget);
	}

	void CrazyLauncher::SetupLayout()
	{
		m_centralLayout->addWidget(m_projectView, 1);
		m_centralLayout->addWidget(m_descView, 0);
		m_footerLayout->addWidget(m_settingView);

		m_mainLayout->addLayout(m_centralLayout);
		m_mainLayout->addLayout(m_footerLayout);
	}

	void CrazyLauncher::SetupConnections()
	{
		connect(m_settingView, &SettingsView::E_CreateAddWindow, this, &CrazyLauncher::CreateAddWindow);
		connect(m_settingView, &SettingsView::E_CreateEditWindow, this, &CrazyLauncher::CreateEditWindow);

		connect(m_projectManager, &ProjectManager::E_AddProjectToView, m_projectView, &ProjectView::AddProjectInView);
		connect(m_projectManager, &ProjectManager::E_EditProjectToView, m_projectView, &ProjectView::EditProjectInView);
		connect(m_projectManager, &ProjectManager::E_RemoveProjectToView, m_projectView, &ProjectView::RemoveProjectInView);

		connect(m_settingView, &SettingsView::E_LaunchProject, this, &CrazyLauncher::LaunchProject);
		connect(m_settingView, &SettingsView::E_RemoveProject, this, &CrazyLauncher::OnRemoveProject);

		connect(m_projectView->GetProjectList(), &QListWidget::currentItemChanged, m_descView, &DescriptionView::OnSelectedProjectChanged);
	}

	Project* CrazyLauncher::GetSelectedProjectWidget()
	{
		QListWidgetItem* item = m_projectView->GetProjectList()->currentItem();
		if (item == nullptr) return nullptr;

		ProjectWidgetItem* itemWidget = (ProjectWidgetItem*)m_projectView->GetProjectList()->itemWidget(item);
		if (itemWidget == nullptr) return nullptr;

		for (Project& project : m_projectManager->GetProjects())
		{
			if (project.s_name == itemWidget->GetProjectTitle())
			{
				return &project;
			}
		}

		return nullptr;
	}

	int CrazyLauncher::GetSelectedProjectWidgetIndex()
	{
		QListWidgetItem* item = m_projectView->GetProjectList()->currentItem();
		if (item == nullptr) return -1;

		ProjectWidgetItem* itemWidget = static_cast<ProjectWidgetItem*>(m_projectView->GetProjectList()->itemWidget(item));
		if (itemWidget == nullptr) return -1;

		for (int i = 0; i < m_projectManager->GetProjects().size(); ++i)
		{
			if (m_projectManager->GetProjects()[i].s_name == itemWidget->GetProjectTitle())
			{
				return i;
			}
		}

		return -1;
	}

	// SLOTS
	void CrazyLauncher::CreateAddWindow()
	{
		if (m_addWindow != nullptr) return;

		m_addWindow = new AddWindow(this);
		m_addWindow->resize(this->size());
		m_addWindow->show();

		connect(m_addWindow, &AddWindow::E_CloseWindow, this, &CrazyLauncher::OnCloseUtilityWindow);
		connect(m_addWindow, &AddWindow::E_AddProject, this, &CrazyLauncher::OnProjectAdded);
	}

	void CrazyLauncher::CreateEditWindow()
	{
		Project* selectedProject = GetSelectedProjectWidget();

		if (m_editWindow != nullptr || selectedProject == nullptr) return;

		m_editWindow = new EditWindow(this, selectedProject);
		m_editWindow->resize(this->size());
		m_editWindow->show();

		connect(m_editWindow, &EditWindow::E_CloseWindow, this, &CrazyLauncher::OnCloseUtilityWindow);
		//connect(m_utiltyWindow, &AddWindow::E_EditProject, this, &CrazyLauncher::OnProjectEdited);
	}

	void CrazyLauncher::OnProjectAdded(const Project& project)
	{
		m_projectManager->AddProject(project);
	}

	void CrazyLauncher::OnProjectEdited(Project* baseProjectEdited)
	{
		m_projectManager->EditProjects(baseProjectEdited);
	}

	void CrazyLauncher::LaunchProject()
	{
		Project* selectedProject = GetSelectedProjectWidget();

		if (selectedProject)
		{
			m_projectManager->LaunchProjects(selectedProject);
		}
	}

	void CrazyLauncher::OnRemoveProject()
	{
		if (GetSelectedProjectWidgetIndex() == -1) return;
		int currentProjectSelectedIndex = GetSelectedProjectWidgetIndex();
		m_projectManager->RemoveProjects(currentProjectSelectedIndex);
	}

	void CrazyLauncher::OnCloseUtilityWindow()
	{
		if (m_addWindow != nullptr)
		{
			m_addWindow = nullptr;
		}
		else
		{
			m_editWindow = nullptr;
		}
	}
}