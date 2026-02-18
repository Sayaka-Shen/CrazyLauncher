#include "UtilityWindow.h"
#include "ProjectManager.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QComboBox>

namespace Cl
{
	UtilityWindow::UtilityWindow(QWidget* parent)
	{
		CreateLayout();
		CreateUI();
		SetupLayout();

		SetupProjectTypeDP();
		SetupConnections();
	}

	UtilityWindow::~UtilityWindow() {}

	void UtilityWindow::CreateLayout()
	{
		m_windowLayout = new QVBoxLayout(this);
		m_buttonLayout = new QHBoxLayout();
		m_typeLayout = new QHBoxLayout();
		m_pathProjectLayout = new QHBoxLayout();
		m_pathSoftwareLayout = new QHBoxLayout();
	}

	void UtilityWindow::CreateUI()
	{
		m_name = new QLabel("Project Name :", this);
		m_nameField = new QLineEdit();

		m_desc = new QLabel("Description :", this);
		m_descField = new QLineEdit();

		m_projectType = new QLabel("Project Type :", this);
		m_projectTypeDP = new QComboBox(this);

		m_path = new QLabel("Project Path :", this);
		m_pathField = new QLineEdit();

		m_projectExplorer = new QPushButton(this);

		m_cancelBtn = new QPushButton("Cancel", this);
		m_registerBtn = new QPushButton();
	}

	void UtilityWindow::SetupLayout()
	{
		// Name
		m_windowLayout->addWidget(m_name);
		m_windowLayout->addWidget(m_nameField);

		// Description
		m_windowLayout->addWidget(m_desc);
		m_windowLayout->addWidget(m_descField);

		// Project Type
		m_windowLayout->addWidget(m_projectType);
		m_windowLayout->addWidget(m_projectTypeDP);

		// Project Path
		m_windowLayout->addWidget(m_path);
		m_pathProjectLayout->addWidget(m_pathField);
		m_pathProjectLayout->addWidget(m_projectExplorer);

		// Add to bottom layout
		m_buttonLayout->addWidget(m_cancelBtn);
		m_buttonLayout->addWidget(m_registerBtn);

		// Add to main layout
		m_windowLayout->addLayout(m_pathProjectLayout);
		m_windowLayout->addLayout(m_pathSoftwareLayout);
		m_windowLayout->addLayout(m_buttonLayout);
	}

	void UtilityWindow::SetupConnections()
	{
		connect(m_cancelBtn, &QPushButton::pressed, this, &UtilityWindow::OnCancelClicked);

		/*connect(m_directoryType, &QCheckBox::checkStateChanged, this, &AddWindow::UpdatePathState);
		//connect(m_fileType, &QCheckBox::checkStateChanged, this, &AddWindow::UpdatePathState); */

		connect(m_projectExplorer, &QPushButton::pressed, this, &UtilityWindow::OpenExplorer);
	}

	void UtilityWindow::SetupProjectTypeDP()
	{
		m_projectTypeDP->addItem("Executable", QVariant::fromValue(ProjectType::Executable));
		m_projectTypeDP->addItem("Script", QVariant::fromValue(ProjectType::Script));
		m_projectTypeDP->addItem("Unreal", QVariant::fromValue(ProjectType::Unreal));
		m_projectTypeDP->addItem("Unity", QVariant::fromValue(ProjectType::Unity));
		m_projectTypeDP->addItem("Blender", QVariant::fromValue(ProjectType::Blender));
		m_projectTypeDP->addItem("Photoshop", QVariant::fromValue(ProjectType::Photoshop));
		m_projectTypeDP->addItem("Custom", QVariant::fromValue(ProjectType::Custom));
	}
	
	void UtilityWindow::OpenExplorer()
	{
		QString path;

		if (m_projectTypeDP->currentData().value<ProjectType>() == ProjectType::Unity)
		{
			path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/C:");
		}
		else
		{
			path = QFileDialog::getOpenFileName(this, tr("Open File"), "/C:");
		}

		if (!path.isEmpty())
		{
			m_pathField->setText(path);
		}
	}

	// Utilities Functions
	void UtilityWindow::SetButtonRegisterText(QString registerText)
	{
		m_registerBtn->setText(registerText);
	}

	bool UtilityWindow::IsOneOfTheFieldEmpty()
	{
		return m_nameField->text().isEmpty() || m_descField->text().isEmpty() || m_pathField->text().isEmpty();
	}

	// Close Window
	void UtilityWindow::closeEvent(QCloseEvent* event)
	{
		QDialog::closeEvent(event);
		emit E_CloseWindow();
	}

	void UtilityWindow::OnCancelClicked()
	{
		emit E_CloseWindow();
		reject();
	}
}