#pragma once
#include <QList>
#include <QObject>
#include "Project.h"

class QString;

class ProjectManager : public QObject
{
	Q_OBJECT

public:
	explicit ProjectManager(QObject* parent = nullptr);
	~ProjectManager() = default;

	void AddProjects(const Project& project);
	void RemoveProjects(int indexProject);
	void EditProjects(Project* baseProjectEdited);
	void LaunchProjects(Project* project);
	QList<Project>& GetProjects();

private:
	QList<Project> projects;

signals:
	void E_AddProjectToView(const Project& project);
	void E_EditProjectToView(Project* project);
	void E_RemoveProjectToView(int indexProject);
};

