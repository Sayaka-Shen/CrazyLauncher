#include "DescriptionView.h"
#include <QVBoxLayout>
#include <QLabel>

DescriptionView::DescriptionView(QWidget* parent)
{
	CreateLayout();
	CreateUI();
	SetupLayout();
	SetupConnections();
}

DescriptionView::~DescriptionView() {}

void DescriptionView::CreateLayout()
{
	m_descViewLayout = new QVBoxLayout(this);
}

void DescriptionView::CreateUI()
{
	m_title = new QLabel(this);
	m_title->setText("Project");

	m_description = new QLabel(this);
	m_description->setText("Description :");

	m_descriptionField = new QLabel(this);
	m_descriptionField->setText("Project X");

	m_path = new QLabel(this);
	m_path->setText("Path :");

	m_pathField = new QLabel(this);
	m_pathField->setText("C:/");
}

void DescriptionView::SetupLayout()
{
	m_descViewLayout->addWidget(m_title);

	m_descViewLayout->addWidget(m_description);
	m_descViewLayout->addWidget(m_descriptionField);

	m_descViewLayout->addWidget(m_path);
	m_descViewLayout->addWidget(m_pathField);
}

void DescriptionView::SetupConnections()
{

}