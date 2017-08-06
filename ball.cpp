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

#include "ball.h"
#include <QtMath>
#include <QVector>
#include <QtMath>
#include <QVector2D>
#include <QVector3D>

GeometryBall::GeometryBall()
    : quadIndexBuf(QOpenGLBuffer::IndexBuffer)
{

    initializeOpenGLFunctions();
    quadArrayBuf.create();
    quadIndexBuf.create();
    normalBuf.create();


    initCubeBall();
}

GeometryBall::~GeometryBall()
{
    quadArrayBuf.destroy();
    quadIndexBuf.destroy();
    normalBuf.destroy();
}


void GeometryBall::initCubeBall()
{

    QVector <GLfloat> vertexs;
    QVector <GLfloat> normals;

    int theta1N=20,phiN=50,thetaN=30;
    float dphi=2.0*M_PI/phiN;
    float th1=0.3,th2=M_PI-0.6,th3=th1;
    float l1=th1,l2=M_PI-th1;
    float ra=dphi-0.0001;
    float dth1=th1/theta1N,dth2=th2/thetaN,dth3=th3/theta1N;

    for(int i=0;i<theta1N;i++){
       for(int j=0;j<phiN;j++){
           //a dot
          if(j==(phiN-1)){
          vertexs.append((GLfloat)qSin(i*dth1)*qCos(j*dphi+ra));
          vertexs.append(-(GLfloat)qCos(i*dth1));
          vertexs.append((GLfloat)qSin(i*dth1)*qSin(j*dphi+ra));

          }
          else{
          vertexs.append((GLfloat)qSin(i*dth1)*qCos(j*dphi));
          vertexs.append(-(GLfloat)qCos(i*dth1));
          vertexs.append((GLfloat)qSin(i*dth1)*qSin(j*dphi));
          }
       }
    }

    for(int i=0;i<thetaN;i++){
       for(int j=0;j<phiN;j++){
           //a dot
          if(j==(phiN-1)){
          vertexs.append((GLfloat)qSin(i*dth2+l1)*qCos(j*dphi+ra));
          vertexs.append(-(GLfloat)qCos(i*dth2+l1));
          vertexs.append((GLfloat)qSin(i*dth2+l1)*qSin(j*dphi+ra));
          }
          else{
          vertexs.append((GLfloat)qSin(i*dth2+l1)*qCos(j*dphi));
          vertexs.append(-(GLfloat)qCos(i*dth2+l1));
          vertexs.append((GLfloat)qSin(i*dth2+l1)*qSin(j*dphi));
          }

       }
    }

    for(int i=0;i<=theta1N;i++){
       for(int j=0;j<phiN;j++){
           //a dot
          if(j==(phiN-1)){
          vertexs.append((GLfloat)qSin(i*dth3+l2)*qCos(j*dphi+ra));
          vertexs.append(-(GLfloat)qCos(i*dth3+l2));
          vertexs.append((GLfloat)qSin(i*dth3+l2)*qSin(j*dphi+ra));
          }
          else{
          vertexs.append((GLfloat)qSin(i*dth3+l2)*qCos(j*dphi));
          vertexs.append(-(GLfloat)qCos(i*dth3+l2));
          vertexs.append((GLfloat)qSin(i*dth3+l2)*qSin(j*dphi));
          }

       }
    }

    quadArrayBuf.bind();
    quadArrayBuf.allocate(vertexs.constData(),vertexs.count()*sizeof(GLfloat));
    quadArrayBuf.release();

    normalBuf.bind();
    normalBuf.allocate(normals.constData(),normals.count()*sizeof(GLfloat));
    normalBuf.release();
    phiN++;
    QVector <GLuint> indices;
    for(int i=0;i<phiN*(theta1N*2+thetaN-2);i++){
            if(i%phiN==(phiN-2)){
                indices.append(i);
                indices.append(i+phiN);
                indices.append(i+phiN+1);
                indices.append(i+1);
            }
        else if(i%phiN!=(phiN-1) || i!=0){
                indices.append(i);
                indices.append(i+phiN);
                indices.append(i+phiN+1);
                indices.append(i+1);
            }
    }
    count=indices.count();

    quadIndexBuf.bind();
    quadIndexBuf.allocate(indices.constData(),indices.count()*sizeof(GLint));
    quadIndexBuf.release();

}

void GeometryBall::drawBallGeometry(QOpenGLShaderProgram *program)
{

    quadArrayBuf.bind();
    program->enableAttributeArray(0);
    program->setAttributeBuffer(0,GL_FLOAT,0,3,sizeof(GLfloat)*3);
    program->enableAttributeArray(1);
    program->setAttributeBuffer(1,GL_FLOAT,0,3,sizeof(GLfloat)*3);
    quadArrayBuf.release();


    quadIndexBuf.bind();
//    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glDrawElements(GL_QUADS,count,GL_UNSIGNED_INT,0);
    quadIndexBuf.release();



}
