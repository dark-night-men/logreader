#include "logfile.h"
#include <QDebug>

LogFile::LogFile(const QString & filename)
    :QFile(filename)
{
    qDebug() << filename;
}


void LogFile::read()
{
    qDebug() << fileName();
    if (!open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    //while (!file_.atEnd()) {
    //    content_ = file_.readLine();
    //    //process_line(line);
    //}
    

    content_ = readAll();
}

void LogFile::splitArray()
{
    stringList_.clear();
    foreach(  QByteArray s , content_.split('\n') ) { stringList_ << s ; }
}
