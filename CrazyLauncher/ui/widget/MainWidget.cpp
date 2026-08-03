#include "MainWidget.h"
#include "ProjectWidgetItem.h"

#include <QListWidget>


namespace Cl {

	MainWidget::MainWidget(QWidget* parent /*= nullptr*/) : QWidget(parent)
	{
		InitUI();
		InitController();
		InitConnections();

		m_projectController->LoadProjects();
	}

	MainWidget::~MainWidget() { }

	void MainWidget::InitUI()
	{
		m_projectView = new ProjectView();
		m_descView = new DescriptionView();
		m_settingView = new SettingsView();

		m_mainLayout = new QVBoxLayout(this);
		m_centralLayout = new QHBoxLayout();
		m_footerLayout = new QHBoxLayout();

		m_mainLayout->setContentsMargins(0, 0, 0, 0);

		m_centralLayout->addWidget(m_projectView, 2);
		m_centralLayout->addWidget(m_descView, 2);
		m_footerLayout->addWidget(m_settingView);

		m_mainLayout->addLayout(m_centralLayout);
		m_mainLayout->addLayout(m_footerLayout);
	}

	void MainWidget::InitController()
	{
		m_projectController = new ProjectController(this);
	}


	void MainWidget::InitConnections()
	{
		// Create windows the user use to add project or edit project
		connect(m_settingView, &SettingsView::E_CreateAddWindow, this, &MainWidget::CreateAddWindow);
		connect(m_settingView, &SettingsView::E_CreateEditWindow, this, &MainWidget::CreateEditWindow);

		// Manage to display project in views
		connect(m_projectController, &ProjectController::E_AddProjectToView, m_projectView, &ProjectView::AddProjectInView);
		connect(m_projectController, &ProjectController::E_EditProjectToView, m_projectView, &ProjectView::EditProjectInView);
		connect(m_projectController, &ProjectController::E_RemoveProjectToView, m_projectView, &ProjectView::RemoveProjectInView);

		connect(m_projectView->GetProjectList(), &QListWidget::currentItemChanged, this, &MainWidget::GetSelectedProjectWidget);
		connect(this, &MainWidget::E_DisplayProject, m_descView, &DescriptionView::OnSelectedProjectChanged);
		connect(m_projectController, &ProjectController::E_EditProjectToDescriptionView, m_descView, &DescriptionView::OnSelectedProjectChanged);

		// Launch / Remove Projects
		connect(m_settingView, &SettingsView::E_LaunchProject, this, &MainWidget::LaunchProject);
		connect(m_settingView, &SettingsView::E_RemoveProject, this, &MainWidget::OnRemoveProject);

		// Load saves projects
		connect(m_projectController, &ProjectController::E_ClearProjectInListWidget, this, &MainWidget::ClearListWidget);
		connect(m_projectController, &ProjectController::E_FillProjectInListWidget, this, &MainWidget::FillListWidget);

		// Filter Projects
		connect(m_projectView, &ProjectView::E_FilterProjects, this, &MainWidget::FilterProjects);
	}



	void MainWidget::GetSelectedProjectWidget(QListWidgetItem* current, QListWidgetItem* previous)
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

	int MainWidget::GetSelectedProjectWidgetIndex()
	{
		return m_projectView->GetProjectList()->currentRow();
	}

	// SLOTS
	void MainWidget::CreateAddWindow()
	{
		if (m_addWindow != nullptr) return;

		m_addWindow = new AddWindow(this);
		m_addWindow->setFixedWidth(600);
		m_addWindow->show();

		connect(m_addWindow, &AddWindow::E_AddProject, this, &MainWidget::OnProjectAdded);
		connect(m_addWindow, &AddWindow::E_CloseWindow, this, &MainWidget::OnCloseUtilityWindow);
	}

	void MainWidget::CreateEditWindow()
	{
		if (m_editWindow != nullptr || m_currentProjectSelected == nullptr) return;

		m_editWindow = new EditWindow(this, m_currentProjectSelected);
		m_editWindow->setFixedWidth(600);
		m_editWindow->show();

		connect(m_editWindow, &EditWindow::E_EditProject, this, &MainWidget::OnProjectEdited);
		connect(m_editWindow, &EditWindow::E_CloseWindow, this, &MainWidget::OnCloseUtilityWindow);
	}

	void MainWidget::OnProjectAdded(const Project& project)
	{
		m_projectController->AddProject(project);
	}

	void MainWidget::OnProjectEdited(Project* baseProjectEdited)
	{
		m_projectController->EditProjects(baseProjectEdited);
	}

	void MainWidget::OnRemoveProject()
	{
		if (GetSelectedProjectWidgetIndex() == -1) return;
		int currentProjectSelectedIndex = GetSelectedProjectWidgetIndex();
		m_projectController->RemoveProjects(currentProjectSelectedIndex);
	}

	void MainWidget::LaunchProject()
	{
		if (m_currentProjectSelected == nullptr) return;
		m_projectController->LaunchProjects(m_currentProjectSelected);
	}

	void MainWidget::ClearListWidget()
	{
		m_projectView->GetProjectList()->clear();
	}

	void MainWidget::FillListWidget(Project& project)
	{
		m_projectView->AddProjectInView(project);
	}

	void MainWidget::FilterProjects(const QString& text)
	{
		for (int i = 0; i < m_projectView->GetProjectList()->count(); ++i)
		{
			QListWidgetItem* item = m_projectView->GetProjectList()->item(i);
			ProjectWidgetItem* widgetItem = static_cast<ProjectWidgetItem*>(m_projectView->GetProjectList()->itemWidget(item));

			bool matches = widgetItem->GetProjectTitle().contains(text, Qt::CaseInsensitive);

			item->setHidden(!matches);
		}
	}

	void MainWidget::OnCloseUtilityWindow()
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