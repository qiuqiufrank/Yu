#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtWidgets>
#include <QGridLayout>
#include <QFont>
#include <QDebug>
#include "mainwidget.h"
#include <QFontDialog>
#include "QTimer"
#include <QToolBar>



MainWindow::MainWindow()
{

    createMenu();
    creatOperations();
    setMenuBar(menuBar);

    QHBoxLayout *mainLayout=new QHBoxLayout;

    openglWidget =new MainWidget(this);
    QWidget * operateWidget=new QWidget;
    openglWidget->setMinimumSize(600,600);
    mainLayout->setMenuBar(menuBar);
    operateWidget->setLayout(operateLayout);
    QToolBar *toolBar=new QToolBar;
    operateWidget->setMaximumWidth(380);

    toolBar->addWidget(operateWidget);
    addToolBar(Qt::RightToolBarArea,toolBar);

    setCentralWidget(openglWidget);
    setWindowTitle(tr("Yu"));
    setFont(QFont("freesans",13));

    timer=new QTimer(this);
    initTimer=new QTimer(this);
    connect(startButton,SIGNAL(clicked(bool)),this,SLOT(start()));
    connect(pauseButton,SIGNAL(clicked(bool)),this,SLOT(pause()));
    connect(stopButton,SIGNAL(clicked(bool)),this,SLOT(stop()));
    connect(fullScreenButton,SIGNAL(clicked(bool)),this,SLOT(fsgl()));
    initTimer->start(300);
    connect(initTimer,SIGNAL(timeout()),this,SLOT(displayInit()));
    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(sliderChanged(int)));
    connect(fontAction,SIGNAL(triggered(bool)),this,SLOT(setFontStyle()));
    connect(exitAction,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(imagePathAction,SIGNAL(triggered(bool)),this,SLOT(chooseImage()));
    connect(closeColorAction,SIGNAL(triggered(bool)),this,SLOT(closeColor()));

    connect(grabScreenAction,SIGNAL(triggered(bool)),this,SLOT(grabScreen()));
    connect(ball1PathAction,SIGNAL(triggered(bool)),this,SLOT(drawPath1()));
    connect(ball2PathAction,SIGNAL(triggered(bool)),this,SLOT(drawPath2()));
    connect(ballAllPathAction,SIGNAL(triggered(bool)),this,SLOT(drawAllPaths()));
    connect(ballClosePath,SIGNAL(triggered(bool)),this,SLOT(closePath()));

    connect(enAction,SIGNAL(triggered(bool)),this,SLOT(setEN()));
    connect(cnAction,SIGNAL(triggered(bool)),this,SLOT(setCN()));

    connect(aboutQtAction,SIGNAL(triggered(bool)),this,SLOT(displayAboutQt()));
    connect(aboutAuthorAction,SIGNAL(triggered(bool)),this,SLOT(displayAboutAuthor()));



}

void MainWindow::displayAboutQt(){
     QMessageBox::aboutQt(0,"");
}

void MainWindow::displayAboutAuthor(){
    QMessageBox::about(0,tr("author"),tr("if you want to discuss double pendulum with the author, please send an email via 2298096612@qq.com"));
}

void MainWindow::grabScreen(){
    QString fileType;
    QString path=QFileDialog::getSaveFileName(this,tr("save screencut"),QDir::currentPath(),"image *.png ;;image *.jpg",&fileType);
    if(!path.isEmpty()){
        QPixmap image=openglWidget->grab();
        image.save(path,fileType.section('.',1,1).toLatin1().data());
    }

}

void MainWindow::drawPath1(){
    openglWidget->pathIsOn=openglWidget->path1;
    openglWidget->rb1=vb1;
    openglWidget->update();

}

void MainWindow::drawPath2()
{
    openglWidget->pathIsOn=openglWidget->path2;
    openglWidget->rb2=vb2;
    openglWidget->update();

}

void MainWindow::setEN()
{

      QFile file("language");
      if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
          return;

      QTextStream out(&file);
      out << "default:" << "en"<< "\n";
}

void MainWindow::setCN()
{

      QFile file("language");
      if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
          return;

      QTextStream out(&file);
      out << "default:" << "cn"<< "\n";
}

void MainWindow::drawAllPaths()
{
    openglWidget->pathIsOn=openglWidget->pathAll;
    openglWidget->rb1=vb2;
    openglWidget->rb2=vb2;
    openglWidget->update();

}
void MainWindow::closePath(){
    openglWidget->pathIsOn=openglWidget->allOff;
    openglWidget->update();

}

void MainWindow::drawPath()
{



    openglWidget->xyz1Points.clear();
    openglWidget->xyz2Points.clear();
    for(int i=0;i<points.count();i++){
//        qDebug()<<sqrt(pow(initValues[10],2)*(pow(points[i].dth1,2) + pow(points[i].dph1,2)*pow(sin(points[i].th1),2)));
        openglWidget->xyz1Points.append(points[i].x1);
        openglWidget->xyz1Points.append(points[i].y1);
        openglWidget->xyz1Points.append(points[i].z1);
    }
    for(int i=0;i<points.count();i++){
        openglWidget->xyz2Points.append(points[i].x2);
        openglWidget->xyz2Points.append(points[i].y2);
        openglWidget->xyz2Points.append(points[i].z2);
        qDebug()<<sqrt(pow(points[i].dth1*initValues[10]*sin(points[i].th1) + points[i].dth2*initValues[11]*sin(points[i].th2),2) +
    pow(points[i].dth1*initValues[10]*cos(points[i].th1)*sin(points[i].ph1) + points[i].dth2*initValues[11]*cos(points[i].th2)*sin(points[i].ph2) +
      points[i].dph1*initValues[10]*cos(points[i].ph1)*sin(points[i].th1) + points[i].dph2*initValues[11]*cos(points[i].ph2)*sin(points[i].th2),2) +
    pow(points[i].dth1*initValues[10]*cos(points[i].ph1)*cos(points[i].th1) + points[i].dth2*initValues[11]*cos(points[i].ph2)*cos(points[i].th2) -
      points[i].dph1*initValues[10]*sin(points[i].ph1)*sin(points[i].th1) - points[i].dph2*initValues[11]*sin(points[i].ph2)*sin(points[i].th2),2));
    }

}

void MainWindow::closeColor(){
    openglWidget->colorIsOn=!openglWidget->colorIsOn;
    openglWidget->update();

}


void MainWindow::setFontStyle(){
        bool ok=false;
        QFont font=QFontDialog::getFont(&ok);
        this->setFont(font);

}

void MainWindow::chooseImage()
{
   QString path= QFileDialog::getOpenFileName(this,tr("choose scene"),QDir::currentPath(),"images(*.png *.jpg );;any image(*.*)");
   if(!path.isEmpty()){
        openglWidget->imagePath=path;
        openglWidget->initTextures();
        openglWidget->update();
   }

}



void MainWindow::sliderChanged(int n){
    currentIndex=n;
    openglWidget->updateGL(points[currentIndex].x1,points[currentIndex].y1,
                   points[currentIndex].z1,points[currentIndex].x2,
                   points[currentIndex].y2,points[currentIndex].z2);
    displayParameters();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_Space){
        if(currentIndex==0||currentIndex==points.count()){
            start();
        }
        else{
            pause();
        }
    }
    else if(e->key()==Qt::Key_F10){
            QApplication::sendEvent(this->openglWidget,e);
        }


}



void MainWindow::displayInit(){
    readInitParamters();
    double r1=initValues[10];
    double r2=initValues[11];
    double st1=initValues[0];
    double st2=initValues[1];
    double sp1=initValues[2];
    double sp2=initValues[3];


    double x1=sin(st1)*cos(sp1)*r1;
    double y1=-cos(st1)*r1;
    double z1=sin(st1)*sin(sp1)*r1;

    double x2=sin(st2)*cos(sp2)*r2+x1;
    double y2=-cos(st2)*r2+y1;
    double z2=sin(st2)*sin(sp2)*r2+z1;
    openglWidget->setViewCenter({0.0,-(initValues[10]+initValues[11])/2,0.0});
    openglWidget->updateGL(x1,y1,z1,x2,y2,z2);

}


void MainWindow::pause(){
   isPaused=!isPaused;
   if(isPaused){
        disconnect(timer,SIGNAL(timeout()),this,SLOT(renderGL()));
   }
   else{
    connect(timer,SIGNAL(timeout()),this,SLOT(renderGL()));
   }
}

void MainWindow::renderGL(){
    if(currentIndex==points.count()){
        disconnect(timer,SIGNAL(timeout()),this,SLOT(renderGL()));
        return;
       }
    openglWidget->updateGL(points[currentIndex].x1,points[currentIndex].y1,
                   points[currentIndex].z1,points[currentIndex].x2,
                   points[currentIndex].y2,points[currentIndex].z2);
    slider->setValue(currentIndex);
    displayParameters();
    currentIndex++;
}


void MainWindow::stop(){
    disconnect(timer,SIGNAL(timeout()),this,SLOT(renderGL()));
    currentIndex=0;
    openglWidget->updateGL(points[currentIndex].x1,points[currentIndex].y1,
               points[currentIndex].z1,points[currentIndex].x2,
               points[currentIndex].y2,points[currentIndex].z2);

    connect(initTimer,SIGNAL(timeout()),this,SLOT(displayInit()));
    slider->setValue(0);
    isPaused=false;
    drawPath();
}

void MainWindow::start(){
    disconnect(initTimer,SIGNAL(timeout()),this,SLOT(displayInit()));
    readInitParamters();
    makeData();

    slider->setMinimum(0);
    slider->setMaximum(points.count()-1);
    slider->setSingleStep(1.0);

    disconnect(timer,SIGNAL(timeout()),this,SLOT(renderGL()));
    currentIndex=0;

    connect(timer,SIGNAL(timeout()),this,SLOT(renderGL()));
    timer->start(1000.0/rate);
    isPaused=false;

}

void MainWindow::fsgl()
{
   ke=new QKeyEvent(QEvent::KeyPress,Qt::Key_F10,Qt::NoModifier);
    QApplication::sendEvent(this->openglWidget,ke);

}

void MainWindow::readInitParamters(){
    for(int i=0;i<initNumber;i++){
        if(i<8){
            initValues[i]=qDegreesToRadians(initBox[i]->value());
        }
        else{
            initValues[i]=initBox[i]->value();
        }
    }
}

double MainWindow::getPM(double &x,double y){
    double r=fmod(x,y);
    if(r<0.0){
        r+=y;
    }
    return r;

}

void MainWindow::displayParameters(){
        displayBox[0]->setText(QString("%1").arg(qRadiansToDegrees(getPM(points[currentIndex].th1,M_PI)),0,'f',2));
        displayBox[1]->setText(QString("%1").arg(qRadiansToDegrees(getPM(points[currentIndex].th2,M_PI)),0,'f',2));
        displayBox[2]->setText(QString("%1").arg(qRadiansToDegrees(getPM(points[currentIndex].ph1,2*M_PI)),0,'f',2));
        displayBox[3]->setText(QString("%1").arg(qRadiansToDegrees(getPM(points[currentIndex].ph2,2*M_PI)),0,'f',2));
        displayBox[4]->setText(QString("%1").arg(qRadiansToDegrees(getPM(points[currentIndex].dth1,M_PI)),0,'f',2));
        displayBox[5]->setText(QString("%1").arg(qRadiansToDegrees(getPM(points[currentIndex].dth2,M_PI)),0,'f',2));
        displayBox[6]->setText(QString("%1").arg(qRadiansToDegrees(getPM(points[currentIndex].dph1,2*M_PI)),0,'f',2));
        displayBox[7]->setText(QString("%1").arg(qRadiansToDegrees(getPM(points[currentIndex].dph2,2*M_PI)),0,'f',2));
        displayBox[8]->setText(QString("%1").arg(vb1[currentIndex],0,'f',2));
        displayBox[9]->setText(QString("%1").arg(vb2[currentIndex],0,'f',2));
        displayBox[10]->setText(QString("%1").arg(points[currentIndex].t,0,'f',2));

}

void MainWindow::makeData(){
    Dpendulum pend;
    QList<Res> resList=pend.getPoints(
        initValues[0],initValues[1],initValues[2],
        initValues[3],initValues[4],initValues[5],
        initValues[6],initValues[7],initValues[10],
        initValues[11],initValues[8],initValues[9],initValues[13]);
    QVector<Res> resVec=resList.toVector();
    int j=0,num=0;
    double r1=initValues[10],r2=initValues[11];
    double sp1=0,sp2=0,st1=0,st2=0,t=0;
    double dsp1=0,dsp2=0,dst1=0,dst2=0;
    rate=initValues[12];
    points.clear();
    for(int i=0;i<resVec.size();i++){
        st1+=resVec[i].th1;
        st2+=resVec[i].th2;
        sp1+=resVec[i].ph1;
        sp2+=resVec[i].ph2;
        dst1+=resVec[i].dth1;
        dst2+=resVec[i].dth2;
        dsp1+=resVec[i].dph1;
        dsp2+=resVec[i].dph2;
        t+=resVec[i].t;
        num++;
        if((int)(resVec[i].t*rate)>j){
            st1=st1/num;
            st2=st2/num;
            sp1=sp1/num;
            sp2=sp2/num;

            dst1=dst1/num;
            dst2=dst2/num;
            dsp1=dsp1/num;
            dsp2=dsp2/num;
            t=t/num;
            double x1=sin(st1)*cos(sp1)*r1;
            double y1=-cos(st1)*r1;
            double z1=sin(st1)*sin(sp1)*r1;

            double x2=sin(st2)*cos(sp2)*r2+x1;
            double y2=-cos(st2)*r2+y1;
            double z2=sin(st2)*sin(sp2)*r2+z1;

            points.append({t,x1,y1,z1,x2,y2,z2,
                           st1,st2,sp1,sp2,
                          dst1,dst2,dsp1,dsp2});
            j++;
            num=0;
            sp1=0,sp2=0,st1=0,st2=0,dst1=0,dst2=0,dsp1=0,dsp2=0,t=0;
        }
    }

    vb1.clear(),vb2.clear();
    double vxyz1Max=0,vxyz1Min=0;
    double vxyz2Max=0,vxyz2Min=0;
    vxyz1Max=vxyz1Min=sqrt(pow(initValues[10],2)*(pow(points[0].dth1,2) + pow(points[0].dph1,2)*pow(sin(points[0].th1),2)));
    vxyz2Max=vxyz2Min=sqrt(pow(points[0].dth1*initValues[10]*sin(points[0].th1) + points[0].dth2*initValues[11]*sin(points[0].th2),2) +
    pow(points[0].dth1*initValues[10]*cos(points[0].th1)*sin(points[0].ph1) + points[0].dth2*initValues[11]*cos(points[0].th2)*sin(points[0].ph2) +
      points[0].dph1*initValues[10]*cos(points[0].ph1)*sin(points[0].th1) + points[0].dph2*initValues[11]*cos(points[0].ph2)*sin(points[0].th2),2) +
    pow(points[0].dth1*initValues[10]*cos(points[0].ph1)*cos(points[0].th1) + points[0].dth2*initValues[11]*cos(points[0].ph2)*cos(points[0].th2) -
      points[0].dph1*initValues[10]*sin(points[0].ph1)*sin(points[0].th1) - points[0].dph2*initValues[11]*sin(points[0].ph2)*sin(points[0].th2),2));

    for(int i=0;i<points.count();i++){
        float tmp=sqrt(pow(initValues[10],2)*(pow(points[i].dth1,2) + pow(points[i].dph1,2)*pow(sin(points[i].th1),2)));
        vb1.push_back(tmp);
        if(tmp>vxyz1Max){
            vxyz1Max=tmp;
        }
        if(tmp<vxyz1Min){
            vxyz1Min=tmp;
        }
    }
    for(int i=0;i<points.count();i++){
        float tmp=sqrt(pow(points[i].dth1*initValues[10]*sin(points[i].th1) + points[i].dth2*initValues[11]*sin(points[i].th2),2) +
    pow(points[i].dth1*initValues[10]*cos(points[i].th1)*sin(points[i].ph1) + points[i].dth2*initValues[11]*cos(points[i].th2)*sin(points[i].ph2) +
      points[i].dph1*initValues[10]*cos(points[i].ph1)*sin(points[i].th1) + points[i].dph2*initValues[11]*cos(points[i].ph2)*sin(points[i].th2),2) +
    pow(points[i].dth1*initValues[10]*cos(points[i].ph1)*cos(points[i].th1) + points[i].dth2*initValues[11]*cos(points[i].ph2)*cos(points[i].th2) -
      points[i].dph1*initValues[10]*sin(points[i].ph1)*sin(points[i].th1) - points[i].dph2*initValues[11]*sin(points[i].ph2)*sin(points[i].th2),2));
        vb2.push_back(tmp);
        if(tmp>vxyz2Max){
            vxyz2Max=tmp;
        }
        if(tmp<vxyz2Min){
            vxyz2Min=tmp;
        }
    }
    float vb1range=vxyz1Max-vxyz1Min;
    float vb2range=vxyz2Max-vxyz2Min;
    for(int i=0;i<vb1.size();i++){
        vb1[i]=(vb1[i]-vxyz1Min)/vb1range*0.9+0.1;
    }
    for(int i=0;i<vb2.size();i++){
        vb2[i]=(vb2[i]-vxyz2Min)/vb2range*0.9+0.1;
    }

    qDebug()<<vxyz1Max<<vxyz1Min<<"---------"<<vxyz2Max<<vxyz2Min;

}

void MainWindow::createMenu(){
   menuBar =new QMenuBar;
   fileMenu=new QMenu(tr("File"));
   exitAction=new QAction(tr("exit"));
   imagePathAction=new QAction(tr("scene"));
   closeColorAction=new QAction(tr("close color"));
   grabScreenAction=new QAction(tr("export image"));

   fileMenu->addAction(exitAction);
   fileMenu->addAction(grabScreenAction);

   preferenceMenu=new QMenu(tr("Preference"));
   fontAction=new QAction(tr("font"));
   languageAction=new QAction(tr("language"));
   preferenceMenu->addAction(fontAction);
   preferenceMenu->addAction(languageAction);



   langMenu=new QMenu();
   enAction=new QAction("english");
   cnAction=new QAction("中文");
   langMenu->addAction(enAction);
   langMenu->addAction(cnAction);
   languageAction->setMenu(langMenu);


   preferenceMenu->addAction(imagePathAction);
   preferenceMenu->addAction(closeColorAction);

   ballPathMenu=new QMenu(tr("Path"));
   ball1PathAction=new QAction(tr("ball1"));
   ball2PathAction=new QAction(tr("ball2"));
   ballAllPathAction=new QAction(tr("all"));
   ballClosePath=new QAction(tr("close Path"));
   ballPathMenu->addAction(ball1PathAction);
   ballPathMenu->addAction(ball2PathAction);
   ballPathMenu->addAction(ballAllPathAction);
   ballPathMenu->addAction(ballClosePath);

   helpMenu=new QMenu(tr("Help"));
   aboutQtAction =new QAction(tr("about Qt"));
   aboutAuthorAction =new QAction(tr("about Author"));
   helpMenu->addAction(aboutQtAction);
   helpMenu->addAction(aboutAuthorAction);

   menuBar->addMenu(fileMenu);
   menuBar->addMenu(preferenceMenu);
   menuBar->addMenu(ballPathMenu);
   menuBar->addMenu(helpMenu);



}

void MainWindow::creatOperations(){
    this->operateLayout=new QVBoxLayout;

    QGridLayout *initLayout=new QGridLayout;
    QGridLayout *displayLayout=new QGridLayout;
    QHBoxLayout *buttonLayout=new QHBoxLayout;


    initBoxs =new QGroupBox(tr("init"));
    displayBoxs =new QGroupBox(tr("display"));



    QString initNames[initNumber]={tr("θ<sub>1</sub> (D)"),tr("θ<sub>2</sub>(D)"),tr("φ<sub>1</sub>(D)"),
                           tr("φ<sub>2</sub>(D)"),tr("θ'<sub>1</sub>(D/s)"),tr("θ'<sub>2</sub>(D/s)"),//3,4,5
                           tr("φ'<sub>1</sub>(D/s)"),tr("φ'<sub>2</sub>(D/s)"),tr("m<sub>1</sub>(kg)"),
                           tr("m<sub>2</sub>(kg)"),tr("r<sub>1</sub>(m)"),tr("r<sub>2</sub>(m)"),  //9,10,11
                           tr("rate(F/s)"), tr("time(s)")};
    QString displayNames[displayNumber]={tr("θ<sub>1</sub>(D)"),tr("θ<sub>2</sub>(D)"),tr("φ<sub>1</sub>(D)"),
                           tr("φ<sub>2</sub>(D)"),tr("θ'<sub>1</sub>(D/s)"),tr("θ'<sub>2</sub>(D/s)"),
                           tr("φ'<sub>1</sub>(D/s)"),tr("φ'<sub>2</sub>(D/s)"),tr("v<sub>1</sub>(m/s)"),
                                         tr("v<sub>2</sub>(m/s)"),tr("moment(s)")};

    qreal initMaximumValues[initNumber]={180,180,360,
                                         360,3600.00,3600.00,
                                         3600.00,3600.00,10.00,
                                         10.00,5.00,5.00,
                                         100.00,180.00};
    qreal initMinimumValues[initNumber]={0.00,0.00,0.00,
                                         0.00,0.00,0.00,
                                         0.00,0.00,0.10,
                                         0.10,0.50,0.50,
                                         10.00,5.00};
    qreal initDefaultValues[initNumber]={45.00,45.00,45.00,
                                         45.00,0.00,0.00,
                                         0.00,0.00,1.00,
                                         1.00,2.00,2.00,
                                         60.00,10.00};

    int num=0;
    for(int i=0;i<7;i++){
        for(int j=0;j<4;j+=2){
           if(num==initNumber) break;

           initLabel[num]=new QLabel(initNames[num]);
           initBox[num]=new QDoubleSpinBox();

           initBox[num]->setMaximum(initMaximumValues[num]);
           initBox[num]->setMinimum(initMinimumValues[num]);
           initBox[num]->setValue(initDefaultValues[num]);
           initBox[num]->setSingleStep(0.5);

           initLayout->addWidget(initLabel[num],i,j);
           initLayout->addWidget(initBox[num],i,j+1);
           num++;

        }
    }

    num=0;
    for(int i=0;i<6;i++){
        for(int j=0;j<4;j+=2){
           if(num==displayNumber) break;
           displayLabel[num]=new QLabel(displayNames[num]);
           displayBox[num]=new QLineEdit;
           displayLayout->addWidget(displayLabel[num],i,j);
           displayLayout->addWidget(displayBox[num],i,j+1);
           num++;

        }
    }

    startButton=new QPushButton(tr("start"));
    pauseButton=new QPushButton(tr("pause"));
    stopButton=new QPushButton(tr("stop"));
    fullScreenButton=new QPushButton(tr("fullScreen"));

    slider=new QSlider(Qt::Horizontal);

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(pauseButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(fullScreenButton);

    initBoxs->setLayout(initLayout);
    displayBoxs->setLayout(displayLayout);

    operateLayout->addWidget(initBoxs);
    operateLayout->addWidget(displayBoxs);
    operateLayout->addLayout(buttonLayout);
    operateLayout->addWidget(slider);


}
