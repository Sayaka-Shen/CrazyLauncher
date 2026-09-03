#pragma once
#include "QWidget"
#include "core/CategoryController.h"
#include "data/CategoryModalData.h"

class QListWidgetItem;
class QVBoxLayout;
class QHBoxLayout;

namespace Cl
{
	struct Project;
	class AddWindow;
	class EditWindow;
	class ProjectWidgetItem;
	class CategoryWidget;
	class DescriptionView;
	class ProjectView;
	class ProjectController;
	

	class MainWidget : public QWidget
	{
		Q_OBJECT

	public:
		explicit MainWidget(QWidget* parent = nullptr);
		~MainWidget() override = default;

		void CreateAddWindow();
		void CreateEditWindow();
		void OnCloseUtilityWindow();

		void OnProjectAdded(const Project& project);
		void OnProjectEdited(Project* baseProjectEdited);
		void OnRemoveProject();
		void LaunchProject();

		// Load saved data
		void ClearListWidget();
		void FillListWidget(Project& project);

		void FilterProjects(const QString& text);

	private:
		CategoryController* m_categoryController;
		Project* m_currentProjectSelected;

		//// Main app layout
		QHBoxLayout* m_mainLayout;
		//QHBoxLayout* m_projectLayout;
		//QVBoxLayout* m_descLayout;

		// Main app views
		CategoryWidget* m_categoryWidget;
		ProjectView* m_projectWidget;
		DescriptionView* m_descWidget;

		// Pop up Window for Add - Edit projects 
		AddWindow* m_addWindow;
		EditWindow* m_editWindow;

	private:
		void InitUI();
		void InitConnections();

		// Get  Set
		void InitController();
		//void GetSelectedProjectWidget(QListWidgetItem* current, QListWidgetItem* previous);
		int GetSelectedProjectWidgetIndex();


	signals:
		void E_DisplayProject(Project& project);

	private slots:
		void OnCreateCategory(const CategoryModalData& data);
		int OnGetNumberOfProjects(QString categoryName);
	};
}