#include "UtilityWindow.h"
#include <QCheckBox>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "ProjectManager.h"
#include <QFileDialog>

UtilityWindow::UtilityWindow(WindowMode mode, QWidget* parent, Project* project) : m_mode(mode), m_project(project)
{
	CreateLayout();
	CreateUI();
	SetupLayout();
	SetupConnections();
	
	if (m_mode == Edit && m_project != nullptr)
	{
		QString path = project->s_path;
		if (path.isEmpty()) return;
		CheckPathContent(path);

		SetEditModeDefaultValue();
	}
}

UtilityWindow::~UtilityWindow() {}

void UtilityWindow::CreateUI()
{
	m_name = new QLabel("Project Name :", this);
	m_nameField = new QLineEdit();

	m_desc = new QLabel("Description :", this);
	m_descField = new QLineEdit();

	m_pathType = new QLabel("Choose Path Type :", this);
	m_typesGroup = new QButtonGroup(this);

	m_directoryType = new QCheckBox("Directory", this);
	m_directoryType->setCheckState(Qt::Checked);

	m_fileType = new QCheckBox("File", this);

	m_path = new QLabel("Project Path :", this);
	m_pathField = new QLineEdit();

	m_projectExplorer = new QPushButton(this);
	
	m_cancelBtn = new QPushButton("Cancel", this);
	m_registerBtn = new QPushButton(m_mode == Add ? "Register" : "Edit", this);
}

void UtilityWindow::CreateLayout()
{
	m_windowLayout = new QVBoxLayout(this);
	m_buttonLayout = new QHBoxLayout();
	m_typeLayout = new QHBoxLayout();
	m_pathProjectLayout = new QHBoxLayout();
	m_pathSoftwareLayout = new QHBoxLayout();
}

void UtilityWindow::SetupLayout()
{
	// Name
	m_windowLayout->addWidget(m_name);
	m_windowLayout->addWidget(m_nameField);

	// Description
	m_windowLayout->addWidget(m_desc);
	m_windowLayout->addWidget(m_descField);

	// Path and Icon path
	m_typesGroup->addButton(m_directoryType);
	m_typesGroup->addButton(m_fileType);

	m_windowLayout->addWidget(m_pathType);
	m_typeLayout->addWidget(m_directoryType);
	m_typeLayout->addWidget(m_fileType);
	m_windowLayout->addLayout(m_typeLayout);

	m_pathProjectLayout->addWidget(m_path);
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
	connect(m_registerBtn, &QPushButton::pressed, this, m_mode == Add ? &UtilityWindow::OnRegisterClicked : &UtilityWindow::OnEditClicked);
	connect(m_cancelBtn, &QPushButton::pressed, this, &UtilityWindow::OnCancelClicked);

	connect(m_directoryType, &QCheckBox::checkStateChanged, this, &UtilityWindow::UpdatePathState);
	connect(m_fileType, &QCheckBox::checkStateChanged, this, &UtilityWindow::UpdatePathState);

	connect(m_projectExplorer, &QPushButton::pressed, this, &UtilityWindow::OpenProjectExplorer);
}

void UtilityWindow::SetEditModeDefaultValue()
{
	m_nameField->setText(m_project->s_name);
	m_descField->setText(m_project->s_description);
	m_pathField->setText(m_project->s_path);
	
	if (m_project->s_pathState == PathState::Directory)
	{
		m_directoryType->setCheckState(Qt::Checked);
	}
	else
	{
		m_fileType->setCheckState(Qt::Checked);
	}
	
	if (m_softwarePath == nullptr) return;
	m_softwarePathField->setText(m_project->s_software);
}


void UtilityWindow::closeEvent(QCloseEvent* event)
{
	QDialog::closeEvent(event);
	emit E_CloseWindow();
}

void UtilityWindow::UpdatePathState()
{
	if (m_directoryType->checkState() == Qt::Checked)
	{
		m_pathState = Directory;
	}
	else if (m_fileType->checkState() == Qt::Checked)
	{
		m_pathState = File;
	}
}

void UtilityWindow::OpenProjectExplorer()
{
	QString path;
	
	if (m_pathState == PathState::Directory)
	{
		path = QFileDialog::getExistingDirectory(this, "Choose a folder");
	}
	else
	{
		path = QFileDialog::getOpenFileName(this, "Choose a file");
	}

	if (!path.isEmpty())
	{
		m_pathField->setText(path);
		CheckPathContent(path);
	}
}

void UtilityWindow::OpenSoftwareExplorer()
{
	QString path;
	path = QFileDialog::getOpenFileName(this, "Choose a file");

	if (!path.isEmpty())
	{
		m_softwarePathField->setText(path);
	}

}

void UtilityWindow::CheckPathContent(QString& path)
{
	QFileInfo fileInfo(path);
	QString ext = fileInfo.suffix().toLower();

	if ((QFile::exists(path + "/Assets") && QFile::exists(path + "/ProjectSettings")) || ext == "blend" || ext == "psd")
	{
		m_softwarePath = new QLabel("Software Path :", this);
		m_softwarePathField = new QLineEdit();
		m_softwareExplorer = new QPushButton(this);

		m_pathSoftwareLayout->addWidget(m_softwarePath);
		m_pathSoftwareLayout->addWidget(m_softwarePathField);
		m_pathSoftwareLayout->addWidget(m_softwareExplorer);

		connect(m_softwareExplorer, &QPushButton::pressed, this, &UtilityWindow::OpenSoftwareExplorer);
	}
	else
	{
		m_pathSoftwareLayout->removeWidget(m_softwarePath);
		m_pathSoftwareLayout->removeWidget(m_softwarePathField);
		m_pathSoftwareLayout->removeWidget(m_softwareExplorer);

		m_softwarePath = nullptr;
		m_softwarePathField = nullptr;
		m_softwareExplorer = nullptr;
	}
}

void UtilityWindow::OnRegisterClicked()
{
	if (m_nameField->text().isEmpty() || m_descField->text().isEmpty() || m_pathField->text().isEmpty()) return;
	if (m_softwarePath != nullptr && m_softwarePathField->text().isEmpty()) return;

	QString software = m_softwarePathField->text();
	Project project(m_nameField->text(), m_descField->text(), m_pathField->text(), software != "" ? software : "");

	emit E_AddProject(project);
	emit E_CloseWindow();
	accept();
}

void UtilityWindow::OnEditClicked()
{
	if (m_project == nullptr) return;
	if (m_project->s_name == m_nameField->text() && m_project->s_description == m_descField->text() && m_project->s_path == m_pathField->text()) return;
	if (m_softwarePathField != nullptr)
	{
		if (m_project->s_software == m_softwarePathField->text()) return;
	}

	m_project->s_name = m_nameField->text();
	m_project->s_description = m_descField->text();
	m_project->s_path = m_pathField->text();
	m_project->s_software = m_softwarePathField->text();
	m_project->s_pathState = m_pathState;

	emit E_EditProject(m_project);
	emit E_CloseWindow();
	accept();
}

void UtilityWindow::OnCancelClicked()
{
	emit E_CloseWindow();
	reject();
}


