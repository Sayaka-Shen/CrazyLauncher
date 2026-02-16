#include "ProjectManager.h"
#include <QString>


ProjectManager::ProjectManager(QObject* parent /*= nullptr*/)
{

}

void ProjectManager::AddProjects(const Project& project)
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

QList<Project>& ProjectManager::GetProjects()
{
	return projects;
}
