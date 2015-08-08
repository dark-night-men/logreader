//! [Quoting ModelView Tutorial]
// main.cpp
#include <QtGui>
#include <QtWidgets>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTableView>
#include "mymodel.h"
#include "logfile.h"
#include "ilogfile.h"
#include "myview.h"
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QString files = QFileDialog::getOpenFileName(0, ("Select File"), "/");
    //if (files.isEmpty())
    //    return 1;
    //QString fileName = QFileInfo(files).fileName();

    QMainWindow mainWindow;
    mainWindow.setCentralWidget(new MainWidget);
    mainWindow.show();

    return a.exec();
}
