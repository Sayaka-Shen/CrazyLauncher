#include "Utils.h"
#include <QWidget>

namespace Cl::Utils
{
	void SetWidgetFont(int newWeight, QWidget* widget)
	{
		QFont font = widget->font();
		font.setWeight(QFont::Weight(newWeight));
		widget->setFont(font);
	}
}