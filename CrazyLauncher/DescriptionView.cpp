#include "DescriptionView.h"
#include <QVBoxLayout>
#include <QLabel>

DescriptionView::DescriptionView(QWidget* parent)
{
	m_title = new QLabel(this);
	m_title->setText("Project A");

	m_description = new QLabel(this);
	m_description->setText("Description of project A..");

	m_path = new QLabel(this);
	m_path->setText("C:/Documents/ProjetPerso/Test/Blabla");

	m_descViewLayout = new QVBoxLayout(this);
	m_descViewLayout->addWidget(m_title);
	m_descViewLayout->addWidget(m_description);
	m_descViewLayout->addWidget(m_path);
}

DescriptionView::~DescriptionView() {}
