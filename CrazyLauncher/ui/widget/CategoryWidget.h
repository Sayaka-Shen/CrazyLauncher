#pragma once
#include <QWidget>

class QVBoxLayout;
class QHBoxLayout;
class QLabel;

namespace Cl
{
	class CategoryWidget : public QWidget
	{
		Q_OBJECT

	public:
		explicit CategoryWidget(QWidget* parent = nullptr);
		~CategoryWidget();

	private:
		QVBoxLayout* m_mainLayout;
		QHBoxLayout* m_titleLayout;
		QVBoxLayout* m_listingLayout;
		QVBoxLayout* m_settingsLayout;

		QLabel* m_titleWidget;

		void InitUI();
		void InitConnections();
		
	};
}