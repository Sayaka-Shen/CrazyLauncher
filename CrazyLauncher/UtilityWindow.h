#pragma once
#include <QDialog>
#include "Project.h"
#include <WindowMode.h>
#include <PathState.h>

class QString;
class QLabel;
class QLineEdit;
class QWidget;
class QCheckBox;
class QVBoxLayout;
class QHBoxLayout;
class QButtonGroup;
class QCheckBox;


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
	void SetEditModeDefaultValue();
	void closeEvent(QCloseEvent* event) override;

	// Path
	void UpdatePathState();
	void CheckPathContent(QString& path);
	void OpenProjectExplorer();
	void OpenSoftwareExplorer();

	// Button Function 
	void OnRegisterClicked();
	void OnEditClicked();
	void OnCancelClicked();
	
	// Button custom functions
	WindowMode m_mode;
	PathState m_pathState = PathState::File;
	Project* m_project;

	QVBoxLayout* m_windowLayout;
	QHBoxLayout* m_buttonLayout;
	QHBoxLayout* m_pathProjectLayout;
	QHBoxLayout* m_pathSoftwareLayout;
	QHBoxLayout* m_typeLayout;

	QLabel* m_name;
	QLabel* m_desc;

	// Create different ways for handling different project
	QLabel* m_pathType;
	QButtonGroup* m_typesGroup;
	QCheckBox* m_directoryType;
	QCheckBox* m_fileType;

	QLabel* m_path;
	QLabel* m_softwarePath;

	QLineEdit* m_nameField;
	QLineEdit* m_descField;
	QLineEdit* m_pathField;
	QLineEdit* m_softwarePathField;
	
	QPushButton* m_projectExplorer;
	QPushButton* m_softwareExplorer;

	QPushButton* m_cancelBtn;
	QPushButton* m_registerBtn;

signals:
	void E_AddProject(const Project& project);
	void E_EditProject(Project* baseProjectEdited);
	void E_CloseWindow();

};

