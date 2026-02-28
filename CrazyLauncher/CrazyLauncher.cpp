#include "CrazyLauncher.h"
#include "Core/ProjectManager.h"
#include "Core/Project.h"

#include "Views/ProjectView.h"
#include "Views/DescriptionView.h"
#include "Views/SettingsView.h"
#include "Views/ProjectWidgetItem.h"

#include "Views/Windows/AddWindow.h"
#include "Views/Windows/EditWindow.h"

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

		m_projectManager->LoadProjects();
	}

	CrazyLauncher::~CrazyLauncher() {}

	void CrazyLauncher::CreateController()
	{
		m_projectManager = new ProjectManager(this);
	}

	void CrazyLauncher::CreateLayout()
	{
		m_mainLayout = new QVBoxLayout(m_centralWidget);
		m_centralLayout = new QHBoxLayout();
		m_footerLayout = new QHBoxLayout();

		m_mainLayout->setContentsMargins(0, 0, 0, 0);
		m_mainLayout->setSpacing(0);
	}

	void CrazyLauncher::CreateUI()
	{
		m_projectView = new ProjectView(m_centralWidget);
		m_descView = new DescriptionView(m_centralWidget);
		m_settingView = new SettingsView(m_centralWidget);
	}

	void CrazyLauncher::SetupLayout()
	{
		m_centralLayout->addWidget(m_projectView, 2);
		m_centralLayout->addWidget(m_descView, 2);
		m_footerLayout->addWidget(m_settingView);

		m_mainLayout->addLayout(m_centralLayout);
		m_mainLayout->addLayout(m_footerLayout);
	}

	void CrazyLauncher::SetupConnections()
	{
		// Create windows the user use to add project or edit project
		connect(m_settingView, &SettingsView::E_CreateAddWindow, this, &CrazyLauncher::CreateAddWindow);
		connect(m_settingView, &SettingsView::E_CreateEditWindow, this, &CrazyLauncher::CreateEditWindow);

		// Manage to display project in views
		connect(m_projectManager, &ProjectManager::E_AddProjectToView, m_projectView, &ProjectView::AddProjectInView);
		connect(m_projectManager, &ProjectManager::E_EditProjectToView, m_projectView, &ProjectView::EditProjectInView);
		connect(m_projectManager, &ProjectManager::E_RemoveProjectToView, m_projectView, &ProjectView::RemoveProjectInView);

		connect(m_projectView->GetProjectList(), &QListWidget::currentItemChanged, this, &CrazyLauncher::GetSelectedProjectWidget);
		connect(this, &CrazyLauncher::E_DisplayProject, m_descView, &DescriptionView::OnSelectedProjectChanged);
		connect(m_projectManager, &ProjectManager::E_EditProjectToDescriptionView, m_descView, &DescriptionView::OnSelectedProjectChanged);

		// Launch / Remove Projects
		connect(m_settingView, &SettingsView::E_LaunchProject, this, &CrazyLauncher::LaunchProject);
		connect(m_settingView, &SettingsView::E_RemoveProject, this, &CrazyLauncher::OnRemoveProject);

		// Load saves projects
		connect(m_projectManager, &ProjectManager::E_ClearProjectInListWidget, this, &CrazyLauncher::ClearListWidget);
		connect(m_projectManager, &ProjectManager::E_FillProjectInListWidget, this, &CrazyLauncher::FillListWidget);

		// Filter Projects
		connect(m_projectView, &ProjectView::E_FilterProjects, this, &CrazyLauncher::FilterProjects);
	}

	void CrazyLauncher::GetSelectedProjectWidget(QListWidgetItem* current, QListWidgetItem* previous)
	{
		if (current == nullptr) return;

		ProjectWidgetItem* itemWidget = static_cast<ProjectWidgetItem*>(m_projectView->GetProjectList()->itemWidget(current));
		if (itemWidget == nullptr) return;

		for (Project& project : m_projectManager->GetProjects())
		{
			if (project.name == itemWidget->GetProjectTitle())
			{
				emit E_DisplayProject(project);
				m_currentProjectSelected = &project; 
			}
		}
	}

	int CrazyLauncher::GetSelectedProjectWidgetIndex()
	{
		return m_projectView->GetProjectList()->currentRow();
	}

	// SLOTS
	void CrazyLauncher::CreateAddWindow()
	{
		if (m_addWindow != nullptr) return;

		m_addWindow = new AddWindow(this);
		m_addWindow->setFixedWidth(600);
		m_addWindow->show();

		connect(m_addWindow, &AddWindow::E_AddProject, this, &CrazyLauncher::OnProjectAdded);
		connect(m_addWindow, &AddWindow::E_CloseWindow, this, &CrazyLauncher::OnCloseUtilityWindow);
	}

	void CrazyLauncher::CreateEditWindow()
	{
		if (m_editWindow != nullptr || m_currentProjectSelected == nullptr) return;

		m_editWindow = new EditWindow(this, m_currentProjectSelected);
		m_editWindow->setFixedWidth(600);
		m_editWindow->show();

		connect(m_editWindow, &EditWindow::E_EditProject, this, &CrazyLauncher::OnProjectEdited);
		connect(m_editWindow, &EditWindow::E_CloseWindow, this, &CrazyLauncher::OnCloseUtilityWindow);
	}

	void CrazyLauncher::OnProjectAdded(const Project& project)
	{
		m_projectManager->AddProject(project);
	}

	void CrazyLauncher::OnProjectEdited(Project* baseProjectEdited)
	{
		m_projectManager->EditProjects(baseProjectEdited);
	}

	void CrazyLauncher::OnRemoveProject()
	{
		if (GetSelectedProjectWidgetIndex() == -1) return;
		int currentProjectSelectedIndex = GetSelectedProjectWidgetIndex();
		m_projectManager->RemoveProjects(currentProjectSelectedIndex);
	}

	void CrazyLauncher::LaunchProject()
	{
		if (m_currentProjectSelected == nullptr) return;
		m_projectManager->LaunchProjects(m_currentProjectSelected);
	}

	void CrazyLauncher::ClearListWidget()
	{
		m_projectView->GetProjectList()->clear();
	}

	void CrazyLauncher::FillListWidget(Project& project)
	{
		m_projectView->AddProjectInView(project);
	}

	void CrazyLauncher::FilterProjects(const QString& text)
	{
		for (int i = 0; i < m_projectView->GetProjectList()->count(); ++i)
		{
			QListWidgetItem* item = m_projectView->GetProjectList()->item(i);
			ProjectWidgetItem* widgetItem = static_cast<ProjectWidgetItem*>(m_projectView->GetProjectList()->itemWidget(item));

			bool matches = widgetItem->GetProjectTitle().contains(text, Qt::CaseInsensitive);
			
			item->setHidden(!matches);
		}
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