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
		InitConnections();
	}

	void ProjectDetailsView::InitUI()
	{
		m_descViewLayout = new QVBoxLayout(this);

		m_title = new QLabel("Project");
		m_title->setObjectName("ProjectTitle");

		m_descViewLayout->addWidget(m_title);

		m_description = new QLabel("Description :");
		m_description->setObjectName("DescriptionLabel");

		m_descViewLayout->addWidget(m_description);
		m_descViewLayout->addSpacing(0);

		m_descriptionField = new QLabel("This is Project X...");
		m_descriptionField->setObjectName("DescriptionField");
		m_descriptionField->setWordWrap(true);

		m_descViewLayout->addWidget(m_descriptionField);

		m_path = new QLabel("Path :");
		m_path->setObjectName("PathLabel");

		m_descViewLayout->addWidget(m_path);

		m_pathField = new QLabel("C:/project");
		m_pathField->setObjectName("PathField");
		m_pathField->setWordWrap(true);

		m_descViewLayout->addWidget(m_pathField);

		m_pathSoftware = new QLabel("Software Used :");
		m_pathSoftware->setObjectName("SoftwareLabel");

		m_descViewLayout->addWidget(m_pathSoftware);

		m_pathSoftwareField = new QLabel("C:/Blender.exe");
		m_pathSoftwareField->setObjectName("SoftwareField");
		m_pathSoftwareField->setWordWrap(true);

		m_descViewLayout->addWidget(m_pathSoftwareField);

		m_descViewLayout->addStretch(1);
	}

	void ProjectDetailsView::InitConnections() {}

	void ProjectDetailsView::OnSelectedProjectChanged(Project& project)
	{
		m_title->setText(project.name);
		m_descriptionField->setText(project.description);
		m_pathField->setText(project.path);

		if (project.softwareExe == "")
		{
			m_pathSoftware->hide();
			m_pathSoftwareField->hide();
		}
		else
		{
			m_pathSoftware->show();
			m_pathSoftwareField->show();
			m_pathSoftwareField->setText(project.softwareExe);
		}
	}
}