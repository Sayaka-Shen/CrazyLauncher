#pragma once
#include <QString>

class Project
{
public:
	QString s_name;
	QString s_description;
	QString s_path;

	Project() = default;
	Project(QString name, QString descripton, QString path) : s_name(name), s_description(descripton), s_path(path) {};
	~Project() = default;
};