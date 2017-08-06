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

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "ball.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QtMath>
#include "line.h"
#include <QKeyEvent>
#include <QApplication>
#include <QMainWindow>

struct Points{
    double t;
    double x1;
    double y1;
    double z1;
    double x2;
    double y2;
    double z2;
    double th1;
    double th2;
    double ph1;
    double ph2;
    double dth1;
    double dth2;
    double dph1;
    double dph2;

};


class GeometryEngine;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    void setViewCenter(QVector3D viewCenter);
    void updateGL(double x1, double y1, double z1,
                  double x2, double y2, double z2);
    void drawPath(QVector<GLfloat> &xyzPoint);
    QString imagePath=":/360.jpg";
    void initTextures();
    bool colorIsOn=true;
    int pathIsOn=allOff;
    QVector<GLfloat> xyz1Points;
    QVector<GLfloat> xyz2Points;
    enum{allOff,path1,path2,pathAll};

    QVector<GLfloat> rb1;
    QVector<GLfloat> rb2;

protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

    void initShaders();

    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *e);


private:

    QWidget *m_parent;
    QSize m_size;
    Qt::WindowFlags m_flag;
    Qt::WindowStates m_state;

    QBasicTimer timer;
    QOpenGLShaderProgram *program;
    QOpenGLShaderProgram *ballProgram;
    QOpenGLShaderProgram *lineProgram;

    GeometryBall *geometries;
    Line *line;

    QOpenGLTexture *texture;

    QMatrix4x4 projection;
    QMatrix4x4 model;
    QMatrix4x4 view;
    bool rightPress=false;
    bool leftPress=false;
    bool fs=false;

    QPoint mousePressLeftPosition;
    QPoint mousePressRightPosition;
    const qreal viewRatio=M_PI/10000.0;
    QVector3D rotationAxis;
    QVector3D lookAt;
    QVector3D viewPos;
    QVector3D viewCenter;

    qreal aspect;
    qreal farn=50.0;
    qreal nearn=4.0;
    qreal sphereScale=30.0;
    qreal ballScale=0.3;


    QQuaternion rotation;
    QQuaternion viewRotation;
    qreal dist=5.0;
    qreal offset=-0.1;
    GLfloat  x1=0.0,y1=0.0,z1=0.0,x2=0.0,y2=0.0,z2=0.0;
    float ratio=0.3;

};

#endif // MAINWIDGET_H
