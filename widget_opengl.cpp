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
    myTorus = Torus(0.5f, 0.2f, 48);
    int numTorusVertices = myTorus.getNumVertices();
    int numTorusIndices = myTorus.getNumIndices();;

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

void WidgetOpenGL::setupVertices() {
    std::vector<int> ind = myTorus.getIndices();
    std::vector<QVector3D> vert = myTorus.getVertices();
    std::vector<QVector2D> tex = myTorus.getTexCoords();
    std::vector<QVector3D> norm = myTorus.getNormals();

    std::vector<float> pvalues;
    std::vector<float> tvalues;
    std::vector<float> nvalues;

    for (int i = 0; i < myTorus.getNumVertices(); i++) {
        pvalues.push_back(vert[i].x());
        pvalues.push_back(vert[i].y());
        pvalues.push_back(vert[i].z());
        tvalues.push_back(tex[i].x());
        tvalues.push_back(tex[i].y());
        nvalues.push_back(norm[i].x());
        nvalues.push_back(norm[i].y());
        nvalues.push_back(norm[i].z());
    }
    vaoTorus.create();
    vaoTorus.bind();
    vboTorus->create();
    vboTorus[0].setUsagePattern(QOpenGLBuffer::StaticDraw); //Modificar
    vboTorus[0].bind();
    vboTorus[0].allocate(pvalues.data(),sizeof(pvalues));
    vboTorus[1].setUsagePattern(QOpenGLBuffer::StaticDraw); //Modificar
    vboTorus[1].bind();
    vboTorus[1].allocate(tvalues.data(),sizeof(tvalues));
    vboTorus[2].setUsagePattern(QOpenGLBuffer::StaticDraw); //Modificar
    vboTorus[2].bind();
    vboTorus[2].allocate(nvalues.data(),sizeof(nvalues));
    vboTorus[3].setUsagePattern(QOpenGLBuffer::StaticDraw); //Modificar
    vboTorus[3].bind();
    vboTorus[3].allocate(ind.data(),sizeof(ind));






/*

    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 pvalues.size() * 4,
                 &pvalues[0],
            GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 tvalues.size() * 4,
                 &tvalues[0],
            GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER,
                 nvalues.size() * 4,
                 &nvalues[0],
            GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 ind.size() * 4,
                 &ind[0],
            GL_STATIC_DRAW);*/
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
                                       "    gl_Position = mv_matrix * vec4(position.x*0.2,position.y*0.2,position.z*0.2, 1.0);\n"
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

    float ejeX[]= {
        0.0,0.0,0.0,
        5.0,0.0,0.0
    };
    vaoX.create();
    vaoX.bind();
    vboX.create();
    vboX.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboX.bind();
    vboX.allocate(ejeX,sizeof (ejeX));
    m_program->enableAttributeArray("position");
    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);
    vaoX.release();

    float ejeY[]= {
        0.0,0.0,0.0,
        0.0,5.0,0.0
    };
    vaoY.create();
    vaoY.bind();
    vboY.create();
    vboY.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboY.bind();
    vboY.allocate(ejeY,sizeof (ejeY));
    m_program->enableAttributeArray("position");
    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);
    vaoY.release();

    float ejeZ[]= {
        0.0,0.0,0.0,
        0.0,0.0,5.0
    };
    vaoZ.create();
    vaoZ.bind();
    vboZ.create();
    vboZ.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboZ.bind();
    vboZ.allocate(ejeZ,sizeof (ejeZ));
    m_program->enableAttributeArray("position");
    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);
    vaoZ.release();







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
void WidgetOpenGL::drawAxis(){
    vaoX.bind();
    m_program->setAttributeValue("color",QVector3D(1,0,0));
    glDrawArrays(GL_LINE_LOOP, 0, 2);

    vaoY.bind();
    m_program->setAttributeValue("color",QVector3D(0,1,0));
    glDrawArrays(GL_LINE_LOOP, 0, 2);

    vaoZ.bind();
    m_program->setAttributeValue("color",QVector3D(0,0,1));
    glDrawArrays(GL_LINE_LOOP, 0, 2);
}

void WidgetOpenGL::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear( GL_COLOR_BUFFER_BIT);
    m_program->bind();
    m_program->setUniformValue("mv_matrix",base);
    if (f1){
        drawAxis();
        vao1.bind();
        m_program->setAttributeValue("color",QVector3D(0,1,0));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    if (f2){
        drawAxis();
        vao2.bind();
        glDrawArrays(GL_TRIANGLES, 0, 18);
    }
   valorScala=1;
   /*
   glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
   glEnableVertexAttribArray(0);

   glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
   glEnableVertexAttribArray(1);

   glEnable(GL_CULL_FACE);
   glFrontFace(GL_CCW);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
   glDrawElements(GL_TRIANGLES, numTorusIndices, GL_UNSIGNED_INT, 0);*/
}

