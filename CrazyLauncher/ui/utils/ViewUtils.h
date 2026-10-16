#pragma once
#include <QColor>

class QWidget;

namespace Cl::ViewUtils
{
	void ApplyShadowEffect(QWidget* widget, int blurRadius = 10, int offsetX = 0, int offsetY = 1, QColor color = QColor(0, 0, 0, 80));
}


