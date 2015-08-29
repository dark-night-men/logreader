#include "../debugprint/debugprint.h"
#include "ilogfile.h"
#include <QDebug>
#include <assert.h>

#include <regex.h>        

IReader::IReader(const QString & filename, ILogFile* ilogFile )
    :QFile(filename)
     ,ilogFile_(ilogFile) 
{ 
    assert(ilogFile_);
}

void IReader::read( const QString & ppp )
{
    qDebug() << "IReader::read started" << ppp;
    forever {
        if (!open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Cannot open file";
            return;
        }

        bool seekStatus = seek(ilogFile_->currentPos_);

        //while (!file_.atEnd()) {
        //    content_ = file_.readLine();
        //    //process_line(line);
        //}

        QByteArray chunk(readAll());

        close();

        if ( chunk.size() > 0 ) {

            qDebug() << "Chunk size " << chunk.size() 
                << " seekPos : " << ilogFile_->currentPos_
                << " seekStatus : " << seekStatus ;

            ilogFile_->content_.append(chunk);
            ilogFile_->currentPos_ += chunk.size();
        } else {
            continue;
        }

        //qDebug() << "current pos : " << pos() ; 

        quint64 totalSize(0) ;
        int kkk=0;
        foreach( const QByteArray & a, ilogFile_->content_ ){ 
            //qDebug() << "total size" << totalSize << "  " << kkk ;
            totalSize += a.size();
            ++kkk;
        }

        if (totalSize > 1000) {
            emit resultReady("qqqq");
            //break ;
            return ;
        }
    }
}



ILogFile::ILogFile(const QString & filename)
    :currentPos_(0)
    ,reader_(0)
    ,fileName_(filename)
    ,toSplit_(0)
{
    IFinder *finder_ = new IFinder( this );
    finder_->moveToThread(&finderThread_);
    connect(&finderThread_, &QThread::finished, finder_, &QObject::deleteLater);
    connect(this, &ILogFile::signalToFind, finder_, &IFinder::find);
    connect(finder_, &IFinder::resultReady, this, &ILogFile::handleFinderResults);
    finderThread_.start();


    IReader *reader_ = new IReader(filename, this);
    reader_->moveToThread(&readerThread_);
    connect(&readerThread_, &QThread::finished, reader_, &QObject::deleteLater);
    connect(this, &ILogFile::operate, reader_, &IReader::read);
    connect(reader_, &IReader::resultReady, this, &ILogFile::handleResults);
    readerThread_.start();
    read();
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
            qDebug() << "split string  --- " << s ;
        }
    }
    toSplit_ = content_.size() ;


    /*
    quint64 lastLine(stringList_.size()-1);
    if ( stringList_.last().last() != '\n' ) {

    stringList_.last().last()stringList_.size()-1) << s ;
    */
}


quint64 ILogFile::find( const QString & pattern)
{
    logprint(QString("ILogFile::find %1").arg(pattern));
    emit signalToFind(pattern);

    return 0;

    regex_t regex;
    int reti;
    char msgbuf[100];

    /* Compile regular expression */
    reti = regcomp(&regex, "^a[[:alnum:]]", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    /* Execute regular expression */
    reti = regexec(&regex, "abc", 0, NULL, 0);
    if (!reti) {
        puts("Match");
        logprint(QString("ILogFile::find MATCH"));
    }
    else if (reti == REG_NOMATCH) {
        puts("No match");
        logprint(QString("ILogFile::find NO MATCH"));
    }
    else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    /* Free compiled regular expression if you want to use the regex_t again */
    regfree(&regex);

}




IFinder::IFinder( ILogFile* ilogFile )
     :ilogFile_(ilogFile) 
{ 
    assert(ilogFile_);
}

void IFinder::find1( const QString & pattern )
{
    regex_t regex;

    int reti;
    char msgbuf[100];

    /* Compile regular expression */
    //reti = regcomp(&regex, "^a[[:alnum:]]", 0);
    const char * lpattern = pattern.toLatin1().constData();
    reti = regcomp(&regex, lpattern , 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    /* Execute regular expression */
    //reti = regexec(&regex, "abc", 0, NULL, 0);
    const char* pointerToText = ilogFile_->content().first().constData();
    reti = regexec(&regex, pointerToText, 0, NULL, 0);
    if (!reti) {
        puts("Match");
        logprint(QString("IFinder::find1 MATCH"));
    }
    else if (reti == REG_NOMATCH) {
        puts("No match");
        logprint(QString("IFinder::find1 NO MATCH"));
    }
    else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    /* Free compiled regular expression if you want to use the regex_t again */
    regfree(&regex);
}


void IFinder::find( const QString & ppp )
{
    qDebug() << "IFinder::find started" << ppp;
    find1(ppp);
    return;

/*
    forever {
        if (!open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Cannot open file";
            return;
        }

        bool seekStatus = seek(ilogFile_->currentPos_);

        //while (!file_.atEnd()) {
        //    content_ = file_.readLine();
        //    //process_line(line);
        //}

        QByteArray chunk(readAll());

        close();

        if ( chunk.size() > 0 ) {

            qDebug() << "Chunk size " << chunk.size() 
                << " seekPos : " << ilogFile_->currentPos_
                << " seekStatus : " << seekStatus ;

            ilogFile_->content_.append(chunk);
            ilogFile_->currentPos_ += chunk.size();
        } else {
            continue;
        }

        //qDebug() << "current pos : " << pos() ; 

        quint64 totalSize(0) ;
        int kkk=0;
        foreach( const QByteArray & a, ilogFile_->content_ ){ 
            //qDebug() << "total size" << totalSize << "  " << kkk ;
            totalSize += a.size();
            ++kkk;
        }

        if (totalSize > 1000) {
            emit resultReady("qqqq");
            //break ;
            return ;
        }
    }
    */
}

void ILogFile::handleFinderResults(const QString & ppp)
{
    qDebug() << "ILogFile::handleFinderResults started" << ppp;
}

