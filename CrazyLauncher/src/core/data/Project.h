#pragma once
#include "ProjectType.h"

#include <QString>

namespace Cl
{
	struct Project
	{
		QString name;
		QString description;
		ProjectType type;
		QString path;
		QString owningCategory;

		Project(QString name, QString descripton, ProjectType type, QString path) : name(name), description(descripton), type(type), path(path) { }
	};
}
  