#include "MainWidget.h"

#include "core/ProjectController.h"
#include "ProjectWidgetItem.h"
#include "CategoryWidget.h"
#include "ProjectView.h"
#include "DescriptionView.h"
#include "modal/AddWindow.h"
#include "modal/EditWindow.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>


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
		m_categoryWidget = new CategoryWidget();
		m_projectWidget = new ProjectView();
		m_descWidget = new DescriptionView();

		m_mainLayout = new QHBoxLayout(this);
		m_categoryLayout = new QHBoxLayout();
		m_projectLayout = new QHBoxLayout();
		m_descLayout = new QVBoxLayout();

		m_mainLayout->setContentsMargins(0, 0, 0, 0);
		m_categoryWidget->setFixedWidth(220);
		m_descWidget->setFixedWidth(300);

		m_categoryLayout->addWidget(m_categoryWidget);
		m_projectLayout->addWidget(m_projectWidget);
		m_descLayout->addWidget(m_descWidget);

		m_mainLayout->addLayout(m_categoryLayout);
		m_mainLayout->addLayout(m_projectLayout);
		m_mainLayout->addLayout(m_descLayout);
	}

	void MainWidget::InitController()
	{
		m_projectController = new ProjectController(this);
	}


	void MainWidget::InitConnections()
	{
		// Manage to display project in views
		connect(m_projectController, &ProjectController::E_AddProjectToView, m_projectWidget, &ProjectView::AddProjectInView);
		connect(m_projectController, &ProjectController::E_EditProjectToView, m_projectWidget, &ProjectView::EditProjectInView);
		connect(m_projectController, &ProjectController::E_RemoveProjectToView, m_projectWidget, &ProjectView::RemoveProjectInView);

		connect(m_projectWidget->GetProjectList(), &QListWidget::currentItemChanged, this, &MainWidget::GetSelectedProjectWidget);
		connect(this, &MainWidget::E_DisplayProject, m_descWidget, &DescriptionView::OnSelectedProjectChanged);
		connect(m_projectController, &ProjectController::E_EditProjectToDescriptionView, m_descWidget, &DescriptionView::OnSelectedProjectChanged);

		// Load saves projects
		connect(m_projectController, &ProjectController::E_ClearProjectInListWidget, this, &MainWidget::ClearListWidget);
		connect(m_projectController, &ProjectController::E_FillProjectInListWidget, this, &MainWidget::FillListWidget);

		// Filter Projects
		connect(m_projectWidget, &ProjectView::E_FilterProjects, this, &MainWidget::FilterProjects);
	}

	void MainWidget::GetSelectedProjectWidget(QListWidgetItem* current, QListWidgetItem* previous)
	{
		if (current == nullptr) return;

		ProjectWidgetItem* itemWidget = static_cast<ProjectWidgetItem*>(m_projectWidget->GetProjectList()->itemWidget(current));
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
		return m_projectWidget->GetProjectList()->currentRow();
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
		m_projectWidget->GetProjectList()->clear();
	}

	void MainWidget::FillListWidget(Project& project)
	{
		m_projectWidget->AddProjectInView(project);
	}

	void MainWidget::FilterProjects(const QString& text)
	{
		for (int i = 0; i < m_projectWidget->GetProjectList()->count(); ++i)
		{
			QListWidgetItem* item = m_projectWidget->GetProjectList()->item(i);
			ProjectWidgetItem* widgetItem = static_cast<ProjectWidgetItem*>(m_projectWidget->GetProjectList()->itemWidget(item));

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