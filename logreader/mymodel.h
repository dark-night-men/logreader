#ifndef MYMODEL_H
#define MYMODEL_H

//! [Quoting ModelView Tutorial]
// mymodel.h
#include <QAbstractTableModel>

class LogFile;
class MyModel : public QAbstractTableModel
{
Q_OBJECT
Q_PROPERTY(LogFile *logFile_ WRITE setLogFile )

public:
    MyModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    void setLogFile(LogFile * logFile) {logFile_ = logFile;}
    void readData();
private:
    LogFile *logFile_ ;
};
//! [Quoting ModelView Tutorial]

#endif // MYMODEL_H
