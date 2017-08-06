#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
//    translator.load(":/dp_cn.qm");


      QFile file("language");
      if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
          return 0;

      QTextStream in(&file);
      QString line;
      while (!in.atEnd()) {
          line = in.readLine();
      }
      if(line=="default:en"){
          translator.load("/home/qiu/Documents/c++/dp/dp_en.qm");
          a.installTranslator(&translator);
      }
      else if(line=="default:cn"){
          translator.load("/home/qiu/Documents/c++/dp/dp_cn.qm");
          a.installTranslator(&translator);
      }




    MainWindow w;
    w.show();

    return a.exec();
}
