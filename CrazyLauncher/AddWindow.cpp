#include "AddWindow.h"
#include "Project.h"

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
	AddWindow::AddWindow(QWidget* parent)
	{
		SetButtonRegisterText("Register");
		
		connect(m_registerBtn, &QPushButton::pressed, this, &AddWindow::OnRegisterProject);
	}

	AddWindow::~AddWindow() {}

	void AddWindow::OnRegisterProject()
	{
		if (IsOneOfTheFieldEmpty()) return;

		QString path = m_pathField->text();
		QFileInfo info(path);
		bool isDir = info.exists() && info.isDir();

		Project project(m_nameField->text(), m_descField->text(), m_projectTypeDP->currentData().value<ProjectType>(), m_pathField->text(), isDir, m_softwarePathField->text());

		emit E_AddProject(project);
		emit E_CloseWindow();

		accept();
	}


	/*void AddWindow::SetEditModeDefaultValue()
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
	}*/



	/*void AddWindow::UpdatePathState()
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

	void AddWindow::OpenProjectExplorer()
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
	}*/

	/*void AddWindow::OpenSoftwareExplorer()
	{
		QString path;
		path = QFileDialog::getOpenFileName(this, "Choose a file");

		if (!path.isEmpty())
		{
			m_softwarePathField->setText(path);
		}

	}

	void AddWindow::CheckPathContent(QString& path)
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

			connect(m_softwareExplorer, &QPushButton::pressed, this, &AddWindow::OpenSoftwareExplorer);
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
	}*/

	
}

