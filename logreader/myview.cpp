#include "myview.h"
#include <QDebug>

MyView::MyView(QWidget * w)
    :QTableView(w)
{
}

void MyView::rowCountChanged(int oldCount, int newCount)
{
    qDebug() << "MyView::rowCountChanged started" ;

    QTableView::rowCountChanged(oldCount, newCount);
    scrollToBottom();
}
