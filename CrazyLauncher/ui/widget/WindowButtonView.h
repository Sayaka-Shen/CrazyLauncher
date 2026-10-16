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
		~WindowButtonView() override = default;

	private:
		QHBoxLayout* m_buttonLayout;
		QPushButton* m_cancelBtn;
		QPushButton* m_registerBtn;

	private:
		void InitUI();
		void InitConnections();

	signals:
		void onAcceptModal();
		void onCancelModal();
	};
}

