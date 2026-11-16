#include "ProjectExplorer.h"
#include "ProjectWidgetItem.h"

#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QDebug>

namespace Cl
{
	ProjectExplorer::ProjectExplorer(QWidget* parent) : QWidget(parent)
	{
		setAttribute(Qt::WA_StyledBackground, true);

		InitUI();
		InitConnections();
	}

	QListWidget* ProjectExplorer::GetProjectList()
	{
		return m_projectsList;
	}

	int ProjectExplorer::GetProjectListCurrentRow()
	{
		return GetProjectList()->currentRow();
	}

	void ProjectExplorer::InitUI()
	{
		m_projectViewLayout = new QVBoxLayout(this);
		m_projectViewLayout->setContentsMargins(0, 0, 0, 0);

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
		connect(m_projectsList, &QListWidget::currentItemChanged, this, &ProjectExplorer::OnProjectSelected);
	}

	void ProjectExplorer::OnProjetFilter(const QString& text)
	{
		emit filterProjects(text);
	}

	void ProjectExplorer::OnProjectSelected(QListWidgetItem* current, QListWidgetItem* previous)
	{
		if (current == nullptr)
		{
			emit currentProjectChange(nullptr);
			return;
		}

		QWidget* item = m_projectsList->itemWidget(current);
		if (item == nullptr) return;

		auto* widgetItem = static_cast<ProjectWidgetItem*>(item);

		emit currentProjectChange(widgetItem->GetProjectInfo());
	}

	void ProjectExplorer::OnProjectDoubleClicked()
	{
		emit launchProject(m_currentProject);
	}

	void ProjectExplorer::AddProjectInView(const Project& project)
	{
		QListWidgetItem* item = new QListWidgetItem(m_projectsList);
		item->setSizeHint(QSize(0, 65));

		ProjectWidgetItem* widgetItem = new ProjectWidgetItem();
		widgetItem->SetProjectInfo(project.name, project.description);
		connect(widgetItem, &ProjectWidgetItem::onDoubleClicked, this, &ProjectExplorer::OnProjectDoubleClicked);

		m_projectsList->setItemWidget(item, widgetItem);
		m_projectsList->setCurrentItem(item);
	}

	void ProjectExplorer::EditProjectInView(const Project& project)
	{
		QListWidgetItem* item = m_projectsList->currentItem();
		if (item == nullptr) return;

		ProjectWidgetItem* widgetItem = static_cast<ProjectWidgetItem*>(m_projectsList->itemWidget(item));
		if (widgetItem == nullptr) return;

		widgetItem->SetProjectInfo(project.name, project.description);
	}

	void ProjectExplorer::RemoveProjectInView(int indexProject)
	{
		QListWidgetItem* item = m_projectsList->takeItem(indexProject);
		delete item;
	}

	void ProjectExplorer::SetCurrentProject(const Project* currentProject)
	{
		m_currentProject = currentProject;
	}
}