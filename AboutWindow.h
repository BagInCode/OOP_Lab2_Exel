#pragma once

#include <QFont>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextBrowser>

#include "StyleData.h"

class AboutWindow : public QDialog
{
	Q_OBJECT

public:

	AboutWindow();
	~AboutWindow();

private:

	QTextBrowser* mainWidget;
	QVBoxLayout* mainLayout;

};