#include "CrazyLauncher.h"
#include "core/ProjectController.h"
#include "core/Project.h"

#include "widget/ProjectView.h"
#include "widget/DescriptionView.h"
#include "widget/SettingsView.h"
#include "widget/ProjectWidgetItem.h"

#include "modal/AddWindow.h"
#include "modal/EditWindow.h"

#include <QListWidget>
#include <QVBoxLayout>
#include <QSettings>

namespace Cl
{
	CrazyLauncher::CrazyLauncher(QWidget* parent) : QMainWindow(parent)
	{
		setWindowIcon(QIcon(":/new/prefix1/LogoCrazyLauncher.ico"));

		InitController();
		InitUI();
		InitConnections();

		m_projectController->LoadProjects();
	}

	CrazyLauncher::~CrazyLauncher() {}

	void CrazyLauncher::InitController()
	{
		m_projectController = new ProjectController(this);
	}

	void CrazyLauncher::InitUI()
	{
		m_centralWidget = new QWidget(this);
		m_appLayout = new QVBoxLayout(m_centralWidget);
		m_appLayout->setContentsMargins(0, 0, 0, 0);
		m_appLayout->setSpacing(0);

		auto* centralLayout = new QHBoxLayout();
		m_projectView = new ProjectView(m_centralWidget);
		m_descView = new DescriptionView(m_centralWidget);
		centralLayout->addWidget(m_projectView, 2);
		centralLayout->addWidget(m_descView, 2);

		auto* footerLayout = new QHBoxLayout();
		m_settingView = new SettingsView(m_centralWidget);
		footerLayout->addWidget(m_settingView);

		m_appLayout->addLayout(centralLayout);
		m_appLayout->addLayout(footerLayout);
	}

	void CrazyLauncher::InitConnections()
	{
		// Create windows the user use to add project or edit project
		connect(m_settingView, &SettingsView::E_CreateAddWindow, this, &CrazyLauncher::CreateAddWindow);
		connect(m_settingView, &SettingsView::E_CreateEditWindow, this, &CrazyLauncher::CreateEditWindow);

		// Manage to display project in views
		connect(m_projectController, &ProjectController::E_AddProjectToView, m_projectView, &ProjectView::AddProjectInView);
		connect(m_projectController, &ProjectController::E_EditProjectToView, m_projectView, &ProjectView::EditProjectInView);
		connect(m_projectController, &ProjectController::E_RemoveProjectToView, m_projectView, &ProjectView::RemoveProjectInView);

		connect(m_projectView->GetProjectList(), &QListWidget::currentItemChanged, this, &CrazyLauncher::GetSelectedProjectWidget);
		connect(this, &CrazyLauncher::E_DisplayProject, m_descView, &DescriptionView::OnSelectedProjectChanged);
		connect(m_projectController, &ProjectController::E_EditProjectToDescriptionView, m_descView, &DescriptionView::OnSelectedProjectChanged);
		// Launch / Remove Projects
		connect(m_settingView, &SettingsView::E_LaunchProject, this, &CrazyLauncher::LaunchProject);
		connect(m_settingView, &SettingsView::E_RemoveProject, this, &CrazyLauncher::OnRemoveProject);

		// Load saves projects
		connect(m_projectController, &ProjectController::E_ClearProjectInListWidget, this, &CrazyLauncher::ClearListWidget);
		connect(m_projectController, &ProjectController::E_FillProjectInListWidget, this, &CrazyLauncher::FillListWidget);

		// Filter Projects
		connect(m_projectView, &ProjectView::E_FilterProjects, this, &CrazyLauncher::FilterProjects);
	}

	void CrazyLauncher::GetSelectedProjectWidget(QListWidgetItem* current, QListWidgetItem* previous)
	{
		if (current == nullptr) return;

		ProjectWidgetItem* itemWidget = static_cast<ProjectWidgetItem*>(m_projectView->GetProjectList()->itemWidget(current));
		if (itemWidget == nullptr) return;

		for (Project& project : m_projectController->GetProjects())
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
		m_projectController->AddProject(project);
	}

	void CrazyLauncher::OnProjectEdited(Project* baseProjectEdited)
	{
		m_projectController->EditProjects(baseProjectEdited);
	}

	void CrazyLauncher::OnRemoveProject()
	{
		if (GetSelectedProjectWidgetIndex() == -1) return;
		int currentProjectSelectedIndex = GetSelectedProjectWidgetIndex();
		m_projectController->RemoveProjects(currentProjectSelectedIndex);
	}

	void CrazyLauncher::LaunchProject()
	{
		if (m_currentProjectSelected == nullptr) return;
		m_projectController->LaunchProjects(m_currentProjectSelected);
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