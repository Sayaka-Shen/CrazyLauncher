#pragma once
#include "UtilityWindow.h"

namespace Cl
{
	struct Project;

	class EditWindow : public UtilityWindow
	{
		Q_OBJECT

	public:
		explicit EditWindow(QWidget* parent = nullptr, Project* project = nullptr);
		~EditWindow();

	private:
		Project* m_editProject;
		void OnEditProject();

		// Set edit field default value
		void SetEditModeDefaultValue();

	signals:
		void E_EditProject(Project* baseProjectEdited);

	};
}

