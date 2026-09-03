#pragma once
#include <QDialog>

class QLineEdit;
class QLabel;
class QVBoxLayout;
class QPushButton;
class QButtonGroup;
class QGridLayout;

namespace Cl
{
	struct CategoryModalData;

	class CategoryModal : public QDialog
	{
		Q_OBJECT

	public:
		explicit CategoryModal(QWidget* parent = nullptr);
		~CategoryModal() override = default;
	
	private:
		QVBoxLayout* m_mainLayout;

		QLabel* m_modalDesc;

		// Section Name
		QLabel* m_categorySectionName;
		QLineEdit* m_categoryNameInput;

		// Software Path Section
		QLabel* m_softwareSectionName;
		QLineEdit* m_defaultSoftwareInput;
		QPushButton* m_browseSoftwareBtn;

		// Icon Section
		QGridLayout* m_iconRows;
		int m_iconColumns = 6;
		QLabel* m_iconSectionName;
		QButtonGroup* m_btnVirtualContainer;
		QList<QPushButton*> m_iconButtons;
		QPushButton* m_addIconBtn;

		// Footer
		QPushButton* m_validateBtn;
		QPushButton* m_cancelBtn;

	private:
		void InitUI();
		void InitConnections();
		void LoadDefaultIcons();
		void LoadCustomIcons();
		QPushButton* AddIconButtons(const QString& filepath, const QString& iconName = "");

	private slots:
		void OnCancelAction();
		void OnValidateAction();
		void OnAddIcons();
		void OnBrowseSoftware();

	signals:
		void E_validateAction(const CategoryModalData& data);

	};
}