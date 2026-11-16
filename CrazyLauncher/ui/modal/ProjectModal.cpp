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
#include <string>
#include <unordered_map>

namespace Cl
{
	ProjectModal::ProjectModal(ProjectTypeRegistry& projectTypeRegistry, QWidget* parent) : QDialog(parent), m_projectTypeRegistry(projectTypeRegistry)
	{
		setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		setFixedSize(600, 500);
		setObjectName("Modal");

		InitUI();
		InitConnections();
	}

	ProjectModal::ProjectModal(const Project* m_currentProject, ProjectTypeRegistry& projectTypeRegistry, QWidget* parent /*= nullptr*/) : m_currentProject(m_currentProject), QDialog(parent), m_projectTypeRegistry(projectTypeRegistry)
	{
		setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
		setFixedSize(600, 500);
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

		Project project
		{
			m_nameField->text(),
			m_descField->text(),
			m_projectTypeRegistry.GetProjectTypeByName(m_projectTypeButtonGroup->checkedButton()->text()),
			m_pathField->text(),
			m_softwarePathField->text()
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
		m_nameField->setPlaceholderText("Projet A");
		nameLayout->addWidget(m_nameField);

		m_modalLayout->addLayout(nameLayout);

		auto* descLayout = new QVBoxLayout();
		descLayout->setContentsMargins(15, 0, 15, 0);

		m_desc = new QLabel("Description :");
		descLayout->addWidget(m_desc);

		m_descField = new QLineEdit();
		m_descField->setPlaceholderText("Le projet A est [...].");
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
		m_pathField->setPlaceholderText("C:/Projet.[extension]/");
		pathFieldLayout->addWidget(m_pathField, 2);

		m_btnPathEplorer = new QPushButton();
		m_btnPathEplorer->setIcon(QIcon(":/new/prefix1/assets/folder-black-white.png"));
		m_btnPathEplorer->setObjectName("ExplorerButton");
		m_btnPathEplorer->setDefault(false);
		pathFieldLayout->addWidget(m_btnPathEplorer);
		projectPathLayout->addLayout(pathFieldLayout);

		m_modalLayout->addLayout(projectPathLayout);

		auto* softwarePathLayout = new QVBoxLayout();
		softwarePathLayout->setContentsMargins(15, 0, 15, 10);
		m_softwarePath = new QLabel("Software Path :", this);
		softwarePathLayout->addWidget(m_softwarePath);

		auto* softwarePathFieldLayout = new QHBoxLayout();
		softwarePathFieldLayout->setSpacing(2);
		m_softwarePathField = new QLineEdit();
		m_softwarePathField->setEnabled(false);
		m_softwarePathField->setEnabled(false);
		softwarePathFieldLayout->addWidget(m_softwarePathField, 2);

		m_btnSoftwarePathEplorer = new QPushButton();
		m_btnSoftwarePathEplorer->setEnabled(false);
		m_btnSoftwarePathEplorer->setIcon(QIcon(":/new/prefix1/assets/folder-black-white.png"));
		m_btnSoftwarePathEplorer->setObjectName("ExplorerButton");
		m_btnSoftwarePathEplorer->setDefault(false);
		softwarePathFieldLayout->addWidget(m_btnSoftwarePathEplorer);

		softwarePathLayout->addLayout(softwarePathFieldLayout);

		m_modalLayout->addLayout(softwarePathLayout);

		m_buttonView = new WindowButtonView();

		m_modalLayout->addWidget(m_buttonView);
	}

	void ProjectModal::InitConnections()
	{
		connect(m_buttonView, &WindowButtonView::onAcceptModal, this, &ProjectModal::OnAcceptModal);
		connect(m_buttonView, &WindowButtonView::onCancelModal, this, &ProjectModal::OnRejectModal);
		connect(m_btnPathEplorer, &QPushButton::pressed, this, &ProjectModal::FindProject);
		connect(m_btnSoftwarePathEplorer, &QPushButton::pressed, this, &ProjectModal::FindSoftware);
		connect(m_projectTypeButtonGroup, &QButtonGroup::buttonPressed, this, &ProjectModal::OnButtonTypePressed);
	}

	QButtonGroup* ProjectModal::InitProjectType(QGridLayout* projectTypeLayout)
	{
		QButtonGroup* buttonGroup = new QButtonGroup(this);
		buttonGroup->setExclusive(true);

		QMap<QString, ProjectTypeInfo> projectTypesInfo = m_projectTypeRegistry.GetProjectTypes();

		int columnLength = 4;
		int indexOfElement = 0;

		for(auto [key, value] : projectTypesInfo.asKeyValueRange())
		{
			int column = indexOfElement % columnLength;
			int row = indexOfElement / columnLength;

			QPushButton* btn = new QPushButton(key);
			btn->setObjectName("TypeButton");
			btn->setCheckable(true);
			btn->setCursor(Qt::PointingHandCursor);
			buttonGroup->addButton(btn);	
			projectTypeLayout->addWidget(btn, row, column);

			indexOfElement++;
		}

		return buttonGroup;
	}

	// if modal is construct with the second constructor
	void ProjectModal::SetFieldDefaultValue()
	{
		if (m_currentProject == nullptr) return;
		m_nameField->setText(m_currentProject->name);
		m_descField->setText(m_currentProject->description);

		// Set current project type to edit
		for (QAbstractButton* btn : m_projectTypeButtonGroup->buttons())
		{
			const auto& buttonType = m_projectTypeRegistry.GetProjectTypeByName(btn->text());
			if (buttonType == m_currentProject->type)
			{
				btn->setChecked(true);

				if (btn->text() == "Unity" || btn->text() == "Script" || btn->text() == "Unreal")
				{
					m_softwarePathField->setEnabled(false);
					m_btnSoftwarePathEplorer->setEnabled(false);
					break;
				}

				m_softwarePathField->setEnabled(true);
				m_btnSoftwarePathEplorer->setEnabled(true);

				break;
			}
		}

		m_pathField->setText(m_currentProject->path);
		m_softwarePathField->setText(m_currentProject->executable);
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

	void ProjectModal::OnButtonTypePressed(QAbstractButton* button)
	{
		QPushButton* btn = static_cast<QPushButton*>(button);
		if (btn->text() == "Unity" || btn->text() == "Script" || btn->text() == "Unreal")
		{
			m_softwarePathField->setEnabled(false);
			m_btnSoftwarePathEplorer->setEnabled(false);
			return;
		}

		m_softwarePathField->setEnabled(true);
		m_btnSoftwarePathEplorer->setEnabled(true);
	}

	// Utilities
	bool ProjectModal::IsOneOfTheFieldEmpty()
	{
		return m_nameField->text().isEmpty() || m_descField->text().isEmpty() || m_pathField->text().isEmpty();
	}

	void ProjectModal::FindProject()
	{
		if (m_projectTypeButtonGroup->checkedButton() == nullptr) return;
		QString path;

		if (m_projectTypeRegistry.GetProjectTypeByName(m_projectTypeButtonGroup->checkedButton()->text()) == ProjectType::Unity)
		{
			path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
		}
		else
		{
			path = QFileDialog::getOpenFileName(this, tr("Open File"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), m_projectTypeRegistry.GetFilterTypeByName(m_projectTypeButtonGroup->checkedButton()->text()));
		}

		if (!path.isEmpty())
		{
			m_pathField->setText(path);
			m_softwarePathField->setText(m_projectTypeRegistry.SetSoftwareApproximation(m_projectTypeRegistry.GetProjectTypeByName(m_projectTypeButtonGroup->checkedButton()->text()), m_pathField->text(), [this](QString text, QString style) { m_buttonView->SetInfoText(text, style); }));
		}
	}

	void ProjectModal::FindSoftware()
	{
		QString path;
		path = QFileDialog::getOpenFileName(this, tr("Open File"), "C:/", "*.exe");

		if (!path.isEmpty())
		{
			m_softwarePathField->setText(path);
			m_projectTypeRegistry.SetExecutableFromChosenPath(m_projectTypeButtonGroup->checkedButton()->text(), m_path->text());
		}
	}
}

