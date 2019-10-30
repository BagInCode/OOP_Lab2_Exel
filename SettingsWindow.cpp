#include "SettingsWindow.h"

SettingsWindow::SettingsWindow()
{
	setModal(true);

	QFont font(SETTINGS_WINDOW_FONT_FAMILY, SETTINGS_WINDOW_FONT_SIZE);

	infoLabel = new QLabel("Input edit line font size:");
	infoLabel->setFont(font);
	infoSpinBox = new QSpinBox();
	infoSpinBox->setMinimum(5);
	infoSpinBox->setValue(StyleData::getInstance()->getLineEditFont().pointSize());
	infoSpinBox->setMaximum(120);
	infoSpinBox->setFont(font);
	infoLayout = new QHBoxLayout;
	infoLayout->addWidget(infoLabel);
	infoLayout->addWidget(infoSpinBox);

	cellLabel = new QLabel("Input cell font size:");
	cellLabel->setFont(font);
	cellSpinBox = new QSpinBox();
	cellSpinBox->setMinimum(5);
	cellSpinBox->setValue(StyleData::getInstance()->getCellFont().pointSize());
	cellSpinBox->setMaximum(60);
	cellSpinBox->setFont(font);
	cellLayout = new QHBoxLayout;
	cellLayout->addWidget(cellLabel);
	cellLayout->addWidget(cellSpinBox);

	okButton = new QPushButton("OK");
	okButton->setFont(font);

	mainLayout = new QVBoxLayout;
	mainLayout->addLayout(infoLayout);
	mainLayout->addLayout(cellLayout);
	mainLayout->addWidget(okButton);


	setLayout(mainLayout);

	connect(infoSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeInfoFontSize(int)));
	connect(cellSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeCellFontSize(int)));
	connect(okButton, SIGNAL(clicked()), this, SLOT(close()));
}

SettingsWindow::~SettingsWindow()
{
	delete infoLabel;
	delete infoSpinBox;
	delete infoLayout;

	delete cellLabel;
	delete cellSpinBox;
	delete cellLayout;

	delete okButton;

	delete mainLayout;
}

void SettingsWindow::changeInfoFontSize(int val)
{
	StyleData::getInstance()->lineEditFont.setPointSize(val);
}

void SettingsWindow::changeCellFontSize(int val)
{
	StyleData::getInstance()->cellFont.setPointSize(val);
}