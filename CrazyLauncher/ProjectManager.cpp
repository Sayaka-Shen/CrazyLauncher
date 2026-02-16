#include "ProjectManager.h"
#include <QString>
#include <QProcess>
#include <QFile>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QSettings>
#include <QDir>

ProjectManager::ProjectManager(QObject* parent) {}

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

void ProjectManager::LaunchProjects(Project* project)
{
	if (!project || project->s_path.isEmpty()) return;

	QString cleanPath = QDir::cleanPath(project->s_path);
	QFileInfo fileInfo(cleanPath);

	if (fileInfo.isDir())
	{
		if (QFile::exists(project->s_path + "/Assets") && QFile::exists(project->s_path + "/ProjectSettings"))
		{
			QString unityPath = "C:/Program Files/Unity/Hub/Editor/6000.3.5f1/Editor/Unity.exe";
			if (!unityPath.isEmpty()) {
				QStringList args;
				args << "-projectPath" << (project->s_path);

				QProcess::startDetached(unityPath, args);
			}
		}
		else
		{
			QDesktopServices::openUrl(QUrl::fromLocalFile(project->s_path));
		}
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
			QDesktopServices::openUrl(QUrl::fromLocalFile(project->s_path));
		}
	}
}

QList<Project>& ProjectManager::GetProjects()
{
	return projects;
}

