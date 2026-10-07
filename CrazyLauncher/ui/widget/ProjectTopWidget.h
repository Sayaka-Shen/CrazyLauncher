#pragma once
#include <QWidget>
#include <core/data/category.h>

class QVBoxLayout;
class QPushButton;
class QLabel;
class QLineEdit;

namespace Cl
{
	class ProjectTopWidget : public QWidget
	{
		Q_OBJECT

	public:
		explicit ProjectTopWidget(Category currentCategory, QWidget* parent = nullptr);
		~ProjectTopWidget() override = default;


	private:
		Category m_currentCategory;
		QVBoxLayout* m_mainLayout;

		QLabel* m_categoryIcon;
		QLabel* m_categoryName;
		QLabel* m_numberOfProjects;

		QPushButton* m_addProjectButton;

		QLineEdit* m_searchBar;

	private:
		void InitUI();
	};
}


