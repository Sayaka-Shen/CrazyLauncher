#pragma once
#include "QDialog"
#include "../../Core/Project.h"

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

		std::map<ProjectType, QString> projectTypeToFilter =
		{
			{ Executable, "*.exe" },
			{ Script, "*.sln" },
			{ Unreal, "*.uproject" },
			{ Unity, "" },
			{ Blender, "*.blend" },
			{ Photoshop, "*.psd" },
			{ Custom, "" },
		};

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
		QPushButton* m_projectExplorer;

		QLabel* m_softwareExe;
		QLineEdit* m_softwarePathField;
		QPushButton* m_softwareExplorer;

		QPushButton* m_cancelBtn;
		QPushButton* m_registerBtn;


		// Utility functions
		void SetButtonRegisterText(QString registerText);

		bool IsOneOfTheFieldEmpty();
		bool HasOneOfTheFieldChanged(const Project& project);

		void ShowSoftwarePath();
		void HideSoftwarePath();

	private:
		// UI Add Window base functions
		void CreateLayout();
		void CreateUI();
		void SetupLayout();
		void SetupConnections();

		void SetupProjectTypeDP();

		// Utility Functions 
		void FindProject();
		void FindSoftware();
		void CheckProjectType(int index);


		// Close Window
		void closeEvent(QCloseEvent* event) override;
		void OnCancelClicked();
	
	signals:
		void E_CloseWindow();

	};
}


