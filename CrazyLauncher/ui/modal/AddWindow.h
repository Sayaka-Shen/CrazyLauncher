#pragma once
#include "UtilityWindow.h"

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
		void E_AddProject(const Project& project);

	};
}
