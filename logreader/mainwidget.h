#include <QtGui>
#include <QtWidgets>

class MyModel;
class ILogFile;
class MyView;
class MainWidget : public QWidget
{
Q_OBJECT
public:
    MainWidget(QWidget * parent=0);

public slots:
    void findButtonSlot();

private:
    MyModel *tableModel_;
    ILogFile *logFile_;
    MyView *tableView_;
    QLineEdit *findField_;
};
