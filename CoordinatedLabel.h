#pragma once

#include <QtWidgets/QMainWindow>
#include <Qlabel>
#include <QTCore>
#include <QtGui>

class Coordinatedlabel : public QLabel
{
	Q_OBJECT

public:
	
	Coordinatedlabel();
	Coordinatedlabel(int x, int y);

	int x;
	int y;

	void mousePressEvent(QMouseEvent* ev);

signals:
	void mousePressed();
};

