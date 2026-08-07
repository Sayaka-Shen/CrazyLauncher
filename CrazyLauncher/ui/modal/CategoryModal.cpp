#include "CategoryModal.h"
#include <iostream>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Cl
{
	CategoryModal::CategoryModal(QWidget* parent /*= nullptr*/) : QDialog(parent)
	{
		setFixedSize(300, 150);
		InitUI();
		InitConnections();
	}

	void CategoryModal::InitUI()
	{
		m_mainLayout = new QVBoxLayout(this);
		m_buttonLayout = new QHBoxLayout();
		
		m_mainLayout->setSpacing(5);
		m_mainLayout->setContentsMargins(10, 10, 10, 10);

		m_categoryName = new QLabel("Nom de la catégorie");
		m_categoryInput = new QLineEdit();
		m_mainLayout->addWidget(m_categoryName);
		m_mainLayout->addWidget(m_categoryInput);
		m_mainLayout->addStretch();

		m_cancelBtn = new QPushButton("Annuler");
		m_validateBtn = new QPushButton("Ajouter une catégorie");
		m_buttonLayout->addWidget(m_cancelBtn);
		m_buttonLayout->addWidget(m_validateBtn);
		m_buttonLayout->setSpacing(5);

		m_mainLayout->addLayout(m_buttonLayout);
	}

	void CategoryModal::InitConnections()
	{
		connect(m_cancelBtn, &QPushButton::pressed, this, &CategoryModal::OnCancelAction);
		connect(m_validateBtn, &QPushButton::pressed, this, &CategoryModal::OnValidateAction);
	}

	void CategoryModal::OnCancelAction()
	{
		std::cout << "Cancel" << std::endl;
		emit E_cancelAction();
	}

	void CategoryModal::OnValidateAction()
	{
		std::cout << "Ajoute une catégorie" << std::endl;
		emit E_validateAction();
	}

}