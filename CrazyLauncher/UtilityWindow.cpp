#include "UtilityWindow.h"
#include "ProjectManager.h"
#include "Project.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QComboBox>
#include <QStandardPaths>

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

		m_softwareExe = new QLabel("Software Used :", this);
		m_softwarePathField = new QLineEdit();
		m_softwareExplorer = new QPushButton(this);
		HideSoftwarePath();

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
		m_windowLayout->addLayout(m_pathProjectLayout);

		// Software Path
		m_windowLayout->addWidget(m_softwareExe);
		m_pathSoftwareLayout->addWidget(m_softwarePathField);
		m_pathSoftwareLayout->addWidget(m_softwareExplorer);
		m_windowLayout->addLayout(m_pathSoftwareLayout);

		// Add to bottom layout
		m_buttonLayout->addWidget(m_cancelBtn);
		m_buttonLayout->addWidget(m_registerBtn);

		// Add to main layout
		m_windowLayout->addLayout(m_buttonLayout);
	}

	void UtilityWindow::SetupConnections()
	{
		connect(m_cancelBtn, &QPushButton::pressed, this, &UtilityWindow::OnCancelClicked);

		connect(m_projectTypeDP, &QComboBox::currentIndexChanged, this, &UtilityWindow::CheckProjectType);
		
		connect(m_projectExplorer, &QPushButton::pressed, this, &UtilityWindow::FindProject);
		connect(m_softwareExplorer, &QPushButton::pressed, this, &UtilityWindow::FindSoftware);
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

	// Utilities Functions
	void UtilityWindow::SetButtonRegisterText(QString registerText)
	{
		m_registerBtn->setText(registerText);
	}

	bool UtilityWindow::IsOneOfTheFieldEmpty()
	{
		return m_nameField->text().isEmpty() || m_descField->text().isEmpty() || m_pathField->text().isEmpty();
	}

	bool UtilityWindow::HasOneOfTheFieldChanged(const Project& project) 
	{
		return project.s_name != m_nameField->text() || project.s_description != m_descField->text() || project.s_path != m_pathField->text() || project.s_softwareExe != m_softwarePathField->text();
	}
	
	void UtilityWindow::FindProject()
	{
		QString path;

		if (m_projectTypeDP->currentData().value<ProjectType>() == ProjectType::Unity)
		{
			path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
		}
		else
		{
			path = QFileDialog::getOpenFileName(this, tr("Open File"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
		}

		if (!path.isEmpty())
		{
			m_pathField->setText(path);
		}
	}

	void UtilityWindow::FindSoftware()
	{
		QString path = QFileDialog::getOpenFileName(this, tr("Open File"), QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation), tr("Executables (*.exe)"));

		if (!path.isEmpty())
		{
			m_softwarePathField->setText(path);
		}
	}

	void UtilityWindow::CheckProjectType(int index)
	{
		ProjectType projectType = m_projectTypeDP->itemData(index).value<ProjectType>();
		if (projectType == ProjectType::Script || projectType == ProjectType::Executable || projectType == ProjectType::Unreal)
		{
			HideSoftwarePath();
		}
		else
		{
			ShowSoftwarePath();
		}
	}

	void UtilityWindow::ShowSoftwarePath()
	{
		m_softwareExe->show();
		m_softwarePathField->show();
		m_softwareExplorer->show();
	}

	void UtilityWindow::HideSoftwarePath()
	{
		m_softwarePathField->setText("");
		m_softwareExe->hide();
		m_softwarePathField->hide();
		m_softwareExplorer->hide();
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