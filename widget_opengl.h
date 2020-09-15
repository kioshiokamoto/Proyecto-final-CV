#ifndef WIDGETTRIANGLE_H
#define WIDGETTRIANGLE_H
#include <QMainWindow>
#include <QOpenGLWindow>
#include <qopenglwidget.h>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QGLFunctions>
#include <QtOpenGL>
#include "Torus.h"
#define PI 3.14159265f
class WidgetOpenGL : public QOpenGLWidget
{
    Q_OBJECT

public:
    WidgetOpenGL(QWidget *parent = nullptr  );
    ~WidgetOpenGL();
    bool f1, f2 ,f3 ,f4 ,f5 ;

    QMatrix4x4 base;
    int xRot;
    int yRot;
    int zRot;
    float valorScala;
    Torus myTorus;
    QVector<GLfloat> m_points;

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
private:

    QOpenGLVertexArrayObject vaoX,vaoY,vaoZ,vao1, vao2,vaoTorus,vaoSphere;
    QOpenGLBuffer vboX,vboY,vboZ,vbo, _vbo,vboTorus[4], vboSphere;
    QOpenGLShaderProgram *m_program;
    void drawAxis();
    void setupVertices();
    void drawSphere();
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
