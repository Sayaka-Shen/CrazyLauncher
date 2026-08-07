#pragma once
#include "data/Project.h"

#include <QList>
#include <QObject>

class QString;

Q_DECLARE_METATYPE(Cl::ProjectType)

namespace Cl
{
	class ProjectController : public QObject
	{
		Q_OBJECT

	public:
		explicit ProjectController(QObject* parent = nullptr);
		~ProjectController();

	public:
		/*QList<Project>& GetProjects();
		QString GetProjectFilePath() const;

		void AddProject(const Project& project);
		void RemoveProject(int index);
		void EditProject(int index, Project& project);
		void LaunchProject(Project* project);

		void SaveProjects();
		void LoadProjects();*/

	private:
		QList<Project> m_projects;

	signals:
		void E_addProject(const Project& project);
		void E_EditProjectToView(Project* project);
		void E_EditProjectToDescriptionView(Project& project);
		void E_removeProject(int index);

		void E_clearProject();
		void E_fillProject(Project& project);
	};
}
