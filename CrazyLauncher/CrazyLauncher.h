#pragma once
#include <QtWidgets/QMainWindow>

class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class ProjectView;
class DescriptionView;
class SettingsView;
class QString;
class Project;
class UtilityWindow;
class ProjectManager;
class ProjectWidgetItem;

class CrazyLauncher : public QMainWindow
{
    Q_OBJECT

public:
    CrazyLauncher(QWidget *parent = nullptr);
    ~CrazyLauncher();

private:
    void CreateController();
    void CreateLayout();
    void CreateUI();
    void SetupLayout();
    void SetupConnections();

    Project* GetSelectedProjectWidget();
    int GetSelectedProjectWidgetIndex();
    
    QWidget* m_centralWidget;
    ProjectManager* m_projectManager;
	UtilityWindow* m_utiltyWindow;

    QVBoxLayout* m_mainLayout;
    QHBoxLayout* m_centralLayout;
    QHBoxLayout* m_footerLayout;

    ProjectView* m_projectView;
    DescriptionView* m_descView;
    SettingsView* m_settingView;

public slots:
    void RegisterUtilityWindow();
    void EditUtilityWindow();

    void OnProjectAdded(const Project& project);
    void OnProjectEdited(Project* baseProjectEdited);
    void LaunchProject();
    void OnRemoveProject();

    void OnCloseUtilityWindow();

};

