#pragma once
#include "QWidget"
#include "memory"

class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QMouseEvent;

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

		const ProjectItem* GetProjectInfo() const;
		void SetProjectInfo(QString name, QString desc);

	protected:
		void mouseDoubleClickEvent(QMouseEvent* event) override;

	private:
		QHBoxLayout* m_itemLayout;

		QLabel* m_projectIcon;
		QLabel* m_projectTitle;
		QLabel* m_projectDesc;

		std::unique_ptr<ProjectItem> m_projectItem;

	private:
		void InitUI();
		void InitConnections();

	signals:
		void onDoubleClicked();

	};
}

