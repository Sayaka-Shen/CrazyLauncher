#pragma once
#include "QWidget"

class QHBoxLayout;
class QPushButton;

namespace Cl
{
	class WindowButtonView : public QWidget
	{
		Q_OBJECT

	public:
		WindowButtonView(QWidget* parent = nullptr);
		~WindowButtonView();

		// Getter - Setter
		QPushButton* GetRegisterBtn();
		QPushButton* GetCancelBtn();

	private:
		QHBoxLayout* m_buttonLayout;
		QPushButton* m_cancelBtn;
		QPushButton* m_registerBtn;

		void CreateLayout();
		void CreateUI();
		void SetupLayout();
	};
}

