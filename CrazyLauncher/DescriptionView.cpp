#include "DescriptionView.h"
#include <QVBoxLayout>
#include <QLabel>
#include "ProjectWidgetItem.h"
#include <QListWidget>

DescriptionView::DescriptionView(QWidget* parent)
{
	CreateLayout();
	CreateUI();
	SetupLayout();
	SetupConnections();
	SetDefaultValue();
}

DescriptionView::~DescriptionView() {}

void DescriptionView::CreateLayout()
{
	m_descViewLayout = new QVBoxLayout(this);
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
	m_descViewLayout->addWidget(m_descriptionField);

	m_descViewLayout->addWidget(m_path);
	m_descViewLayout->addWidget(m_pathField);

	m_descViewLayout->addWidget(m_pathSoftware);
	m_descViewLayout->addWidget(m_pathSoftwareField);
}

void DescriptionView::SetupConnections()
{

}

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

void DescriptionView::OnSelectedProjectChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
	if (current == nullptr)
	{
		SetDefaultValue();
		return;
	}

	QListWidget* projectList = current->listWidget();
	ProjectWidgetItem* currentWidgetItem = static_cast<ProjectWidgetItem*>(projectList->itemWidget(current));

	m_title->setText(currentWidgetItem->GetProjectTitle());
	m_descriptionField->setText(currentWidgetItem->GetProjectDescription());
}
