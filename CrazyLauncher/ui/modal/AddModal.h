#pragma once
#include "core/Project.h"

#include <QDialog>

class QLabel;
class QLineEdit;
class QWidget;
class QCheckBox;
class QVBoxLayout;
class QHBoxLayout;
class QButtonGroup;
class QCheckBox;
class QComboBox;

namespace Cl
{
	class WindowButtonView;

	class AddModal : public QDialog
	{
		Q_OBJECT

	public:
		explicit AddModal(QWidget* parent = nullptr);
		~AddModal() override = default;

		

	private:
		QVBoxLayout* m_modalLayout;

		QLabel* m_name;
		QLineEdit* m_nameField;

		QLabel* m_desc;
		QLineEdit* m_descField;

		QLabel* m_projectType;
		QComboBox* m_projectTypeComboBox;

		QLabel* m_path;
		QLineEdit* m_pathField;
		QPushButton* m_projectExplorer;

		QLabel* m_softwareExe;
		QLineEdit* m_softwarePathField;
		QPushButton* m_softwareExplorer;

		WindowButtonView* m_buttonView;

		std::map<ProjectType, QString> projectTypeToFilter =
		{
			{ Script, "*.sln" },
			{ Unreal, "*.uproject" },
			{ Unity, "" },
			{ Blender, "*.blend" },
			{ Photoshop, "*.psd" },
			{ Zbrush, "*.zpr" },
		};

	private:
		void InitUI();
		void InitConnections();
		void InitProjectType();

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
