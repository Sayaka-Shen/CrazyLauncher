#include "EditWindow.h"

namespace Cl
{

	EditWindow::EditWindow(QWidget* parent, Project* project) : m_editProject(project)
	{
		SetButtonRegisterText("Edit");
	}

	EditWindow::~EditWindow() {}

	/* void AddWindow::OnEditClicked()
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
	}*/
}