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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QString files = QFileDialog::getOpenFileName(0, ("Select File"), "/");
    //if (files.isEmpty())
    //    return 1;
    //QString fileName = QFileInfo(files).fileName();

    QMainWindow mainWindow;
    QWidget *mainWidget = new QWidget( &mainWindow );
    mainWindow.setCentralWidget(mainWidget);
    QVBoxLayout *layout = new QVBoxLayout( mainWidget );

    QPushButton *options = new QPushButton( "options");
    QHBoxLayout *optionsLayout = new QHBoxLayout;
    optionsLayout->addStretch();
    optionsLayout->addWidget(options);

    layout->addLayout(optionsLayout);

    MyView *tableView=new MyView;
    layout->addWidget(tableView);

    QLineEdit *findField = new QLineEdit;
    QHBoxLayout *layoutFind = new QHBoxLayout;
    layoutFind->addWidget(new QLabel("Find"));
    layoutFind->addWidget(findField);
    layout->addLayout(layoutFind);

    //mainWindow.setCentralWidget(tableView);


    MyModel myModel(0);
    myModel.setView(tableView);
    ILogFile logFile("./autogen.log");
    //LogFile logFile(fileName);
    myModel.setLogFile(&logFile);
    //myModel.readData();
    tableView->setModel( &myModel );
    //tableView->show();
    mainWindow.show();

    return a.exec();
}
