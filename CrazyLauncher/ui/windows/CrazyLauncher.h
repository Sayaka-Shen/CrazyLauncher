#pragma once
#include <QtWidgets/QMainWindow>
#include "core/ProjectTypeRegistry.h"

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
	class ProjectModal;
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
		ProjectTypeRegistry m_projectTypeRegistry;

		// Project
		Project* m_currentProjectSelected;

		QVBoxLayout* m_appLayout;
		QWidget* m_centralWidget;

		ProjectExplorer* m_projectExplorer;
		ProjectDetailsView* m_projectDetailsView;
		ProjectActionBar* m_projectActionBar;

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
		void OnAddProject(const Project& project);
		void OnEditProject(const Project& project);

		void OnRemoveProject();
		void LaunchProject();

		// Load saved data
		void ClearListWidget();
		void FillListWidget(Project& project);

		void FilterProjects(const QString& text);

	};
}


