#pragma once
#include "ProjectTypeRegistry.h"

#include <QString>

namespace Cl
{
	struct Project
	{
		QString name;
		QString description;
		ProjectType type;
		QString path;
		QString executable;

		bool IsEmpty()
		{
			return name.isEmpty() && description.isEmpty() && path.isEmpty() && type == ProjectType::None && executable.isEmpty();
		}
	};
}
