#ifndef MYMODEL_H
#define MYMODEL_H

#include <QtGui>
#include <QtCore>
#include <QtWidgets>

#include <QAbstractTableModel>

class ILogFile;
class MyModel : public QAbstractTableModel
{
Q_OBJECT
//Q_PROPERTY(ILogFile *logFile_ WRITE setLogFile )
//Q_PROPERTY(QAbstractTableModel* view_ READ WRITE setLogFile )

public:
    MyModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    void setLogFile(ILogFile * logFile); 
    void setView(QTableView* view) {view_ = view;}

    bool insertRows(int position, int rows, const QModelIndex &index);

public slots:
    void readData();
private:
    void chunkReaded( int chunkSize);

private:
    ILogFile *logFile_ ;
    QTableView* view_;
    quint64 tableSize_;
};

#endif // MYMODEL_H
