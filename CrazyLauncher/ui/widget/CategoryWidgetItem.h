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
		explicit CategoryWidgetItem(QString name, QWidget* parent);
		~CategoryWidgetItem() = default;

	private:
		QHBoxLayout* m_mainLayout;
		QVBoxLayout* m_infoLayout;

		QLabel* m_categoryName;
		QLabel* m_categoryProjectNumber;

	private: 
		void InitUI(QString name);

	};
}