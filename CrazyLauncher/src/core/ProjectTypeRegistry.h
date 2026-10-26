#pragma once

#include <QString>
#include <QVector>

namespace Cl
{
	enum ProjectType
	{
		Script,
		Unreal,
		Unity,
		Blender,
		Photoshop,
		Zbrush,
	};

	struct ProjectTypeInfo
	{
		QString name;
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
		const QVector<ProjectTypeInfo>& GetProjectTypes() const;
		const ProjectType GetProjectTypeByName(QString name) const;
		const QString GetFilterTypeByName(QString name) const;

	private:
		QVector<ProjectTypeInfo> m_projectTypes;
	};
}
