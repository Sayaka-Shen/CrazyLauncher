#include "EditWindow.h"
#include "../../Core/Project.h"

#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QComboBox>
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

		m_editProject->name = m_nameField->text();
		m_editProject->description = m_descField->text();
		m_editProject->path = m_pathField->text();
		m_editProject->softwareExe = m_softwarePathField->text();
		
		emit E_EditProject(m_editProject);
		emit E_CloseWindow();

		accept();
	}

	void EditWindow::SetEditModeDefaultValue()
	{
		m_nameField->setText(m_editProject->name);
		m_descField->setText(m_editProject->description);

		int currentProjectTypeIndex = m_projectTypeDP->findData(m_editProject->type);
		m_projectTypeDP->setCurrentIndex(currentProjectTypeIndex);
		
		m_pathField->setText(m_editProject->path);

		if (!m_editProject->softwareExe.isEmpty())
		{
			m_softwarePathField->setText(m_editProject->softwareExe);
			ShowSoftwarePath();
		}
		else
		{
			HideSoftwarePath();
		}
	}
}