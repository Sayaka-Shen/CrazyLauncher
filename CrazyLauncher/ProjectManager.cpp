#include "ProjectManager.h"
#include "Project.h"

#include <QString>
#include <QProcess>
#include <QFileInfo>
#include <QDesktopServices>
#include <QDir>
#include <QUrl>
#include <QStandardPaths>
#include <QIODevice>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QSettings>

namespace Cl
{
	ProjectManager::ProjectManager(QObject* parent) {}

	void ProjectManager::AddProject(const Project& project)
	{
		projects.append(project);
		SaveProjects();
		emit E_AddProjectToView(project);
	}

	void ProjectManager::RemoveProjects(int indexProject)
	{
		projects.remove(indexProject);
		SaveProjects();
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

		QString cleanProjectPath = QDir::cleanPath(project->s_path);
		QString cleanSoftwarePath = QDir::cleanPath(project->s_softwareExe);

		QFileInfo softwareFI(cleanSoftwarePath);

		if (!cleanSoftwarePath.isEmpty())
		{
			if (softwareFI.suffix().toLower() == "url")
			{
				QSettings settings(cleanSoftwarePath, QSettings::IniFormat);
				QString urlString = settings.value("InternetShortcut/URL").toString();
				QUrl url(urlString);

				if (url.isValid())
				{
					QDesktopServices::openUrl(url);
				}

				return;
			}
			
			QProcess::startDetached(cleanSoftwarePath, { cleanProjectPath });

			return;
		}

		QDesktopServices::openUrl(QUrl::fromLocalFile(cleanProjectPath));
	}

	QList<Project>& ProjectManager::GetProjects()
	{
		return projects;
	}

	QString ProjectManager::GetProjectsFilePath() const
	{
		QString savePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

		// Create path if it does not exist
		QDir().mkpath(savePath);
		return savePath + "/crazy_projects.json";
	}

	void ProjectManager::SaveProjects()
	{
		QFile file(GetProjectsFilePath());

		if (!file.open(QIODevice::WriteOnly)) return;

		QJsonArray jsonArray;

		for (const Project& project : projects)
		{
			QJsonObject obj;
			obj["name"] = project.s_name;
			obj["description"] = project.s_description;
			obj["type"] = static_cast<ProjectType>(project.s_type);
			obj["path"] = project.s_path;
			obj["isDir"] = project.s_isDirectory;
			obj["softwareExe"] = project.s_softwareExe;

			jsonArray.append(obj);
		}

		QJsonDocument doc(jsonArray);
		file.write(doc.toJson());
		file.close();
	}

	void ProjectManager::LoadProjects()
	{
		projects.clear();
		emit E_ClearProjectInListWidget();

		QFile file(GetProjectsFilePath());

		if (!file.open(QIODevice::ReadOnly)) return;

		QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
		QJsonArray jsonArray = doc.array();

		for (const QJsonValue& value : jsonArray)
		{
			QJsonObject obj = value.toObject();
			Project project(obj["name"].toString(), obj["description"].toString(), static_cast<ProjectType>(obj["type"].toInt()), obj["path"].toString(), obj["isDir"].toBool(), obj["softwareExe"].toString());

			projects.append(project);
			emit E_FillProjectInListWidget(project);
		}
		
		file.close();
	}

}