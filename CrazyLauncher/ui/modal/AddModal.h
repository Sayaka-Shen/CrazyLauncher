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

namespace Cl
{
	class WindowButtonView;

	class AddModal : public QDialog
	{
		Q_OBJECT

	public:
		explicit AddModal(ProjectTypeRegistry& projectTypeRegistry, QWidget* parent = nullptr);
		~AddModal() override = default;

	private:
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
		QPushButton* m_projectExplorer;

		QLabel* m_softwareExe;
		QLineEdit* m_softwarePathField;
		QPushButton* m_softwareExplorer;

		WindowButtonView* m_buttonView;

	private:
		void InitUI();
		void InitConnections();
		QButtonGroup* InitProjectType(QGridLayout* projectTypeLayout);

		// Utilities
		bool IsOneOfTheFieldEmpty();
		void FindProject();

	signals:
		void addProject(const Project project);
		void rejectModal();

	public slots:
		void OnAcceptModal();
		void OnRejectModal();
	};
}
