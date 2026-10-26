#include "ProjectWidgetItem.h"

#include "QLabel"
#include "QHBoxLayout"

namespace Cl
{
	ProjectWidgetItem::ProjectWidgetItem(QWidget* parent) : QWidget(parent), m_projectItem(std::make_unique<ProjectItem>())
	{
		setObjectName("ProjectWidgetItem");
		setAttribute(Qt::WA_StyledBackground, true);

		InitUI();
	}

	void ProjectWidgetItem::InitUI()
	{
		m_itemLayout = new QHBoxLayout(this);
		m_itemLayout->setSpacing(0);
		m_itemLayout->setContentsMargins(0, 0, 0, 0);
		
		m_projectIcon = new QLabel(this);
		m_projectIcon->setObjectName("Icon");
		QPixmap pixmap(":/new/prefix1/assets/Folder-Icon");
		pixmap = pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		m_projectIcon->setPixmap(pixmap);

		m_itemLayout->addWidget(m_projectIcon, 0);

		auto* textLayout = new QVBoxLayout();
		textLayout->setSpacing(0);
		textLayout->setContentsMargins(0, 0, 0, 0);

		m_projectTitle = new QLabel();
		m_projectTitle->setObjectName("Title");
		textLayout->addWidget(m_projectTitle);

		m_projectDesc = new QLabel();
		m_projectDesc->setObjectName("Desc");
		textLayout->addWidget(m_projectDesc);

		textLayout->addStretch(1);

		m_itemLayout->addLayout(textLayout, 1);
	}

	const ProjectItem* ProjectWidgetItem::GetProjectInfo() const
	{
		return m_projectItem.get();
	}

	void ProjectWidgetItem::SetProjectInfo(QString name, QString desc)
	{
		m_projectItem->name = name;

		int textLimit = 35;
		QString displayText = desc;

		if (desc.length() > textLimit)
		{
			displayText = desc.left(textLimit) + "...";
		}

		m_projectItem->desc = displayText;

		m_projectTitle->setText(name);
		m_projectDesc->setText(desc);
	}
}
