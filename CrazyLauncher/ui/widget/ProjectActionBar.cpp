#include "ProjectActionBar.h"
#include "utils/ViewUtils.h"
#include "modal/AddModal.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QDebug>

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
		m_addBtn->setIcon(QIcon(":/new/prefix1/assets/Plus-Icon.png"));

		Cl::ViewUtils::ApplyShadowEffect(m_addBtn);
		crudLayout->addWidget(m_addBtn);

		m_editBtn = new QPushButton("Edit");
		m_editBtn->setIcon(QIcon(":/new/prefix1/assets/Edit-Icon.png"));

		Cl::ViewUtils::ApplyShadowEffect(m_editBtn);
		crudLayout->addWidget(m_editBtn);

		m_deleteBtn = new QPushButton("Delete");
		m_deleteBtn->setIcon(QIcon(":/new/prefix1/assets/Bin-Icon.png"));

		Cl::ViewUtils::ApplyShadowEffect(m_deleteBtn);
		crudLayout->addWidget(m_deleteBtn);

		m_launchBtn = new QPushButton("Launch");
		m_launchBtn->setObjectName("LaunchBtn");

		m_actionBarLayout->addStretch();
		m_actionBarLayout->addLayout(crudLayout);
		m_actionBarLayout->addStretch();

		Cl::ViewUtils::ApplyShadowEffect(m_launchBtn);
		m_actionBarLayout->addWidget(m_launchBtn);
	}

	void ProjectActionBar::InitConnections()
	{
		connect(m_addBtn, &QPushButton::pressed, this, &ProjectActionBar::OnAddWindowClicked);
		//connect(m_editBtn, &QPushButton::pressed, this, &ProjectActionBar::OnEditWindowClicked);
		connect(m_deleteBtn, &QPushButton::pressed, this, &ProjectActionBar::OnRemoveProjectClicked);
		connect(m_launchBtn, &QPushButton::pressed, this, &ProjectActionBar::OnLaunchProjectClicked);
	}

	void ProjectActionBar::OnAddWindowClicked()
	{
		if (m_addWindow != nullptr) return;

		m_addWindow = new AddModal(m_projectTypeRegistry, this);
		m_addWindow->show();

		connect(m_addWindow, &AddModal::addProject, this, &ProjectActionBar::addProject);
		connect(m_addWindow, &AddModal::rejectModal, this, [this]() { m_addWindow = nullptr; });
	}


	/*void ProjectActionBar::OnEditWindowClicked()
	{
		if (m_editWindow != nullptr || m_currentProjectSelected == nullptr) return;

		m_editWindow = new EditWindow(this, m_currentProjectSelected);
		m_editWindow->setFixedWidth(600);
		m_editWindow->show();

		connect(m_editWindow, &EditWindow::E_EditProject, this, &CrazyLauncher::OnProjectEdited);
		connect(m_editWindow, &EditWindow::E_CloseWindow, this, &CrazyLauncher::OnCloseUtilityWindow);
	}*/

	void ProjectActionBar::OnRemoveProjectClicked()
	{
		//emit E_RemoveProject();
	}

	void ProjectActionBar::OnLaunchProjectClicked()
	{
		//emit E_LaunchProject();
	}
}