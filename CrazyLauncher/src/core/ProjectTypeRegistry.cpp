#include "ProjectTypeRegistry.h"

#include <QDirIterator>

namespace Cl
{
	ProjectTypeRegistry::ProjectTypeRegistry()
	{
		m_projectTypes =
		{ 
			{ "Script",{ ProjectType::Script, "*.sln", "" }},
			{ "Unreal",{ ProjectType::Unreal, "*.uproject", "" }},
			{ "Unity",{ ProjectType::Unity, "", "" }},
			{ "Blender",{ ProjectType::Blender, "*.blend", ""}},
			{ "Photoshop",{ ProjectType::Photoshop, "*.psd", ""}},
			{ "Zbrush",{ ProjectType::Zbrush, "*.zpr", "" } }
		};
	}

	const QMap<QString, ProjectTypeInfo>& ProjectTypeRegistry::GetProjectTypes() const
	{
		return m_projectTypes;
	}

	const ProjectType ProjectTypeRegistry::GetProjectTypeByName(QString name) const
	{
		return m_projectTypes.value(name).projectType;
	}

	const QString ProjectTypeRegistry::GetFilterTypeByName(QString name) const
	{
		return m_projectTypes.value(name).filter;
	}

	QString ProjectTypeRegistry::GetTypeInfoExecutable(QString name)
	{
		return m_projectTypes[name].executable;
	}

	QString ProjectTypeRegistry::SetSoftwareApproximation(ProjectType type, QString projectPath)
	{
		QString path = "";

		switch (type)
		{
		case ProjectType::Blender:
		{
			if (!m_projectTypes["Blender"].executable.isEmpty()) return m_projectTypes["Blender"].executable;

			path = FindExecutableAtPath("C:/Program Files (x86)/Steam/steamapps/common/Blender/", "blender-launcher.exe");

			if (path.isEmpty())
			{
				path = FindExecutableAtPath("C:/Program Files/Blender Foundation/Blender/", "blender-launcher.exe");
			}
			
			m_projectTypes["Blender"].executable = path;
			return path;
		}
		case ProjectType::Unity:
		{
			path = FindExecutableAtPath("C:/Program Files/Unity/Hub/Editor/" + FindUnityCurrentVersion(projectPath) + "/Editor/", "Unity.exe");
			return path;
		}
		case ProjectType::Photoshop:
		{
			if (!m_projectTypes["Photoshop"].executable.isEmpty()) return m_projectTypes["Photoshop"].executable;

			path = FindExecutableAtPath("C:/Program Files/Adobe/", "Photoshop.exe");

			m_projectTypes["Photoshop"].executable = path;
			return path;
		}
		case ProjectType::Zbrush:
		{
			if (!m_projectTypes["ZBrush"].executable.isEmpty()) return m_projectTypes["ZBrush"].executable;

			path = FindExecutableAtPath("C:/Program Files/Maxon ZBrush 2026/", "ZBrush.exe");

			m_projectTypes["ZBrush"].executable = path;
			return path;
		}
		default:
			return path = "Aucun chemin nécessaire.";
		}

		return path;
	}

	void ProjectTypeRegistry::SetExecutableFromChosenPath(QString path, QString type)
	{
		if (type == "Unity") return;
		m_projectTypes[type].executable = path;
	}

	QString ProjectTypeRegistry::FindExecutableAtPath(QString path, QString exe)
	{
		QDirIterator it(path, QStringList() << exe, QDir::Files, QDirIterator::Subdirectories);

		if (it.hasNext())
		{
			return it.next();
		}

		return "";
	}

	QString ProjectTypeRegistry::FindUnityCurrentVersion(QString projectPath)
	{
		QString cleanPath = QDir::cleanPath(projectPath);

		if (QFile::exists(cleanPath + "/ProjectSettings/ProjectVersion.txt"))
		{
			QFile file(cleanPath + "/ProjectSettings/ProjectVersion.txt");
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
				return "";

			QTextStream in(&file);
			while (!in.atEnd())
			{
				QString line = in.readLine();

				if (line.contains("m_EditorVersion"))
				{
					return line.section(":", 1).trimmed();
				}
			}
		}

		return "";
	}
}