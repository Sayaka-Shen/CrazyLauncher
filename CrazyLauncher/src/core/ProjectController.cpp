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
	ProjectController::ProjectController(ProjectTypeRegistry& projectTypeRegistry, QObject* parent) : m_projectTypeRegistry(projectTypeRegistry), QObject(parent)
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

		if (project->type == ProjectType::Script || project->type == ProjectType::Unreal)
		{

		}
		else
		{

		}
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
			obj["exe"] = project.executable;

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
			Project project{obj["name"].toString(), obj["description"].toString(), static_cast<ProjectType>(obj["type"].toInt()), obj["path"].toString(), obj["exe"].toString()};

			m_projects.append(project);
			emit E_FillProjectInListWidget(project);
		}
		
		file.close();
	}
}