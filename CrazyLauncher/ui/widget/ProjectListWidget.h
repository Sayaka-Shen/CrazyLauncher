#pragma once
#include <QWidget>
#include "core/data/category.h"
#include "core/data/project.h"

class QLineEdit;
class QListWidget;
class QVBoxLayout;

namespace Cl
{
	class ProjectListWidget : public QWidget
	{
		Q_OBJECT

	public:
		explicit ProjectListWidget(Category currentCategory, QWidget* parent = nullptr);
		~ProjectListWidget() override = default;	

		QListWidget* GetProjectList();

	private:
		QVBoxLayout* m_projectListWidgetLayout;
		QListWidget* m_projectsList;
		Category m_currentCategory;

	private:
		void InitUI();
		void SetupLayout();

	public slots:
		void AddProjectInView(const Project& project);
		void EditProjectInView(Project* project);
		void RemoveProjectInView(int indexProject);

	};
}