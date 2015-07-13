#ifndef MYVIEW_H
#define MYVIEW_H

#include <QtWidgets>

class MyView : public QTableView
{
Q_OBJECT
public:
    MyView(QWidget * parent = 0);

protected slots:
    void rowCountChanged(int oldCount, int newCount);

};
#endif
