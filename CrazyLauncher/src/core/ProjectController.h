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
		void AddProject(const Project& project);
		void RemoveProjects(int indexProject);
		void EditProject(const Project& project);
		void LaunchProjects(Project* project);
		QList<Project>& GetProjects();

		void SaveProjects();
		void LoadProjects();

	private:
		QList<Project> projects;

	signals:
		void E_EditProjectToDescriptionView(const Project& project);
		void E_RemoveProjectToView(int indexProject);

		void E_ClearProjectInListWidget();
		void E_FillProjectInListWidget(Project& project);
	};
}
