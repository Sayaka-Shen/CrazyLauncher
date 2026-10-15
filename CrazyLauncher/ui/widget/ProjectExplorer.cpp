#include "ProjectExplorer.h"
#include "ProjectWidgetItem.h"
#include "core/Project.h"

#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QSize>

namespace Cl
{
	ProjectExplorer::ProjectExplorer(QWidget* parent) : QWidget(parent)
	{
		setObjectName("ProjectExplorer");
		setAttribute(Qt::WA_StyledBackground, true);

		InitUI();
		InitConnections();
	}

	QListWidget* ProjectExplorer::GetProjectList()
	{
		return m_projectsList;
	}

	void ProjectExplorer::InitUI()
	{
		m_projectViewLayout = new QVBoxLayout(this);

		m_searchBar = new QLineEdit();
		m_searchBar->setPlaceholderText("Search....");
		m_searchBar->setObjectName("SearchBar");

		m_projectsList = new QListWidget();
		m_projectsList->setSelectionMode(QAbstractItemView::SingleSelection);

		m_projectViewLayout->addWidget(m_searchBar);
		m_projectViewLayout->addWidget(m_projectsList);
	}

	void ProjectExplorer::InitConnections()
	{
		connect(m_searchBar, &QLineEdit::textChanged, this, &ProjectExplorer::OnProjetFilter);
	}

	void ProjectExplorer::OnProjetFilter(const QString& text)
	{
		emit E_FilterProjects(text);
	}

	void ProjectExplorer::AddProjectInView(const Project& project)
	{
		QListWidgetItem* item = new QListWidgetItem(m_projectsList);
		item->setSizeHint(QSize(0, 65));

		ProjectWidgetItem* widgetItem = new ProjectWidgetItem(project.name, project.description, this);

		m_projectsList->setItemWidget(item, widgetItem);
	}

	void ProjectExplorer::EditProjectInView(Project* project)
	{
		QListWidgetItem* item = m_projectsList->currentItem();
		if (item == nullptr) return;

		ProjectWidgetItem* widgetItem = static_cast<ProjectWidgetItem*>(m_projectsList->itemWidget(item));
		if (widgetItem == nullptr) return;

		widgetItem->SetProjectTitle(project->name);
		widgetItem->SetProjectDescription(project->description);
	}

	void ProjectExplorer::RemoveProjectInView(int indexProject)
	{
		QListWidgetItem* item = m_projectsList->takeItem(indexProject);
		delete item;
	}
}