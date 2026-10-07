#include "ProjectTopWidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

namespace Cl
{
	ProjectTopWidget::ProjectTopWidget(Category currentCategory, QWidget* parent /*= nullptr*/) : m_currentCategory(currentCategory), QWidget(parent)
	{
		InitUI();
	}

	void ProjectTopWidget::InitUI()
	{
		m_mainLayout = new QVBoxLayout(this);

		auto* headerSection = new QHBoxLayout();

		auto* titleSection = new QHBoxLayout();

		QIcon categoryIcon(m_currentCategory.iconPath);
		m_categoryIcon = new QLabel();
		m_categoryIcon->setPixmap(categoryIcon.pixmap(32, 32));

		auto* categoryInfo = new QVBoxLayout();
		m_categoryName = new QLabel(m_currentCategory.name);
		m_numberOfProjects = new QLabel(QString::number(m_currentCategory.projects.size()) + " Projects");
		titleSection->addWidget(m_categoryIcon);
		titleSection->addLayout(categoryInfo);

		auto* actionLayout = new QHBoxLayout();
		m_addProjectButton = new QPushButton("Add Project");
		actionLayout->addWidget(m_addProjectButton);

		headerSection->addLayout(titleSection);
		headerSection->addLayout(actionLayout);

		m_searchBar = new QLineEdit(this);
		m_searchBar->setPlaceholderText("Search....");
		m_searchBar->setObjectName("SearchBar");

		m_mainLayout->addLayout(headerSection);
		m_mainLayout->addWidget(m_searchBar);
	}
}