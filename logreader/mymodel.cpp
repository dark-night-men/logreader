// mymodel.cpp
#include "mymodel.h"
#include "ilogfile.h"
#include "../debugprint/debugprint.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

MyModel::MyModel(QObject *parent)
    :QAbstractTableModel(parent)
     ,logFile_(0)
     ,view_(0)
     ,tableSize_(0)
{
    QTimer* t = new QTimer(this);
    t->setInterval(0);
    connect(t,&QTimer::timeout,this,&MyModel::readData);
    t->start();
}

int MyModel::rowCount(const QModelIndex & parent) const
{

    //logprint(QString("MyModel::rowCount %1").arg(logFile_->stringList().size()));
    //return logFile_->stringList().size();
    //return 1000000;
    if ( parent.isValid() ){
        return 0;
    } else {

        //int listsize = logFile_->stringList().size();
        //qDebug() << "MyModel::rowCount started " << listsize;
        //return listsize;
        //logprint(QString("MyModel::rowCount %1").arg(tableSize_));
        return tableSize_;
    }

    //return 10;
    //printStack(99);
    //return rand() % 3 + 10 ;
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 1;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole && index.row() < 1000000)
    {

        if( index.column() == 0 ) {
            if (index.row() >= logFile_->stringList().size()) {
                return QVariant(); 
            } else {
                return logFile_->stringList().at(qMax(0,index.row()-1));
            }
            //return logFile_->stringList()
            //    .at(logFile_->stringList().size() % 3);

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
    const quint64 ssize0 = logFile_->stringList().size();

    logFile_->splitArray();
    chunkReaded(logFile_->stringList().size() - ssize0 );
    //view_->scrollTo(index(rowCount(),0));
    //view_->scrollToBottom();

}

void MyModel::setLogFile(ILogFile * logFile) 
{
    logFile_ = logFile;
    //connect(logFile_, &ILogFile::chunkReaded, this, &MyModel::chunkReaded);
}

void MyModel::chunkReaded( int chunkSize)
{
    if (chunkSize>0) {
        logprint("MyModel::chunkReaded");
        insertRows( tableSize_+1, chunkSize, QModelIndex());
    }
}

bool MyModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    logprint(QString("insertRows pos %1 , rows %2").arg(position).arg(rows));
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    tableSize_ += rows;

    endInsertRows();
    return true;
}

