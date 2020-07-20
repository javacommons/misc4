#include <QtCore>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

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

    QTemporaryDir dir;
    qDebug() << "dir.path():" << dir.path();
    QDir dir2(dir.path());
    qDebug() << dir2.exists();
    QString fpath = dir.filePath("latest.tar.xz");
    qDebug() << fpath;

    return 0;
}
