#pragma once
#include <functional>

#include <QString>
#include <QVector>
#include <QMap>

namespace Cl
{
	enum ProjectType
	{
		None, 
		Script,
		Unreal,
		Unity,
		Blender,
		Photoshop,
		Zbrush,
		Substance,
		AfterEffect,
	};

	struct ProjectTypeInfo
	{
		ProjectType projectType;
		QString filter;
	};

	class ProjectTypeRegistry
	{
	public:
		ProjectTypeRegistry();
		~ProjectTypeRegistry() = default;

	public:
		const QMap<QString, ProjectTypeInfo>& GetProjectTypes() const;
		const ProjectType GetProjectTypeByName(QString name) const;
		const QString GetFilterTypeByName(QString name) const;
		const QString GetSoftwarePathByProjectType() const;
		QString GetTypeInfoExecutable(QString name);

		QString SetSoftwareApproximation(ProjectType type, QString projectPath, std::function<void(QString, QString)> func);
		void SetExecutableFromChosenPath(QString path, QString type);

		QString FindExecutableAtPath(QString path, QString exe);
		QString FindUnityCurrentVersion(QString projectPath);

		void SaveProjectTypeExecutables();
		void LoadProjectTypeExecutables();

	private:
		QMap<QString, ProjectTypeInfo> m_projectTypes;
		QMap<QString, QString> m_projectExecutables;
	};
}
