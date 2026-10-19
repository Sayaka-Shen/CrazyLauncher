#pragma once
#include <QWidget>

class QVBoxLayout;
class QLabel;
class QListWidgetItem;
class QScrollArea;

namespace Cl
{
	struct Project;

	class ProjectDetailsView : public QWidget
	{
		Q_OBJECT

	public:
		explicit ProjectDetailsView(QWidget* parent = nullptr);
		~ProjectDetailsView() override = default;

	public:
		void SetCurrentProject(const Project& project);

	private:
		QVBoxLayout* m_descViewLayout;

		QLabel* m_title;

		QLabel* m_description;
		QLabel* m_descriptionField;

		QLabel* m_path;
		QLabel* m_pathField;

		QLabel* m_pathSoftware;
		QLabel* m_pathSoftwareField;

	private:
		void InitUI();

	};
}

