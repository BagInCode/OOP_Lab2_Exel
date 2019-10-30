#pragma once

#include <QtWidgets/QMainWindow>
#include <QTCore>
#include <QtGui>
#include <Qlabel>
#include <QLineEdit>
#include <QFont>

#include <string>
#include <vector>
#include <algorithm>

#include "ui_MSExcel.h"
#include "CoordinatedLabel.h"
#include "SizeInputWindow.h"
#include "AboutWindow.h"
#include "MainField.h"
#include "SettingsWindow.h"
#include "StyleData.h"

class MSExcel : public QMainWindow
{
	Q_OBJECT

public:
	MSExcel(QWidget *parent = Q_NULLPTR);
	~MSExcel();

private:
	Ui::MSExcelClass ui;

	QLineEdit* infoLineEdit;

	MainField* field;
	

public slots:

	void closeApplication();

	void changeSettings();
	void showAbout();

};
