#include "ilogfile.h"
#include <QDebug>
#include <assert.h>


IReader::IReader(const QString & filename, ILogFile* ilogFile )
    :QFile(filename)
     ,ilogFile_(ilogFile) 
{ 
    assert(ilogFile_);
}

void IReader::read( const QString & )
{
    qDebug() << fileName();
    forever {
        if (!open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        seek(ilogFile_->currentPos_);
        //while (!file_.atEnd()) {
        //    content_ = file_.readLine();
        //    //process_line(line);
        //}


        ilogFile_->content_.append(readAll());
        ilogFile_->currentPos_ = pos();

        quint64 totalSize ;
        foreach( const QByteArray & a, ilogFile_->content_ ){ 
            totalSize += a.size();
        }

        if (totalSize > 10000) {
            emit resultReady("qqqq");
            break ;
        }
    }
}



ILogFile::ILogFile(const QString & filename)
    :currentPos_(0)
    ,reader_(0)
    ,fileName_(filename)
    ,toSplit_(0)
{

    IReader *reader_ = new IReader(filename, this);
    reader_->moveToThread(&readerThread_);
    connect(&readerThread_, &QThread::finished, reader_, &QObject::deleteLater);
    connect(this, &ILogFile::operate, reader_, &IReader::read);
    connect(reader_, &IReader::resultReady, this, &ILogFile::handleResults);
    readerThread_.start();
}

ILogFile::~ILogFile() {
    readerThread_.quit();
    readerThread_.wait();
}

void ILogFile::read()
{
    emit operate("qqq");
}

void ILogFile::handleResults(const QString &)
{
    qDebug() << "ILogFile::handleResults slot started";
}

void ILogFile::splitArray()
{
    //QLinkedList< QString > tmp;
    for( quint64 i=toSplit_ ; i<content_.size() ; ++i ){
        foreach( const QString & s , content_.at(i).split('\n') ) {
            stringList_ << s ; 
        }
    }

    /*
    quint64 lastLine(stringList_.size()-1);
    if ( stringList_.last().last() != '\n' ) {

    stringList_.last().last()stringList_.size()-1) << s ;
    */
}

