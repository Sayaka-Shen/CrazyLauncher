#pragma once
#include "Project.h"

#include <QList>
#include <QObject>

class QString;

Q_DECLARE_METATYPE(Cl::ProjectType)

namespace Cl
{
	class ProjectManager : public QObject
	{
		Q_OBJECT

	public:
		explicit ProjectManager(QObject* parent = nullptr);
		~ProjectManager() = default;

		void AddProject(const Project& project);
		void RemoveProjects(int indexProject);
		void EditProjects(Project* baseProjectEdited);
		void LaunchProjects(Project* project);
		QList<Project>& GetProjects();

		QString GetProjectsFilePath() const;
		void SaveProjects();
		void LoadProjects();

	private:
		QList<Project> projects;

	signals:
		void E_AddProjectToView(const Project& project);
		void E_EditProjectToView(Project* project);
		void E_EditProjectToDescriptionView(Project& project);
		void E_RemoveProjectToView(int indexProject);

		void E_ClearProjectInListWidget();
		void E_FillProjectInListWidget(Project& project);
	};
}
