#pragma once
#include <QWidget>

class QHBoxLayout;
class QPushButton;
class QDialog;

namespace Cl
{
	class AddModal;
	class EditWindow;

	class ProjectActionBar : public QWidget
	{
		Q_OBJECT

	public:
		explicit ProjectActionBar(QWidget* parent = nullptr);
		~ProjectActionBar() override = default;

	public:
		void OnAddWindowClicked();
		//void OnEditWindowClicked();
		void OnRemoveProjectClicked();
		void OnLaunchProjectClicked();

	private:
		QHBoxLayout* m_actionBarLayout;

		QPushButton* m_addBtn;
		QPushButton* m_editBtn;
		QPushButton* m_deleteBtn;
		QPushButton* m_launchBtn;

		QDialog* m_addBtnWindow;
		QDialog* m_editBtnWindow;

		// Pop up Window for Add - Edit projects 
		AddModal* m_addWindow;
		EditWindow* m_editWindow;

	private:
		void InitUI();
		void InitConnections();

	signals:
		void addProject();

		/*void E_RemoveProject();
		void E_LaunchProject();*/

	};
}
