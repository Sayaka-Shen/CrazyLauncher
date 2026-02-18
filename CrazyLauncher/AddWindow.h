#pragma once
#include "UtilityWindow.h"

class QString;
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
	struct Project;

	class AddWindow : public UtilityWindow
	{
		Q_OBJECT

	public:
		explicit AddWindow(QWidget* parent = nullptr);
		~AddWindow();

	private:
		void OnRegisterProject();

	signals:
		void E_AddProject(const Project& project)

	};
}
