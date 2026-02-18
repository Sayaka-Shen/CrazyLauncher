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

		// Edit Window base functions
		void CreateLayout();
		void CreateUI();
		void SetupLayout();
		void SetupConnections();

		// Set edit field default value
		// void SetEditModeDefaultValue();
		// void closeEvent(QCloseEvent* event) override;

	signals:
		void E_EditProject(Project* baseProjectEdited);

	};
}

