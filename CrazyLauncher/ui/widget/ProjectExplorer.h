#pragma once
#include <QWidget>

class QLineEdit;
class QListWidget;
class QVBoxLayout;

namespace Cl
{
	struct Project;

	class ProjectExplorer : public QWidget
	{
		Q_OBJECT

	public:
		explicit ProjectExplorer(QWidget* parent = nullptr);
		~ProjectExplorer() override = default;

	public:
		QListWidget* GetProjectList();

	private:
		QVBoxLayout* m_projectViewLayout;
		QLineEdit* m_searchBar;
		QListWidget* m_projectsList;

	private:
		void InitUI();
		void InitConnections();
		void OnProjetFilter(const QString& text);

	signals:
		void E_FilterProjects(const QString& text);

	public slots:
		void AddProjectInView(const Project& project);
		void EditProjectInView(Project* project);
		void RemoveProjectInView(int indexProject);

	};
}