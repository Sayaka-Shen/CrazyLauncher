#pragma once
#include <QWidget>

class QVBoxLayout;
class QLabel;
class QListWidgetItem;

class DescriptionView : public QWidget
{
	Q_OBJECT

public:
	explicit DescriptionView(QWidget* parent = nullptr);
	~DescriptionView();

private:
	void CreateLayout();
	void CreateUI();
	void SetupLayout();
	void SetupConnections();

	void SetDefaultValue();

	QVBoxLayout* m_descViewLayout;

	QLabel* m_title;

	QLabel* m_description;
	QLabel* m_descriptionField;

	QLabel* m_path;
	QLabel* m_pathField;

public slots:
	void OnSelectedProjectChanged(QListWidgetItem* current, QListWidgetItem* previous);

};

