#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QDir>

QString process_line(QString &line) {
    QStringList dataSet = line.split(";");
    QString azs_id = dataSet.at(0);
    QString fromPath = dataSet.at(1);
    QString toPathFile = dataSet.at(2);
    QStringList onlyPathToList = toPathFile.split('/');
    QString toPath = "";
    QString resultString;
    QString fileName = onlyPathToList.at(onlyPathToList.size() - 1);
    QString newFileName;
    QDir currentDir;

    fileName = fileName.trimmed();

    for ( int i = 0; i < onlyPathToList.size() - 1; i++ ) {
        toPath += onlyPathToList.at(i);
        toPath += "/";
    }

    currentDir = QDir::current();

    toPath = "C:/LEARN_QT/renamer" + toPath;
    if ( currentDir.mkpath(toPath) ) {
        qDebug() << "new Path created OK" << endl;
    }
    newFileName = toPath + fileName;

    if ( QFile::copy(fromPath, newFileName) ) {
        qDebug() << "File copied OK";
        resultString = azs_id + ";" + newFileName;
    } else {
        qDebug() << "File copied ERROR";
    }

    return resultString;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString photoList = QFileDialog::getOpenFileName(0, "Open file", "C:/LEARN_QT/", "Text files (*.txt | *.csv)");
    QFile inFile(photoList);
    QFile fileOut("out.csv");
    if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Unable to open output file";
    } else {
        if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Error opening file";
        } else {
            while (!inFile.atEnd()) {
                QString line = inFile.readLine();
                QString result = process_line(line);
                QTextStream out(&fileOut);
                out << result << endl;
            }
            inFile.close();
        }
    }
    fileOut.close();
    qDebug() << "FINISH!";
    
    return a.exec();
}
