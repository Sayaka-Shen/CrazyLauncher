#pragma once
#include "QWidget"

class QHBoxLayout;
class QVBoxLayout;
class QLabel;

namespace Cl
{
	struct ProjectItem
	{
		QString name;
		QString desc;
	};

	class ProjectWidgetItem : public QWidget
	{
		Q_OBJECT

	public:
		explicit ProjectWidgetItem(QWidget* parent = nullptr);
		~ProjectWidgetItem() override = default;

		const ProjectItem& GetProjectInfo() const;
		void SetProjectInfo(QString name, QString desc);

	private:
		QHBoxLayout* m_itemLayout;

		QLabel* m_projectIcon;
		QLabel* m_projectTitle;
		QLabel* m_projectDesc;

		ProjectItem m_projectItem;

	private:
		void InitUI();

	};
}

