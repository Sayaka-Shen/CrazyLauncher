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
		SetDefaultValue();
	}
}

UtilityWindow::~UtilityWindow() 
{
}

void UtilityWindow::CreateUI()
{
	m_name = new QLabel("Nom du projet :", this);
	m_nameField = new QLineEdit();

	m_desc = new QLabel("Description :", this);
	m_descField = new QLineEdit();

	m_path = new QLabel("Chemin à lancer :", this);
	m_pathField = new QLineEdit();

	m_cancelBtn = new QPushButton("Annuler", this);
	m_registerBtn = new QPushButton(m_mode == Add ? "Enregistrer" : "Modifier", this);

	m_openFileExplorer = new QPushButton(this);
	m_openFolderExplorer = new QPushButton(this);
}

void UtilityWindow::CreateLayout()
{
	m_windowLayout = new QVBoxLayout(this);
	m_buttonLayout = new QHBoxLayout();
	m_pathLayout = new QHBoxLayout();
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
	m_windowLayout->addWidget(m_path);
	m_pathLayout->addWidget(m_pathField);
	m_pathLayout->addWidget(m_openFileExplorer);
	m_pathLayout->addWidget(m_openFolderExplorer);

	// Add to bottom layout
	m_buttonLayout->addWidget(m_cancelBtn);
	m_buttonLayout->addWidget(m_registerBtn);

	// Add to main layout
	m_windowLayout->addLayout(m_pathLayout);
	m_windowLayout->addLayout(m_buttonLayout);
}

void UtilityWindow::SetupConnections()
{
	connect(m_registerBtn, &QPushButton::pressed, this, m_mode == Add ? &UtilityWindow::OnRegisterClicked : &UtilityWindow::OnEditClicked);
	connect(m_cancelBtn, &QPushButton::pressed, this, &UtilityWindow::OnCancelClicked);
	connect(m_openFileExplorer, &QPushButton::pressed, this, &UtilityWindow::OpenFileExplorer);
	connect(m_openFolderExplorer, &QPushButton::pressed, this, &UtilityWindow::OpenFolderExplorer);
}

void UtilityWindow::SetDefaultValue()
{
	m_nameField->setText(m_project->s_name);
	m_descField->setText(m_project->s_description);
	m_pathField->setText(m_project->s_path);
}


void UtilityWindow::closeEvent(QCloseEvent* event)
{
	QDialog::closeEvent(event);
	emit E_CloseWindow();
}

void UtilityWindow::OpenFileExplorer()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Select a project file"), QString(), tr("All Files (*.*)"));

	if (!path.isEmpty())
	{
		m_pathField->setText(path);
	}
}

void UtilityWindow::OpenFolderExplorer()
{
	QString path = QFileDialog::getExistingDirectory(this, tr("Select a project folder"));

	if (!path.isEmpty())
	{
		m_pathField->setText(path);
	}
}

// SIGNALS
void UtilityWindow::OnRegisterClicked()
{
	if (m_nameField->text().isEmpty() || m_descField->text().isEmpty() || m_pathField->text().isEmpty()) return;

	Project project(m_nameField->text(), m_descField->text(), m_pathField->text());
	emit E_AddProject(project);
	emit E_CloseWindow();
	accept();
}

void UtilityWindow::OnEditClicked()
{
	if (m_project == nullptr) return;
	if (m_project->s_name == m_nameField->text() && m_project->s_description == m_descField->text() && m_project->s_path == m_pathField->text()) return;

	m_project->s_name = m_nameField->text();
	m_project->s_description = m_descField->text();
	m_project->s_path = m_pathField->text();

	emit E_EditProject(m_project);
	emit E_CloseWindow();
	accept();
}

void UtilityWindow::OnCancelClicked()
{
	emit E_CloseWindow();
	reject();
}

