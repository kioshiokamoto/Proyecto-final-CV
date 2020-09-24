#include "widget_opengl.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glu.h>
#include <stdio.h>
#include "toroide.h"
#include "cilindro.h"
QMatrix4x4 pMat, vMat, mMat, mvMat, invTrMat, rMat;
float i=0;
int angleOld = 0;

WidgetOpenGL::WidgetOpenGL(QWidget *parent) : QOpenGLWidget {parent}
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
    x = 5;
    y = 5;

    smooth = false;
    wire = false;

    t1 = toroide(5,5);
}

WidgetOpenGL::~WidgetOpenGL()
{

}

static void qNormalizeAngle(int &angle, int &angleOld)
{
   int aux = angle-angleOld;
   int auxAntiguo = angle;
   if(aux < 0)
   {    
      angle= angle-angleOld;
   }
   if(aux > 0)
   {
     angle= angle-angleOld;
   }
   angleOld =auxAntiguo;
}


void WidgetOpenGL::setXRotation(int angle)
{
    qNormalizeAngle(angle,angleOld);
    if (angle != xRot) 
    {
        xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}
void WidgetOpenGL::setYRotation(int angle)
{
    qNormalizeAngle(angle,angleOld);
    if (angle != yRot) 
    {
        yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void WidgetOpenGL::setZRotation(int angle)
{
    qNormalizeAngle(angle,angleOld);
    if (angle != zRot) 
    {
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
    if (scala != valorScala) 
    {
        float aux = 1.0/valorScala;
        base.scale(aux,aux,aux);
        valorScala= scala;
        emit ScalaChanged(scala);
        base.scale(valorScala,valorScala,valorScala);
        update();
    }
    qNormalizeScala(scala,&valorScala);
}

void WidgetOpenGL::drawCono()
{
    float conePositions[150]={0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.0f,0.0f, 1.0f, (float)sin(0.261667)*1.0f, (float)cos(0.261667)*1.0f, 0.0f, 0.0f, 0.0f, 1.0f, (float)sin(0.523333)*1.0f,(float) cos(0.523333)*1.0f, 0.0f,
            0.0f, 0.0f, 1.0f, (float)sin(0.785)*1.0f, (float)cos(0.785)*1.0f, 0.0f, 0.0f, 0.0f, 1.0f, (float)sin(1.04667)*1.0f, (float)cos(1.04667)*1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,(float)sin(1.30833)*1.0f, (float)cos(1.30833)*1.0f, 0.0f, 0.0f, 0.0f,1.0f, (float)sin(1.57)*1.0f,(float) cos(1.57)*1.0f, 0.0f,
            0.0f, 0.0f, 1.0f, (float)sin(1.83167)*1.0f,(float) cos(1.83167)*1.0f, 0.0f,0.0f, 0.0f, 1.0f,(float) sin(2.09333)*1.0f, (float)cos(2.09333)*1.0f, 0.0f ,
            0.0f ,0.0f, 1.0f,(float)sin(2.355)*1.0f,(float) cos(2.355)*1.0f, 0.0f,0.0f, 0.0f, 1.0f,(float)sin(2.61667)*1.0f, (float)cos(2.61667)*1.0f, 0.0f ,
            0.0f ,0.0f, 1.0f,(float)sin(2.87833)*1.0f, (float)cos(2.87833)*1.0f, 0.0f,0.0f, 0.0f, 1.0f,(float)sin(3.14)*1.0f,(float) cos(3.14)*1.0f, 0.0f ,
            0.0f ,0.0f, 1.0f,(float)sin(3.40167)*1.0f,(float) cos(3.40167)*1.0f, 0.0f,0.0f, 0.0f, 1.0f,(float)sin(3.66333)*1.0f, (float)cos(3.66333)*1.0f, 0.0f ,
            0.0f ,0.0f, 1.0f,(float)sin(3.925)*1.0f, (float)cos(3.925)*1.0f, 0.0f,0.0f, 0.0f, 1.0f,(float)sin(4.18667)*1.0f, (float)cos(4.18667)*1.0f, 0.0f ,
            0.0f ,0.0f, 1.0f,(float)sin(4.44833)*1.0f, (float)cos(4.44833)*1.0f, 0.0f,0.0f, 0.0f, 1.0f,(float)sin(4.71)*1.0f, (float)cos(4.71)*1.0f, 0.0f ,
            0.0f ,0.0f, 1.0f,(float)sin(4.97167)*1.0f,(float) cos(4.97167)*1.0f, 0.0f,0.0f, 0.0f, 1.0f,(float)sin(5.23333)*1.0f, (float)cos(5.23333)*1.0f, 0.0f ,
            0.0f ,0.0f, 1.0f,(float)sin(5.495)*1.0f, (float)cos(5.495)*1.0f, 0.0f,0.0f, 0.0f, 1.0f,(float)sin(5.75667)*1.0f, (float)cos(5.75667)*1.0f, 0.0f ,
            0.0f ,0.0f, 1.0f,(float)sin(6.01833)*1.0f, (float)cos(6.01833)*1.0f, 0.0f, 0.0f ,0.0f, 1.0f,(float)sin(6.28)*1.0f, (float)cos(6.28)*1.0f, 0.0f

    };
        
    float circlePositions[81]={0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            (float)sin(0.261667)*1.0f, (float) cos(0.261667)*1.0f, 0.0f, (float) sin(0.523333)*1.0f, (float)cos(0.523333)*1.0f, 0.0f,
            (float) sin(0.785)*1.0f, (float)cos(0.785)*1.0f, 0.0f,  (float)sin(1.04667)*1.0f, (float)cos(1.04667)*1.0f, 0.0f,
            (float)sin(1.30833)*1.0f, (float)cos(1.30833)*1.0f, 0.0f,  (float)sin(1.57)*1.0f, (float)cos(1.57)*1.0f, 0.0f,
            (float)sin(1.83167)*1.0f, (float)cos(1.83167)*1.0f, 0.0f,(float) sin(2.09333)*1.0f, (float)cos(2.09333)*1.0f, 0.0f ,
            (float)sin(2.355)*1.0f,(float) cos(2.355)*1.0f, 0.0f,(float)sin(2.61667)*1.0f, (float)cos(2.61667)*1.0f, 0.0f ,
            (float)sin(2.87833)*1.0f,(float) cos(2.87833)*1.0f, 0.0f,(float)sin(3.14)*1.0f, (float)cos(3.14)*1.0f, 0.0f ,
            (float)sin(3.40167)*1.0f, (float)cos(3.40167)*1.0f, 0.0f,(float)sin(3.66333)*1.0f, (float)cos(3.66333)*1.0f, 0.0f ,
            (float)sin(3.925)*1.0f, (float)cos(3.925)*1.0f, 0.0f,(float)sin(4.18667)*1.0f, (float)cos(4.18667)*1.0f, 0.0f ,
            (float)sin(4.44833)*1.0f, (float)cos(4.44833)*1.0f, 0.0f,(float)sin(4.71)*1.0f, (float)cos(4.71)*1.0f, 0.0f ,
            (float)sin(4.97167)*1.0f,(float) cos(4.97167)*1.0f, 0.0f,(float)sin(5.23333)*1.0f, (float)cos(5.23333)*1.0f, 0.0f ,
            (float)sin(5.495)*1.0f, (float)cos(5.495)*1.0f, 0.0f,(float)sin(5.75667)*1.0f,(float) cos(5.75667)*1.0f, 0.0f ,
            (float)sin(6.01833)*1.0f, (float)cos(6.01833)*1.0f, 0.0f,(float)sin(6.01833)*1.0f, (float)cos(6.01833)*1.0f, 0.0f,
            (float)sin(6.28)*1.0f, (float)cos(6.28)*1.0f, 0.0f

    };

    vaoCono.create();
    vaoCono.bind();
    vboCono1.create();
    vboCono1.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboCono1.bind();
    vboCono1.allocate(conePositions,sizeof(conePositions));
    m_program->enableAttributeArray("position");
    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);

    vaoCono.release();

    vaoCono1.create();
    vaoCono1.bind();
    vboCono2.create();
    vboCono2.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboCono2.bind();
    vboCono2.allocate(circlePositions,sizeof(circlePositions));
    m_program->enableAttributeArray("position");
    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);
    vaoCono1.release();

}
void WidgetOpenGL::drawCylinder()
{
    int i = 0;
    for (i = 0; i <= 360; i += 15)
    {
         float p = i * 3.14 / 180;
         m_points_Cylinder<<sin(p)<<cos(p)<<0.0f;
         m_points_Cylinder<<sin(p)<<cos(p)<<1.0f;
    }
    vaoCylinder.create();
    vaoCylinder.bind();
    vboCylinder.create();
    vboCylinder.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboCylinder.bind();
    vboCylinder.allocate(m_points_Cylinder.constData(),m_points_Cylinder.size() * sizeof (GLfloat));
    m_program->enableAttributeArray("position");
    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);
    vaoCylinder.release();

}
void WidgetOpenGL::drawSphere(int x, int y)
{
    vaoSphere.destroy();
        vboSphere.destroy();
        m_points.clear();
        float r=1.0;
        int angleSpan =  (250 - x - y)/10;
        for(int vAngle = -90; vAngle < 90; vAngle = vAngle + angleSpan)
        {
            for(int hAngle = 0; hAngle <= 360; hAngle = hAngle + angleSpan)
            {
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

void WidgetOpenGL::drawgeneral(vector<int> indices,vector<QVector3D> vertices,vector<QVector3D> normal,int numberVer)
{
    vector<float> pvalues;
    vector<float> nvalues;
    vector<float> normales;
     
    for (int i = 0; i < numgeneralInd; i++)
    {
         pvalues.push_back((vertices[indices[i]]).x());
         pvalues.push_back((vertices[indices[i]]).y());
         pvalues.push_back((vertices[indices[i]]).z());
         nvalues.push_back((normal[indices[i]]).x());
         nvalues.push_back((normal[indices[i]]).y());
         nvalues.push_back((normal[indices[i]]).z());
    }

    vaogeneral.bind();
    vbogeneral.bind();
    vbogeneral.allocate(&pvalues[0],pvalues.size()*4);
    vbogeneral1.bind();
    vbogeneral1.allocate(&nvalues[0],nvalues.size()*4);
    vbogeneral2.bind();
    vbogeneral2.allocate(&indices[0],indices.size()*4);
    for (int i = 0; i <numberVer; i++) 
    {
        normales.push_back(normal[i].x());
        normales.push_back(normal[i].y());
        normales.push_back(normal[i].z());
        normales.push_back(normal[i].x()+normal[i].x()*0.2);
        normales.push_back(normal[i].y()+normal[i].y()*0.2);
        normales.push_back(normal[i].z()+normal[i].z()*0.2);
    }

    vbogeneral3.bind();
    vbogeneral3.allocate(&normales[0],normales.size()*4);
    vbogeneral.bind();
}

void WidgetOpenGL::initializeGL()
{


    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                       "#version 450\n" 
                                       "in vec3 position;\n" 
                                       "in vec3 color;\n"
                                       "out vec4 fragColor;\n"
                                       "uniform mat4 mv_matrix;\n"
                                       "void main() {\n"
                                       "    fragColor = vec4(color, 1.0);\n"
                                       "    gl_Position = mv_matrix * vec4(position.x*0.2,position.y*0.2,position.z*0.2, 1.0);\n"
                                       "}\n"
                                       );
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                       "#version 450\n" 
                                       "in vec4 fragColor;\n"
                                       "out vec4 finalcolor;\n"
                                       "void main() {\n"
                                       "    finalcolor = fragColor;\n"
                                       "}\n"
                                       );
    m_program->link();
    m_program->bind();
    vaogeneral.create();
    vaogeneral.bind();
    vbogeneral.create();
    vbogeneral.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbogeneral.bind();
    m_program->enableAttributeArray("position");
    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);

    vbogeneral1.create();
    vbogeneral1.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbogeneral1.bind();

    vbogeneral2.create();
    vbogeneral2.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbogeneral2.bind();

    vbogeneral3.create();
    vbogeneral3.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbogeneral3.bind();

    vbogeneral.release();
    vbogeneral1.release();
    vbogeneral2.release();
    vbogeneral3.release();
    vaogeneral.release();



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

   
    base = QTransform();
  
    base.rotate(xRot,1.0f,0.0f,0.0f);
    base.rotate(yRot,0.0f,1.0f,0.0f);
    base.rotate(zRot,0.0f,0.0f,1.0f);
    base.scale(valorScala);

    float ejeX[]=
    {
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

    float ejeY[]=
    {
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

    float ejeZ[]=
    {
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
    drawCono();

    m_program->setAttributeValue("color",QVector3D(0,1,0));

    m_program->setUniformValue("mv_matrix",base);
    m_program->release();
    vaoluz.release();
    vboluz.release();
    vbo1luz.release();
}

void WidgetOpenGL::resizeGL(int w, int h)
{

}
void WidgetOpenGL::drawAxis()
{
    vaoX.bind();
    m_program->setAttributeValue("color",QVector3D(1,0,0));
    glDrawArrays(GL_LINE_LOOP, 0, 2);

    vaoY.bind();
    m_program->setAttributeValue("color",QVector3D(0,1,0));
    glDrawArrays(GL_LINE_LOOP, 0, 2);

    vaoZ.bind();
    m_program->setAttributeValue("color",QVector3D(0,1,1));
    glDrawArrays(GL_LINE_LOOP, 0, 2);

}

void WidgetOpenGL::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear( GL_COLOR_BUFFER_BIT);
    m_program->bind();
    m_program->setUniformValue("mv_matrix",base);
    drawAxis();

    if(smooth)
    {
        if (f1)
        {
            vao1.bind();
            m_program->setAttributeValue("color",QVector3D(0,1,0));
            glDrawArrays(GL_TRIANGLES, 0, 36);
            update();
        }
        if (f2)
        {

            drawSphere(x,y);
            vaoSphere.bind();
            m_program->setAttributeValue("color",QVector3D(1,0,0));

            glDrawArrays(GL_TRIANGLES,0,m_points.count()/3);
            update();

        }
        if(f3)
        {
           
            cono cone(x,y);
            vector<int> indices = cone.getIndices();
            vector<QVector3D> vertices = cone.getVertices();
            vector<QVector3D> normal = cone.getNormals();
            numgeneralInd= cone.getNumIndices();
            int numberVer = cone.getNumVertices();
            drawgeneral(indices,vertices,normal,numberVer);
            m_program->setAttributeValue("color",QVector3D(1,0,1));
            glDrawArrays(GL_TRIANGLES,0,numgeneralInd);
            update();

        }
        if(f4)
        {
            cilindro cylinder(x,y);
            vector<int> indices = cylinder.getIndices();
            vector<QVector3D> vertices = cylinder.getVertices();
            vector<QVector3D> normal = cylinder.getNormals();
            numgeneralInd= cylinder.getNumIndices();
            int numberVer = cylinder.getNumVertices();
            drawgeneral(indices,vertices,normal,numberVer);
            m_program->setAttributeValue("color",QVector3D(0,1,1));
            glDrawArrays(GL_TRIANGLES,0,numgeneralInd);
            update();

        }
        if(f5)
        {
            toroide torus(x,y);
            vector<int> indices = torus.getIndices();
            vector<QVector3D> vertices = torus.getVertices();
            vector<QVector3D> normal = torus.getNormals();
            numgeneralInd= torus.getNumIndices();
            int numberVer = torus.getNumVertices();
            drawgeneral(indices,vertices,normal,numberVer);
            m_program->setAttributeValue("color",QVector3D(0,0,1));
            glDrawArrays(GL_TRIANGLES,0,numgeneralInd);
            update();
        }
    }
    if(wire)
    {
        if (f1)
        {
            vao1.bind();
            m_program->setAttributeValue("color",QVector3D(1,1,0));
            glDrawArrays(GL_LINES, 0, 36);
            update();

        }
        if (f2)
        {
            m_program->setAttributeValue("color",QVector3D(1,1,0));
            glDrawArrays(GL_LINES,0,m_points.count()/3);
            update();
        }
        if(f3)
        {
            cono cone(x,y);
            vector<int> indices = cone.getIndices();
            vector<QVector3D> vertices = cone.getVertices();
            vector<QVector3D> normal = cone.getNormals();
            numgeneralInd= cone.getNumIndices();
            int numberVer = cone.getNumVertices();
            drawgeneral(indices,vertices,normal,numberVer);
            m_program->setAttributeValue("color",QVector3D(1,1,0));
            for(int i=0; i<numgeneralInd/3 ; i++)
            {
                  glDrawArrays(GL_LINE_LOOP, i*3,3 );
            }
        }
        if(f4)
        {
            cilindro cylinder(x,y);
            vector<int> indices = cylinder.getIndices();
            vector<QVector3D> vertices = cylinder.getVertices();
            vector<QVector3D> normal = cylinder.getNormals();
            numgeneralInd= cylinder.getNumIndices();
            int numberVer = cylinder.getNumVertices();
            drawgeneral(indices,vertices,normal,numberVer);
            m_program->setAttributeValue("color",QVector3D(1,1,0));
            for(int i=0; i<numgeneralInd/3 ; i++)
            {
                glDrawArrays(GL_LINE_LOOP, i*3,3 );
            }
        }
        if(f5)
        {
            toroide torus(x,y);
            vector<int> indices = torus.getIndices();
            vector<QVector3D> vertices = torus.getVertices();
            vector<QVector3D> normal = torus.getNormals();
            numgeneralInd= torus.getNumIndices();
            int numberVer = torus.getNumVertices();
            drawgeneral(indices,vertices,normal,numberVer);
            m_program->setAttributeValue("color",QVector3D(1,1,0));
            for(int i=0; i<numgeneralInd/3 ; i++)
            {
                glDrawArrays(GL_LINE_LOOP, i*3,3 );
            }
        }
    }
}

