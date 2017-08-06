#include "line.h"


#include <QPolygonF>
#include <QtMath>
#include <QVector>
#include <QtMath>
#include <QVector2D>
#include <QVector3D>
#include <QPainterPath>
#include <QFont>

Line::Line()
{

    initializeOpenGLFunctions();
    lineArrayBuf.create();
    textArrayBuf.create();
    xyzLineBuf.create();
    xyzPathBuf.create();
    rBallBuf.create();
    initLine();
}

Line::~Line()
{
    lineArrayBuf.destroy();
    textArrayBuf.destroy();
    xyzPathBuf.release();
    rBallBuf.release();
}

void Line::drawPath(QOpenGLShaderProgram *program, QVector<GLfloat> &XYZPoint,QVector<GLfloat> &rb){

    xyzPathBuf.bind();
    xyzPathBuf.allocate(XYZPoint.constData(),sizeof(GLfloat)*XYZPoint.count());
    program->enableAttributeArray(0);
    program->setAttributeArray(0,GL_FLOAT,0,3,sizeof(GLfloat)*3);
    xyzPathBuf.release();

    rBallBuf.bind();
    rBallBuf.allocate(rb.constData(),sizeof(GLfloat)*rb.count());
    program->enableAttributeArray(1);
    program->setAttributeArray(1,GL_FLOAT,0,1,sizeof(GLfloat));
    rBallBuf.release();

    glDrawArrays(GL_LINE_STRIP,0,XYZPoint.count()/3);
}



void Line::initLine()
{
    GLfloat length=2.0;

    QVector <GLfloat> xyzLine;
    //x
    xyzLine.append({-length,0.0,0.0});
    xyzLine.append({length,0.0,0.0});
    xyzLine.append({length,0.05,0.0});
    xyzLine.append({length*1.05,0.0,0.0});
    xyzLine.append({length,-0.05,0.0});
    xyzLine.append({length,0.0,0.0});


    xyzLine.append({0.0,length,0.0});
    xyzLine.append({0.0,-length,0.0});
    xyzLine.append({0.0,-length,0.05});
    xyzLine.append({0.0,-length*1.05,0.0});
    xyzLine.append({0.0,-length,-0.05});
    xyzLine.append({0.0,-length,0.0});


    xyzLine.append({0.0,0.0,-length});
    xyzLine.append({0.0,0.0,length});
    xyzLine.append({0.05,0.0,length});
    xyzLine.append({0.0,0.0,length*1.05});
    xyzLine.append({-0.05,0.0,length});
    xyzLine.append({0.0,0.0,length});

    xyzLinesize=xyzLine.size();

    xyzLineBuf.bind();
    xyzLineBuf.allocate(xyzLine.constData(),xyzLine.size()*sizeof(GLfloat));
    xyzLineBuf.release();




    QPainterPath xpath;
    xpath.addText(0,0,QFont("Times",20),"x");
    QPolygonF poly=xpath.toFillPolygon();
    QPolygonF::iterator itor=poly.begin();
    QVector <GLfloat> textPoints;
    xNameSize=0;
    for(;itor<poly.end();itor++){
        GLfloat x=(*itor).x()/60.0+length*0.5;
        GLfloat y=-(*itor).y()/60.0;
        textPoints.append({x,y,0.0});
        xNameSize+=1;
    }


    yNameSize=0;
    QPainterPath ypath;
    ypath.addText(0,0,QFont("Times",20),"y");
    poly=ypath.toFillPolygon();
    itor=poly.begin();
    for(;itor<poly.end();itor++){
        GLfloat x=(*itor).x()/60.0;
        GLfloat y=-(*itor).y()/60.0-length*0.5;
        textPoints.append({x,y,0.0});
        yNameSize+=1;
    }

    zNameSize=0;
    QPainterPath zpath;
    zpath.addText(0,0,QFont("Times",20),"z");
    poly=zpath.toFillPolygon();
    itor=poly.begin();
    for(;itor<poly.end();itor++){
        GLfloat x=(*itor).x()/60.0;
        GLfloat y=-(*itor).y()/60.0;
        textPoints.append({x,y,length*0.5});
        zNameSize+=1;
    }

    textsize=textPoints.size();
    textArrayBuf.bind();
    textArrayBuf.allocate(textPoints.constData(),sizeof(GLfloat)*textPoints.size());
    textArrayBuf.release();
}


void Line::drawLines(QOpenGLShaderProgram *program,
                     QVector <GLfloat> points)
{
    lineArrayBuf.bind();
    lineArrayBuf.allocate(points.constData(),sizeof(GLfloat)*points.size());
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0,GL_FLOAT,0,3,sizeof(GLfloat)*3);
    glLineWidth(5);
    glDrawArrays(GL_LINE_STRIP,0,3);
    lineArrayBuf.release();


    textArrayBuf.bind();
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0,GL_FLOAT,0,3,sizeof(GLfloat)*3);
    glDrawArrays(GL_LINE_STRIP,0,xNameSize);
    glDrawArrays(GL_LINE_STRIP,xNameSize,yNameSize);
    glDrawArrays(GL_LINE_STRIP,xNameSize+yNameSize,zNameSize);
    textArrayBuf.release();

    xyzLineBuf.bind();
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0,GL_FLOAT,0,3,sizeof(GLfloat)*3);
    glDrawArrays(GL_LINE_STRIP,0,xyzLinesize/9);
    glDrawArrays(GL_LINE_STRIP,6,xyzLinesize/9);
    glDrawArrays(GL_LINE_STRIP,12,xyzLinesize/9);
    xyzLineBuf.release();


}
