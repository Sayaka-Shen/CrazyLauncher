#include "CategoryModal.h"
#include <iostream>

#include <data/CategoryModalData.h>
#include <utils/Utils.h>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QFileDialog>
#include <qstandardpaths.h>
#include <QDebug>

namespace Cl
{
	struct DefaultIconEntry
	{
		QString iconPath;
		QString iconName;
	};

	CategoryModal::CategoryModal(QWidget* parent /*= nullptr*/) : QDialog(parent)
	{
		setWindowTitle("Ajouter une categorie");
		InitUI();
		InitConnections();
	}

	void CategoryModal::InitUI()
	{
		m_mainLayout = new QVBoxLayout(this);
		m_mainLayout->setSpacing(20);
		m_mainLayout->setContentsMargins(10, 10, 10, 10);

		m_modalDesc = new QLabel("Informations generales");
		m_modalDesc->setObjectName("description");
		m_modalDesc->setContentsMargins(0, 10, 0, 0);
		Cl::Utils::SetWidgetFont(600, m_modalDesc);
		m_mainLayout->addWidget(m_modalDesc);

		// Category Name Section
		auto* nameSection = new QVBoxLayout();
		nameSection->setSpacing(6);
		m_categorySectionName = new QLabel("Nom de la categorie :");
		m_categoryNameInput = new QLineEdit();
		m_categoryNameInput->setPlaceholderText("Ex: Blender");
		nameSection->addWidget(m_categorySectionName);
		nameSection->addWidget(m_categoryNameInput);

		m_mainLayout->addLayout(nameSection);

		// Software Path Section
		auto* softwareSection = new QVBoxLayout();
		softwareSection->setSpacing(6);
		m_softwareSectionName = new QLabel("Logiciel par defaut : ");
		softwareSection->addWidget(m_softwareSectionName);

		auto* inputSoftwareLayout = new QHBoxLayout();
		inputSoftwareLayout->setSpacing(6);
		m_defaultSoftwareInput = new QLineEdit();
		m_defaultSoftwareInput->setPlaceholderText("Ex: C:/Blender/Blender.exe");
		m_browseSoftwareBtn = new QPushButton("Parcourir...");
		inputSoftwareLayout->addWidget(m_defaultSoftwareInput);
		inputSoftwareLayout->addWidget(m_browseSoftwareBtn);
		softwareSection->addLayout(inputSoftwareLayout);

		m_mainLayout->addLayout(softwareSection);

		// Icon Section
		auto* iconSection = new QVBoxLayout();
		iconSection->setSpacing(6);
		m_iconSectionName = new QLabel("Icone :");
		iconSection->addWidget(m_iconSectionName);
		m_btnVirtualContainer = new QButtonGroup(iconSection);
		m_btnVirtualContainer->setExclusive(true);

		m_iconRows = new QGridLayout();
		m_iconRows->setSpacing(6);
		LoadDefaultIcons();
		LoadCustomIcons();
		iconSection->addLayout(m_iconRows);

		m_addIconBtn = new QPushButton("Choisir une icone personalise");
		iconSection->addWidget(m_addIconBtn);

		m_mainLayout->addLayout(iconSection);

		// Push down the footer section if dialog is getting bigger
		m_mainLayout->addStretch();

		// Footer modal
		auto* footerSection = new QHBoxLayout();
		footerSection->setSpacing(8);
		// push right the two buttons
		footerSection->addStretch();
		m_cancelBtn = new QPushButton("Annuler");
		m_validateBtn = new QPushButton("Ajouter une categorie");
		m_validateBtn->setObjectName("validationButtons");
		footerSection->addWidget(m_cancelBtn);
		footerSection->addWidget(m_validateBtn);

		m_mainLayout->addLayout(footerSection);
	}

	void CategoryModal::InitConnections()
	{
		connect(m_cancelBtn, &QPushButton::clicked, this, &CategoryModal::OnCancelAction);
		connect(m_validateBtn, &QPushButton::clicked, this, &CategoryModal::OnValidateAction);
		connect(m_addIconBtn, &QPushButton::clicked, this, &CategoryModal::OnAddIcons);
		connect(m_browseSoftwareBtn, &QPushButton::clicked, this, &CategoryModal::OnBrowseSoftware);
	}

	void CategoryModal::LoadDefaultIcons()
	{
		QVector<DefaultIconEntry> icons =
		{
			{":/resources/assets/visualStudioIcon.png", "Visual Studio"},
			{":/resources/assets/blenderIcon.png", "Blender"},
			{":/resources/assets/unityIcon.png", "Unity"},
			{":/resources/assets/photoshopIcon.png", "Photoshop"},
			{":/resources/assets/ueIcon.png", "Unreal Engine"},
			{":/resources/assets/folderCategoryIcon.png", "Folder"},
		};

		for (int i = 0; i < icons.length(); ++i)
		{
			AddIconButtons(icons[i].iconPath, icons[i].iconName);
		}
	}

	void CategoryModal::LoadCustomIcons()
	{
		QString storeIconPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/icons";
		QDir dir(storeIconPath);

		if (!dir.exists()) return;

		QStringList files = dir.entryList(QStringList() << "*.png", QDir::Files);

		if (files.isEmpty()) return;

		for (const QString& fileName : files)
		{
			QString fullPath = dir.absoluteFilePath(fileName);
			AddIconButtons(fullPath);
		}
	}

	QPushButton* CategoryModal::AddIconButtons(const QString& filepath, const QString& iconName /*="" */)
	{
		QString displayName = iconName.isEmpty() ? QFileInfo(filepath).baseName() : iconName;

		auto* btn = new QPushButton();
		btn->setIcon(QIcon(filepath));
		btn->setIconSize(QSize(28, 28));
		btn->setCheckable(true);
		btn->setFixedSize(56, 56);
		btn->setObjectName("iconOption");
		btn->setProperty("iconName", displayName);
		btn->setProperty("iconPath", filepath);
		
		int newId = m_iconButtons.size();
		int row = newId / m_iconColumns;
		int col = newId % m_iconColumns;
		m_iconRows->addWidget(btn, row, col);

		m_btnVirtualContainer->addButton(btn, newId);
		m_iconButtons.append(btn);

		return btn;
	}

	void CategoryModal::OnCancelAction()
	{
		reject();
	}

	void CategoryModal::OnValidateAction()
	{
		CategoryModalData data;
		data.name = m_categoryNameInput->text();
		data.softwarePath = m_defaultSoftwareInput->text();

		auto* selectedButton = (QPushButton*)m_btnVirtualContainer->checkedButton();
		if (selectedButton)
		{
			data.iconPath = selectedButton->property("iconPath").toString();
		}

		emit E_validateAction(data);
		accept(); 
	}

	void CategoryModal::OnAddIcons()
	{
		QString filepath = QFileDialog::getOpenFileName(this, "Choisir une icone", QString(), "Images (*.png)");
		
		if (filepath.isEmpty()) return;

		QString storeIconPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/icons";
		QDir().mkpath(storeIconPath);

		QString destpath = storeIconPath + "/" + QFileInfo(filepath).fileName();

		if (QFile::copy(filepath, destpath))
		{
			QPushButton* btn = AddIconButtons(destpath);
			btn->setChecked(true);
		}
	}

	void CategoryModal::OnBrowseSoftware()
	{
		m_defaultSoftwareInput->setText(QFileDialog::getOpenFileName(this, "Choisir un logiciel", QString(), "Logiciel (*.exe)"));
	}
}