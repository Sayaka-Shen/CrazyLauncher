#include "CategoryWidgetItem.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

namespace Cl
{
	CategoryWidgetItem::CategoryWidgetItem(QString name, int projectNb, QString iconPath, QWidget* parent /*= nullptr*/) : 
		QWidget(parent), m_categoryName(name), m_projectNb(projectNb), m_iconPath(iconPath)
	{
		InitUI();
	}

	void CategoryWidgetItem::InitUI()
	{
		m_mainLayout = new QHBoxLayout(this);
		
		auto* infoLayout = new QVBoxLayout();
		m_categoryNameLabel = new QLabel(m_categoryName);
		m_categoryProjectNumber = new QLabel(QString::number(m_projectNb) + " projets");
		infoLayout->addWidget(m_categoryNameLabel);
		infoLayout->addWidget(m_categoryProjectNumber);

		m_mainLayout->addLayout(infoLayout);
	}
}