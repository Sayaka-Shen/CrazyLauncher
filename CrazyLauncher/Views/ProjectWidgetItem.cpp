#include "ProjectWidgetItem.h"

#include "QLabel"
#include "QHBoxLayout"
#include "QPixmap"
#include "QVBoxLayout"

namespace Cl
{
	ProjectWidgetItem::ProjectWidgetItem(QString title, QString description, QWidget* parent)
	{
		CreateLayout();
		CreateUI();
		SetupLayout();

		SetProjectTitle(title);
		SetProjectDescription(description);
	}

	ProjectWidgetItem::~ProjectWidgetItem() {}

	void ProjectWidgetItem::CreateUI()
	{
		m_projectIcon = new QLabel(this);
		m_projectTitle = new QLabel(this);
		m_projectDesc = new QLabel(this);

		QPixmap pixmap(":/new/prefix1/Folder-Icon");
		pixmap = pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		m_projectIcon->setPixmap(pixmap);
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

	// Getter, Setter for the widget infos
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
		int textLimit = 35;
		QString displayText = newDescription; 

		if (newDescription.length() > textLimit)
		{
			displayText = newDescription.left(textLimit) + "...";
		}
		
		m_projectDesc->setText(displayText);
	}
}
