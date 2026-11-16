#pragma once
#include "QWidget"

class QHBoxLayout;
class QPushButton;
class QLabel;
class QString;

namespace Cl
{
	class WindowButtonView : public QWidget
	{
		Q_OBJECT

	public:
		WindowButtonView(QWidget* parent = nullptr);
		~WindowButtonView() override = default;

		void SetInfoText(QString text, QString style);

	private:
		QHBoxLayout* m_buttonLayout;

		QLabel* m_info;
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

