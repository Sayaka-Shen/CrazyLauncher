#pragma once
#include "QDialog"

class QString;
class QLabel;
class QLineEdit;
class QWidget;
class QCheckBox;
class QVBoxLayout;
class QHBoxLayout;
class QButtonGroup;
class QCheckBox;
class QComboBox;

namespace Cl
{
	class UtilityWindow : public QDialog
	{
		Q_OBJECT 

	public:
		explicit UtilityWindow(QWidget* parent = nullptr);
		~UtilityWindow();

	protected:
		QVBoxLayout* m_windowLayout;
		QHBoxLayout* m_buttonLayout;
		QHBoxLayout* m_pathProjectLayout;
		QHBoxLayout* m_pathSoftwareLayout;
		QHBoxLayout* m_typeLayout;

		QLabel* m_name;
		QLineEdit* m_nameField;

		QLabel* m_desc;
		QLineEdit* m_descField;

		QLabel* m_projectType;
		QComboBox* m_projectTypeDP;

		QLabel* m_path;
		QLineEdit* m_pathField;

		QLabel* m_softwarePath;
		QLineEdit* m_softwarePathField;

		QPushButton* m_projectExplorer;
		QPushButton* m_softwareExplorer;

		QPushButton* m_cancelBtn;
		QPushButton* m_registerBtn;

		void SetButtonRegisterText(QString registerText);
		bool IsOneOfTheFieldEmpty();

	private:
		// UI Add Window base functions
		void CreateLayout();
		void CreateUI();
		void SetupLayout();
		void SetupConnections();

		void SetupProjectTypeDP();

		// Close Window
		void closeEvent(QCloseEvent* event) override;
		void OnCancelClicked();
	
	signals:
		void E_CloseWindow();

	};
}


