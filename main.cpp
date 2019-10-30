#include "StyleData.h"
#include "MSExcel.h"
#include <QtWidgets/QApplication>

StyleData* StyleData::instance = nullptr;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MSExcel w;
	w.show();
	return a.exec();
}
