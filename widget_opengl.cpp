#include "widget_opengl.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glu.h>
#include <stdio.h>




WidgetOpenGL::WidgetOpenGL(QWidget *parent) : QOpenGLWidget {parent}//: QWidget{parent}
{
    f1 = false;
    f2 = false;
    f3 = false;
    f4 = false;
    f5 = false;
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
void qNormalizeScala(float scala, float *valorScala)
{

    *valorScala = scala;

}
void WidgetOpenGL::setScala(float scala)
{
    float aux = 1.0/scala;
    if (scala != valorScala) {
        float aux = 1.0/valorScala;
        base.scale(aux,aux,aux);
        valorScala= scala;
        emit ScalaChanged(scala);
        base.scale(valorScala,valorScala,valorScala);
        update();

    }
    qNormalizeScala(scala,&valorScala);


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



}

void WidgetOpenGL::drawSphere(){

    float r=1.0;
    int angleSpan = 10;
    for(int vAngle = -90; vAngle < 90; vAngle = vAngle + angleSpan){
        for(int hAngle = 0; hAngle <= 360; hAngle = hAngle + angleSpan){
            float x0 = r * qCos(vAngle * PI / 180) * qCos(hAngle * PI / 180);
            float y0 = r * qCos(vAngle * PI / 180) * qSin(hAngle * PI / 180);
            float z0 = r * qSin(vAngle * PI / 180);

            float x1 = r * qCos(vAngle * PI / 180) * qCos((hAngle + angleSpan) * PI / 180);
            float y1 = r * qCos(vAngle * PI / 180) * qSin((hAngle + angleSpan) * PI / 180);
            float z1 = r * qSin(vAngle * PI / 180);

            float x2 = r * qCos((vAngle + angleSpan) * PI / 180) * qCos((hAngle + angleSpan) * PI / 180);
            float y2 = r * qCos((vAngle + angleSpan) * PI / 180) * qSin((hAngle + angleSpan) * PI / 180);
            float z2 = r * qSin((vAngle + angleSpan) * PI / 180);

            float x3 = r * qCos((vAngle + angleSpan) * PI / 180) * qCos(hAngle * PI / 180);
            float y3 = r * qCos((vAngle + angleSpan) * PI / 180) * qSin(hAngle * PI / 180);
            float z3 = r * qSin((vAngle + angleSpan) * PI / 180);

            m_points << x1 << y1 << z1 << x3 << y3 << z3
                   << x0 << y0 << z0 << x1 << y1 << z1
                   << x2 << y2 << z2 << x3 << y3 << z3;
        }
    }
    vaoSphere.create();
    vaoSphere.bind();
    vboSphere.create();
    vboSphere.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboSphere.bind();
    vboSphere.allocate(m_points.constData(),m_points.size() * sizeof (GLfloat));
    m_program->enableAttributeArray("position");
    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);
    vaoSphere.release();


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
    drawSphere();
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
    drawAxis();
    if (f1){
        vao1.bind();
        m_program->setAttributeValue("color",QVector3D(0,1,0));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    if (f2){
        vaoSphere.bind();
        m_program->setAttributeValue("color",QVector3D(1,0,0));
        glDrawArrays(GL_TRIANGLES,0,m_points.count()/3);

    }
    if(f3){
        vao2.bind();
        glDrawArrays(GL_TRIANGLES, 0, 18);
    }
    if(f4){

    }
    if(f5){

    }
   //valorScala=1;

}

