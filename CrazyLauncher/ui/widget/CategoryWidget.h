#pragma once
#include <QWidget>

namespace Cl
{
	class CategoryWidget : public QWidget
	{
		Q_OBJECT

	public:
		explicit CategoryWidget(QWidget* parent = nullptr);
		~CategoryWidget();

	};
}