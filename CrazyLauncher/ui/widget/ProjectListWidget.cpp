#include "ProjectListWidget.h"
#include "ProjectWidgetItem.h"

#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QSize>

namespace Cl
{
	ProjectListWidget::ProjectListWidget(Category currentCategory, QWidget* parent)
		: m_currentCategory(currentCategory), QWidget(parent)
	{
		// Style for the whole widget
		setObjectName("ProjectListWidget");
		setAttribute(Qt::WA_StyledBackground, true);
		
		InitUI();

		m_projectsList->setSelectionMode(QAbstractItemView::SingleSelection);
	}

	QListWidget* ProjectListWidget::GetProjectList()
	{
		return m_projectsList;
	}

	void ProjectListWidget::InitUI()
	{
		m_projectListWidgetLayout = new QVBoxLayout(this);
		m_projectsList = new QListWidget(this);
		m_projectListWidgetLayout->addWidget(m_projectsList);
	}

	void ProjectListWidget::AddProjectInView(const Project& project)
	{
		QListWidgetItem* item = new QListWidgetItem(m_projectsList);
		item->setSizeHint(QSize(0, 65));

		ProjectWidgetItem* widgetItem = new ProjectWidgetItem(project.name, project.description, this);

		m_projectsList->setItemWidget(item, widgetItem);
	}

	void ProjectListWidget::EditProjectInView(Project* project)
	{
		QListWidgetItem* item = m_projectsList->currentItem();
		if (item == nullptr) return;

		ProjectWidgetItem* widgetItem = static_cast<ProjectWidgetItem*>(m_projectsList->itemWidget(item));
		if (widgetItem == nullptr) return;

		widgetItem->SetProjectTitle(project->name);
		widgetItem->SetProjectDescription(project->description);
	}

	void ProjectListWidget::RemoveProjectInView(int indexProject)
	{
		QListWidgetItem* item = m_projectsList->takeItem(indexProject);
		delete item;
	}
}