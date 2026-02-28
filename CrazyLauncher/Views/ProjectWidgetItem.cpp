#include "ProjectWidgetItem.h"

#include "QLabel"
#include "QHBoxLayout"
#include "QPixmap"
#include "QVBoxLayout"

namespace Cl
{
	ProjectWidgetItem::ProjectWidgetItem(QString title, QString description, QWidget* parent)
	{
		setObjectName("ProjectWidgetItem");
		setAttribute(Qt::WA_StyledBackground, true);

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
		m_projectIcon->setObjectName("Icon");

		m_projectTitle = new QLabel(this);
		m_projectTitle->setObjectName("Title");

		m_projectDesc = new QLabel(this);
		m_projectDesc->setObjectName("Desc");

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

		m_textItemLayout->setSpacing(0);
		m_textItemLayout->setContentsMargins(0, 0, 0, 0);
		m_textItemLayout->addStretch(1);

		m_itemLayout->addWidget(m_projectIcon, 0);
		m_itemLayout->addLayout(m_textItemLayout, 1);

		m_itemLayout->setSpacing(0);
		m_itemLayout->setContentsMargins(0, 0, 0, 0);
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
