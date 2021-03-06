#ifndef WIDGETTRIANGLE_H
#define WIDGETTRIANGLE_H
#include <QMainWindow>
#include <QOpenGLWindow>
#include <qopenglwidget.h>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QGLFunctions>
#include <QtOpenGL>
#include "Iluminacion.h"
#include "toroide.h"
#include "cono.h"
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
        int numgeneralInd;

        int x,y;
        lighting *luz = new lighting();
        QOpenGLBuffer vboluz{QOpenGLBuffer::VertexBuffer};
        QOpenGLBuffer vbo1luz{QOpenGLBuffer::VertexBuffer};
        QOpenGLVertexArrayObject vaoluz;
        QOpenGLBuffer vbogeneral{QOpenGLBuffer::VertexBuffer};
        QOpenGLBuffer vbogeneral1{QOpenGLBuffer::VertexBuffer};
        QOpenGLBuffer vbogeneral2{QOpenGLBuffer::VertexBuffer};
        QOpenGLBuffer vbogeneral3{QOpenGLBuffer::VertexBuffer};



    protected:
        virtual void initializeGL() override;
        virtual void resizeGL(int w, int h) override;
        virtual void paintGL() override;
    private:

        QOpenGLVertexArrayObject vaoX,vaoY,vaoZ,vao1, vao2,vaogeneral,vaoSphere,vaoCylinder,vaoCono,vaoCono1;
        QOpenGLBuffer vboX,vboY,vboZ,vbo, _vbo, vboSphere,vboCylinder,vboCono1,vboCono2;
        QOpenGLShaderProgram *m_program;
        QOpenGLShaderProgram *luces;

        void drawAxis();
        void setupVertices();
        void drawSphere(int x, int y);
        void drawCylinder();
        void drawCono();
        void drawgeneral(vector<int> indices,vector<QVector3D> vertices,
                        vector<QVector3D> normal,int numberVer);
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
#endif 
