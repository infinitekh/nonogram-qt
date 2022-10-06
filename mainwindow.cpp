#include "mainwindow.h"
#include "ui_dialog.h"
MainWindow::MainWindow(QWidget *parent)  {
	window = new QWidget();
	menu = new QMenuBar(window);
	fileMenu = new QMenu(tr("&File"), window);
	helpMenu = new QMenu(tr("&Help"), window);
	menu->addMenu(fileMenu);
	menu->addMenu(helpMenu);
	exitAction = new QAction(tr("E&xit"), fileMenu);
	connect(exitAction, SIGNAL(triggered()), this, SLOT(quit()));
	helpAction = new QAction(tr("&Help"), helpMenu);
	connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));
	aboutAction = new QAction(tr("&About"), helpMenu);
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
	fileMenu->addAction(exitAction);
	helpMenu->addAction(helpAction);
	helpMenu->addAction(aboutAction);
	layout = new QVBoxLayout(window);
    top = new QHBoxLayout(window);
    top->setAlignment(Qt::AlignLeft);
    auto scroll = new QScrollArea;
    scroll->setWidget(window);
	grid = new QGridLayout(window);
	grid->setSpacing(0);
	grid->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	style = new QCommonStyle();
	widthBox = new QSpinBox(window);
	heightBox = new QSpinBox(window);
	widthBox->setRange(MIN_PUZZLE_SIZE, MAX_PUZZLE_SIZE);
	heightBox->setRange(MIN_PUZZLE_SIZE, MAX_PUZZLE_SIZE);
	widthBox->setValue(DEFAULT_PUZZLE_SIZE);
	heightBox->setValue(DEFAULT_PUZZLE_SIZE);
	widthLabel = new QLabel(tr("Columns:"), window);
	heightLabel = new QLabel(tr("Rows:"), window);
    generate = new QPushButton(tr("Generate puzzle"), this);
    connect(generate, SIGNAL(clicked()), this, SLOT(generatePuzzle()));
    generate_specified = new QPushButton(tr("Make"), this);
    connect(generate_specified, SIGNAL(clicked()), this, SLOT(call_named_puzzle()));
    surrender = new QPushButton(tr("Give up"), this);
	connect(surrender, SIGNAL(clicked()), this, SLOT(giveUp()));
	surrender->setEnabled(false);
	ngram = NULL;
	lockAction = false;
    swapButton = new QPushButton(tr("Function Swap"),this);
    swapButton->setCheckable(true);
    swapButton->setStyleSheet(" *::checked{"
                              "background: #880000; "
                              ""
                              "}"
                              "");
    swapButton->setMinimumHeight(50);
	window->setLayout(layout);
	setCentralWidget(window);
	top->addWidget(heightLabel);
	top->addWidget(heightBox);
	top->addWidget(widthLabel);
	top->addWidget(widthBox);
	top->addWidget(generate);
    top->addWidget(generate_specified);
	top->addWidget(surrender);
	layout->addSpacing(20);
    layout->addLayout(top);
	layout->addLayout(grid);
    layout->addWidget(swapButton);
    dialog = new QDialog(this);
    Ui::Dialog * ui = new Ui::Dialog;
    ui->setupUi(dialog);
}

MainWindow::~MainWindow() {
	if (ngram) {
		cleanUp();
	}
	delete style;
	style = NULL;
	delete window;
	window = NULL;
}

// Generates, verifies and displays the puzzle and its graphical components.
void MainWindow::generatePuzzle() {
	int pos, spacer_x, spacer_y;
	// Start by disabling the buttons, so the user can't mess things up, as
	// generating the puzzle can take some time. (Especially the big ones.)
	widthBox->setEnabled(false);
	heightBox->setEnabled(false);
	generate->setEnabled(false);
    generate_specified->setEnabled(false);
	// If this isn't the first puzzle generated, we need to clean out the garbage.
	// ngram will be a NULL pointer the first time, but defined on subsequent calls.
	if (ngram) {
		cleanUp();
	}
	width = widthBox->value();
	height = heightBox->value();
	// We need to map the clicks and right clicks to the respective methods.
	// Using mappers allows us to easily identify the button that sent the signal.
	mapperLeftButton = new QSignalMapper(this);
	mapperRightButton = new QSignalMapper(this);
	ngram = new Nonogram(width, height);
	xAxisClue = ngram->getXAxis();
	yAxisClue = ngram->getYAxis();
	Solver *solv = new Solver(width, height, xAxisClue, yAxisClue);
	// Retry puzzle creation until we get a solvable one.
	while (!solv->solve()) {
		delete solv;
		delete ngram;
		ngram = new Nonogram(width, height);
		xAxisClue = ngram->getXAxis();
		yAxisClue = ngram->getYAxis();
		solv = new Solver(width, height, xAxisClue, yAxisClue);
	}
	delete solv;
	// Create and add the clue labels
	spacer_x = 0;
	spacer_y = 0;
	for (int i = 0; i < width; ++i) {
		QString str = "";
		QString num = "";
		for (int j = 0; j < xAxisClue[i]->size(); ++j) {
			num.setNum(xAxisClue[i]->at(j), 10);
			str.append(num);
			if (j < xAxisClue[i]->size() - 1) {
				str.append("\n");
			}
		}
		xAxis.push_back(new QLabel(str));
		xAxis.at(i)->setAlignment(Qt::AlignCenter | Qt::AlignBottom);
		// We want to separate the UI buttons in 5 x 5 chunks, so that counting
		// blocks becomes easier for the user.
		if (i > 0 && i % 5 == 0) {
			++spacer_x;
			grid->setColumnMinimumWidth(i + spacer_x, 2);
		}
		grid->addWidget(xAxis.at(i), 0, i + spacer_x + 1);
	}
	for (int i = 0; i < height; ++i) {
		QString str = "";
		QString num = "";
		for (int j = 0; j < yAxisClue[i]->size(); ++j) {
			num.setNum(yAxisClue[i]->at(j), 10);
			str.append(num);
			str.append("  ");
		}
		yAxis.push_back(new QLabel(str));
		yAxis.at(i)->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
		if (i > 0 && i % 5 == 0) {
			++spacer_y;
			grid->setRowMinimumHeight(i + spacer_y, 2);
		}
		grid->addWidget(yAxis.at(i), i + spacer_y + 1, 0);
	}
	// Create the playing field itself.
	spacer_y = 0;
	for (int i = 0; i < height; ++i) {
		if (i > 0 && i % 5 == 0) {
			++spacer_y;
		}
		spacer_x = 0;
		for (int j = 0; j < width; ++j) {
			if (j > 0 && j % 5 == 0) {
				++spacer_x;
			}
			pos = i * width + j;
			status.push_back(UNKNOWN);
			puzzle.push_back(new PushButton(&mouseButton, &firstClick));
			puzzle.at(pos)->setStyle(style);
			connect(puzzle.at(pos), SIGNAL(solid()), mapperLeftButton, SLOT(map()));
			connect(puzzle.at(pos), SIGNAL(dot()), mapperRightButton, SLOT(map()));
			connect(puzzle.at(pos), SIGNAL(released()), this, SLOT(checkSolution()));
            connect(swapButton,SIGNAL(toggled(bool)),puzzle.at(pos),SLOT(setMouseSwap(bool)));
			mapperLeftButton->setMapping(puzzle.at(pos), pos);
			mapperRightButton->setMapping(puzzle.at(pos), pos);
			grid->addWidget(puzzle.at(pos), i + spacer_y + 1, j + spacer_x + 1);
		}
	}
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
	connect(mapperLeftButton, SIGNAL(mapped(int)), this, SLOT(solidClicked(int)));
	connect(mapperRightButton, SIGNAL(mapped(int)), this, SLOT(dotClicked(int)));
#else
	connect(mapperLeftButton, &QSignalMapper::mappedInt,this,  &MainWindow::solidClicked);
	connect(mapperRightButton, &QSignalMapper::mappedInt, this, &MainWindow::dotClicked);
#endif
	// Enable button that lets user see the solution without solving
	surrender->setEnabled(true);
}

// Cleans up stuff before a new game is started
void MainWindow::cleanUp() {
	delete ngram;
	ngram = NULL;
        for (int i = 0; i < xAxis.size(); ++i) {
		delete xAxis.at(i);
	}
	xAxis.clear();
	for (int i = 0; i < yAxis.size(); ++i) {
		delete yAxis.at(i);
	}
	yAxis.clear();
    for (int i = 0; i < puzzle.size(); ++i) {
		delete puzzle.at(i);
	}
	puzzle.clear();
	delete mapperLeftButton;
	delete mapperRightButton;
	status.clear();
}

// Display all solids that the user has missed, in grey and all
// dots he has mistakenly identified as solids in red.
void MainWindow::giveUp() {
	surrender->setEnabled(false);
	int pos;
	for (int i = 0; i < height; ++i) {
		size_t mask = 1 << width;
		for (int j = 0; j < width; ++j) {
			mask >>= 1;
			pos = i * width + j;
			if (status.at(pos) == SOLID) {
				if (!(ngram->getField()[i] & mask)) {
					puzzle.at(pos)->setStyleSheet("background-color: rgb(255, 0, 0)");
				}
			}
			else if (ngram->getField()[i] & mask) {
                puzzle.at(pos)->setStyleSheet("background-color: rgb(150, 150, 150) ;"
                                              "color : rgb(255,0,0)");
			}
		}
	}
	widthBox->setEnabled(true);
	heightBox->setEnabled(true);
	generate->setEnabled(true);
    generate_specified->setEnabled(true);
}

// Called when a button is clicked or dragged over with button depressed.
// The firstClick & lockAction variables are used to determine which call to
// the function represents the first click, then lock the behaviour of the
// function to the behaviour expected from that first click.
void MainWindow::solidClicked(int position) {
	puzzle.at(position)->setText("");
	if (status.at(position) == SOLID) {
		if (firstClick || lockAction) {
			status.at(position) = UNKNOWN;
			puzzle.at(position)->setStyleSheet("background-color: rgb(215, 215, 215)");
			lockAction = true;
		}
	}
	else {
		status.at(position) = SOLID;
		puzzle.at(position)->setStyleSheet("background-color: rgb(50, 50, 50)");
    }
	firstClick = false;
}

// Same as above, but for the right mouse button.
void MainWindow::dotClicked(int position) {
	if (status.at(position) == DOT) {
		if (firstClick || lockAction) {
			status.at(position) = UNKNOWN;
			puzzle.at(position)->setText("");
			puzzle.at(position)->setStyleSheet("background-color: rgb(215, 215, 215)");
            lockAction = true;
		}
	}
	else {
		status.at(position) = DOT;
		puzzle.at(position)->setText("X");
        puzzle.at(position)->setStyleSheet("background-color: rgb(215, 215, 215);"
                                           "color: black");
	}
	firstClick = false;
}

// Check whether the puzzle is solved or not. Display a message if it is.
void MainWindow::checkSolution() {
	// Since this function is called when the mouse button is released,
	// we use it to unset the lockAction variable.
	lockAction = false;
	for (int i = 0; i < height; ++i) {
		size_t test = 0;
		size_t mask = 1 << width;
		for (int j = 0; j < width; ++j) {
			mask >>= 1;
			if (status.at(i * width + j) == SOLID) {
				test |= mask;
			}
		}
		if (test != ngram->getField()[i]) {
			return;
		}
	}
	for (int i = 0; i < width * height; ++i) {
		puzzle.at(i)->setEnabled(false);
	}
	QMessageBox mb;
	mb.setWindowTitle(tr("Well done"));
	mb.setText(tr("You have solved the puzzle!"));
	mb.exec();
	widthBox->setEnabled(true);
	heightBox->setEnabled(true);
    generate->setEnabled(true);
    generate_specified->setEnabled(true);
    surrender->setEnabled(false);
}

void MainWindow::call_named_puzzle()
{

    time_t time_a;
    dialog->findChild<QSpinBox *>("puz_width")->setValue(width);
    dialog->findChild<QSpinBox *>("puz_height")->setValue(height);
    if ( QDialog::Rejected == dialog->exec()) {
       return;
    }


    width = dialog->findChild<QSpinBox *>("puz_width")->value();
    height = dialog->findChild<QSpinBox *>("puz_height")->value();
    time_a = dialog->findChild<QSpinBox *>("puz_num")->value();

    int pos, spacer_x, spacer_y;
    // Start by disabling the buttons, so the user can't mess things up, as
    // generating the puzzle can take some time. (Especially the big ones.)
    widthBox->setEnabled(false);
    heightBox->setEnabled(false);
    generate->setEnabled(false);
    generate_specified->setEnabled(false);
    // If this isn't the first puzzle generated, we need to clean out the garbage.
    // ngram will be a NULL pointer the first time, but defined on subsequent calls.
    if (ngram) {
        cleanUp();
    }
    widthBox->setValue(width);
    heightBox->setValue(height);
    // We need to map the clicks and right clicks to the respective methods.
    // Using mappers allows us to easily identify the button that sent the signal.
    mapperLeftButton = new QSignalMapper(this);
    mapperRightButton = new QSignalMapper(this);
    ngram = new Nonogram(width, height,time_a);
    xAxisClue = ngram->getXAxis();
    yAxisClue = ngram->getYAxis();
    Solver *solv = new Solver(width, height, xAxisClue, yAxisClue);
    // Retry puzzle creation until we get a solvable one.
    while (!solv->solve()) {
        delete solv;
        delete ngram;
        ngram = new Nonogram(width, height);
        xAxisClue = ngram->getXAxis();
        yAxisClue = ngram->getYAxis();
        solv = new Solver(width, height, xAxisClue, yAxisClue);
    }
    delete solv;
    // Create and add the clue labels
    spacer_x = 0;
    spacer_y = 0;
    for (int i = 0; i < width; ++i) {
        QString str = "";
        QString num = "";
        for (int j = 0; j < xAxisClue[i]->size(); ++j) {
            num.setNum(xAxisClue[i]->at(j), 10);
            str.append(num);
            if (j < xAxisClue[i]->size() - 1) {
                str.append("\n");
            }
        }
        xAxis.push_back(new QLabel(str));
        xAxis.at(i)->setAlignment(Qt::AlignCenter | Qt::AlignBottom);
        // We want to separate the UI buttons in 5 x 5 chunks, so that counting
        // blocks becomes easier for the user.
        if (i > 0 && i % 5 == 0) {
            ++spacer_x;
            grid->setColumnMinimumWidth(i + spacer_x, 2);
        }
        grid->addWidget(xAxis.at(i), 0, i + spacer_x + 1);
    }
    for (int i = 0; i < height; ++i) {
        QString str = "";
        QString num = "";
        for (int j = 0; j < yAxisClue[i]->size(); ++j) {
            num.setNum(yAxisClue[i]->at(j), 10);
            str.append(num);
            str.append("  ");
        }
        yAxis.push_back(new QLabel(str));
        yAxis.at(i)->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        if (i > 0 && i % 5 == 0) {
            ++spacer_y;
            grid->setRowMinimumHeight(i + spacer_y, 2);
        }
        grid->addWidget(yAxis.at(i), i + spacer_y + 1, 0);
    }
    // Create the playing field itself.
    spacer_y = 0;
    for (int i = 0; i < height; ++i) {
        if (i > 0 && i % 5 == 0) {
            ++spacer_y;
        }
        spacer_x = 0;
        for (int j = 0; j < width; ++j) {
            if (j > 0 && j % 5 == 0) {
                ++spacer_x;
            }
            pos = i * width + j;
            status.push_back(UNKNOWN);
            puzzle.push_back(new PushButton(&mouseButton, &firstClick));
            puzzle.at(pos)->setStyle(style);
            connect(puzzle.at(pos), SIGNAL(solid()), mapperLeftButton, SLOT(map()));
            connect(puzzle.at(pos), SIGNAL(dot()), mapperRightButton, SLOT(map()));
            connect(puzzle.at(pos), SIGNAL(released()), this, SLOT(checkSolution()));
            mapperLeftButton->setMapping(puzzle.at(pos), pos);
            mapperRightButton->setMapping(puzzle.at(pos), pos);
            grid->addWidget(puzzle.at(pos), i + spacer_y + 1, j + spacer_x + 1);
        }
    }
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
	connect(mapperLeftButton, SIGNAL(mapped(int)), this, SLOT(solidClicked(int)));
	connect(mapperRightButton, SIGNAL(mapped(int)), this, SLOT(dotClicked(int)));
#else
	connect(mapperLeftButton, &QSignalMapper::mappedInt,this,  &MainWindow::solidClicked);
	connect(mapperRightButton, &QSignalMapper::mappedInt, this, &MainWindow::dotClicked);
#endif
    // Enable button that lets user see the solution without solving
    surrender->setEnabled(true);
}

void MainWindow::about() {
	QMessageBox mb;
	mb.setWindowTitle(tr("About"));
	mb.setText(tr("<p><h3>Nonogram-qt 1.1.1</h3></p><p>Copyright: Daniel Suni, 2012, 2013, 2018</p><p>Distributed under the GNU GPL v3</p>"));
	mb.exec();
}

void MainWindow::help() {
	QWidget *helpWindow = new QWidget();
	helpWindow->setWindowTitle(tr("Help"));
	QHBoxLayout *bl = new QHBoxLayout(helpWindow);
	QLabel *text = new QLabel(tr("<h2>What are nonograms?</h2>\
<p>Nonograms are logic puzzles consisting of a rectangular grid divided into cells. These cells can be either<br>\
colored (solids) or blank (dots). At the start of the game all cells are blank, and the purpose of the game is<br>\
to figure out which ones should be colored.</p>\
<p>Each row and column in the grid is fitted with a clue consisting of a series of numbers. These numbers reveal<br>\
how many solids there are on the row/column as well as something about their grouping. If e.g. the clue is<br>\
(3 1 2) we know that from left to right there is first a series of 3 consequtive solids, then X number of blanks,<br>\
where X >= 1, then a single solid, then another unspecified number of blanks, and finally 2 consequtive solids.<br>\
If the row was 10 cells long, one possible arrangement would be (-###-#--##), another one would be (###-#-##--).<br>\
Since there are rules for both rows and columns, only one arrangement is actually correct, though. The puzzle is<br>\
to find the arrangement that conforms to all the given clues.</p>\
<h2>How to play</h2>\
<p>In order to start a new game, please select the size of the desired playing field, and click the &quot;Generate puzzle&quot;<br>\
button. Generating the puzzle can take a few seconds - especially if it's a big one, so please be patient.</p>\
<p>When starting all cells are blank. You can mark a cell as a solid by clicking on it. You can also mark larger areas<br>\
by dragging the mouse with the button pressed. If you've made a mistake, just click the cell again to revert it to a<br>\
dot. You can also mark known dots by right clicking (and dragging). This will be shown by an 'X' appearing in that<br>\
cell. Notice that you don't need to explicitly mark the dots in order to solve the puzzle. That functionality only<br>\
exists for your own convenience.</p>\
<p>Every time you make a move the computer will automatically check whether you've successfully solved the puzzle<br>\
 or not. Once the puzzle is solved, you will immediately be informed. If the puzzle turns out to be too hard, you can<br>\
end it, and look at the solution by pressing the &quot;Give up&quot; button. Remaining solids will be displayed in<br>\
grey, and possible mistakes (i.e. dots marked as solids) will be displayed in red.</p>"), helpWindow);
	helpWindow->setLayout(bl);
	bl->addWidget(text);
	helpWindow->show();
}

void MainWindow::quit() {
	if (ngram) {
		cleanUp();
	}
	delete style;
	style = NULL;
	delete window;
	window = NULL;
	exit(0);
}
