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
	m_searchBar->setPlaceholderText("Rechercher....");

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

	ProjectWidgetItem* widgetItem = new ProjectWidgetItem(project.s_name, project.s_description, this);
	m_projectsList->setItemWidget(item, widgetItem);
}

void ProjectView::RemoveProjectInView(int indexProject)
{
	m_projectsList->takeItem(indexProject);
}
