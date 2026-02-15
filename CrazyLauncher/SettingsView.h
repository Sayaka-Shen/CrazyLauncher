#pragma once
#include <QWidget>

class QHBoxLayout;
class QPushButton;
class QDialog;

class SettingsView : public QWidget
{
	Q_OBJECT

public:
	explicit SettingsView(QWidget* parent = nullptr);
	~SettingsView();

	void OnAddWindowClicked();
	void OnEditWindowClicked();
	void OnRemoveProjectClicked();

private:
	void CreateUI();
	void CreateLayout();
	void SetupLayout();
	void SetupConnections();

	QHBoxLayout* m_settingsLayout;

	QPushButton* m_addBtn;
	QPushButton* m_editBtn;
	QPushButton* m_deleteBtn;
	QPushButton* m_launchBtn;

	QDialog* m_addBtnWindow;
	QDialog* m_editBtnWindow;

signals:
	void E_CreateAddWindow();
	void E_CreateEditWindow();
	void E_RemoveProject();

};

