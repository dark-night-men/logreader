#ifndef READER_H
#define READER_H
#include <QtCore>
#include <QtGui>

class LogFile : public QFile
{
Q_OBJECT
Q_PROPERTY( QByteArray content_ READ content )
Q_PROPERTY( QStringList stringList_ READ stringList )

public:
    LogFile(const QString & filename)
        :QFile(filename)
    {
    }

    const QByteArray & content() const { return content_; }
    void read();
    const QStringList & stringList() const { return stringList_; }
    void splitArray();

private:
    QString fileName_;
    QFile file_;
    QByteArray content_;
    QStringList stringList_;
};
#endif //READER_H
