#include "ProjectModal.h"
#include "core/Project.h"
#include "ui/widget/WindowButtonView.h"

#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStandardPaths>
#include <QAbstractButton>
#include <QButtonGroup>

namespace Cl
{
	ProjectModal::ProjectModal(ProjectTypeRegistry& projectTypeRegistry, QWidget* parent) : QDialog(parent), m_projectTypeRegistry(projectTypeRegistry)
	{
		setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		setFixedSize(600, 400);
		setObjectName("Modal");

		InitUI();
		InitConnections();
	}

	ProjectModal::ProjectModal(Project* existedProject, ProjectTypeRegistry& projectTypeRegistry, QWidget* parent /*= nullptr*/) : m_currentProject(existedProject), QDialog(parent), m_projectTypeRegistry(projectTypeRegistry)
	{
		setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		setFixedSize(600, 400);
		setObjectName("Modal");

		InitUI();
		SetFieldDefaultValue();
		InitConnections();
	}

	void ProjectModal::closeEvent(QCloseEvent* event)
	{
		reject();
	}

	Project ProjectModal::GetProject() const
	{
		QString path = m_pathField->text();
		QFileInfo info(path);
		bool isDir = info.exists() && info.isDir();

		Project project
		{
			m_nameField->text(),
			m_descField->text(),
			m_projectTypeRegistry.GetProjectTypeByName((m_projectTypeButtonGroup->checkedButton()->text())),
			m_pathField->text(),
			isDir
		};

		return project;
	}

	void ProjectModal::InitUI()
	{
		m_modalLayout = new QVBoxLayout(this);
		m_modalLayout->setAlignment(Qt::AlignLeft);
		m_modalLayout->setContentsMargins(0, 0, 0, 0);
		m_modalLayout->setSpacing(10);

		auto* nameLayout = new QVBoxLayout();
		nameLayout->setContentsMargins(15, 10, 15, 0);
		m_name = new QLabel("Project Name :");
		nameLayout->addWidget(m_name);

		m_nameField = new QLineEdit();
		nameLayout->addWidget(m_nameField);

		m_modalLayout->addLayout(nameLayout);

		auto* descLayout = new QVBoxLayout();
		descLayout->setContentsMargins(15, 0, 15, 0);

		m_desc = new QLabel("Description :");
		descLayout->addWidget(m_desc);

		m_descField = new QLineEdit();
		m_descField->setMaxLength(150);
		descLayout->addWidget(m_descField);

		m_modalLayout->addLayout(descLayout);

		auto* projectTypeLayout = new QVBoxLayout();
		projectTypeLayout->setContentsMargins(15, 0, 15, 0);
		m_projectType = new QLabel("Project Type :");
		projectTypeLayout->addWidget(m_projectType);

		auto* projectCheckBoxLayout = new QGridLayout();
		projectCheckBoxLayout->setAlignment(Qt::AlignLeft);
		projectCheckBoxLayout->setVerticalSpacing(10);
		m_projectTypeButtonGroup = InitProjectType(projectCheckBoxLayout);

		projectTypeLayout->addLayout(projectCheckBoxLayout);
		m_modalLayout->addLayout(projectTypeLayout);

		auto* projectPathLayout = new QVBoxLayout();
		projectPathLayout->setContentsMargins(15, 0, 15, 10);
		m_path = new QLabel("Project Path :", this);
		projectPathLayout->addWidget(m_path);

		auto* pathFieldLayout = new QHBoxLayout();
		pathFieldLayout->setSpacing(2);
		m_pathField = new QLineEdit();
		pathFieldLayout->addWidget(m_pathField, 2);

		m_btnplorer = new QPushButton();
		m_btnplorer->setIcon(QIcon(":/new/prefix1/assets/folder-black-white.png"));
		m_btnplorer->setObjectName("ExplorerButton");
		m_btnplorer->setDefault(false);
		pathFieldLayout->addWidget(m_btnplorer);

		projectPathLayout->addLayout(pathFieldLayout);

		m_modalLayout->addLayout(projectPathLayout);

		m_buttonView = new WindowButtonView();

		m_modalLayout->addWidget(m_buttonView);
	}

	void ProjectModal::InitConnections()
	{
		connect(m_buttonView, &WindowButtonView::onAcceptModal, this, &ProjectModal::OnAcceptModal);
		connect(m_buttonView, &WindowButtonView::onCancelModal, this, &ProjectModal::OnRejectModal);
		connect(m_btnplorer, &QPushButton::pressed, this, &ProjectModal::FindProject);
	}

	QButtonGroup* ProjectModal::InitProjectType(QGridLayout* projectTypeLayout)
	{
		QButtonGroup* buttonGroup = new QButtonGroup(this);
		buttonGroup->setExclusive(true);

		int columnLength = 3;

		for(int i = 0; i < m_projectTypeRegistry.GetProjectTypes().length(); ++i)
		{
			ProjectTypeInfo projectTypeInfo = m_projectTypeRegistry.GetProjectTypes()[i];

			int column = i % columnLength;
			int row = i / columnLength;

			QPushButton* btn = new QPushButton(projectTypeInfo.name);
			btn->setObjectName("TypeButton");
			btn->setCheckable(true);
			btn->setCursor(Qt::PointingHandCursor);
			buttonGroup->addButton(btn);
			projectTypeLayout->addWidget(btn, row, column);
		}

		return buttonGroup;
	}

	// if modal is construct with the second constructor
	void ProjectModal::SetFieldDefaultValue()
	{
		m_nameField->setText(m_currentProject->name);
		m_descField->setText(m_currentProject->description);

		// Set current project type to edit
		for (QAbstractButton* btn : m_projectTypeButtonGroup->buttons())
		{
			auto buttonType = m_projectTypeRegistry.GetProjectTypeByName(btn->text());
			if (buttonType == m_currentProject->type)
			{
				btn->setChecked(true);
				break;
			}
		}

		m_pathField->setText(m_currentProject->path);
	}

	// SLOTS
	void ProjectModal::OnAcceptModal()
	{
		if (IsOneOfTheFieldEmpty()) return;
		accept();
	}

	void ProjectModal::OnRejectModal()
	{
		reject();
	}

	// Utilities
	bool ProjectModal::IsOneOfTheFieldEmpty()
	{
		return m_nameField->text().isEmpty() || m_descField->text().isEmpty() || m_pathField->text().isEmpty();
	}

	void ProjectModal::FindProject()
	{
		QString path;

		if (m_projectTypeRegistry.GetProjectTypeByName((m_projectTypeButtonGroup->checkedButton()->text())) == ProjectType::Unity)
		{
			path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
		}
		else
		{
			path = QFileDialog::getOpenFileName(this, tr("Open File"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), m_projectTypeRegistry.GetFilterTypeByName((m_projectTypeButtonGroup->checkedButton()->text())));
		}

		if (!path.isEmpty())
		{
			m_pathField->setText(path);
		}
	}
}

