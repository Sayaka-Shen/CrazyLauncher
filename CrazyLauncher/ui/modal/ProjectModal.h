#pragma once
#include "core/Project.h"

#include <QDialog>
#include "core/ProjectTypeRegistry.h"

class QLabel;
class QLineEdit;
class QWidget;
class QCheckBox;
class QVBoxLayout;
class QHBoxLayout;
class QButtonGroup;
class QGridLayout;
class QCloseEvent;

namespace Cl
{
	class WindowButtonView;

	class ProjectModal : public QDialog
	{
		Q_OBJECT

	public:
		explicit ProjectModal(ProjectTypeRegistry& projectTypeRegistry, QWidget* parent = nullptr);
		explicit ProjectModal(Project* existedProject, ProjectTypeRegistry& projectTypeRegistry, QWidget* parent = nullptr);
		~ProjectModal() override = default;

		void closeEvent(QCloseEvent* event) override;
		Project GetProject() const;

	private:
		Project* m_currentProject;

		ProjectTypeRegistry& m_projectTypeRegistry;

		QVBoxLayout* m_modalLayout;

		QLabel* m_name;
		QLineEdit* m_nameField;

		QLabel* m_desc;
		QLineEdit* m_descField;

		QLabel* m_projectType;
		QButtonGroup* m_projectTypeButtonGroup;

		QLabel* m_path;
		QLineEdit* m_pathField;
		QPushButton* m_btnplorer;

		WindowButtonView* m_buttonView;

	private:
		void InitUI();
		void InitConnections();
		QButtonGroup* InitProjectType(QGridLayout* projectTypeLayout);
		void SetFieldDefaultValue();

		// Utilities
		bool IsOneOfTheFieldEmpty();
		void FindProject();

	signals:

	public slots:
		void OnAcceptModal();
		void OnRejectModal();
	};
}
