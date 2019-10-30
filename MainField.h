#pragma once

#include <QtWidgets/QMainWindow>
#include <QTCore>
#include <QtGui>
#include <Qlabel>
#include <QLineEdit>
#include <QFont>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#include "CoordinatedLabel.h"
#include "SizeInputWindow.h"
#include "StyleData.h"

#define ALPHABET_SIZE 26
#define SPECIAL_SYMBOL '$'

class MainField : public QObject
{
	Q_OBJECT

private:

	QMainWindow* parent;

	int activeLabelX, activeLabelY;

	QGridLayout* uiField_p;
	QLineEdit* infoLineEdit_p;
	QLabel* infoLabel_p;

public:

	MainField(QGridLayout* uiField, QLineEdit* infoLineEdit, QLabel* infoLabel, QMainWindow* parent);
	~MainField();

	int fieldWidth, fieldHeight;
	std::string** dataField;
	Coordinatedlabel** labelField;
	QLabel* upperCoordinateLabel, * leftCoordinateLabel;

	void resetLabelStyle();

	void clear();

	QString getStringUpperCoordinate(int position);
	QString getStringLeftCoordinate(int position);

public slots:

	void createNewField(int height = -1, int width = -1);
	void selectActiveCell();
	void refreshCell();
	void saveField();
	void openField();
};