#pragma once
#include <QtWidgets/QMainWindow>

class QWidget;
class QVBoxLayout;
class QPushButton;
class QString;
class QListWidgetItem;

namespace Cl
{
	class ProjectExplorer;
	class ProjectDetailsView;
	class ProjectActionBar;
	struct Project;
	class AddWindow;
	class EditWindow;
	class ProjectController;
	class ProjectWidgetItem;

	class CrazyLauncher : public QMainWindow
	{
		Q_OBJECT

	public:
		CrazyLauncher(QWidget* parent = nullptr);
		~CrazyLauncher() override = default;

	private:
		// Controller 
		ProjectController* m_projectController;

		// Project
		Project* m_currentProjectSelected;

		QVBoxLayout* m_appLayout;
		QWidget* m_centralWidget;

		ProjectExplorer* m_projectExplorer;
		ProjectDetailsView* m_projectDetailsView;
		ProjectActionBar* m_projectActionBar;

		// Pop up Window for Add - Edit projects 
		AddWindow* m_addWindow;
		EditWindow* m_editWindow;

	private:
		void InitController();
		void InitUI();
		void InitConnections();

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

		// Load saved data
		void ClearListWidget();
		void FillListWidget(Project& project);

		void FilterProjects(const QString& text);
	};
}


