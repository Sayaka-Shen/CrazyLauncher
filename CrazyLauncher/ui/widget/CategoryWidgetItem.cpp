#include "CategoryWidgetItem.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

namespace Cl
{
	CategoryWidgetItem::CategoryWidgetItem(QString name, QWidget* parent) : QWidget(parent)
	{
		InitUI(name);
	}

	void CategoryWidgetItem::InitUI(QString name)
	{
		m_mainLayout = new QHBoxLayout(this);
		m_infoLayout = new QVBoxLayout();
		
		m_categoryName = new QLabel(name);
		m_categoryProjectNumber = new QLabel("12 projets");
		m_infoLayout->addWidget(m_categoryName);
		m_infoLayout->addWidget(m_categoryProjectNumber);

		m_mainLayout->addLayout(m_infoLayout);
	}
}