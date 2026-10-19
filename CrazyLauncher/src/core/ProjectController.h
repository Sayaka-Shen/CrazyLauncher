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
		explicit ProjectController(QObject* parent = nullptr);
		~ProjectController() override = default;

	public:
		QList<Project>& GetProjects();
		const Project* GetProjectByName(QString name);

		void AddProject(const Project& project);
		void RemoveProjects(int indexProject);
		void EditProject(const Project& project);
		void LaunchProjects(Project* project);

		void LoadProjects();

	private:
		QList<Project> m_projects;

	private:
		void SaveProjects();

	signals:
		void E_EditProjectToDescriptionView(const Project& project);
		void E_RemoveProjectToView(int indexProject);

		void E_ClearProjectInListWidget();
		void E_FillProjectInListWidget(Project& project);
	};
}
