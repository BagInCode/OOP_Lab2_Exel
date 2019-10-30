#include "CoordinatedLabel.h"

Coordinatedlabel::Coordinatedlabel() : x(-1), y(-1)
{

}

Coordinatedlabel::Coordinatedlabel(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Coordinatedlabel::mousePressEvent(QMouseEvent* ev)
{
	emit mousePressed();
}