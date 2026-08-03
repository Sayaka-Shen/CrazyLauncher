#include "CategoryWidget.h"

#include <QVBoxLayout>
#include <QLabel>

namespace Cl
{
	CategoryWidget::CategoryWidget(QWidget* parent /*= nullptr*/) : QWidget(parent)
	{
		InitUI();
	}
	
	CategoryWidget::~CategoryWidget() { }

	void CategoryWidget::InitUI()
	{
		m_mainLayout = new QVBoxLayout(this);
		m_titleLayout = new QHBoxLayout();
		m_listingLayout = new QVBoxLayout();
		m_settingsLayout = new QVBoxLayout();

		m_titleWidget = new QLabel("Category", this);
	}

}