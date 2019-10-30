#pragma once

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "StyleData.h"

#define DEFAULT_HEIGHT 10
#define DEFAULT_WIDTH 10
#define DEFAULT_MAX_HEIGHT 50
#define DEFAULT_MAX_WIDTH 50

class SizeInputWindow : public QDialog
{
	Q_OBJECT

public:

	SizeInputWindow();
	SizeInputWindow(int defaultHeight, int defaulWidth, int maxHeight = DEFAULT_MAX_HEIGHT, int maxWidth = DEFAULT_MAX_WIDTH);
	~SizeInputWindow();

	std::pair<int, int> getSize();

private:

	QVBoxLayout* mainLayout;
	QHBoxLayout* heightLayout, * widthLayout;
	QLabel* heightLabel, * widthLabel;
	QSpinBox* heightSpinBox, * widthSpinBox;
	QPushButton* okButton;

	int height, width;
	
	void setUpUI(int maxHeight = DEFAULT_MAX_HEIGHT, int maxWidth = DEFAULT_MAX_WIDTH);

private slots:
	
	void updateSize();

};