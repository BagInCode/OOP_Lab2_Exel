#include "AboutWindow.h"

AboutWindow::AboutWindow()
{
	mainWidget = new QTextBrowser;
	mainWidget->setFont(StyleData::getInstance()->getAboutWindowFont());// + - * / min max
	mainWidget->setText("Welcome to the Maximka and Sergijko Excel (MSExcel)!!!\n\nYou can use following functions and operations:\n+ (add)\n- (subtract)\n* (multiply)\n/ (divide)\nmin(x1,...,xN) (minimum)\nmax(x1,...,xN) (maximum)\n\nDeveloped by @BagInCode and @reeWorld");
	
	mainLayout = new QVBoxLayout;
	mainLayout->addWidget(mainWidget);

	setMinimumSize(StyleData::getInstance()->getAboutWindowSize());
	setMaximumSize(StyleData::getInstance()->getAboutWindowSize());

	setLayout(mainLayout);
}

AboutWindow::~AboutWindow()
{
	delete mainWidget;
	delete mainLayout;
}