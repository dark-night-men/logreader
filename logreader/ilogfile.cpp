#include "../debugprint/debugprint.h"
#include "ilogfile.h"
#include <QDebug>
#include <assert.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

/* The following is the size of a buffer to contain any error messages
   encountered when the regular expression is compiled. */

#define MAX_ERROR_MSG 0x1000

/* Compile the regular expression described by "regex_text" into
   "r". */

static int compile_regex (regex_t * r, const char * regex_text)
{
    int status = regcomp (r, regex_text, REG_EXTENDED|REG_NEWLINE);
    if (status != 0) {
	char error_message[MAX_ERROR_MSG];
	regerror (status, r, error_message, MAX_ERROR_MSG);
        printf ("Regex error compiling '%s': %s\n",
                 regex_text, error_message);
        return 1;
    }
    return 0;
}

/*
  Match the string in "to_match" against the compiled regular
  expression in "r".
 */

static int match_regex (regex_t * r, const char * to_match)
{

    logprint("match_regex started");
    /* "P" is a pointer into the string which points to the end of the
       previous match. */
    const char * p = to_match;
    /* "N_matches" is the maximum number of matches allowed. */
    const int n_matches = 10;
    /* "M" contains the matches found. */
    regmatch_t m[n_matches];

    while (1) {
        int i = 0;
        int nomatch = regexec (r, p, n_matches, m, 0);
        if (nomatch) {
            //printf ("match_regex No more matches.\n");
            logprint ("match_regex No more matches.\n");
            return nomatch;
        }
        for (i = 0; i < n_matches; i++) {
            int start;
            int finish;
            if (m[i].rm_so == -1) {
                break;
            }
            start = m[i].rm_so + (p - to_match);
            finish = m[i].rm_eo + (p - to_match);

            /*
            if (i == 0) {
                printf ("$& is ");
            }
            else {
                printf ("$%d is ", i);
            }
            printf ("'%.*s' (bytes %d:%d)\n", (finish - start),
                    to_match + start, start, finish);
                    */
            QString prefix = "match_regex " ;
            if (i == 0) {
                prefix += " is ";
            }
            else {
                prefix += QString("%1 is ").arg ( i);
            }

            int length = finish - start;

            char* otherString = 0;

            otherString = (char*)malloc(length+1);
            memcpy(otherString,to_match + start,length);
            otherString[length] = 0;

            logprint(prefix + QString(">%1< (bytes %2:%3)\n").arg(otherString).arg(start).arg(finish));
            free(otherString);

        }
        p += m[0].rm_eo;
    }
    logprint("match_regex exit");
    return 0;
}

/*
int main(int argc, char ** argv)
{
    regex_t r;
    const char * regex_text;
    const char * find_text;
    if (argc != 3) {
        regex_text = "([[:digit:]]+)[^[:digit:]]+([[:digit:]]+)";
        find_text = "This 1 is nice 2 so 33 for 4254";
    }
    else {
        regex_text = argv[1];
        find_text = argv[2];
    }
    printf ("Trying to find '%s' in '%s'\n", regex_text, find_text);
    compile_regex(& r, regex_text);
    match_regex(& r, find_text);
    regfree (& r);
    return 0;
}
*/




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
    //reti = regcomp(&regex, lpattern , 0);
    reti = compile_regex(& regex, lpattern);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }




    /* Execute regular expression */
    //reti = regexec(&regex, "abc", 0, NULL, 0);
    const char* pointerToText = ilogFile_->content().first().constData();

    match_regex(& regex, pointerToText );

    /*
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
    */

    /* Free compiled regular expression if you want to use the regex_t again */
    regfree(&regex);

    emit resultReady(QString("IFinder::find1 result %1").arg(pattern));
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

