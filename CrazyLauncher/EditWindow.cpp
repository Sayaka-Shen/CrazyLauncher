#include "EditWindow.h"
#include "Project.h"

#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QComboBox>
#include <QPushButton>
#include <QPushButton>

namespace Cl
{
	EditWindow::EditWindow(QWidget* parent, Project* project) : m_editProject(project)
	{
		SetButtonRegisterText("Edit");
		SetEditModeDefaultValue();

		connect(m_registerBtn, &QPushButton::pressed, this, &EditWindow::OnEditProject);
	}

	EditWindow::~EditWindow() {}

	void EditWindow::OnEditProject()
	{
		if (m_editProject == nullptr) return;
		if (!HasOneOfTheFieldChanged(*m_editProject)) return;

		m_editProject->s_name = m_nameField->text();
		m_editProject->s_description = m_descField->text();
		m_editProject->s_path = m_pathField->text();
		m_editProject->s_softwareExe = m_softwarePathField->text();
		
		emit E_EditProject(m_editProject);
		emit E_CloseWindow();

		accept();
	}

	void EditWindow::SetEditModeDefaultValue()
	{
		m_nameField->setText(m_editProject->s_name);
		m_descField->setText(m_editProject->s_description);
		m_pathField->setText(m_editProject->s_path);
		m_softwarePathField->setText(m_editProject->s_softwareExe);
	}
}