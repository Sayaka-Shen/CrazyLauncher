#pragma once
#include <QWidget>

class QVBoxLayout;
class QLabel;
class QListWidgetItem;

namespace Cl
{
	struct Project;

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
		QLabel* m_descriptionField;

		QLabel* m_path;
		QLabel* m_pathField;

		QLabel* m_pathSoftware;
		QLabel* m_pathSoftwareField;

		void CreateLayout();
		void CreateUI();
		void SetupLayout();
		void SetupConnections();

		void SetDefaultValue();

	public slots:
		void OnSelectedProjectChanged(Project& project);
	};
}

