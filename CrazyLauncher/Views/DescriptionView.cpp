#include "DescriptionView.h"
#include "ProjectWidgetItem.h"
#include "../Core/Project.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>


namespace Cl
{
	DescriptionView::DescriptionView(QWidget* parent)
	{
		// Style for the whole widget
		setObjectName("DescriptionView");
		setAttribute(Qt::WA_StyledBackground, true);

		CreateLayout();
		CreateUI();
		SetupLayout();
		SetupConnections();
		SetDefaultValue();
		SetupStyle();
	}

	DescriptionView::~DescriptionView() {}

	void DescriptionView::CreateLayout()
	{
		m_descViewLayout = new QVBoxLayout(this);
		m_descViewLayout->setContentsMargins(0, 0, 0, 0);
		m_descViewLayout->setSpacing(0);
	}

	void DescriptionView::CreateUI()
	{
		m_title = new QLabel(this);

		m_description = new QLabel(this);
		m_descriptionField = new QLabel(this);

		m_path = new QLabel(this);
		m_pathField = new QLabel(this);

		m_pathSoftware = new QLabel(this);
		m_pathSoftwareField = new QLabel(this);
	}

	void DescriptionView::SetupLayout()
	{
		m_descViewLayout->addWidget(m_title);

		m_descViewLayout->addWidget(m_description);
		m_descViewLayout->addSpacing(0);
		m_descViewLayout->addWidget(m_descriptionField);

		m_descViewLayout->addWidget(m_path);
		m_descViewLayout->addWidget(m_pathField);

		m_descViewLayout->addWidget(m_pathSoftware);
		m_descViewLayout->addWidget(m_pathSoftwareField);

		m_descViewLayout->addStretch(1);
	}

	void DescriptionView::SetupConnections() {}

	void DescriptionView::SetDefaultValue()
	{
		m_title->setText("Project");
		m_description->setText("Description :");
		m_descriptionField->setText("This is Project X...");
		m_path->setText("Path :");
		m_pathField->setText("C:/");  
		m_pathSoftware->setText("Software Used :");
		m_pathSoftwareField->setText("C:/");
	}

	void DescriptionView::SetupStyle()
	{
		// Title
		m_title->setObjectName("ProjectTitle");
		
		// Description Label and Field
		m_description->setObjectName("DescriptionLabel");

		m_descriptionField->setObjectName("DescriptionField");
		m_descriptionField->setWordWrap(true);

		// Project Path Label and Field
		m_path->setObjectName("PathLabel");

		m_pathField->setObjectName("PathField");
		m_pathField->setWordWrap(true);

		// Software Path Label and Field
		m_pathSoftware->setObjectName("SoftwareLabel");

		m_pathSoftwareField->setObjectName("SoftwareField");
		m_pathSoftwareField->setWordWrap(true);
	}

	void DescriptionView::OnSelectedProjectChanged(Project& project)
	{
		if (project.IsEmpty())
		{
			SetDefaultValue();
			return;
		}

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