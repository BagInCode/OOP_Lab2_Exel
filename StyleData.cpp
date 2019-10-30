#include "StyleData.h"

StyleData::StyleData()
{
	// set dafault styles

	lineEditFont.setFamily(STYLE_DATA_LINE_EDIT_FONT_FAMILY);
	lineEditFont.setPointSize(STYLE_DATA_LINE_EDIT_FONT_SIZE);

	cellFont.setFamily(STYLE_DATA_CELL_FONT_FAMILY);
	cellFont.setPointSize(STYLE_DATA_CELL_FONT_SIZE);

	cellDefaultBorderStyle.append("border-right: 1px solid black;");
	cellDefaultBorderStyle.append("border-top: 1px solid black;");
	cellDefaultBorderStyle.append("border-left: 1px solid black;");
	cellDefaultBorderStyle.append("border-bottom: 1px solid black;");
	cellDefaultBorderStyle.append("background-color : white;");

	cellSelectedBorderStyle.append("border-right: 2px solid red;");
	cellSelectedBorderStyle.append("border-top: 2px solid red;");
	cellSelectedBorderStyle.append("border-left: 2px solid red;");
	cellSelectedBorderStyle.append("border-bottom: 2px solid red;");
	cellSelectedBorderStyle.append("background-color : white;");

	coordinateCellBorderStyle.append("border-right: 1px solid black;");
	coordinateCellBorderStyle.append("border-left: 1px solid black;");
	coordinateCellBorderStyle.append("border-top: 1px solid black;");
	coordinateCellBorderStyle.append("border-bottom: 1px solid black;");

	sizeInputWindowFont.setFamily(STYLE_DATA_SIZE_INPUT_WINDOW_FONT_FAMILY);
	sizeInputWindowFont.setPointSize(STYLE_DATA_SIZE_INPUT_WINDOW_FONT_SIZE);

	aboutWindowFont.setFamily(STYLE_DATA_ABOUT_WINDOW_FONT_FAMILY);
	aboutWindowFont.setPointSize(STYLE_DATA_ABOUT_WINDOW_FONT_SIZE);

	aboutWindowSize.setHeight(300);
	aboutWindowSize.setWidth(700);
}

StyleData::~StyleData()
{
	
}

StyleData* StyleData::getInstance()
{
	if (instance == nullptr)
	{
		instance = new StyleData();
	}

	return instance;
}

QFont StyleData::getLineEditFont()
{
	return lineEditFont;
}

QFont StyleData::getCellFont()
{
	return cellFont;
}

QString StyleData::getCellDefaultBorderStyle()
{
	return cellDefaultBorderStyle;
}

QString StyleData::getCellSelectedBorderStyle()
{
	return cellSelectedBorderStyle;
}

QString StyleData::getCoordinateCellBorderStyle()
{
	return coordinateCellBorderStyle;
}

QFont StyleData::getSizeInputWindowFont()
{
	return sizeInputWindowFont;
}

QFont StyleData::getAboutWindowFont()
{
	return aboutWindowFont;
}

QSize StyleData::getAboutWindowSize()
{
	return aboutWindowSize;
}