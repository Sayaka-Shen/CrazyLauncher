#include "CoreUtils.h"
#include <QStandardPaths>
#include <QFileDialog>
#include <QJsonArray>

namespace Cl::CoreUtils
{
	QString GetProjectsFilePath()
	{
		QString savePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

		// Create path if it does not exist
		QDir().mkpath(savePath);
		return savePath + "/crazy_projects.json";
	}
}