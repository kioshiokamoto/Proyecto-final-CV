#ifndef TORUS_H
#define TORUS_H

#include <QMainWindow>
#include <QOpenGLWindow>
#include <qopenglwidget.h>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QGLFunctions>
#include <QtOpenGL>

class Torus
{
public:
	Torus();
    int getXSegments() const;
    void setXSegments(int value);

    int getYSegments() const;
    void setYSegments(int value);
    QVector<GLfloat> vertex;
    QVector<GLfloat> index;
    void setupVertices(int sx,int sy) ;

private:

    int xSegments;
    int ySegments;
};

#endif
