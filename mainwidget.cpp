/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QDebug>
#include "mainwidget.h"
#include "dpendulum.h"

#include <QMouseEvent>


#include <math.h>

QList<Points>::iterator itor;

MainWidget::MainWidget(QWidget *parent) :
        QOpenGLWidget(parent)
{
    view.setToIdentity();
    lookAt=QVector3D(0.0,.0,-dist);
    m_parent=parent;
    setFocusPolicy(Qt::TabFocus);

}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete geometries;
    delete line;
    doneCurrent();
}

void MainWidget::updateGL(double x1, double y1, double z1, double x2, double y2, double z2){
    this->x1=x1;
    this->y1=y1;
    this->z1=z1;
    this->x2=x2;
    this->y2=y2;
    this->z2=z2;
    update();

}



void MainWidget::setViewCenter(QVector3D viewCenter)
{
    this->viewCenter=viewCenter;

}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton){
        leftPress=true;
        mousePressLeftPosition=cursor().pos();
    }
    else if(e->button()==Qt::RightButton){
        rightPress=true;
        mousePressRightPosition=cursor().pos();
    }
}



void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    if(e->button()==Qt::LeftButton){
        leftPress=false;
    }
    else if(e->button()==Qt::RightButton){
        rightPress=false;
    }

}
//! [0]
double c=0;
//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    update();
    if(leftPress){
        QPoint currentPos=cursor().pos();
        QVector2D diff = QVector2D(currentPos-mousePressLeftPosition);
        mousePressLeftPosition=currentPos;
        QVector3D rotationAxis = QVector3D(diff.y(),diff.x(), 0.0).normalized();
        qreal acc = diff.length() / 10.0;
        rotation=QQuaternion::fromAxisAndAngle(rotationAxis,acc);
        viewPos=viewCenter +rotation*(viewPos-viewCenter);
        dist=(viewPos-viewCenter).length();
    }
    else if(rightPress){
        QPoint currentPos=cursor().pos();
        QVector2D diff = QVector2D(currentPos-mousePressRightPosition);
        mousePressRightPosition=currentPos;
        QVector3D rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
        qreal acc = diff.length() / 10.0;
        viewRotation=QQuaternion::fromAxisAndAngle(rotationAxis,acc);
        viewCenter=viewPos +viewRotation*(viewCenter-viewPos);
        dist=(viewPos-viewCenter).length();
    }
}
//! [1]


//! [3]
void MainWidget::initShaders()
{
    program=new QOpenGLShaderProgram(context());
    ballProgram=new QOpenGLShaderProgram(context());
    lineProgram=new QOpenGLShaderProgram(context());

    if (!program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();
    if (!program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();
    if (!program->link())
        close();
    if (!program->bind())
        close();
    program->release();


    if (!ballProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/ballVshader.glsl"))
        close();
    if (!ballProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/ballFshader.glsl"))
        close();
    if (!ballProgram->link())
        close();
    if (!ballProgram->bind())
        close();
    ballProgram->release();

    if (!lineProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/lineVshader.glsl"))
        close();
    if (!lineProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/lineFshader.glsl"))
        close();
    if (!lineProgram->link())
        close();
    if (!lineProgram->bind())
        close();
    lineProgram->release();
}
//! [3]

void MainWidget::wheelEvent(QWheelEvent *event){
    if(event->angleDelta().y()>0.0){
        viewPos-=0.05*(viewPos-viewCenter);
        dist=(viewCenter-viewPos).length();
    }
    else{
        QVector3D oldViewPos=viewPos;
        viewPos+=0.05*(viewPos-viewCenter);
        dist=(viewCenter-viewPos).length();
        if(dist>sphereScale*0.5){
            viewPos=oldViewPos;
            dist=(viewCenter-viewPos).length();
        }
    }
}

void MainWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_F10){
        fs=!fs;
        if(fs){

            m_flag=this->windowFlags();
            m_size=this->size();
            m_state=this->windowState();
            this->setParent(0);
            setWindowFlags(Qt::Window);
            showFullScreen();
        }
        else{
            this->setParent(m_parent);
            ((QMainWindow *)m_parent)->setCentralWidget(this);
            //            this->overrideWindowFlags(m_flag);
            //            this->overrideWindowState(m_state);
            //            this->show();
            showNormal();
        }
    }
    else if(e->key()==Qt::Key_Space){
        QApplication::sendEvent(m_parent,e);
    }
}

//! [4]
void MainWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(imagePath).mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Linear);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::DirectionS,QOpenGLTexture::Repeat);
    texture->setWrapMode(QOpenGLTexture::DirectionT,QOpenGLTexture::Repeat);
}

void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(45.0, aspect, dist-nearn, dist+farn);






}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);
    initShaders();
    initTextures();

    //! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    geometries = new GeometryBall;
    line =new Line;

    viewPos={0.0,offset*sphereScale,dist};
    viewCenter={0.0,0.0,0.0};
    view.lookAt(viewPos,viewCenter,QVector3D(0.0,1.0,0.0));
    timer.start(30,this);


}

void MainWidget::paintGL()
{
    // Clear color and depth buffer


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //balls

    glCullFace(GL_BACK);
    ballProgram->bind();
    texture->bind();
    model.setToIdentity();
    model.translate( x1, y1, z1);
    model.scale(ballScale);
    view.setToIdentity();
    view.lookAt(viewPos,viewCenter,QVector3D(0.0,1.0,0.0));
    projection.setToIdentity();
    projection.perspective(45.0, aspect, dist-nearn, dist+farn);
    ballProgram->setUniformValue("projMatrix", projection);
    ballProgram->setUniformValue("mvMatrix", view* model);
    model.scale(1.0/ballScale);
    ballProgram->setUniformValue("normalMatrix", model.normalMatrix());
    ballProgram->setUniformValue("texture",0);
    geometries->drawBallGeometry(ballProgram);

    model.setToIdentity();
    model.translate( x2, y2, z2);
    model.scale(ballScale);
    ballProgram->setUniformValue("mvMatrix", view* model);
    model.scale(1.0/ballScale);
    geometries->drawBallGeometry(ballProgram);
    ballProgram->release();
    texture->release();
    //lines


    lineProgram->bind();
    model.setToIdentity();
    model.translate(.0, 0.0, 0.0);
    lineProgram->setUniformValue("MVP", projection*view* model);
    lineProgram->setUniformValue("colorIsOn",colorIsOn);
    lineProgram->setUniformValue("isCoordinates",true);
    QVector <GLfloat>linePoints;
    linePoints.append({0.0,0.0,0.0});
    linePoints.append( {x1,y1,z1});
    linePoints.append( {x2,y2,z2});
    line->drawLines(lineProgram,linePoints);
    lineProgram->release();
    //line path

//    for(int i=0;i<xyz1Points.count()/3;i++){
//        rb.push_back(0.3);
//    }

    switch (pathIsOn) {
    case allOff:
        break;
    case path1:
        lineProgram->bind();
        model.setToIdentity();
        lineProgram->setUniformValue("MVP", projection*view* model);
        lineProgram->setUniformValue("colorIsOn",colorIsOn);
        lineProgram->setUniformValue("isCoordinates",false);
        line->drawPath(lineProgram,xyz1Points,rb1);
        lineProgram->release();
        break;
    case path2:
        lineProgram->bind();
        model.setToIdentity();
        lineProgram->setUniformValue("MVP", projection*view* model);
        lineProgram->setUniformValue("colorIsOn",colorIsOn);
        lineProgram->setUniformValue("isCoordinates",false);
        line->drawPath(lineProgram,xyz2Points,rb2);
        lineProgram->release();
        break;
    case pathAll:
        lineProgram->bind();
        model.setToIdentity();
        lineProgram->setUniformValue("MVP", projection*view* model);
        lineProgram->setUniformValue("colorIsOn",colorIsOn);
        lineProgram->setUniformValue("isCoordinates",false);
        line->drawPath(lineProgram,xyz1Points,rb1);
        line->drawPath(lineProgram,xyz2Points,rb2);
        lineProgram->release();
        break;


    default:
        break;
    }







    //scene
    program->bind();
    glCullFace(GL_FRONT);
    texture->bind();
    model.setToIdentity();
    model.translate(0.0,offset*sphereScale, 0.0);
    model.scale(sphereScale);
    program->setUniformValue("projMatrix", projection);
    program->setUniformValue("mvMatrix", view* model);
    model.scale(1.0/sphereScale);
    program->setUniformValue("normalMatrix", model.normalMatrix());
    program->setUniformValue("texture",0);
    //    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    geometries->drawBallGeometry(program);
    program->release();
    texture->release();

}
