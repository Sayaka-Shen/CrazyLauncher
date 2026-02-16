#pragma once
#include <QWidget>

class QLineEdit;
class QListWidget;
class QVBoxLayout;
class Project;

class ProjectView : public QWidget
{
	Q_OBJECT

public:
	explicit ProjectView(QWidget* parent = nullptr);
	~ProjectView();

	QListWidget* GetProjectList();

private:
	void CreateLayout();
	void CreateUI();
	void SetupLayout();
	void SetupConnections();

	QVBoxLayout* m_projectViewLayout;
	QLineEdit* m_searchBar;
	QListWidget* m_projectsList;

public slots:
	void AddProjectInView(const Project& project);
	void EditProjectInView(Project* project);
	void RemoveProjectInView(int indexProject);

};

