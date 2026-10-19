#include "ProjectController.h"
#include "Project.h"
#include <utils/CoreUtils.h>

#include <QProcess>
#include <QFileInfo>
#include <QDesktopServices>
#include <QDir>
#include <QUrl>
#include <QIODevice>
#include <QJsonArray>
#include <QJsonObject>

namespace Cl
{
	ProjectController::ProjectController(QObject* parent) : QObject(parent) 
	{
	}

	void ProjectController::AddProject(const Project& project)
	{
		projects.append(project);
		SaveProjects();
	}

	void ProjectController::RemoveProjects(int indexProject)
	{
		projects.remove(indexProject);
		SaveProjects();
		emit E_RemoveProjectToView(indexProject);
	}

	void ProjectController::EditProject(const Project& project)
	{
		SaveProjects();
		emit E_EditProjectToDescriptionView(project);
	}

	void ProjectController::LaunchProjects(Project* project)
	{
		if (!project || project->path.isEmpty()) return;

		QString cleanProjectPath = QDir::cleanPath(project->path);
		//QString cleanSoftwarePath = QDir::cleanPath(project->softwareExe);

		//if (!cleanSoftwarePath.isEmpty())
		//{
		//	QProcess::startDetached(cleanSoftwarePath, { QDir::toNativeSeparators(cleanProjectPath) });
		//	return;
		//}

		QDesktopServices::openUrl(QUrl::fromLocalFile(cleanProjectPath));
	}

	QList<Project>& ProjectController::GetProjects()
	{
		return projects;
	}

	void ProjectController::SaveProjects()
	{
		QFile file(Cl::CoreUtils::GetProjectsFilePath());

		if (!file.open(QIODevice::WriteOnly)) return;

		QJsonArray jsonArray;

		for (const Project& project : projects)
		{
			QJsonObject obj;
			obj["name"] = project.name;
			obj["description"] = project.description;
			obj["type"] = static_cast<ProjectType>(project.type);
			obj["path"] = project.path;
			obj["isDir"] = project.isDirectory;

			jsonArray.append(obj);
		}

		QJsonDocument doc(jsonArray);
		file.write(doc.toJson());
		file.close();
	}

	void ProjectController::LoadProjects()
	{
		projects.clear();
		emit E_ClearProjectInListWidget();

		QFile file(Cl::CoreUtils::GetProjectsFilePath());

		if (!file.open(QIODevice::ReadOnly)) return;

		QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
		QJsonArray jsonArray = doc.array();

		for (const QJsonValue& value : jsonArray)
		{
			QJsonObject obj = value.toObject();
			Project project{obj["name"].toString(), obj["description"].toString(), static_cast<ProjectType>(obj["type"].toInt()), obj["path"].toString(), obj["isDir"].toBool()};

			projects.append(project);
			emit E_FillProjectInListWidget(project);
		}
		
		file.close();
	}
}