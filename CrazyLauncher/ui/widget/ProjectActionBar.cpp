#include "ProjectActionBar.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QDialog>

namespace Cl
{
	ProjectActionBar::ProjectActionBar(QWidget* parent) : QWidget(parent)
	{
		// Style for the whole widget
		setObjectName("ProjectActionBar");
		setAttribute(Qt::WA_StyledBackground, true);

		InitUI();
		InitConnections();
	}

	void ProjectActionBar::InitUI()
	{
		m_actionBarLayout = new QHBoxLayout(this);

		m_addBtn = new QPushButton("Add");
		m_addBtn->setIcon(QIcon(":/new/prefix1/assets/Plus-Icon.png"));

		m_actionBarLayout->addWidget(m_addBtn);

		m_editBtn = new QPushButton("Edit");
		m_editBtn->setIcon(QIcon(":/new/prefix1/assets/Edit-Icon.png"));

		m_actionBarLayout->addWidget(m_editBtn);

		m_deleteBtn = new QPushButton("Delete");
		m_deleteBtn->setIcon(QIcon(":/new/prefix1/assets/Bin-Icon.png"));

		m_actionBarLayout->addWidget(m_deleteBtn);

		m_launchBtn = new QPushButton("Launch");
		m_launchBtn->setObjectName("LaunchBtn");

		m_actionBarLayout->addWidget(m_launchBtn);
	}

	void ProjectActionBar::InitConnections()
	{
		connect(m_addBtn, &QPushButton::pressed, this, &ProjectActionBar::OnAddWindowClicked);
		connect(m_editBtn, &QPushButton::pressed, this, &ProjectActionBar::OnEditWindowClicked);
		connect(m_deleteBtn, &QPushButton::pressed, this, &ProjectActionBar::OnRemoveProjectClicked);
		connect(m_launchBtn, &QPushButton::pressed, this, &ProjectActionBar::OnLaunchProjectClicked);
	}

	void ProjectActionBar::OnAddWindowClicked()
	{
		emit E_CreateAddWindow();
	}

	void ProjectActionBar::OnEditWindowClicked()
	{
		emit E_CreateEditWindow();
	}

	void ProjectActionBar::OnRemoveProjectClicked()
	{
		emit E_RemoveProject();
	}

	void ProjectActionBar::OnLaunchProjectClicked()
	{
		emit E_LaunchProject();
	}
}