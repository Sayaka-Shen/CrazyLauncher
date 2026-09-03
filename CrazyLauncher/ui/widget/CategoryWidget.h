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
	struct CategoryModalData;
	class CategoryModal;

	class CategoryWidget : public QWidget
	{
		Q_OBJECT

	public:
		explicit CategoryWidget(QWidget* parent = nullptr);
		~CategoryWidget() override = default;

	private:
		QVBoxLayout* m_mainLayout;

		QLabel* m_titleWidget;
		QPushButton* m_newCategory; 
		CategoryModal* m_categoryModal;

		QListWidget* m_categoryList;

		QPushButton* m_backgroundStyleSettings;

	private:
		void InitUI();
		void InitConnections();
		void AddCategory(const CategoryModalData& data);

	signals:
		void E_createCategory(const CategoryModalData& data);

	private slots: 
		void OnCreateModalCategory();
		void OnCategoryValidated(const CategoryModalData& data);
		
	}; 
}