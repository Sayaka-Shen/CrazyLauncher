#include "ProjectWidgetItem.h"
#include "QLabel"
#include "QHBoxLayout"
#include "QVBoxLayout"


ProjectWidgetItem::ProjectWidgetItem(QString title, QString description, QWidget* parent)
{
	CreateLayout();
	CreateUI();
	SetupLayout();
	
	m_projectTitle->setText(title);
	m_projectDesc->setText(description);
}

ProjectWidgetItem::~ProjectWidgetItem() {}

QString ProjectWidgetItem::GetProjectTitle()
{
	return m_projectTitle->text();
}

QString ProjectWidgetItem::GetProjectDescription()
{
	return m_projectDesc->text();
}

void ProjectWidgetItem::SetProjectTitle(QString newTitle)
{
	m_projectTitle->setText(newTitle);
}

void ProjectWidgetItem::SetProjectDescription(QString newDescription)
{
	m_projectDesc->setText(newDescription);
}

void ProjectWidgetItem::CreateUI()
{
	m_projectIcon = new QLabel(this);
	m_projectTitle = new QLabel(this);
	m_projectDesc = new QLabel(this);
}

void ProjectWidgetItem::CreateLayout()
{
	m_itemLayout = new QHBoxLayout(this);
	m_textItemLayout = new QVBoxLayout();
}

void ProjectWidgetItem::SetupLayout()
{
	m_textItemLayout->addWidget(m_projectTitle);
	m_textItemLayout->addWidget(m_projectDesc);

	m_itemLayout->addWidget(m_projectIcon, 0);
	m_itemLayout->addLayout(m_textItemLayout, 1);
}
