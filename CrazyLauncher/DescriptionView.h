#pragma once
#include <QWidget>

class QVBoxLayout;
class QLabel;

class DescriptionView : public QWidget
{
	Q_OBJECT

public:
	explicit DescriptionView(QWidget* parent = nullptr);
	~DescriptionView();

private:
	QVBoxLayout* m_descViewLayout;
	QLabel* m_title;
	QLabel* m_description;
	QLabel* m_path;

};

