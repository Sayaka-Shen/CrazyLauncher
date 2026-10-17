#pragma once
#include "ProjectTypeRegistry.h"

#include <QString>
#include <QMetaType>

namespace Cl
{
	struct Project
	{
		QString name;
		QString description;
		ProjectType type;
		QString path;
		bool isDirectory;
		QString softwareExe;

		bool IsEmpty()
		{
			return name.isEmpty() && description.isEmpty() && path.isEmpty() && softwareExe.isEmpty();
		}
	};
}
