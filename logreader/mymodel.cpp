//! [Quoting ModelView Tutorial]
// mymodel.cpp
#include "mymodel.h"
#include "ilogfile.h"

#include <stdio.h>
#include <stdlib.h>

MyModel::MyModel(QObject *parent)
    :QAbstractTableModel(parent)
     ,logFile_(0)
     ,view_(0)
{
    QTimer* t = new QTimer(this);
    t->setInterval(0);
    connect(t,&QTimer::timeout,this,&MyModel::readData);
    t->start();
}

int MyModel::rowCount(const QModelIndex & parent) const
{
    //if ( parent.isValid() ){
    //    return 0;
    //} else {

    //    int listsize = logFile_->stringList().size();
    //    qDebug() << "MyModel::rowCount started " << listsize;
    //    return listsize;
    //}

    //return 100;
    return rand() % 3 + 10 ;
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 1;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {

        if( index.column() == 0 ) {
            return logFile_->stringList()
                .at(logFile_->stringList().size() % 3);
            //qDebug() << "string list size " << logFile_->stringList().size() ;
            //return "eeeeeeeeee";

        } else {
            return QString("Row%1, Column%2")
                .arg(index.row() + 1)
                .arg(index.column() +1);
        }
    }
    return QVariant();
}

void MyModel::readData()
{

    //qDebug() << "MyModel::readData started" ;
    if(!logFile_){
        qDebug() << "MyModel::readData logfile_ is NULL" ;
        return;
    }

    logFile_->read();
    logFile_->splitArray();
    //view_->scrollTo(index(rowCount(),0));
    //view_->scrollToBottom();

}
//! [Quoting ModelView Tutorial]
