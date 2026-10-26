#include "CrazyLauncher.h"
#include "core/ProjectController.h"
#include "core/ProjectTypeRegistry.h"
#include "core/Project.h"

#include "widget/ProjectExplorer.h"
#include "widget/ProjectDetailsView.h"
#include "widget/ProjectActionBar.h"

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
		// Link add/edit actionBar button to projectController
		connect(m_projectActionBar, &ProjectActionBar::addProject, this, &CrazyLauncher::OnAddProject);
		connect(m_projectActionBar, &ProjectActionBar::editProject, this, &CrazyLauncher::OnEditProject);

		// Link remove actionBar button to projectController
		connect(m_projectActionBar, &ProjectActionBar::removeProject, this, &CrazyLauncher::OnRemoveProject); 

		// Display in project detail view the current selected project
		connect(m_projectExplorer, &ProjectExplorer::currentProjectChange, this, &CrazyLauncher::OnChangeProjectSelected);

		// Potentiellement à changer
		/*connect(m_projectActionBar, &ProjectActionBar::E_LaunchProject, this, &CrazyLauncher::LaunchProject);*/

		// Load saves projects
		connect(m_projectController, &ProjectController::E_ClearProjectInListWidget, this, &CrazyLauncher::ClearListWidget);
		connect(m_projectController, &ProjectController::E_FillProjectInListWidget, this, &CrazyLauncher::FillListWidget);

		// Filter Projects
		connect(m_projectExplorer, &ProjectExplorer::E_FilterProjects, this, &CrazyLauncher::FilterProjects);
	}

	void CrazyLauncher::OnAddProject(const Project& project)
	{
		m_projectController->AddProject(project);
		m_projectExplorer->AddProjectInView(project);
	}

	void CrazyLauncher::OnEditProject(const Project& project)
	{
		m_projectController->EditProject();
		m_projectExplorer->EditProjectInView(project);
	}

	void CrazyLauncher::OnRemoveProject()
	{
		if (m_projectExplorer->GetProjectListCurrentRow() == -1) return;
		m_projectController->RemoveProject(m_projectExplorer->GetProjectListCurrentRow());
		m_projectExplorer->RemoveProjectInView(m_projectExplorer->GetProjectListCurrentRow());
	}

	void CrazyLauncher::LaunchProject()
	{
		if (m_currentProjectSelected == nullptr) return;
		m_projectController->LaunchProjects(m_currentProjectSelected);
	}

	void CrazyLauncher::OnChangeProjectSelected(const ProjectItem* projectItem)
	{
		if (projectItem == nullptr)
		{
			m_projectActionBar->SetCurrentProject(nullptr);
			m_projectDetailsView->SetCurrentProject(nullptr);
		}
		else
		{
			m_projectActionBar->SetCurrentProject(m_projectController->GetProjectByName(projectItem->name));
			m_projectDetailsView->SetCurrentProject(m_projectController->GetProjectByName(projectItem->name));
		}
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

			bool matches = widgetItem->GetProjectInfo()->name.contains(text, Qt::CaseInsensitive);
			
			item->setHidden(!matches);
		}
	}
}