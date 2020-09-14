#ifndef WIDGETTRIANGLE_H
#define WIDGETTRIANGLE_H
#include <QMainWindow>
#include <QOpenGLWindow>
#include <qopenglwidget.h>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QGLFunctions>
#include <QtOpenGL>

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
    QPoint lastPos;

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    QOpenGLVertexArrayObject vao1, vao2;
    QOpenGLBuffer vbo, _vbo;
    QOpenGLShaderProgram *m_program;
public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
};
#endif // WIDGETTRIANGLE_H
