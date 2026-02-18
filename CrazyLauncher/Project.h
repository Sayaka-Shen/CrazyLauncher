#pragma once
#include <QString>
#include "PathState.h"

struct Project
{
	QString s_name;
	QString s_description;
	QString s_path;
	QString s_software;
	PathState s_pathState;

	Project(QString& name, QString& descripton, QString& path, QString& software) : s_name(name), s_description(descripton), s_path(path), s_software(software) {};
};)