#include "CategoryWidgetItem.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QIcon>

namespace Cl
{
	CategoryWidgetItem::CategoryWidgetItem(QString name, int projectNb, QString iconPath, QWidget* parent /*= nullptr*/) : 
		QWidget(parent), m_categoryName(name), m_projectNb(projectNb), m_iconPath(iconPath)
	{
		setObjectName("categoryCard");
		setAttribute(Qt::WA_StyledBackground, true);
		InitUI();
	}

	void CategoryWidgetItem::InitUI()
	{
		m_mainLayout = new QHBoxLayout(this);
		
		m_categoryIconLabel = new QLabel();
		m_categoryIconLabel->setContentsMargins(10, 0, 10, 0);
		QPixmap pixmap(m_iconPath);
		m_categoryIconLabel->setPixmap(pixmap.scaled(28, 28, Qt::KeepAspectRatio, Qt::SmoothTransformation));

		m_mainLayout->addWidget(m_categoryIconLabel);

		auto* infoLayout = new QVBoxLayout();
		infoLayout->setContentsMargins(0, 5, 0, 5);
		m_categoryNameLabel = new QLabel(m_categoryName);
		m_categoryProjectNumber = new QLabel(QString::number(m_projectNb) + " projet");
		infoLayout->addWidget(m_categoryNameLabel);
		infoLayout->addWidget(m_categoryProjectNumber);

		m_mainLayout->addLayout(infoLayout);
		m_mainLayout->addStretch();
	}
}