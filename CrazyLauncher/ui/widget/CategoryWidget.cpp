#include "CategoryWidget.h"
#include "CategoryWidgetItem.h"
#include "modal/CategoryModal.h"
#include <utils/Utils.h>
#include <data/CategoryModalData.h>

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

namespace Cl
{
	CategoryWidget::CategoryWidget(QWidget* parent /*= nullptr*/) : QWidget(parent)
	{
		setObjectName("categoryPanel");
		setAttribute(Qt::WA_StyledBackground, true);
		InitUI();
		InitConnections(); 
	}
	
	void CategoryWidget::InitUI()
	{
		m_mainLayout = new QVBoxLayout(this);
		m_mainLayout->setContentsMargins(8, 20, 8, 20);

		// Title Name Section
		auto* titleSection = new QHBoxLayout();
		titleSection->setContentsMargins(8, 0, 10, 0);
		m_titleWidget = new QLabel("CATEGORIES");
		m_titleWidget->setObjectName("grey");
		Cl::Utils::SetWidgetFont(600, m_titleWidget);
		m_newCategory = new QPushButton();
		m_newCategory->setObjectName("addCategoryButton");
		m_newCategory->setIcon(QIcon(":/resources/assets/plus_grey_icon.png"));
		m_newCategory->setIconSize(QSize(14, 14));
		Cl::Utils::SetWidgetFont(100, m_newCategory);
		titleSection->addWidget(m_titleWidget);
		titleSection->addStretch();
		titleSection->addWidget(m_newCategory);

		m_mainLayout->addLayout(titleSection);

		// Listing Category Name Section
		auto* categoryListSection = new QVBoxLayout();
		categoryListSection->setContentsMargins(5, 12, 5, 12);
		m_categoryList = new QListWidget();
		categoryListSection->addWidget(m_categoryList);

		m_mainLayout->addLayout(categoryListSection);

		// Settings layout
		auto* settingsSection = new QVBoxLayout();
		settingsSection->setContentsMargins(8, 0, 10, 0);
		m_backgroundStyleSettings = new QPushButton("Parametres");
		settingsSection->addWidget(m_backgroundStyleSettings);

		m_mainLayout->addLayout(settingsSection);
	}

	void CategoryWidget::InitConnections()
	{
		connect(m_newCategory, &QPushButton::clicked, this, &CategoryWidget::OnCreateModalCategory);
	}

	void CategoryWidget::OnCreateModalCategory()
	{
		auto* modal = new CategoryModal(this);
		modal->setFixedWidth(400);
		modal->setMaximumHeight(600);
		modal->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint, true);

		connect(modal, &CategoryModal::E_validateAction, this, &CategoryWidget::OnCategoryValidated);
		modal->exec();
	}

	void CategoryWidget::OnCategoryValidated(const CategoryModalData& data)
	{
		emit E_createCategory(data);
		AddCategory(data);
	}

	void CategoryWidget::AddCategory(const CategoryModalData& data)
	{
		QListWidgetItem* item = new QListWidgetItem(m_categoryList);
		item->setSizeHint(QSize(0, 65));
		
		auto* categoryWidgetItem = new CategoryWidgetItem(data.name, E_getNumberOfProject(data.name), data.iconPath, this);
		categoryWidgetItem->setFixedHeight(70);
		m_categoryList->setItemWidget(item, categoryWidgetItem);
	}
}