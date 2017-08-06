#ifndef LINE_H
#define LINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>


class Line: protected QOpenGLFunctions
{
public:
    Line();
    virtual ~Line();


    void drawPath(QOpenGLShaderProgram *program, QVector<GLfloat> &XYZPoint, QVector<GLfloat> &rb);
    void drawLines(QOpenGLShaderProgram *program, QVector<GLfloat> point12);
private:
    void initLine();

    QOpenGLBuffer lineArrayBuf;
    QOpenGLBuffer textArrayBuf;
    QOpenGLBuffer xyzLineBuf;
    QOpenGLBuffer xyzPathBuf;
    QOpenGLBuffer rBallBuf;

    int textsize;
    int xyzLinesize;
    int xNameSize,yNameSize,zNameSize;

};


#endif // LINE_H
