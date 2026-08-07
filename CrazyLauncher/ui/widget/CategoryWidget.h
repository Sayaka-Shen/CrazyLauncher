#pragma once
#include <QWidget>

class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QListWidget;
class QFrame;

namespace Cl
{
	class CategoryModal;

	class CategoryWidget : public QWidget
	{
		Q_OBJECT

	public:
		explicit CategoryWidget(QWidget* parent = nullptr);
		~CategoryWidget() = default;

		void AddCategory();

	private:
		QVBoxLayout* m_mainLayout;
		QHBoxLayout* m_titleLayout;
		QVBoxLayout* m_listingLayout;
		QVBoxLayout* m_settingsLayout;

		QLabel* m_titleWidget;
		QPushButton* m_newCategory; 
		CategoryModal* m_categoryModal;

		QListWidget* m_categoryList;

		QPushButton* m_backgroundStyleSettings;

	private:
		void InitUI();
		void InitConnections();
		
	}; 
}