#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTimer>
#include <QVector>
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QDialogButtonBox>
#include <QString>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include "mainwidget.h"
#include "dpendulum.h"
#include <QSlider>
#include <QAction>

#include <QMainWindow>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
protected:
    void keyPressEvent(QKeyEvent *e);
private slots:
    void renderGL();
    void pause();
    void stop();
    void start();
    void fsgl();
    void displayParameters();
    void displayInit();
    void sliderChanged(int n);
    void setFontStyle();
    void chooseImage();
    void closeColor();
    void grabScreen();
    void drawPath();
    void drawPath1();
    void drawPath2();
    void drawAllPaths();
    void closePath();
private:
    QKeyEvent *ke;
    MainWidget *openglWidget;
    enum {initNumber=14 ,displayNumber=11};
    QLabel *initLabel[initNumber];
    QDoubleSpinBox *initBox[initNumber];
    QLabel *displayLabel[displayNumber];
    QLineEdit *displayBox[displayNumber];
    QSlider *slider;

    QPushButton *stopButton;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *fullScreenButton;
    qreal initValues[initNumber];

    QAction *fontAction;
    QAction *exitAction;
    QAction *imagePathAction;
    QAction *closeColorAction;
    QAction *grabScreenAction;
    QAction *ball1PathAction;
    QAction *ball2PathAction;
    QAction *ballAllPathAction;
    QAction *ballClosePath;

//    QPushButton *stopButton;
    QVBoxLayout * operateLayout;
    QGroupBox * initBoxs;
    QGroupBox * displayBoxs;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *preferenceMenu;
    QMenu *ballPathMenu;
    QTimer *timer;
    QTimer *initTimer;

    QVector <Points> points;
    QVector <float> vb1;
    QVector <float> vb2;
    void createMenu();
    void creatOperations();
    int currentIndex=0;
    bool isPaused=false;
    bool isStoped=false;
    void makeData();
    double rate;
    void readInitParamters();
    double getPM(double &x, double y);
};

#endif // MAINWINDOW_H
