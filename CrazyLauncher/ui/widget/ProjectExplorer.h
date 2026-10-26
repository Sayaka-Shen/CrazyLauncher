#pragma once
#include "widget/ProjectWidgetItem.h"
#include "core/Project.h"

#include <QWidget>

class QLineEdit;
class QListWidget;
class QVBoxLayout;
class QListWidgetItem;

namespace Cl
{
	class ProjectExplorer : public QWidget
	{
		Q_OBJECT

	public:
		explicit ProjectExplorer(QWidget* parent = nullptr);
		~ProjectExplorer() override = default;

	public:
		QListWidget* GetProjectList();
		int GetProjectListCurrentRow();

		void AddProjectInView(const Project& project);
		void EditProjectInView(const Project& project);
		void RemoveProjectInView(int indexProject);

	private:
		QVBoxLayout* m_projectViewLayout;
		QLineEdit* m_searchBar;
		QListWidget* m_projectsList;

	private:
		void InitUI();
		void InitConnections();
		void OnProjetFilter(const QString& text);

	signals:
		void currentProjectChange(const ProjectItem* projectItem);
		void E_FilterProjects(const QString& text);

	public slots:
		void OnProjectSelected(QListWidgetItem* current, QListWidgetItem* previous);

	};
}