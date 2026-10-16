#include "ViewUtils.h"
#include <QWidget>
#include <QGraphicsDropShadowEffect>

namespace Cl
{
	void ApplyShadowEffect(QWidget* widget, int blurRadius /*= 15*/, int offsetX /*= 0*/, int offsetY /*= 1*/, QColor color /*= QColor(0, 0, 0, 80)*/)
	{
		auto* shadow = new QGraphicsDropShadowEffect(widget);
		shadow->setBlurRadius(blurRadius);
		shadow->setOffset(offsetX, offsetY);
		shadow->setColor(color);

		widget->setGraphicsEffect(shadow);
	}
}

