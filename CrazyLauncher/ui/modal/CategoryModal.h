#pragma once
#include "QDialog"

class QLineEdit;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;

namespace Cl
{
	class CategoryModal : public QDialog
	{
		Q_OBJECT

	public:
		explicit CategoryModal(QWidget* parent = nullptr);
		~CategoryModal() = default;
	
	private:
		QVBoxLayout* m_mainLayout;
		QHBoxLayout* m_buttonLayout;

		QLabel* m_categoryName;
		QLineEdit* m_categoryInput;

		QPushButton* m_validateBtn;
		QPushButton* m_cancelBtn;

	private:
		void InitUI();
		void InitConnections();

		void OnCancelAction();
		void OnValidateAction();

	signals:
		void E_cancelAction();
		void E_validateAction();

	};
}