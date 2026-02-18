#pragma once
#include "QWidget"

class QHBoxLayout;
class QVBoxLayout;
class QLabel;

namespace Cl
{
	class ProjectWidgetItem : public QWidget
	{
		Q_OBJECT

	public:
		explicit ProjectWidgetItem(QString title, QString description, QString path, QString softwarePath, QWidget* parent = nullptr);
		~ProjectWidgetItem();

		QString GetProjectTitle();
		QString GetProjectDescription();

		void SetProjectTitle(QString newTitle);
		void SetProjectDescription(QString newDescription);

	private:
		void CreateUI();
		void CreateLayout();
		void SetupLayout();

		QHBoxLayout* m_itemLayout;
		QVBoxLayout* m_textItemLayout;

		QLabel* m_projectIcon;
		QLabel* m_projectTitle;
		QLabel* m_projectDesc;

	};
}

