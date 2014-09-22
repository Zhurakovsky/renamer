//#include "widget.h"
#include <QApplication>
#include <QFileDialog>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Widget w;
    //w.show();
    QString fromDir = QFileDialog::getExistingDirectory(0, "Open dir",
                                                        "C:/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //qDebug() << fromDir << " working directory" << endl;
    QDir dir(fromDir);
    QFileInfoList list = dir.entryInfoList();
    QFile file("out.txt");
    if ( !file.open(QIODevice::WriteOnly | QIODevice::Text) )
        return 0;

    QTextStream out(&file);

    for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);
            out << qPrintable(QString("%1").arg(fileInfo.absoluteFilePath())) << endl;
        }

    QString cp = QDir::currentPath();
    qDebug() << cp << " my current" << endl;
    QString newPath  = cp + "/1/2/3";
    qDebug() << newPath << " my new" << endl;
    QDir rootPath = QDir::rootPath();
    if ( rootPath.mkpath(newPath) ) {
        qDebug() << "new Path created OK" << endl;
    } else {
        qDebug() << "new Path wrong" << endl;
    }
    file.close();
    return a.exec();
}
