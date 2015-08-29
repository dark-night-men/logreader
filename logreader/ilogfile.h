#ifndef IREADER_H
#define IREADER_H
#include <QtCore>
#include <QtGui>

typedef QList< QByteArray > RawContent;
//typedef QLinkedList< QString > StringList;
typedef QStringList StringList;

class ILogFile;
class IReader : public QFile
{
Q_OBJECT
public:
    IReader(const QString & filename, ILogFile* ilogFile );

public slots:
    void read(const QString &parameter); 

signals:
    void resultReady(const QString &result);

private:
    ILogFile* ilogFile_;
};

class IFinder : public QObject 
{
    Q_OBJECT

public:
    IFinder( ILogFile* ilogFile );

public slots:
    void find(const QString &pattern); 

signals:
    void resultReady(const QString &result);

private:
    void find1(const QString &pattern);

private:
    ILogFile* ilogFile_;
};

class ILogFile : public QObject
{
Q_OBJECT
Q_PROPERTY( RawContent content_ READ content )
Q_PROPERTY( StringList stringList_ READ stringList )

public:
    ILogFile(const QString & filename); 
    ~ILogFile(); 

    const RawContent & content() const { return content_; }
    void read();
    const StringList& stringList() const { return stringList_; }
    void splitArray();


public slots:
    void handleResults(const QString &);
    //search string for regex
    quint64 find( const QString & pattern);
    void handleFinderResults(const QString &);

signals:
    void operate(const QString &);
    void signalToFind(const QString &);


private:
    quint64 currentPos_; 
    IReader * reader_;
    IFinder * finder_;
    QString fileName_;
    RawContent content_;
    StringList stringList_;
    QThread readerThread_;
    QThread finderThread_;
    quint64 toSplit_;

    friend class IReader;
    friend class IFinder;
};

#endif //IREADER_H
