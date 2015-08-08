
#include <QtGui>
#include <QtWidgets>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTableView>
#include "mymodel.h"
#include "logfile.h"
#include "ilogfile.h"
#include "myview.h"
#include "../debugprint/debugprint.h"
#include "mainwidget.h"

MainWidget::MainWidget(QWidget * parent)
    :QWidget(parent)

    ,findField_(new QLineEdit(this))
    ,tableModel_(new MyModel(0))
    ,logFile_(new ILogFile("./autogen.log"))
    ,tableView_(new MyView)
{
    QVBoxLayout *layout = new QVBoxLayout( this );

    //options eg on/off line numbering
    QPushButton *options = new QPushButton( "options");
    QHBoxLayout *optionsLayout = new QHBoxLayout;
    optionsLayout->addStretch();
    optionsLayout->addWidget(options);

    layout->addLayout(optionsLayout);

    layout->addWidget(tableView_);

    QHBoxLayout *layoutFind = new QHBoxLayout;
    layoutFind->addWidget(new QLabel("Find"));
    layoutFind->addWidget(findField_);
    QPushButton *findButton = new QPushButton("Find");
    layoutFind->addWidget(findField_);
    layoutFind->addWidget(findButton);
    layout->addLayout(layoutFind);
    
    tableModel_->setView(tableView_);
    tableModel_->setLogFile(logFile_);
    tableView_->setModel(tableModel_);

    connect(findButton,SIGNAL(clicked(bool)),SLOT(findButtonSlot()));
}

void MainWidget::findButtonSlot()
{
    logFile_->find(findField_->text());
}


