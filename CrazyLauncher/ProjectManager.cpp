#include "ProjectManager.h"

#include <QString>

namespace Cl
{
	ProjectManager::ProjectManager(QObject* parent) {}

	void ProjectManager::AddProject(const Project& project)
	{
		projects.append(project);
		emit E_AddProjectToView(project);
	}

	void ProjectManager::RemoveProjects(int indexProject)
	{
		projects.remove(indexProject);
		emit E_RemoveProjectToView(indexProject);
	}

	void ProjectManager::EditProjects(Project* baseProjectEdited)
	{
		emit E_EditProjectToView(baseProjectEdited);
	}

	void ProjectManager::LaunchProjects(Project* project)
	{
		if (!project || project->s_path.isEmpty()) return;

	}

	QList<Project>& ProjectManager::GetProjects()
	{
		return projects;
	}
}