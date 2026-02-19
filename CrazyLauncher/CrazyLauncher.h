#pragma once
#include <QtWidgets/QMainWindow>

class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QString;
class QListWidgetItem;

namespace Cl
{
	class ProjectView;
	class DescriptionView;
	class SettingsView;
	struct Project;
	class AddWindow;
	class EditWindow;
	class ProjectManager;
	class ProjectWidgetItem;

	class CrazyLauncher : public QMainWindow
	{
		Q_OBJECT

	public:
		CrazyLauncher(QWidget* parent = nullptr);
		~CrazyLauncher();

	private:
		QWidget* m_centralWidget;
		ProjectManager* m_projectManager;
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
		void CreateController();
		void CreateLayout();
		void CreateUI();
		void SetupLayout();
		void SetupConnections();

		// Get  Set
		void GetSelectedProjectWidget(QListWidgetItem* current, QListWidgetItem* previous);
		int GetSelectedProjectWidgetIndex();


	signals:
		void E_DisplayProject(Project& project);

	public slots:
		void CreateAddWindow();
		void CreateEditWindow();
		void OnCloseUtilityWindow();

		void OnProjectAdded(const Project& project);
		void OnProjectEdited(Project* baseProjectEdited);
		void OnRemoveProject();
		void LaunchProject();


	};
}


