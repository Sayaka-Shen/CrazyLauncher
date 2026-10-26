#include "ProjectTypeRegistry.h"

namespace Cl
{
	ProjectTypeRegistry::ProjectTypeRegistry()
	{
		m_projectTypes = {
			{ "Script", ProjectType::Script, "*.sln", "" },
			{ "Unreal", ProjectType::Unreal, "*.uproject", "" },
			{ "Unity", ProjectType::Unity, "", "" },
			{ "Blender", ProjectType::Blender, "*.blend", "" },
			{ "Photoshop", ProjectType::Photoshop, "*.psd", "" },
			{ "Zbrush", ProjectType::Zbrush, "*.zpr", "" }
		};
	}

	const QVector<Cl::ProjectTypeInfo>& ProjectTypeRegistry::GetProjectTypes() const
	{
		return m_projectTypes;
	}

	const ProjectType ProjectTypeRegistry::GetProjectTypeByName(QString name) const
	{
		for (ProjectTypeInfo projectTypeInfo : m_projectTypes)
		{
			if (projectTypeInfo.name == name)
			{
				return projectTypeInfo.projectType;
			}
		}

		return m_projectTypes[0].projectType; // Return the first project type as a default if not found
	}

	const QString ProjectTypeRegistry::GetFilterTypeByName(QString name) const
	{
		for (ProjectTypeInfo projectTypeInfo : m_projectTypes)
		{
			if (projectTypeInfo.name == name)
			{
				return projectTypeInfo.filter;
			}
		}

		return m_projectTypes[0].filter;
	}

}