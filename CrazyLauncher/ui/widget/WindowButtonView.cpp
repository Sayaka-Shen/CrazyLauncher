#include "WindowButtonView.h"

#include "QHBoxLayout"
#include "QPushButton"

namespace Cl 
{
	WindowButtonView::WindowButtonView(QWidget* parent) : QWidget(parent)
	{
		setObjectName("WindowButtonView");
		setAttribute(Qt::WA_StyledBackground, true);

		InitUI();
		InitConnections();
	}
	
	void WindowButtonView::InitUI()
	{
		m_buttonLayout = new QHBoxLayout(this);

		m_cancelBtn = new QPushButton("Cancel");
		m_cancelBtn->setDefault(false);

		m_buttonLayout->addWidget(m_cancelBtn);

		m_registerBtn = new QPushButton("Add");
		m_registerBtn->setDefault(true);
		m_registerBtn->setObjectName("RegisterBtn");

		m_buttonLayout->addWidget(m_registerBtn);
	}

	void WindowButtonView::InitConnections()
	{
		connect(m_cancelBtn, &QPushButton::pressed, this, &WindowButtonView::onCancelModal);
		connect(m_registerBtn, &QPushButton::pressed, this, &WindowButtonView::onAcceptModal);
	}
}

