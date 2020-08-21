#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtNetwork>
#include "strconv2.hpp"

#include "qtcommon.hpp"

class My : public QApplication {
    Q_OBJECT
public:
    My(int &argc, char **argv) : QApplication(argc, argv) {
    }
    bool download(QUrl &url, QFile &file) {
        MyDownloader dl;
        return dl.download(url, file);
    }
public slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal) {
        //qInfo() << bytesReceived << "/" << bytesTotal;
        my_io.printf("\r%lld/%lld", bytesReceived, bytesTotal);
    }
};

int main(int argc, char *argv[])
{
   myInstallMessageHandler();
   My a(argc, argv);

   qDebug() << My::applicationDirPath();

   QString cmd = QString("%1/dark.exe").arg(My::applicationDirPath());

   qDebug() << cmd;

   _wsystem(cmd.toStdWString().c_str());

   system("pause");

   //exit(0);

   /*
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
    */

#if 0x0
    QTemporaryDir dir;
#else
    QTemporaryDir dir("XXXXXX.tmp");
    dir.setAutoRemove(false);
#endif
    qDebug() << "dir.path():" << dir.path();
    QDir dir2(dir.path());
    qDebug() << dir2.exists();
#if 0x0
    QString fpath = dir.filePath("msys2-i686-latest.tar.xz");
    qDebug() << fpath;
    QUrl dl_url("http://repo.msys2.org/distrib/msys2-i686-latest.tar.xz");
    QFile dl_file(dir.filePath("msys2-i686-latest.tar.xz"));
#else
    QUrl dl_url("https://aka.ms/vs/16/release/VC_redist.x86.exe");
    QString fpath = dir.filePath("VC_redist.x86.exe");
    qDebug() << fpath;
    QFile dl_file(fpath);
#endif
    MyDownloader dl;
    a.download(dl_url, dl_file);
    QProcess proc;
    proc.execute(cmd, QStringList() << "-x" << "@out" << fpath);
    qInfo() << "finished!";
    system("pause");
    return 0;
}

/*
Microsoft Visual C++ 2015-2019 Redistributable
https://aka.ms/vs/16/release/VC_redist.x86.exe
https://aka.ms/vs/16/release/VC_redist.x64.exe
 */

#include "main.moc"
