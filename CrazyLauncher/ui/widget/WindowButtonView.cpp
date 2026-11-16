#include "WindowButtonView.h"

#include "QHBoxLayout"
#include "QPushButton"
#include "QLabel"
#include "QString"

namespace Cl 
{
	WindowButtonView::WindowButtonView(QString modalAcceptButtonTxt, QWidget* parent) : QWidget(parent), m_modalAcceptButtonText(modalAcceptButtonTxt)
	{
		setObjectName("WindowButtonView");
		setAttribute(Qt::WA_StyledBackground, true);
		setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

		InitUI();
		InitConnections();
	}
	
	void WindowButtonView::SetInfoText(QString text, QString style)
	{
		m_info->setText(text);
		m_info->setStyleSheet(style);
	}

	void WindowButtonView::InitUI()
	{
		m_buttonLayout = new QHBoxLayout(this);

		m_info = new QLabel();
		m_info->setContentsMargins(10, 0, 10, 0);
		m_buttonLayout->addWidget(m_info);

		m_buttonLayout->addStretch();

		m_cancelBtn = new QPushButton("Cancel");
		m_cancelBtn->setObjectName("ApplicationButton");
		m_cancelBtn->setAutoDefault(false);

		m_buttonLayout->addWidget(m_cancelBtn);

		m_registerBtn = new QPushButton(m_modalAcceptButtonText);
		m_registerBtn->setObjectName("HighlightButton");
		m_registerBtn->setAutoDefault(true);
		m_registerBtn->setDefault(true);

		m_buttonLayout->addWidget(m_registerBtn);
	}

	void WindowButtonView::InitConnections()
	{
		connect(m_cancelBtn, &QPushButton::pressed, this, &WindowButtonView::onCancelModal);
		connect(m_registerBtn, &QPushButton::pressed, this, &WindowButtonView::onAcceptModal);
	}
}

