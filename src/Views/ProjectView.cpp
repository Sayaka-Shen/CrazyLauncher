#include "ProjectView.h"
#include "ProjectWidgetItem.h"
#include "../Core/Project.h"

#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QSize>

namespace Cl
{
	ProjectView::ProjectView(QWidget* parent)
	{
		// Style for the whole widget
		setObjectName("ProjectView");
		setAttribute(Qt::WA_StyledBackground, true);

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
		m_searchBar->setObjectName("SearchBar");

		m_projectsList = new QListWidget(this);
	}

	void ProjectView::SetupLayout()
	{
		m_projectViewLayout->addWidget(m_searchBar);
		m_projectViewLayout->addWidget(m_projectsList);
	}

	void ProjectView::SetupConnections()
	{
		connect(m_searchBar, &QLineEdit::textChanged, this, &ProjectView::OnProjetFilter);
	}

	void ProjectView::OnProjetFilter(const QString& text)
	{
		emit E_FilterProjects(text);
	}

	void ProjectView::AddProjectInView(const Project& project)
	{
		QListWidgetItem* item = new QListWidgetItem(m_projectsList);
		item->setSizeHint(QSize(0, 65));

		ProjectWidgetItem* widgetItem = new ProjectWidgetItem(project.name, project.description, this);

		m_projectsList->setItemWidget(item, widgetItem);
	}

	void ProjectView::EditProjectInView(Project* project)
	{
		QListWidgetItem* item = m_projectsList->currentItem();
		if (item == nullptr) return;

		ProjectWidgetItem* widgetItem = static_cast<ProjectWidgetItem*>(m_projectsList->itemWidget(item));
		if (widgetItem == nullptr) return;

		if (widgetItem->GetProjectTitle() != project->name)
		{
			widgetItem->SetProjectTitle(project->name);
		}
		else if (widgetItem->GetProjectDescription() != project->description)
		{
			widgetItem->SetProjectDescription(project->description);
		}
	}

	void ProjectView::RemoveProjectInView(int indexProject)
	{
		m_projectsList->takeItem(indexProject);
	}
}