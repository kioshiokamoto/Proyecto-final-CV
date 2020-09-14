#include "widget_opengl.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glu.h>
#include <stdio.h>
WidgetOpenGL::WidgetOpenGL(QWidget *parent) : QOpenGLWidget {parent}//: QWidget{parent}
{
    f1 = false;
    f2 = false;
    xRot = 0;
    yRot = 0;
    zRot = 0;
    valorScala=1;


}

WidgetOpenGL::~WidgetOpenGL()
{
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}


void WidgetOpenGL::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}
void WidgetOpenGL::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}
void WidgetOpenGL::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}
static void qNormalizeScala(float &scala, float valorScala)
{
    //Solucionar aqui inconvenientes con scala
    /*basicamente el error es pq:
        Si al escala es 1.15 y cambia a 1.20 crecera, si pasa de 1.20 a 1.15 tambien crecera
        Si la escala es 0.9 y cambia a 0.5 disminuira, si pasa de 0.5 a 0.8 tb disminuira
    */

}
void WidgetOpenGL::setScala(float scala)
{
    qNormalizeScala(scala,valorScala);
    if (scala != valorScala) {
        emit ScalaChanged(scala);
        valorScala= scala;
        base.scale(valorScala);
        update();
    }

}



void WidgetOpenGL::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                       "#version 450\n" //GLSL version 1.4
                                       "in vec3 position;\n" //attribute named position with 3 elements per vertex in
                                       "in vec3 color;\n"
                                       "out vec4 fragColor;\n"
                                       "uniform mat4 mv_matrix;\n"
                                       "void main() {\n"
                                       "    fragColor = vec4(color, 1.0);\n"
                                       "    gl_Position = mv_matrix * vec4(position.x*0.05,position.y*0.1,position.z*0.1, 1.0);\n"
                                       "}\n"
                                       );
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                       "#version 450\n" //GLSL version 1.4
                                       "in vec4 fragColor;\n"
                                       "out vec4 finalcolor;\n"
                                       "void main() {\n"
                                       "    finalcolor = fragColor;\n"
                                       "}\n"
                                       );
    //m_program->setUniformValue()
    m_program->link();
    m_program->bind();

    float cubePositions[108] = { -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f,
                -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
                1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f,
                1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f,
                -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,
                1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
                -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
    };

    float pyramidPositions[54] = { -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f,
                1.0f, 0.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, -1.0f,
                -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, -1.0f,
                -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,
                -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f
    };


    //Inicializa la matrix
    base = QTransform();
    //Altera rotaciones iniciales de la figura
    base.rotate(xRot,1.0f,0.0f,0.0f);
    base.rotate(yRot,0.0f,1.0f,0.0f);
    base.rotate(zRot,0.0f,0.0f,1.0f);
    base.scale(valorScala);



    vao1.create();
    vao1.bind();
    vbo.create();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.bind();
    vbo.allocate(cubePositions, sizeof (cubePositions));
    m_program->enableAttributeArray("position");
    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);

    vao1.release();


    vao2.create();
    vao2.bind();
    _vbo.create();
    _vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _vbo.bind();
    _vbo.allocate(pyramidPositions, sizeof (pyramidPositions));

    m_program->enableAttributeArray("position");
    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);



    vao2.release();

    //Para pasar color a shader
    m_program->setAttributeValue("color",QVector3D(0,1,0));
    //Pasar escalamiento y rotacion a shader
    m_program->setUniformValue("mv_matrix",base);

    m_program->release();
}

void WidgetOpenGL::resizeGL(int w, int h)
{
}

void WidgetOpenGL::paintGL()
{
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glClear( GL_COLOR_BUFFER_BIT);
    m_program->bind();
    m_program->setUniformValue("mv_matrix",base);
    if (f1){
        vao1.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    if (f2){
        vao2.bind();
        glDrawArrays(GL_TRIANGLES, 0, 18);
    }
   valorScala=1;
}

