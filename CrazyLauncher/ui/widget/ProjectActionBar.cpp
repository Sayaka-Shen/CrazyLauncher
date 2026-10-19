#include "ProjectActionBar.h"
#include "utils/ViewUtils.h"
#include "modal/ProjectModal.h"

#include <QHBoxLayout>
#include <QPushButton>

namespace Cl
{
	ProjectActionBar::ProjectActionBar(ProjectTypeRegistry& projectTypeRegistry, QWidget* parent) : QWidget(parent), m_projectTypeRegistry(projectTypeRegistry)
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

		auto* crudLayout = new QHBoxLayout();

		m_addBtn = new QPushButton("Add");
		m_addBtn->setObjectName("ApplicationButton");
		m_addBtn->setIcon(QIcon(":/new/prefix1/assets/Plus-Icon.png"));

		Cl::ViewUtils::ApplyShadowEffect(m_addBtn);
		crudLayout->addWidget(m_addBtn);

		m_editBtn = new QPushButton("Edit");
		m_editBtn->setObjectName("ApplicationButton");
		m_editBtn->setIcon(QIcon(":/new/prefix1/assets/Edit-Icon.png"));

		Cl::ViewUtils::ApplyShadowEffect(m_editBtn);
		crudLayout->addWidget(m_editBtn);

		m_deleteBtn = new QPushButton("Delete");
		m_deleteBtn->setObjectName("ApplicationButton");
		m_deleteBtn->setIcon(QIcon(":/new/prefix1/assets/Bin-Icon.png"));

		Cl::ViewUtils::ApplyShadowEffect(m_deleteBtn);
		crudLayout->addWidget(m_deleteBtn);

		m_launchBtn = new QPushButton("Launch");
		m_launchBtn->setObjectName("HighlightButton");

		m_actionBarLayout->addStretch();
		m_actionBarLayout->addLayout(crudLayout);
		m_actionBarLayout->addStretch();

		Cl::ViewUtils::ApplyShadowEffect(m_launchBtn);
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
		m_addModal = new ProjectModal(m_projectTypeRegistry, this);
		if (m_addModal->exec() == QDialog::Accepted)
		{
			emit addProject(m_addModal->GetProject());
		}
		else
		{
			m_addModal = nullptr;
		}
	}

	void ProjectActionBar::OnEditWindowClicked()
	{
		Project project; 
		m_editModal = new ProjectModal(&project, m_projectTypeRegistry, this);
		if (m_editModal->exec() == QDialog::Accepted)
		{
			emit editProject(m_editModal->GetProject());
		}
		else
		{
			m_editModal = nullptr;
		}
	}

	void ProjectActionBar::OnRemoveProjectClicked()
	{
		//emit E_RemoveProject();
	}

	void ProjectActionBar::OnLaunchProjectClicked()
	{
		//emit E_LaunchProject();
	}
}