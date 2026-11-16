#include "ProjectDetailsView.h"
#include "ProjectWidgetItem.h"
#include "core/Project.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QScrollArea>


namespace Cl
{
	ProjectDetailsView::ProjectDetailsView(QWidget* parent) : QWidget(parent)
	{
		setObjectName("ProjectDetailsView");
		setAttribute(Qt::WA_StyledBackground, true);

		InitUI();
	}

	void ProjectDetailsView::EditProjectInDetailsView(const Project& project)
	{
		if (project.name == "") return;
		m_title->setText(project.name);
		m_descriptionField->setText(project.description);
		m_pathField->setText(project.path);
		m_pathSoftwareField->setText(project.executable);
	}

	void ProjectDetailsView::InitUI()
	{
		m_centralLayout = new QVBoxLayout(this);

		m_title = new QLabel("Project");
		m_title->setObjectName("ProjectTitle");

		m_centralLayout->addWidget(m_title);
		m_centralLayout->setSpacing(10);

		auto* descLayout = new QVBoxLayout();
		descLayout->setContentsMargins(3, 0, 2, 0);
		m_description = new QLabel("Description :");
		m_description->setObjectName("DetailsLabel");

		descLayout->addWidget(m_description);

		m_descriptionField = new QLabel("This is Project A [...]");
		m_descriptionField->setObjectName("DetailsField");
		m_descriptionField->setWordWrap(true);

		descLayout->addWidget(m_descriptionField);

		m_centralLayout->addLayout(descLayout);

		auto* pathLayout = new QVBoxLayout();
		pathLayout->setContentsMargins(3, 0, 2, 0);
		m_path = new QLabel("Path :");
		m_path->setObjectName("DetailsLabel");

		pathLayout->addWidget(m_path);

		m_pathField = new QLabel("C:/Project/[...]");
		m_pathField->setObjectName("DetailsField");
		m_pathField->setWordWrap(true);

		pathLayout->addWidget(m_pathField);

		m_centralLayout->addLayout(pathLayout);

		auto* pathSoftwareLayout = new QVBoxLayout();
		pathSoftwareLayout->setContentsMargins(3, 0, 2, 0);
		m_pathSoftware = new QLabel("Executable :");
		m_pathSoftware->setObjectName("DetailsLabel");

		pathSoftwareLayout->addWidget(m_pathSoftware);

		m_pathSoftwareField = new QLabel("C:/Program Files/[...].exe");
		m_pathSoftwareField->setObjectName("DetailsField");
		m_pathSoftwareField->setWordWrap(true);

		pathSoftwareLayout->addWidget(m_pathSoftwareField);

		m_centralLayout->addLayout(pathSoftwareLayout);

		m_centralLayout->addStretch(1);
	}
}