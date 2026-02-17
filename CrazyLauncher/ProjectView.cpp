#include "ProjectView.h"
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include "ProjectWidgetItem.h"
#include <QSize>
#include "Project.h"

ProjectView::ProjectView(QWidget* parent)
{
	CreateLayout();
	CreateUI();
	SetupLayout();
	SetupConnections();

	m_projectsList->setSelectionMode(QAbstractItemView::SingleSelection);
}

ProjectView::~ProjectView() {}

QListWidget* ProjectView::GetProjectList()
{
	return m_projectsList;
}

void ProjectView::CreateLayout()
{
	m_projectViewLayout = new QVBoxLayout(this);
}

void ProjectView::CreateUI()
{
	m_searchBar = new QLineEdit(this);
	m_searchBar->setPlaceholderText("Search....");

	m_projectsList = new QListWidget(this);
}

void ProjectView::SetupLayout()
{
	m_projectViewLayout->addWidget(m_searchBar);
	m_projectViewLayout->addWidget(m_projectsList);
}

void ProjectView::SetupConnections()
{
}

void ProjectView::AddProjectInView(const Project& project)
{
	QListWidgetItem* item = new QListWidgetItem(m_projectsList);
	item->setSizeHint(QSize(0, 56));

	ProjectWidgetItem* widgetItem = new ProjectWidgetItem(project.s_name, project.s_description, project.s_path, project.s_software, this);
	m_projectsList->setItemWidget(item, widgetItem);
}

void ProjectView::EditProjectInView(Project* project)
{
	QListWidgetItem* item = m_projectsList->currentItem();
	if (item == nullptr) return;

	ProjectWidgetItem* widgetItem = (ProjectWidgetItem*)m_projectsList->itemWidget(item);
	if (widgetItem == nullptr) return;

	if (widgetItem->GetProjectTitle() != project->s_name)
	{
		widgetItem->SetProjectTitle(project->s_name);
		widgetItem->SetProjectDescription(project->s_description);
		widgetItem->SetProjectPath(project->s_path);
	}
}

void ProjectView::RemoveProjectInView(int indexProject)
{
	m_projectsList->takeItem(indexProject);
}

