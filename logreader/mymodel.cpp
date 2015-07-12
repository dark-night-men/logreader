//! [Quoting ModelView Tutorial]
// mymodel.cpp
#include "mymodel.h"
#include "logfile.h"

MyModel::MyModel(QObject *parent)
    :QAbstractListModel(parent)
{
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
   return logFile_->stringList().size();
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
            return logFile_->stringList().at(index.row());

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
    if(!logFile_){
        return;
    }

    logFile_->read();
    logFile_->splitArray();
}
//! [Quoting ModelView Tutorial]
