#include "logfile.h"

void LogFile::read()
{
    if (!file_.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    //while (!file_.atEnd()) {
    //    content_ = file_.readLine();
    //    //process_line(line);
    //}
    

    content_ = file_.readAll();
}

void LogFile::splitArray()
{
    stringList_.clear();
    foreach(  QByteArray s , content_.split('\n') ) { stringList_ << s ; }
}
