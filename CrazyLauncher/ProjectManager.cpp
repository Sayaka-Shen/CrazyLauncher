#include "ProjectManager.h"

#include <QString>
#include <QProcess>
#include <QFileInfo>
#include <QDesktopServices>
#include <QDir>
#include <QUrl>

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
		emit E_EditProjectToDescriptionView(*baseProjectEdited);
	}

	void ProjectManager::LaunchProjects(Project* project)
	{
		if (!project || project->s_path.isEmpty()) return;

		QString cleanPath = QDir::cleanPath(project->s_path);
		QFileInfo fileInfo(cleanPath);

		if (!project->s_softwareExe.isEmpty())
		{
			QString softwarePath = project->s_softwareExe;
			QStringList args;
			args << cleanPath;

			QProcess::startDetached(softwarePath, args);
		}
		else
		{
			QString ext = fileInfo.suffix().toLower();

			if (ext == "exe")
			{
				QProcess::startDetached(project->s_path);
			}
			else
			{
				QDesktopServices::openUrl(QUrl::fromLocalFile(cleanPath));
			}
		}
	}

	QList<Project>& ProjectManager::GetProjects()
	{
		return projects;
	}
}