#include "CrazyLauncher.h"
#include "core/ProjectController.h"
#include "core/ProjectTypeRegistry.h"
#include "core/Project.h"

#include "widget/ProjectExplorer.h"
#include "widget/ProjectDetailsView.h"
#include "widget/ProjectActionBar.h"
#include "widget/ProjectWidgetItem.h"

#include <QListWidget>
#include <QVBoxLayout>
#include <QSettings>

namespace Cl
{
	CrazyLauncher::CrazyLauncher(QWidget* parent) : QMainWindow(parent)
	{
		setWindowIcon(QIcon(":/new/prefix1/assets/LogoCrazyLauncher.ico"));

		InitController();
		InitUI();
		InitConnections();

		m_projectController->LoadProjects();
	}

	void CrazyLauncher::InitController()
	{
		m_projectController = new ProjectController(this);
		m_projectTypeRegistry = ProjectTypeRegistry();
	}

	void CrazyLauncher::InitUI()
	{
		m_centralWidget = new QWidget(this);
		setCentralWidget(m_centralWidget);

		m_appLayout = new QVBoxLayout(m_centralWidget);
		m_appLayout->setContentsMargins(0, 0, 0, 0);
		m_appLayout->setSpacing(0);

		auto* centralLayout = new QHBoxLayout();
		m_projectExplorer = new ProjectExplorer();
		centralLayout->addWidget(m_projectExplorer, 2);
		m_projectDetailsView = new ProjectDetailsView();
		centralLayout->addWidget(m_projectDetailsView, 1);

		m_appLayout->addLayout(centralLayout);

		m_projectActionBar = new ProjectActionBar(m_projectTypeRegistry);

		m_appLayout->addWidget(m_projectActionBar);
	}

	void CrazyLauncher::InitConnections()
	{
		// Create windows the user use to add project or edit project
		/*connect(m_projectActionBar, &ProjectActionBar::E_CreateAddWindow, this, &CrazyLauncher::CreateAddWindow);
		connect(m_projectActionBar, &ProjectActionBar::E_CreateEditWindow, this, &CrazyLauncher::CreateEditWindow);*/

		// Manage to display project in views
		connect(m_projectController, &ProjectController::E_AddProjectToView, m_projectExplorer, &ProjectExplorer::AddProjectInView);
		connect(m_projectController, &ProjectController::E_EditProjectToView, m_projectExplorer, &ProjectExplorer::EditProjectInView);
		connect(m_projectController, &ProjectController::E_RemoveProjectToView, m_projectExplorer, &ProjectExplorer::RemoveProjectInView);

		connect(m_projectExplorer->GetProjectList(), &QListWidget::currentItemChanged, this, &CrazyLauncher::GetSelectedProjectWidget);
		connect(this, &CrazyLauncher::E_DisplayProject, m_projectDetailsView, &ProjectDetailsView::OnSelectedProjectChanged);
		connect(m_projectController, &ProjectController::E_EditProjectToDescriptionView, m_projectDetailsView, &ProjectDetailsView::OnSelectedProjectChanged);
		// Launch / Remove Projects
		/*connect(m_projectActionBar, &ProjectActionBar::E_LaunchProject, this, &CrazyLauncher::LaunchProject);
		connect(m_projectActionBar, &ProjectActionBar::E_RemoveProject, this, &CrazyLauncher::OnRemoveProject);*/

		// Load saves projects
		connect(m_projectController, &ProjectController::E_ClearProjectInListWidget, this, &CrazyLauncher::ClearListWidget);
		connect(m_projectController, &ProjectController::E_FillProjectInListWidget, this, &CrazyLauncher::FillListWidget);

		// Filter Projects
		connect(m_projectExplorer, &ProjectExplorer::E_FilterProjects, this, &CrazyLauncher::FilterProjects);
	}

	void CrazyLauncher::GetSelectedProjectWidget(QListWidgetItem* current, QListWidgetItem* previous)
	{
		if (current == nullptr) return;

		ProjectWidgetItem* itemWidget = static_cast<ProjectWidgetItem*>(m_projectExplorer->GetProjectList()->itemWidget(current));
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
		return m_projectExplorer->GetProjectList()->currentRow();
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
		m_projectExplorer->GetProjectList()->clear();
	}

	void CrazyLauncher::FillListWidget(Project& project)
	{
		m_projectExplorer->AddProjectInView(project);
	}

	void CrazyLauncher::FilterProjects(const QString& text)
	{
		for (int i = 0; i < m_projectExplorer->GetProjectList()->count(); ++i)
		{
			QListWidgetItem* item = m_projectExplorer->GetProjectList()->item(i);
			ProjectWidgetItem* widgetItem = static_cast<ProjectWidgetItem*>(m_projectExplorer->GetProjectList()->itemWidget(item));

			bool matches = widgetItem->GetProjectTitle().contains(text, Qt::CaseInsensitive);
			
			item->setHidden(!matches);
		}
	}

	/*void CrazyLauncher::OnCloseUtilityWindow()
	{
		if (m_addWindow != nullptr)
		{
			m_addWindow = nullptr;
		}
		else
		{
			m_editWindow = nullptr;
		}
	}*/
}