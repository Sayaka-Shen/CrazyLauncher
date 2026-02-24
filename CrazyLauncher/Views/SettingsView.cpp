#include "SettingsView.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QDialog>

namespace Cl
{
	SettingsView::SettingsView(QWidget* parent)
	{
		// Style for the whole widget
		setObjectName("SettingsView");
		setAttribute(Qt::WA_StyledBackground, true);

		CreateLayout();
		CreateUI();
		SetupLayout();
		SetupConnections();
	}

	SettingsView::~SettingsView() {}

	void SettingsView::CreateUI()
	{
		m_addBtn = new QPushButton(this);
		m_addBtn->setText("Add");

		m_editBtn = new QPushButton(this);
		m_editBtn->setText("Edit");

		m_deleteBtn = new QPushButton(this);
		m_deleteBtn->setText("Delete");

		m_launchBtn = new QPushButton(this);
		m_launchBtn->setText("Launch");
	}

	void SettingsView::CreateLayout()
	{
		m_settingsLayout = new QHBoxLayout(this);
	}

	void SettingsView::SetupLayout()
	{
		//m_settingsLayout->addStretch(1);
		m_settingsLayout->addWidget(m_addBtn);
		m_settingsLayout->addWidget(m_editBtn);
		m_settingsLayout->addWidget(m_deleteBtn);
		m_settingsLayout->addWidget(m_launchBtn);
	}

	void SettingsView::SetupConnections()
	{
		connect(m_addBtn, &QPushButton::pressed, this, &SettingsView::OnAddWindowClicked);
		connect(m_editBtn, &QPushButton::pressed, this, &SettingsView::OnEditWindowClicked);
		connect(m_deleteBtn, &QPushButton::pressed, this, &SettingsView::OnRemoveProjectClicked);
		connect(m_launchBtn, &QPushButton::pressed, this, &SettingsView::OnLaunchProjectClicked);
	}

	void SettingsView::OnAddWindowClicked()
	{
		emit E_CreateAddWindow();
	}

	void SettingsView::OnEditWindowClicked()
	{
		emit E_CreateEditWindow();
	}

	void SettingsView::OnRemoveProjectClicked()
	{
		emit E_RemoveProject();
	}

	void SettingsView::OnLaunchProjectClicked()
	{
		emit E_LaunchProject();
	}
}