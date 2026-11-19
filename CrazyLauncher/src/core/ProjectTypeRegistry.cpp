#include "ProjectTypeRegistry.h"
#include <utils/CoreUtils.h>

#include <QDirIterator>
#include <QApplication>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QDate>
#include <QDebug>

namespace Cl
{
	ProjectTypeRegistry::ProjectTypeRegistry()
	{
		m_projectTypes =
		{ 
			{ "Script",{ ProjectType::Script, "*.sln" }},
			{ "Unreal",{ ProjectType::Unreal, "*.uproject" }},
			{ "Unity",{ ProjectType::Unity, "" }},
			{ "Blender",{ ProjectType::Blender, "*.blend" }},
			{ "Photoshop",{ ProjectType::Photoshop, "*.psd" }},
			{ "Zbrush",{ ProjectType::Zbrush, "*.zpr *.ztl" } },
			{ "Substance",{ ProjectType::Substance, "*.spp" } },
			{ "AfterEffect",{ ProjectType::AfterEffect, "*.aep" } }
		};

		LoadProjectTypeExecutables();
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
		return m_projectExecutables[name];
	}

	QString ProjectTypeRegistry::SetSoftwareApproximation(ProjectType type, QString projectPath, std::function<void(QString, QString)> func)
	{
		QString path = "";
		func("Recherche logiciel...", "color: #E6A23C;");
		// utilisation d'un thread à part serait le plus propre mais bon là c'est pas des gros calculs
		QApplication::processEvents();

		// tous ça doit pouvoir se refactoriser mais je veux que ça marche
		switch (type)
		{
		case ProjectType::Blender:
		{
			if (!m_projectExecutables["Blender"].isEmpty())
			{
				func("Logiciel trouvé !", "color: #01b20b;");
				return m_projectExecutables["Blender"];
			}

			path = FindExecutableAtPath("C:/Program Files (x86)/Steam/steamapps/common/Blender/", "blender-launcher.exe");

			if (path.isEmpty())
			{
				path = FindExecutableAtPath("C:/Program Files/Blender Foundation/Blender/", "blender-launcher.exe");
			}
			
			if (path.isEmpty())
			{
				func("Logiciel non trouvé !", "color: #d9534f;");
			}
			else
			{
				func("Logiciel trouvé !", "color: #01b20b;");
			}

			m_projectExecutables["Blender"] = path;
			SaveProjectTypeExecutables();
			return path;
		}
		case ProjectType::Unity:
		{
			path = FindExecutableAtPath("C:/Program Files/Unity/Hub/Editor/" + FindUnityCurrentVersion(projectPath) + "/Editor/", "Unity.exe");

			if (path.isEmpty())
			{
				func("Logiciel non trouvé !", "color: #d9534f;");
			}
			else
			{
				func("Logiciel trouvé !", "color: #01b20b;");
			}
			
			return path;
		}
		case ProjectType::Photoshop:
		{
			if (!m_projectExecutables["Photoshop"].isEmpty())
			{
				func("Logiciel trouvé !", "color: #01b20b;");
				return m_projectExecutables["Photoshop"];
			}

			path = FindExecutableAtPath("C:/Program Files/Adobe/", "Photoshop.exe");

			if (path.isEmpty())
			{
				func("Logiciel non trouvé !", "color: #d9534f;");
			}
			else
			{
				func("Logiciel trouvé !", "color: #01b20b;");
			}

			m_projectExecutables["Photoshop"] = path;
			SaveProjectTypeExecutables();
			return path;
		}
		case ProjectType::Zbrush:
		{
			if (!m_projectExecutables["Zbrush"].isEmpty())
			{
				func("Logiciel trouvé !", "color: #01b20b;");
				return m_projectExecutables["Zbrush"];
			}

			path = FindExecutableAtPath(QString("C:/Program Files/Maxon ZBrush %1/").arg(QDate::currentDate().year()), "ZBrush.exe");

			if (path.isEmpty())
			{
				func("Logiciel non trouvé !", "color: #d9534f;");
			}
			else
			{
				func("Logiciel trouvé !", "color: #01b20b;");
			}

			m_projectExecutables["Zbrush"] = path;
			SaveProjectTypeExecutables();
			return path;
		}
		case ProjectType::Substance:
		{
			if (!m_projectExecutables["Substance"].isEmpty())
			{
				func("Logiciel trouvé !", "color: #01b20b;");
				return m_projectExecutables["Substance"];
			}

			path = FindExecutableAtPath("C:/Program Files/Adobe/", "Adobe Substance 3D Painter.exe");

			if (path.isEmpty())
			{
				func("Logiciel non trouvé !", "color: #d9534f;");
			}
			else
			{
				func("Logiciel trouvé !", "color: #01b20b;");
			}

			m_projectExecutables["Substance"] = path;
			SaveProjectTypeExecutables();
			return path;
		}
		case ProjectType::AfterEffect:
		{
			if (!m_projectExecutables["AfterEffect"].isEmpty())
			{
				func("Logiciel trouvé !", "color: #01b20b;");
				return m_projectExecutables["AfterEffect"];
			}

			path = FindExecutableAtPath(QString("C:/Program Files/Adobe/Adobe After Effects %1/Support Files/").arg(QDate::currentDate().year()), "AfterFX.exe");

			if (path.isEmpty())
			{
				func("Logiciel non trouvé !", "color: #d9534f;");
			}
			else
			{
				func("Logiciel trouvé !", "color: #01b20b;");
			}

			m_projectExecutables["AfterEffect"] = path;
			SaveProjectTypeExecutables();
			return path;
		}
		default:
			return path = "Aucun chemin nécessaire";
		}

		return path;
	}

	void ProjectTypeRegistry::SetExecutableFromChosenPath(QString path, QString type)
	{
		if (type == "Unity") return;
		m_projectExecutables[type] = path;
		SaveProjectTypeExecutables();
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

	void ProjectTypeRegistry::SaveProjectTypeExecutables()
	{
		QFile file(Cl::CoreUtils::GetExecutableFilePath());
		if (!file.open(QIODevice::WriteOnly)) return;

		QJsonArray jsonArray;

		for (auto [key, value] : m_projectExecutables.asKeyValueRange())
		{
			QJsonObject obj;
			obj["key"] = key;
			obj["executable"] = value;

			jsonArray.append(obj);
		}

		QJsonDocument doc(jsonArray);
		file.write(doc.toJson());
		file.close();
	}

	void ProjectTypeRegistry::LoadProjectTypeExecutables()
	{
		QFile file(Cl::CoreUtils::GetExecutableFilePath());
		if (!file.open(QIODevice::ReadOnly)) return;

		QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
		QJsonArray jsonArray = doc.array();

		for (const QJsonValue& value : jsonArray)
		{
			QJsonObject obj = value.toObject();
			m_projectExecutables[obj["key"].toString()] = { obj["executable"].toString() };
		}

		file.close();
	}

}