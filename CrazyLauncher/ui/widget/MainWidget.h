#pragma once
#include <qboxlayout.h>
#include "QWidget"
#include "core/ProjectController.h"
#include "widget/ProjectView.h"
#include "widget/DescriptionView.h"
#include "widget/SettingsView.h"
#include "modal/AddWindow.h"
#include "modal/EditWindow.h"

namespace Cl
{
	struct Project;
	class AddWindow;
	class EditWindow;
	class ProjectWidgetItem;

	class MainWidget : public QWidget
	{
		Q_OBJECT

	public:
		explicit MainWidget(QWidget* parent = nullptr);
		~MainWidget();

		void CreateAddWindow();
		void CreateEditWindow();
		void OnCloseUtilityWindow();

		void OnProjectAdded(const Project& project);
		void OnProjectEdited(Project* baseProjectEdited);
		void OnRemoveProject();
		void LaunchProject();

		// Load saved data
		void ClearListWidget();
		void FillListWidget(Project& project);

		void FilterProjects(const QString& text);

	private:
		ProjectController* m_projectController;
		Project* m_currentProjectSelected;

		// Pop up Window for Add - Edit projects 
		AddWindow* m_addWindow;
		EditWindow* m_editWindow;

		// Main app layout
		QVBoxLayout* m_mainLayout;
		QHBoxLayout* m_centralLayout;
		QHBoxLayout* m_footerLayout;

		// Main app views
		ProjectView* m_projectView;
		DescriptionView* m_descView;
		SettingsView* m_settingView;

		// Base Crazy Launcher functions
		void InitUI();
		void InitConnections();

		// Get  Set
		void InitController();
		void GetSelectedProjectWidget(QListWidgetItem* current, QListWidgetItem* previous);
		int GetSelectedProjectWidgetIndex();


	signals:
		void E_DisplayProject(Project& project);

	};
}