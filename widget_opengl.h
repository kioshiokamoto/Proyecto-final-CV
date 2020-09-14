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

class WidgetOpenGL : public QOpenGLWidget
{
    Q_OBJECT

public:
    WidgetOpenGL(QWidget *parent = nullptr  );
    ~WidgetOpenGL();
    bool f1, f2;

    QMatrix4x4 base;
    int xRot;
    int yRot;
    int zRot;
    float valorScala;
    Torus myTorus;

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
private:
    QOpenGLVertexArrayObject vaoX,vaoY,vaoZ,vao1, vao2,vaoTorus;
    QOpenGLBuffer vboX,vboY,vboZ,vbo, _vbo,vboTorus[4];
    QOpenGLShaderProgram *m_program;
    void drawAxis();
    void setupVertices();
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
