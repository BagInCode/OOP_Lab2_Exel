#pragma once

#include <QFont>
#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "StyleData.h"

#define SETTINGS_WINDOW_FONT_FAMILY "Arial"
#define SETTINGS_WINDOW_FONT_SIZE 24

class SettingsWindow : public QDialog
{
	Q_OBJECT

public:

	SettingsWindow();
	~SettingsWindow();

private:
	
	QLabel* infoLabel, * cellLabel;
	QSpinBox* infoSpinBox, * cellSpinBox;
	QHBoxLayout* infoLayout, * cellLayout;
	QVBoxLayout* mainLayout;
	QPushButton* okButton;

public slots:

	void changeInfoFontSize(int val);
	void changeCellFontSize(int val);

};