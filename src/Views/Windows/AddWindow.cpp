#include "AddWindow.h"
#include "../../Core/Project.h"

#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QComboBox>
#include <QPushButton>

namespace Cl
{
	AddWindow::AddWindow(QWidget* parent)
	{
		SetButtonRegisterText("Register");
		
		connect(m_buttonView->GetRegisterBtn(), &QPushButton::pressed, this, &AddWindow::OnRegisterProject);
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
}

