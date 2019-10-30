#include "SizeInputWindow.h"

SizeInputWindow::SizeInputWindow() : QDialog(0), height(DEFAULT_HEIGHT), width(DEFAULT_WIDTH)
{
	setModal(true);

	setUpUI();
}

SizeInputWindow::SizeInputWindow(int defaultHeight, int defaulWidth, int maxHeight, int maxWidth)
	: QDialog(0), height(defaultHeight), width(defaulWidth)
{
	setModal(true);

	setUpUI(maxHeight, maxWidth);
}

SizeInputWindow::~SizeInputWindow()
{
	delete widthLabel;
	delete widthSpinBox;
	delete widthLayout;

	delete heightLabel;
	delete heightSpinBox;
	delete heightLayout;

	delete okButton;

	delete mainLayout;	
}

std::pair<int, int> SizeInputWindow::getSize()
{
	return std::make_pair(height, width);
}

void SizeInputWindow::setUpUI(int maxHeight, int maxWidth)
{
	// create ui
	heightLabel = new QLabel("Input height:");
	heightLabel->setFont(StyleData::getInstance()->getSizeInputWindowFont());
	
	heightSpinBox = new QSpinBox;
	heightSpinBox->setMinimum(1);
	heightSpinBox->setMaximum(maxHeight);
	heightSpinBox->setValue(height);
	heightSpinBox->setFont(StyleData::getInstance()->getSizeInputWindowFont());

	heightLayout = new QHBoxLayout;
	heightLayout->addWidget(heightLabel);
	heightLayout->addWidget(heightSpinBox);


	widthLabel = new QLabel("Input width:");
	widthLabel->setFont(StyleData::getInstance()->getSizeInputWindowFont());
	
	widthSpinBox = new QSpinBox;
	widthSpinBox->setMinimum(1);
	widthSpinBox->setMaximum(maxWidth);
	widthSpinBox->setValue(width);
	widthSpinBox->setFont(StyleData::getInstance()->getSizeInputWindowFont());

	widthLayout = new QHBoxLayout;
	widthLayout->addWidget(widthLabel);
	widthLayout->addWidget(widthSpinBox);


	okButton = new QPushButton("OK");
	okButton->setFont(StyleData::getInstance()->getSizeInputWindowFont());


	mainLayout = new QVBoxLayout;
	mainLayout->addLayout(heightLayout);
	mainLayout->addLayout(widthLayout);
	mainLayout->addWidget(okButton);

	setLayout(mainLayout);

	connect(okButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(heightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateSize()));
	connect(widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateSize()));
}

void SizeInputWindow::updateSize()
{
	height = heightSpinBox->value();
	width = widthSpinBox->value();
}
