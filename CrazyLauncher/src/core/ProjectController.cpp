#include "ProjectController.h"
#include "data/Project.h"

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
#include <QUrlQuery>

namespace Cl
{
	ProjectController::ProjectController(QObject* parent) : QObject(parent) {}

	ProjectController::~ProjectController() {}

// 	void ProjectController::AddProject(const Project& project)
// 	{
// 		m_projects.append(project);
// 		SaveProjects();
// 		emit E_AddProjectToView(project);
// 	}

	/*void ProjectController::RemoveProjects(int indexProject)
	{
		m_projects.remove(indexProject);
		SaveProjects();
		emit E_RemoveProjectToView(indexProject);
	}*/

// 	void ProjectController::EditProjects(Project* baseProjectEdited)
// 	{
// 		emit E_EditProjectToView(baseProjectEdited);
// 		SaveProjects();
// 		emit E_EditProjectToDescriptionView(*baseProjectEdited);
// 	}

	//void ProjectController::LaunchProjects(Project* project)
	//{
	//	if (!project || project->path.isEmpty()) return;

	//	QString cleanProjectPath = QDir::cleanPath(project->path);

	///*	if (!cleanSoftwarePath.isEmpty())
	//	{
	//		QProcess::startDetached(cleanSoftwarePath, { QDir::toNativeSeparators(cleanProjectPath) });
	//		return;
	//	}*/

	//	QDesktopServices::openUrl(QUrl::fromLocalFile(cleanProjectPath));
	//}

	//QString ProjectController::GetProjectsFilePath() const
	//{
	//	QString savePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

	//	// Create path if it does not exist
	//	QDir().mkpath(savePath);
	//	return savePath + "/crazy_projects.json";
	//}

	//void ProjectController::SaveProjects()
	//{
	//	//QFile file(GetProjectsFilePath());

	//	//if (!file.open(QIODevice::WriteOnly)) return;

	//	QJsonArray jsonArray;

	//	for (const Project& project : m_projects)
	//	{
	//		QJsonObject obj;
	//		obj["name"] = project.name;
	//		obj["description"] = project.description;
	//		obj["type"] = static_cast<ProjectType>(project.type);
	//		obj["path"] = project.path;

	//		jsonArray.append(obj);
	//	}

	//	QJsonDocument doc(jsonArray);
	//	//file.write(doc.toJson());
	//	//file.close();
	//}

	//void ProjectController::LoadProjects()
	//{
	//	m_projects.clear();
	//	//emit E_ClearProjectInListWidget();

	//	//QFile file(GetProjectsFilePath());

	//	//if (!file.open(QIODevice::ReadOnly)) return;

	//	QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	//	QJsonArray jsonArray = doc.array();

	//	for (const QJsonValue& value : jsonArray)
	//	{
	//		QJsonObject obj = value.toObject();
	//		Project project(obj["name"].toString(), obj["description"].toString(), static_cast<ProjectType>(obj["type"].toInt()), obj["path"].toString(), obj["isDir"].toBool(), obj["softwareExe"].toString());

	//		m_projects.append(project);
	//		//emit E_FillProjectInListWidget(project);
	//	}
	//	
	//	file.close();
	//}

}