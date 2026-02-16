#pragma once
#include "QWidget"

class QHBoxLayout;
class QVBoxLayout;
class QLabel;

class ProjectWidgetItem : public QWidget
{
	Q_OBJECT

public:
	explicit ProjectWidgetItem(QString title, QString description, QString path, QWidget* parent = nullptr);
	~ProjectWidgetItem();

	QString GetProjectTitle();
	QString GetProjectDescription();
	QString GetProjectPath();

	void SetProjectTitle(QString newTitle);
	void SetProjectDescription(QString newDescription);
	void SetProjectPath(QString newPath);

private:
	void CreateUI();
	void CreateLayout();
	void SetupLayout();

	QHBoxLayout* m_itemLayout;
	QVBoxLayout* m_textItemLayout;

	QLabel* m_projectIcon;
	QLabel* m_projectTitle;
	QLabel* m_projectDesc;
	QLabel* m_projectPath;

};

