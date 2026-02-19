#pragma once
#include <QWidget>

class QLineEdit;
class QListWidget;
class QVBoxLayout;

namespace Cl
{
	struct Project;

	class ProjectView : public QWidget
	{
		Q_OBJECT

	public:
		explicit ProjectView(QWidget* parent = nullptr);
		~ProjectView();

		QListWidget* GetProjectList();

	private:
		QVBoxLayout* m_projectViewLayout;
		QLineEdit* m_searchBar;
		QListWidget* m_projectsList;

		void CreateLayout();
		void CreateUI();
		void SetupLayout();
		void SetupConnections();

	public slots:
		void AddProjectInView(const Project& project);
		void EditProjectInView(Project* project);
		void RemoveProjectInView(int indexProject);

	};
}