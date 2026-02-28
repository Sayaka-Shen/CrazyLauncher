#include "WindowButtonView.h"

#include "QHBoxLayout"
#include "QPushButton"

namespace Cl 
{
	WindowButtonView::WindowButtonView(QWidget* parent)
	{
		// Style for the whole widget
		setObjectName("WindowButtonView");
		setAttribute(Qt::WA_StyledBackground, true);

		CreateLayout();
		CreateUI();
		SetupLayout();
	}

	WindowButtonView::~WindowButtonView()
	{

	}

	QPushButton* WindowButtonView::GetRegisterBtn()
	{
		return m_registerBtn;
	}

	QPushButton* WindowButtonView::GetCancelBtn()
	{
		return m_cancelBtn;
	}

	void WindowButtonView::CreateLayout()
	{
		m_buttonLayout = new QHBoxLayout(this);
	}

	void WindowButtonView::CreateUI()
	{
		m_registerBtn = new QPushButton(this); 
		m_registerBtn->setObjectName("RegisterBtn");

		m_cancelBtn = new QPushButton("Cancel", this);
	}

	void WindowButtonView::SetupLayout()
	{
		m_buttonLayout->addStretch(1);
		m_buttonLayout->addWidget(m_cancelBtn);
		m_buttonLayout->addWidget(m_registerBtn);
	}

}

