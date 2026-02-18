#pragma once
#include <QString>
#include <QMetaType>


namespace Cl
{
	enum ProjectType
	{
		Executable,
		Script,
		Unreal,
		Unity,
		Blender,
		Photoshop,
		Custom,
	};

	struct Project
	{
		QString s_name;
		QString s_description;
		ProjectType s_type;
		QString s_path;
		bool s_isDirectory;
		QString s_softwareExe;


		Project(QString& name, QString& descripton, ProjectType type, QString& path, bool isDirectory, QString& softwareExe)
			: s_name(name), s_description(descripton), s_type(type), s_path(path), s_isDirectory(isDirectory), s_softwareExe(softwareExe)
		{
		}
	};
}
