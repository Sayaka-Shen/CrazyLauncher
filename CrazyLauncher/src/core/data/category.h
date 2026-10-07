#pragma once
#include "Project.h"

#include <QString>
#include <QList>

namespace Cl
{
	struct Category
	{
		QString iconPath = "";
		QString name = "";
		QList<Project> projects = QList<Project>();
		QString software = "";

		bool IsEmpty() const
		{
			return iconPath.isEmpty() && name.isEmpty() && projects.isEmpty() && software.isEmpty();
		}
	};
}