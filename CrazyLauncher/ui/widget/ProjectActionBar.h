#pragma once
#include <QWidget>
#include <core/ProjectTypeRegistry.h>
#include <core/Project.h>

class QHBoxLayout;
class QPushButton;
class QDialog;

namespace Cl
{
	class ProjectModal;

	class ProjectActionBar : public QWidget
	{
		Q_OBJECT

	public:
		explicit ProjectActionBar(ProjectTypeRegistry& projectTypeRegistry, QWidget* parent = nullptr);
		~ProjectActionBar() override = default;

	public:
		void SetCurrentProject(const Project* currentProject);

	private:
		void OnAddWindowClicked();
		void OnEditWindowClicked();
		void OnRemoveProjectClicked();
		void OnLaunchProjectClicked();

	private:
		const Project* m_currentProject;
		ProjectTypeRegistry& m_projectTypeRegistry;

		QHBoxLayout* m_actionBarLayout;

		QPushButton* m_addBtn;
		QPushButton* m_editBtn;
		QPushButton* m_deleteBtn;
		QPushButton* m_launchBtn;

		QDialog* m_addBtnWindow;
		QDialog* m_editBtnWindow;

		// Pop up Window for Add - Edit projects 
		ProjectModal* m_addModal;
		ProjectModal* m_editModal;

	private:
		void InitUI();
		void InitConnections();

	signals:
		void addProject(const Project& project);
		void editProject(const Project& project);
		void removeProject();
		void launchProject(const Project* project);
	};
}
