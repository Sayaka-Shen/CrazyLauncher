#include "ProjectWidgetItem.h"
#include "QLabel"
#include "QHBoxLayout"
#include "QVBoxLayout"


ProjectWidgetItem::ProjectWidgetItem(QString title, QString description, QString path, QString softwarePath, QWidget* parent)
{
	CreateLayout();
	CreateUI();
	SetupLayout();
	
	m_projectTitle->setText(title);
	m_projectDesc->setText(description);
	m_projectPath->setText(path);
	m_softwarePath->setText(softwarePath);
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

QString ProjectWidgetItem::GetProjectPath()
{
	return m_projectPath->text();
}

QString ProjectWidgetItem::GetSoftwarePath()
{
	return m_softwarePath->text();
}

void ProjectWidgetItem::SetProjectTitle(QString newTitle)
{
	m_projectTitle->setText(newTitle);
}

void ProjectWidgetItem::SetProjectDescription(QString newDescription)
{
	m_projectDesc->setText(newDescription);
}

void ProjectWidgetItem::SetProjectPath(QString newPath)
{
	m_projectPath->setText(newPath);
}

void ProjectWidgetItem::SetSoftwarePath(QString newSoftPath)
{
	m_softwarePath->setText(newSoftPath);
}

void ProjectWidgetItem::CreateUI()
{
	m_projectIcon = new QLabel(this);
	m_projectTitle = new QLabel(this);
	m_projectDesc = new QLabel(this);

	m_projectPath = new QLabel(this);
	m_projectPath->hide();

	m_softwarePath = new QLabel(this);
	m_softwarePath->hide();
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
