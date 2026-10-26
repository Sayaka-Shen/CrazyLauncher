#include "ProjectController.h"
#include "Project.h"
#include <utils/CoreUtils.h>

#include <QProcess>
#include <QFileInfo>
#include <QDesktopServices>
#include <QDir>
#include <QUrl>
#include <QJsonArray>
#include <QJsonObject>
#include <QProcess>
#include <QStandardPaths>
#include <QDebug>
#include <QDirIterator>

namespace Cl
{
	ProjectController::ProjectController(QObject* parent) : QObject(parent) 
	{
	}

	void ProjectController::AddProject(const Project& project)
	{
		m_projects.append(project);
		SaveProjects();
	}

	void ProjectController::RemoveProject(int index)
	{
		m_projects.remove(index);
		SaveProjects();
	}

	void ProjectController::EditProject()
	{
		SaveProjects();
	}

	void ProjectController::LaunchProject(const Project* project)
	{
		if (project == nullptr) return;

		QString cleanProjectPath = QDir::cleanPath(project->path);
		QString currentUnityVersion;
		
		if (QFile::exists(cleanProjectPath + "/ProjectSettings/ProjectVersion.txt"))
		{
			QFile file(cleanProjectPath + "/ProjectSettings/ProjectVersion.txt");
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
				return;

			QTextStream in(&file);
			while (!in.atEnd()) {
				QString line = in.readLine();

				if (line.contains("m_EditorVersion"))
				{
					currentUnityVersion = line.section(":", 1).trimmed();
					break;
				}
			}
		}

		QDirIterator blenderIt("C:/Program Files (x86)/Steam/steamapps", QStringList() << "blender-launcher.exe", QDir::Files, QDirIterator::Subdirectories);
		QDirIterator unityIt("C:/Program Files/Unity/Hub/Editor/" + currentUnityVersion, QStringList() << "Unity.exe", QDir::Files, QDirIterator::Subdirectories);
		QString blenderPath;
		while (blenderIt.hasNext())
		{
			blenderPath = blenderIt.next();
			qDebug() << blenderPath;
			break;
		}

		QString unityPath;
		while (unityIt.hasNext())
		{
			unityPath = unityIt.next();
			qDebug() << unityPath;
			break;
		}

		//QProcess::startDetached(blen, { cleanProjectPath });
	}

	QList<Project>& ProjectController::GetProjects()
	{
		return m_projects;
	}

	const Project* ProjectController::GetProjectByName(QString projectName)
	{
		for (const auto& project : m_projects)
		{
			if (project.name == projectName)
			{
				return &project;
			}
		}

		return nullptr;
	}

	void ProjectController::SaveProjects()
	{
		QFile file(Cl::CoreUtils::GetProjectsFilePath());

		if (!file.open(QIODevice::WriteOnly)) return;

		QJsonArray jsonArray;

		for (const Project& project : m_projects)
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
		m_projects.clear();
		emit E_ClearProjectInListWidget();

		QFile file(Cl::CoreUtils::GetProjectsFilePath());

		if (!file.open(QIODevice::ReadOnly)) return;

		QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
		QJsonArray jsonArray = doc.array();

		for (const QJsonValue& value : jsonArray)
		{
			QJsonObject obj = value.toObject();
			Project project{obj["name"].toString(), obj["description"].toString(), static_cast<ProjectType>(obj["type"].toInt()), obj["path"].toString(), obj["isDir"].toBool()};

			m_projects.append(project);
			emit E_FillProjectInListWidget(project);
		}
		
		file.close();
	}
}