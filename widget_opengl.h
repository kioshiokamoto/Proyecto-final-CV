#ifndef WIDGETTRIANGLE_H
#define WIDGETTRIANGLE_H
#include <QMainWindow>
#include <QOpenGLWindow>
#include <qopenglwidget.h>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QGLFunctions>
#include <QtOpenGL>
#include "toroide.h"
#define PI 3.14159265f
class WidgetOpenGL : public QOpenGLWidget
{
    Q_OBJECT

public:
    WidgetOpenGL(QWidget *parent = nullptr  );
    ~WidgetOpenGL();
    bool f1, f2 ,f3 ,f4 ,f5 ;
    bool smooth, wire;

    QMatrix4x4 base;
    int xRot;
    int yRot;
    int zRot;
    float valorScala;
    toroide t1;

    QVector<GLfloat> m_points;
    QVector<GLfloat> m_points_Cylinder;
    int numTorusVertices;
    int numTorusIndices;

    int x,y;


protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
private:

    QOpenGLVertexArrayObject vaoX,vaoY,vaoZ,vao1, vao2,vaoTorus,vaoSphere,vaoCylinder,vaoCono,vaoCono1;
    QOpenGLBuffer vboX,vboY,vboZ,vbo, _vbo,vboTorus[2], vboSphere,vboCylinder,vboCono1,vboCono2;
    QOpenGLShaderProgram *m_program;

    void drawAxis();
    void setupVertices();
    void drawSphere(int x, int y);
    void drawCylinder();
    void drawCono();
public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setScala(float scala);
signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void ScalaChanged(float scala);
};
#endif // WIDGETTRIANGLE_H
