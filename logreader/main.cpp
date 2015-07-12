//! [Quoting ModelView Tutorial]
// main.cpp
#include <QtGui>
#include <QtWidgets>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTableView>
#include "mymodel.h"
#include "logfile.h"

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    //QString files = QFileDialog::getOpenFileName(0, ("Select File"), "/");
    //if (files.isEmpty())
    //    return 1;
    //QString fileName = QFileInfo(files).fileName();


    QListView tableView;
    MyModel myModel(0);
    LogFile logFile("/home/zerg/projects/logreader/textgen/log1k");
    //LogFile logFile(fileName);
    myModel.setLogFile(&logFile);
    myModel.readData();
    tableView.setModel( &myModel );
    tableView.show();
    return a.exec();
}
//! [Quoting ModelView Tutorial]
