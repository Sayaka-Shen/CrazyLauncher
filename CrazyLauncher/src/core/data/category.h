#pragma once
#include "Project.h"

#include <QString>
#include <QList>

namespace Cl
{
	struct Category
	{
		QString iconPath;
		QString name;
		QList<Project> projects;
		QString software;

		Category(QString iconPath, QString name, QString software) : iconPath(iconPath), name(name), software(software) {}
	};
}