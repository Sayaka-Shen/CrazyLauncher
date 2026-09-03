#pragma once
#include <QWidget>

class QString;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;

namespace Cl 
{
	class CategoryWidgetItem : public QWidget
	{
		Q_OBJECT

	public:
		explicit CategoryWidgetItem(QString name, int projectNb, QString iconPath, QWidget* parent = nullptr);
		~CategoryWidgetItem() = default;

	private:
		QHBoxLayout* m_mainLayout;

		QString m_categoryName;
		int m_projectNb;
		QString m_iconPath;

		QLabel* m_categoryNameLabel;
		QLabel* m_categoryProjectNumber;

	private: 
		void InitUI();

	};
}