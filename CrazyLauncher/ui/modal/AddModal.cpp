#include "AddModal.h"
#include "core/Project.h"
#include "ui/widget/WindowButtonView.h"

#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QFileInfo>
#include <QIcon>
#include <QStandardPaths>
#include <QCheckBox>

namespace Cl
{
	AddModal::AddModal(QWidget* parent) : QDialog(parent)
	{
		setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		setFixedSize(600, 400);
		setObjectName("Modal");

		InitUI();
		InitConnections();
	}

	void AddModal::InitUI()
	{
		m_modalLayout = new QVBoxLayout(this);
		m_modalLayout->setContentsMargins(0, 0, 0, 0);
		m_modalLayout->setSpacing(0);

		auto* nameLayout = new QVBoxLayout();
		m_name = new QLabel("Project Name :");
		m_name->setObjectName("ProjectName");
		nameLayout->addWidget(m_name);

		m_nameField = new QLineEdit();
		nameLayout->addWidget(m_nameField);

		m_modalLayout->addLayout(nameLayout);

		auto* descLayout = new QVBoxLayout();
		m_desc = new QLabel("Description :");
		descLayout->addWidget(m_desc);

		m_descField = new QLineEdit();
		m_descField->setMaxLength(150);
		descLayout->addWidget(m_descField);

		m_modalLayout->addLayout(descLayout);

		auto* projectTypeLayout = new QVBoxLayout();
		m_projectType = new QLabel("Project Type :");
		projectTypeLayout->addWidget(m_projectType);

		m_projectTypeComboBox = new QComboBox();
		InitProjectType();
		projectTypeLayout->addWidget(m_projectTypeComboBox);

		m_modalLayout->addLayout(projectTypeLayout);

		auto* projectPathLayout = new QVBoxLayout();
		m_path = new QLabel("Project Path :", this);
		projectPathLayout->addWidget(m_path);

		auto* pathFieldLayout = new QHBoxLayout();
		m_pathField = new QLineEdit();
		m_pathField->setObjectName("PathField");
		pathFieldLayout->addWidget(m_pathField);

		m_projectExplorer = new QPushButton();
		m_projectExplorer->setIcon(QIcon(":/new/prefix1/assets/folder-black-white.png"));
		m_projectExplorer->setDefault(false);
		m_projectExplorer->setAutoDefault(false);
		m_projectExplorer->setObjectName("ExplorerBtn");

		pathFieldLayout->addWidget(m_projectExplorer);

		projectPathLayout->addLayout(pathFieldLayout);

		m_modalLayout->addLayout(projectPathLayout);

		m_buttonView = new WindowButtonView();
		m_modalLayout->addWidget(m_buttonView);
	}

	void AddModal::InitConnections()
	{
		connect(m_buttonView, &WindowButtonView::onAcceptModal, this, &AddModal::OnAcceptModal);
		connect(m_buttonView, &WindowButtonView::onCancelModal, this, &AddModal::OnRejectModal);
		connect(m_projectExplorer, &QPushButton::pressed, this, &AddModal::FindProject);
	}

	void AddModal::InitProjectType()
	{
		m_projectTypeComboBox->addItem("Script", QVariant::fromValue(ProjectType::Script));
		m_projectTypeComboBox->addItem("Unreal", QVariant::fromValue(ProjectType::Unreal));
		m_projectTypeComboBox->addItem("Unity", QVariant::fromValue(ProjectType::Unity));
		m_projectTypeComboBox->addItem("Blender", QVariant::fromValue(ProjectType::Blender));
		m_projectTypeComboBox->addItem("Photoshop", QVariant::fromValue(ProjectType::Photoshop));
		m_projectTypeComboBox->addItem("Zbrush", QVariant::fromValue(ProjectType::Zbrush));
	}

	// SLOTS
	void AddModal::OnAcceptModal()
	{
		if (IsOneOfTheFieldEmpty()) return;

		QString path = m_pathField->text();
		QFileInfo info(path);
		bool isDir = info.exists() && info.isDir();

		Project project{m_nameField->text(), m_descField->text(), m_projectTypeComboBox->currentData().value<ProjectType>(), m_pathField->text(), isDir, m_softwarePathField->text()};

		emit addProject(project);

		accept();
	}

	void AddModal::OnRejectModal()
	{
		emit rejectModal();
		reject();
	}

	// Utilities
	bool AddModal::IsOneOfTheFieldEmpty()
	{
		return m_nameField->text().isEmpty() || m_descField->text().isEmpty() || m_pathField->text().isEmpty();
	}

	void AddModal::FindProject()
	{
		QString path;

		if (m_projectTypeComboBox->currentData().value<ProjectType>() == ProjectType::Unity)
		{
			path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
		}
		else
		{
			path = QFileDialog::getOpenFileName(this, tr("Open File"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), projectTypeToFilter[m_projectTypeComboBox->currentData().value<ProjectType>()]);
		}

		if (!path.isEmpty())
		{
			m_pathField->setText(path);
		}
	}
}

