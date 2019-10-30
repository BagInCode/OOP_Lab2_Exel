#pragma once

#include <QtWidgets/QMainWindow>
#include <QTCore>
#include <QtGui>
#include <Qlabel>
#include <QLineEdit>
#include <QFont>
#include <Qstring>

#define STYLE_DATA_LINE_EDIT_FONT_FAMILY "Arial"
#define STYLE_DATA_LINE_EDIT_FONT_SIZE 16

#define STYLE_DATA_CELL_FONT_FAMILY "Arial"
#define STYLE_DATA_CELL_FONT_SIZE 12

#define STYLE_DATA_SIZE_INPUT_WINDOW_FONT_FAMILY "Arial"
#define STYLE_DATA_SIZE_INPUT_WINDOW_FONT_SIZE 18

#define STYLE_DATA_ABOUT_WINDOW_FONT_FAMILY "Gadugi"
#define STYLE_DATA_ABOUT_WINDOW_FONT_SIZE 14

class StyleData
{
	friend class SettingsWindow;

private:

	StyleData();
	~StyleData();

	static StyleData* instance;

	QFont lineEditFont;

	QFont cellFont;
	QString cellDefaultBorderStyle;
	QString cellSelectedBorderStyle;
	QString coordinateCellBorderStyle;

	QFont sizeInputWindowFont;

	QFont aboutWindowFont;
	QSize aboutWindowSize;

public:

	static StyleData* getInstance();

	//static int pointToPixel

	QFont getLineEditFont();
	QFont getCellFont();
	QString getCellDefaultBorderStyle();
	QString getCellSelectedBorderStyle();
	QString getCoordinateCellBorderStyle();
	QFont getSizeInputWindowFont();
	QFont getAboutWindowFont();
	QSize getAboutWindowSize();
};