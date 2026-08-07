#include "CategoryWidget.h"
#include "CategoryWidgetItem.h"
#include "modal/CategoryModal.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

namespace Cl
{
	CategoryWidget::CategoryWidget(QWidget* parent /*= nullptr*/) : QWidget(parent)
	{
		InitUI();
		InitConnections(); 
	}
	
	void CategoryWidget::InitUI()
	{
		m_mainLayout = new QVBoxLayout(this);
		m_titleLayout = new QHBoxLayout();
		m_listingLayout = new QVBoxLayout();
		m_settingsLayout = new QVBoxLayout();

		m_mainLayout->setContentsMargins(8, 8, 8, 8);

		// Title layout "Category   +"
		m_titleWidget = new QLabel("Category");
		m_newCategory = new QPushButton("+");
		m_categoryModal = new CategoryModal();
		m_titleLayout->addWidget(m_titleWidget);
		m_titleLayout->addWidget(m_newCategory);

		// Listing category layout
		m_categoryList = new QListWidget();
		m_listingLayout->addWidget(m_categoryList);

		// Settings layout
		m_backgroundStyleSettings = new QPushButton("");
		m_settingsLayout->addWidget(m_backgroundStyleSettings);

		m_mainLayout->addLayout(m_titleLayout);
		m_mainLayout->addLayout(m_listingLayout);
		m_mainLayout->addLayout(m_settingsLayout);
	}

	void CategoryWidget::InitConnections()
	{
		connect(m_newCategory, &QPushButton::pressed, m_categoryModal, &CategoryModal::open);
	}

	void CategoryWidget::AddCategory()
	{
		QListWidgetItem* item = new QListWidgetItem(m_categoryList);
		item->setSizeHint(QSize(0, 65));
		
		CategoryWidgetItem* categoryWidgetItem = new CategoryWidgetItem("Blender", this);
		m_categoryList->setItemWidget(item, categoryWidgetItem);
	}

}