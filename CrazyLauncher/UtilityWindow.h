#pragma once
#include <array>
#include <QDialog>
#include "Project.h"

class QString;
class QLabel;
class QLineEdit;
class QWidget;
class QCheckBox;
class QVBoxLayout;
class QHBoxLayout;
class QButtonGroup;

enum WindowMode
{
	Add,
	Edit
};

class UtilityWindow : public QDialog
{
	Q_OBJECT 

public:
	explicit UtilityWindow(WindowMode mode, QWidget* parent = nullptr, Project* project = nullptr);
	~UtilityWindow();

private:
	// UI Window functions
	void CreateUI();
	void CreateLayout();
	void SetupLayout();
	void SetupConnections();

	// Set edit field default value
	void SetDefaultValue();
	void closeEvent(QCloseEvent* event) override;
	void OpenFileExplorer();
	void OpenFolderExplorer();

	// Button Function 
	void OnRegisterClicked();
	void OnEditClicked();
	void OnCancelClicked();
	
	// Button custom functions
	WindowMode m_mode;
	Project* m_project;

	QVBoxLayout* m_windowLayout;
	QHBoxLayout* m_buttonLayout;
	QHBoxLayout* m_pathLayout;

	QLabel* m_name;
	QLabel* m_desc;
	QLabel* m_path;

	QLineEdit* m_nameField;
	QLineEdit* m_descField;
	QLineEdit* m_pathField;
	
	QPushButton* m_openFileExplorer;
	QPushButton* m_openFolderExplorer;

	QPushButton* m_cancelBtn;
	QPushButton* m_registerBtn;

signals:
	void E_AddProject(const Project& project);
	void E_EditProject(Project* baseProjectEdited);
	void E_CloseWindow();

};

