#pragma once
#include "ProjectType.h"

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

		Project() = default;
		Project(QString name, QString descripton, ProjectType type, QString path, bool isDirectory, QString softwareExe)
			: name(name), description(descripton), type(type), path(path), isDirectory(isDirectory), softwareExe(softwareExe)
		{
		}

		bool IsEmpty()
		{
			return name == "" && description == "" && path == "" && softwareExe == "";
		}
	};
}
