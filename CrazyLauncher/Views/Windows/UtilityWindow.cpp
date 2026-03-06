#include "UtilityWindow.h"
#include "../../Core/ProjectManager.h"
#include "../../Core/Project.h"

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
		// Style for the whole widget
		setObjectName("UtilityWindow");
		setAttribute(Qt::WA_StyledBackground, true);

		setWindowIcon(QIcon(":/new/prefix1/LogoCrazyLauncher.ico"));

		CreateLayout();
		CreateUI();
		SetupLayout();

		SetupProjectTypeDP();
		SetupConnections();

		CheckProjectType(m_projectTypeDP->currentIndex());
	}

	UtilityWindow::~UtilityWindow() {}


	// Utilities Functions
	void UtilityWindow::SetButtonRegisterText(QString registerText)
	{
		m_buttonView->GetRegisterBtn()->setText(registerText);
	}

	bool UtilityWindow::IsOneOfTheFieldEmpty()
	{
		return m_nameField->text().isEmpty() || m_descField->text().isEmpty() || m_pathField->text().isEmpty();
	}

	bool UtilityWindow::HasOneOfTheFieldChanged(const Project& project) 
	{
		return project.name != m_nameField->text() || project.description != m_descField->text() || project.path != m_pathField->text() || project.softwareExe != m_softwarePathField->text();
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
		m_name->setObjectName("ProjectName");
		m_nameField = new QLineEdit();

		m_desc = new QLabel("Description :", this);
		m_descField = new QLineEdit();
		m_descField->setMaxLength(150);

		m_projectType = new QLabel("Project Type :", this);
		m_projectTypeDP = new QComboBox(this);

		m_path = new QLabel("Project Path :", this);

		m_pathField = new QLineEdit();
		// QSS
		m_pathField->setObjectName("PathField");

		m_projectExplorer = new QPushButton(this);
		m_projectExplorer->setDefault(false);
		m_projectExplorer->setAutoDefault(false);

		// Button QSS and Icon
		m_projectExplorer->setObjectName("ExplorerBtn");
		m_projectExplorer->setIcon(QIcon(":/new/prefix1/folder-black-white.png"));

		m_softwareExe = new QLabel("Software Used :", this);

		m_softwarePathField = new QLineEdit();
		// QSS
		m_softwarePathField->setObjectName("SoftwarePathField");

		m_softwareExplorer = new QPushButton(this);
		m_softwareExplorer->setDefault(false);
		m_softwareExplorer->setAutoDefault(false);

		// Button QSS and Icon
		m_softwareExplorer->setObjectName("ExplorerBtn");
		m_softwareExplorer->setIcon(QIcon(":/new/prefix1/folder-black-white.png"));

		HideSoftwarePath();

		m_buttonView = new WindowButtonView(this);
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

		m_windowLayout->setContentsMargins(0, 0, 0, 0);
		m_windowLayout->setSpacing(0);
		m_windowLayout->addStretch(1);

		// Add to main layout
		m_windowLayout->addWidget(m_buttonView);
	}

	void UtilityWindow::SetupConnections()
	{
		connect(m_buttonView->GetCancelBtn(), &QPushButton::pressed, this, &UtilityWindow::OnCancelClicked);

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

	void UtilityWindow::FindProject()
	{
		QString path;

		if (m_projectTypeDP->currentData().value<ProjectType>() == ProjectType::Unity)
		{
			path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
		}
		else
		{
			path = QFileDialog::getOpenFileName(this, tr("Open File"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), projectTypeToFilter[m_projectTypeDP->currentData().value<ProjectType>()]);
		}

		if (!path.isEmpty())
		{
			m_pathField->setText(path);
		}
	}

	void UtilityWindow::FindSoftware()
	{
		QString programFiles = qEnvironmentVariable("ProgramFiles(x86)");
		QString path = QFileDialog::getOpenFileName(this, tr("Choose an Application"), programFiles, tr("Applications (*.exe)"));

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

		this->adjustSize();
		this->setFixedHeight(this->sizeHint().height());
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