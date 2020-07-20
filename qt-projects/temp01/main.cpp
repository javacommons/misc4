#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtNetwork>
#include "strconv2.hpp"

strconv::io io;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    switch (type) {
    case QtDebugMsg:
        io.printf("[Debug] %s\n", msg.toUtf8().constData());
        break;
    case QtInfoMsg:
        io.printf("[Info] %s\n", msg.toUtf8().constData());
        break;
    case QtWarningMsg:
        io.printf("[Warning] %s\n", msg.toUtf8().constData());
        break;
    case QtCriticalMsg:
        io.printf("[Critical] %s\n", msg.toUtf8().constData());
        break;
    case QtFatalMsg:
        io.printf("[Fatal] %s\n", msg.toUtf8().constData());
        abort();
    }
}

class MyApplication : public QApplication {
    Q_OBJECT
public:
    MyApplication(int &argc, char **argv) : QApplication(argc, argv) {
    }
    bool download(QUrl &url, QFile &file) {
        QNetworkRequest req(url);
        QNetworkAccessManager nam;
        QNetworkReply *rep = nam.get(req);
        connect(rep, SIGNAL(downloadProgress(qint64, qint64)),
                this, SLOT(downloadProgress(qint64, qint64)));
        QEventLoop loop;
        while(!rep->isFinished()) {
            loop.processEvents(QEventLoop::ExcludeUserInputEvents);
        }
        file.open(QIODevice::WriteOnly);
        file.write(rep->readAll());
        file.close();
        io.printf("\n");
        return true;
    }
public slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal) {
        //qInfo() << bytesReceived << "/" << bytesTotal;
        io.printf("\r%lld/%lld", bytesReceived, bytesTotal);
    }
};

int main(int argc, char *argv[])
{
   //qInstallMessageHandler(myMessageOutput);
   MyApplication a(argc, argv);

#if 0x1
    QTemporaryFile file(QDir::tempPath()+"/XXXXXX.zip");
#else
    QTemporaryFile file;
#endif
    qDebug() << "file.fileName():" << file.fileName();
    file.open();
    qDebug() << "file.fileName():" << file.fileName();
    file.close();
    qDebug() << "file.fileName():" << file.fileName();
    QFile file2(file.fileName());
    qDebug() << file2.exists();

#if 0x0
    QTemporaryDir dir;
#else
    QTemporaryDir dir("XXXXXX.tmp");
    dir.setAutoRemove(false);
#endif
    qDebug() << "dir.path():" << dir.path();
    QDir dir2(dir.path());
    qDebug() << dir2.exists();
    QString fpath = dir.filePath("msys2-i686-latest.tar.xz");
    qDebug() << fpath;
    QUrl dl_url("http://repo.msys2.org/distrib/msys2-i686-latest.tar.xz");
    QFile dl_file(dir.filePath("msys2-i686-latest.tar.xz"));
    a.download(dl_url, dl_file);
    qInfo() << "finished!";
    system("pause");
    return 0;
}

#include "main.moc"
