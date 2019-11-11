#include "MSExcel.h"

MSExcel::MSExcel(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);

	// create styleData instance
	StyleData::getInstance();

	// setup infoLabel
	ui.infoLabel->setFont(StyleData::getInstance()->getLineEditFont());

	// setup infoLineEdit
	infoLineEdit = new QLineEdit;
	infoLineEdit->setFont(StyleData::getInstance()->getLineEditFont());
	infoLineEdit->setDisabled(true);
	ui.centralWidgetGridLayout->addWidget(infoLineEdit, 0, 1);

	// setup field
	field = new MainField(ui.uiField, infoLineEdit, ui.infoLabel, this);

	connect(infoLineEdit, SIGNAL(editingFinished()), field, SLOT(refreshCell()));

	//setup uiField
	ui.uiField->setSpacing(0);

	//connect menuBar
	connect(ui.actionNew, SIGNAL(triggered()), field, SLOT(createNewField()));
	connect(ui.actionSave_as, SIGNAL(triggered()), field, SLOT(saveField()));
	connect(ui.actionOpen, SIGNAL(triggered()), field, SLOT(openField()));
	connect(ui.actionDelete_row, SIGNAL(triggered()), field, SLOT(deleteRow()));
	connect(ui.actionDelete_column, SIGNAL(triggered()), field, SLOT(deleteColumn()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(closeApplication()));
		
	connect(ui.actionSettings, SIGNAL(triggered()), this, SLOT(changeSettings()));
	
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
}

void MSExcel::closeApplication()
{
	QApplication::quit();
}

void MSExcel::changeSettings()
{
	SettingsWindow* settingsWindow = new SettingsWindow();
	settingsWindow->exec();

	ui.infoLabel->setFont(StyleData::getInstance()->getLineEditFont());
	infoLineEdit->setFont(StyleData::getInstance()->getLineEditFont());

	field->resetLabelStyle();

	delete settingsWindow;
}

void MSExcel::showAbout()
{
	AboutWindow* aboutWindow = new AboutWindow();
	aboutWindow->exec();

	delete aboutWindow;
}

MSExcel::~MSExcel()
{
	delete infoLineEdit;
	delete field;
}