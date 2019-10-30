#include "MainField.h"

MainField::MainField(QGridLayout* uiField, QLineEdit* infoLineEdit, QLabel* infoLabel, QMainWindow* parent) : QObject(0), activeLabelX(-1), activeLabelY(-1),
	fieldHeight(-1), fieldWidth(-1), dataField(nullptr), labelField(nullptr), uiField_p(uiField),  parent(parent),
	infoLineEdit_p(infoLineEdit), infoLabel_p(infoLabel), leftCoordinateLabel(nullptr), upperCoordinateLabel(nullptr)
{

}

MainField::~MainField()
{
	clear();
}

void MainField::clear()
{
	if (labelField != nullptr)
	{
		for (int i = 0; i < fieldHeight; i++)
		{
			for (int j = 0; j < fieldWidth; j++)
			{
				disconnect(&labelField[i][j], SIGNAL(mousePressed()), this, SLOT(selectActiveCell()));
			}
		}

		for (int i = 0; i < fieldHeight; i++)
		{
			delete[] labelField[i];
		}
		delete[] labelField;

		for (int i = 0; i < fieldHeight; i++)
		{
			delete[] dataField[i];
		}
		delete[] dataField;

		delete[] upperCoordinateLabel;
		delete[] leftCoordinateLabel;
	}
}

void MainField::resetLabelStyle()
{
	if (labelField==nullptr)
	{
		return;
	}

	QFont font = StyleData::getInstance()->getCellFont();

	for (int i = 0; i < fieldHeight; i++)
	{
		for (int j = 0; j < fieldWidth; j++)
		{
			labelField[i][j].setFont(font);
		}
	}

	for (int j = 0; j < fieldWidth; j++)
	{
		upperCoordinateLabel[j].setFont(font);
	}

	for (int i = 0; i < fieldHeight; i++)
	{
		leftCoordinateLabel[i].setFont(font);
	}
}

void MainField::createNewField(int height, int width)
{
	clear();

	// create new

	activeLabelX = activeLabelY = -1;

	if (height == -1)
	{
		SizeInputWindow* sizeInputWindow = new SizeInputWindow;
		sizeInputWindow->exec();
		fieldHeight = sizeInputWindow->getSize().first;
		fieldWidth = sizeInputWindow->getSize().second;
		delete sizeInputWindow;
	}
	else
	{
		fieldHeight = height;
		fieldWidth = width;
	}

	labelField = new Coordinatedlabel * [fieldHeight];
	for (int i = 0; i < fieldHeight; i++)
	{
		labelField[i] = new Coordinatedlabel[fieldWidth];
		for (int j = 0; j < fieldWidth; j++)
		{
			labelField[i][j].x = i;
			labelField[i][j].y = j;

			labelField[i][j].setText("");
			labelField[i][j].setStyleSheet(StyleData::getInstance()->getCellDefaultBorderStyle());
			labelField[i][j].setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			labelField[i][j].setWordWrap(true);
		}
	}

	upperCoordinateLabel = new QLabel[fieldWidth];
	for (int j = 0; j < fieldWidth; j++)
	{
		upperCoordinateLabel[j].setText(getStringUpperCoordinate(j + 1));
		upperCoordinateLabel[j].setStyleSheet(StyleData::getInstance()->getCoordinateCellBorderStyle());
		upperCoordinateLabel[j].setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		uiField_p->addWidget(&upperCoordinateLabel[j], 0, j + 1);
	}

	leftCoordinateLabel = new QLabel[fieldHeight];
	for (int i = 0; i < fieldHeight; i++)
	{
		leftCoordinateLabel[i].setText(getStringLeftCoordinate(i + 1));
		leftCoordinateLabel[i].setStyleSheet(StyleData::getInstance()->getCoordinateCellBorderStyle());
		leftCoordinateLabel[i].setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		uiField_p->addWidget(&leftCoordinateLabel[i], i + 1, 0);
	}

	for (int i = 0; i < fieldHeight; i++)
	{
		for (int j = 0; j < fieldWidth; j++)
		{
			uiField_p->addWidget(&labelField[i][j], labelField[i][j].x + 1, labelField[i][j].y + 1);

			connect(&labelField[i][j], SIGNAL(mousePressed()), this, SLOT(selectActiveCell()));
		}
	}

	resetLabelStyle();

	dataField = new std::string * [fieldHeight];
	for (int i = 0; i < fieldHeight; i++)
	{
		dataField[i] = new std::string[fieldHeight];
	}

	infoLabel_p->setText("No active cell:");
	infoLineEdit_p->setText("");
	infoLineEdit_p->setDisabled(true);

	// call parser about new field
	// mazaevZrobuNovijField
	// void newField(int n, int m)
}

void MainField::selectActiveCell()
{
	// deselect prev cell

	if (activeLabelX != -1)
	{
		labelField[activeLabelX][activeLabelY].setStyleSheet(StyleData::getInstance()->getCellDefaultBorderStyle());
	}

	// upd selected cell
	activeLabelX = ((Coordinatedlabel*)sender())->x;
	activeLabelY = ((Coordinatedlabel*)sender())->y;

	labelField[activeLabelX][activeLabelY].setStyleSheet(StyleData::getInstance()->getCellSelectedBorderStyle());

	//upd info
	infoLineEdit_p->setDisabled(false);
	infoLabel_p->setText("Active cell is {" + getStringLeftCoordinate(activeLabelX+1) + ":" + QString::number(activeLabelY + 1) + "}:");
	infoLineEdit_p->setText(QString::fromStdString(dataField[activeLabelX][activeLabelY]));
	infoLineEdit_p->setFocus();
}

void MainField::refreshCell()
{
	if (activeLabelX == -1)
	{
		return;
	}

	QString dat = ((QLineEdit*)sender())->text();

	dataField[activeLabelX][activeLabelY] = dat.toStdString();

	// to call parser updateCell() and update label value
	if (dat != "")
	{
		labelField[activeLabelX][activeLabelY].setText("notEmpty");
	}
	else
	{
		labelField[activeLabelX][activeLabelY].setText("");
	}
	// vector<pair<pair<int, int>,string> > updateCell(int x, int y, string newLine)
}

QString MainField::getStringUpperCoordinate(int position)
{
	QString res;

	if (position < 10)
	{
		res = "  " + QString::number(position) + "  ";
	}
	else
	{
		res = " " + QString::number(position) + " ";
	}

	return res;
}

QString MainField::getStringLeftCoordinate(int position)
{
	QString res;

	if (position <= ALPHABET_SIZE)
	{
		res += char(position - 1 + 'A');
	}
	else
	{
		res += char((position - ALPHABET_SIZE - 1) / ALPHABET_SIZE + 'A');
		res += char((position - ALPHABET_SIZE - 1) % ALPHABET_SIZE + 'A');
	}

	return res;
}

void MainField::saveField()
{
	if (labelField == nullptr)
	{
		QMessageBox::warning(parent, "Error", "No ative board!");

		return;
	}

	QString fileName = QFileDialog::getSaveFileName(parent, "Save file");

	if (fileName == "")
	{
		QMessageBox::warning(parent, "Error", "No file choosen!");

		return;
	}

	std::string stdFileName = fileName.toStdString();

	std::ofstream out(stdFileName);

	if (!out.is_open())
	{
		QMessageBox::warning(parent, "Error", "Can`t open the file!");

		return;
	}

	out << fieldHeight << " " << fieldWidth << "\n";
	for (int i = 0; i < fieldHeight; i++)
	{
		for (int j = 0; j < fieldWidth; j++)
		{
			out << dataField[i][j] << SPECIAL_SYMBOL;
		}
	}

	out.close();
}

void MainField::openField()
{
	QString fileName = QFileDialog::getOpenFileName(parent, "Save file");

	if (fileName == "")
	{
		QMessageBox::warning(parent, "Error", "No file choosen!");

		return;
	}

	std::string stdFileName = fileName.toStdString();

	std::ifstream in(stdFileName);

	if (!in.is_open())
	{
		QMessageBox::warning(parent, "Error", "Can`t open the file!");

		return;
	}

	int tempHeight=0, tempWidth=0, specialSymbolCount = 0;
	std::string context, tempContext;

	if (!(in >> tempHeight >> tempWidth))
	{
		QMessageBox::warning(parent, "Error", "Incorrect file input!");

		return;
	}

	if (tempHeight<1 || tempHeight>DEFAULT_MAX_HEIGHT || tempWidth<1 || tempWidth>DEFAULT_MAX_WIDTH)
	{
		QMessageBox::warning(parent, "Error", "Incorrect board size!");

		return;
	}

	in >> context;
	while (in >> tempContext)
	{
		context += " ";
		context += tempContext;
	}
	in.close();

	for (size_t i = 0; i < context.size(); i++)
	{
		if (context[i] == SPECIAL_SYMBOL)
		{
			specialSymbolCount++;
		}
	}

	if (specialSymbolCount != tempHeight * tempWidth || context.back() != SPECIAL_SYMBOL)
	{
		QMessageBox::warning(parent, "Error", "Incorrect file input!");

		return;
	}

	createNewField(tempHeight, tempWidth);

	tempContext.clear();
	int fieldPositionI = 0, fieldPositionJ = 0;
	for (size_t i = 0; i < context.size(); i++)
	{
		if (context[i] == SPECIAL_SYMBOL)
		{
			dataField[fieldPositionI][fieldPositionJ] = tempContext;
			fieldPositionJ++;
			if (fieldPositionJ == tempWidth)
			{
				fieldPositionI++;
				fieldPositionJ = 0;
			}
			tempContext.clear();
		}
		else
		{
			tempContext += context[i];
		}
	}

	// to call parser create new field
	// vector<pair<pair<int, int>,string> > newField(int n, int m, vector<vector<string> > field)
	for (int i = 0; i < tempHeight; i++)
	{
		for (int j = 0; j < tempWidth; j++)
		{
			if (dataField[i][j] != "")
			{
				labelField[i][j].setText("notEmpty");
			}
		}
	}
}