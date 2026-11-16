#pragma once

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
	};

	struct ProjectTypeInfo
	{
		ProjectType projectType;
		QString filter;
		QString executable;
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

		QString SetSoftwareApproximation(ProjectType type, QString projectPath);
		void SetExecutableFromChosenPath(QString path, QString type);

		QString FindExecutableAtPath(QString path, QString exe);
		QString FindUnityCurrentVersion(QString projectPath);

	private:
		QMap<QString, ProjectTypeInfo> m_projectTypes;
	};
}
