#pragma once
#include "Project.h"
#include "ProjectTypeRegistry.h"

#include <QList>
#include <QObject>

class QString;

namespace Cl
{
	class ProjectController : public QObject
	{
		Q_OBJECT

	public:
		explicit ProjectController(ProjectTypeRegistry& projectTypeRegistry, QObject* parent = nullptr);
		~ProjectController() override = default;

	public:
		QList<Project>& GetProjects();
		const Project* GetProjectByName(QString projectName);

		void AddProject(const Project& project);
		void RemoveProject(int index);
		void EditProject();
		void LaunchProject(const Project* project);

		void LoadProjects();

	private:
		QList<Project> m_projects;
		ProjectTypeRegistry& m_projectTypeRegistry;

	private:
		void SaveProjects();

	signals:
		void clearProjectInListWidget();
		void fillProjectInListWidget(Project& project);
	};
}
