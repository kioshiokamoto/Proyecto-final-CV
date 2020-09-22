#include "widget_opengl.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glu.h>
#include <stdio.h>
#include "toroide.h"
QMatrix4x4 pMat, vMat, mMat, mvMat, invTrMat, rMat;
float i=0;

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
    x = 5;
    y = 5;

    smooth = false;
    wire = false;

    t1 = toroide(5,5);


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

void WidgetOpenGL::drawCono(){
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
        //ESTE ES LA TAPITA DEL CONO
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
                        (float)sin(6.01833)*1.0f, (float)cos(6.01833)*1.0f, 0.0f,(float)sin(6.01833)*1.0f, (float)cos(6.01833)*1.0f, 0.0f
                        ,(float)sin(6.28)*1.0f, (float)cos(6.28)*1.0f, 0.0f

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
void WidgetOpenGL::drawCylinder(){
    int i = 0;
    for (i = 0; i <= 360; i += 15){
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
void WidgetOpenGL::drawSphere(int x, int y){
    vaoSphere.destroy();
    vboSphere.destroy();
    m_points.clear();
    luces->bind();
    glDisable(GL_CULL_FACE);
    QMatrix4x4 modelo= QTransform();
    vMat.setToIdentity();
    vMat.translate(QVector3D(4, -10, 500));
    modelo.rotate(xRot,QVector3D(1.0f, 0.0f, 0.0f));
    modelo.rotate(yRot,QVector3D(0.0f, 1.0f, 0.0f));
    modelo.rotate(zRot,QVector3D(0.0f, 0.0f, 1.0f));
    modelo.scale(valorScala);
    QMatrix4x4 position;
    position = QTransform();
    position.translate(0,0,0);
    position.rotate(.0,0.0f,0.0f,0.0f);
    luces->setUniformValue("position", position);
    luz->install_Lights();
    if(i>23.0){
        i=0;
    }
    luz->differentMaterial(int (i));
    i+=0.05;
    luz->light.position=QVector3D(luz->currentLightPos);
    luces->setUniformValue("globalAmbient",luz->global_Ambient);
    luces->setUniformValue("light.ambient", luz->light.Ambient);
    luces->setUniformValue("light.diffuse", luz->light.Diffuse);
    luces->setUniformValue("light.specular", luz->light.Specular);
    luces->setUniformValue("light.position", luz->light.position);
    luces->setUniformValue("material.ambient", luz->material.Ambient);
    luces->setUniformValue("material.diffuse", luz->material.Diffuse);
    luces->setUniformValue("material.specular", luz->material.Specular);
    luces->setUniformValue("material.shininess", luz->material.shininess);
    mvMat.setToIdentity();
    mvMat = vMat * modelo;
    invTrMat.setToIdentity();
    invTrMat=mvMat.inverted().transposed();
    //Estableciendo valor para la matriz vista y modelo
    luces->setUniformValue("mv_matrix",mvMat);
    //Estableciendo valores para la normal de la luz
    luces->setUniformValue("norm_matrix",invTrMat);
    //Estableciendo valor para la matriz de transformación del sólido
    luces->setUniformValue("model", modelo);
    float r=1.0;
    int angleSpan = 30 - x - y;
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
    m_program->enableAttributeArray("position");
    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);
    vbo1luz.bind();
    vbo1luz.allocate(m_points.constData(),m_points.size() * sizeof (GLfloat));
    luces->enableAttributeArray("vertPos");
    luces->setAttributeBuffer("vertPos", GL_FLOAT, 0, 3);
    vboluz.bind();
    vboluz.allocate(m_points.constData(),m_points.size() * sizeof (GLfloat));
    luces->enableAttributeArray("vertNormal");
    luces->setAttributeBuffer("vertNormal", GL_FLOAT, 0, 3);
    vaoSphere.release();


}

void WidgetOpenGL::drawgeneral(vector<int> indices,vector<QVector3D> vertices,vector<QVector3D> normal,int numberVer){
    vector<float> pvalues;
    vector<float> nvalues;
    vector<float> normales;
    for (int i = 0; i < numgeneralInd; i++) {
         pvalues.push_back((vertices[indices[i]]).x());
         pvalues.push_back((vertices[indices[i]]).y());
         pvalues.push_back((vertices[indices[i]]).z());
         nvalues.push_back((normal[indices[i]]).x());
         nvalues.push_back((normal[indices[i]]).y());
         nvalues.push_back((normal[indices[i]]).z());
  }

    vaogeneral.create();
    vaogeneral.bind();
    vbogeneral.bind();
    vbogeneral.allocate(&pvalues[0],pvalues.size()*4);
    vbogeneral.create();
    vbogeneral.bind();
    vbogeneral1.allocate(&nvalues[0],nvalues.size()*4);
    vbogeneral1.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbogeneral2.create();
    vbogeneral2.bind();
    vbogeneral2.allocate(&indices[0],indices.size()*4);
    vbogeneral2.setUsagePattern(QOpenGLBuffer::StaticDraw);

    for (int i = 0; i <numberVer; i++) {
              normales.push_back(normal[i].x());
              normales.push_back(normal[i].y());
              normales.push_back(normal[i].z());
              normales.push_back(normal[i].x()+normal[i].x()*0.2);
              normales.push_back(normal[i].y()+normal[i].y()*0.2);
              normales.push_back(normal[i].z()+normal[i].z()*0.2);
         }
    vbogeneral3.bind();
    vbogeneral3.allocate(&normales[0],normales.size()*4);
    vbogeneral3.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_program->enableAttributeArray("position");
    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);
    vaogeneral.release();
}

void WidgetOpenGL::initializeGL()
{
    vbogeneral.create();
    vbogeneral.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbogeneral.release();
    vbogeneral1.create();
    vbogeneral1.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbogeneral1.release();
    vbogeneral2.create();
    vbogeneral2.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbogeneral2.release();
    vbogeneral3.create();
    vbogeneral3.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbogeneral3.release();

    luces = new QOpenGLShaderProgram();
    luces->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Light_Vertex.glsl");
    luces->addShaderFromSourceFile(QOpenGLShader::Fragment,":/Light_Fragment.glsl");
    luces->link();
    vaoluz.create();
    vaoluz.bind();
    vboluz.create();
    vbo1luz.create();
    vboluz.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo1luz.setUsagePattern(QOpenGLBuffer::StaticDraw);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
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





    vao2.create();
    vao2.bind();
    _vbo.create();
    _vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _vbo.bind();
    _vbo.allocate(pyramidPositions, sizeof (pyramidPositions));

    m_program->enableAttributeArray("position");
    m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);



    vao2.release();




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
    //drawCylinder();
    //Para pasar color a shader
    m_program->setAttributeValue("color",QVector3D(0,1,0));
    //Pasar escalamiento y rotacion a shader
    m_program->setUniformValue("mv_matrix",base);

    m_program->release();
    vaoluz.release();
    vboluz.release();
    vbo1luz.release();


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

    if(smooth){
        if (f1){

            vao1.bind();
            m_program->setAttributeValue("color",QVector3D(0,1,0));
            glDrawArrays(GL_TRIANGLES, 0, 36);
            /*

            m_program->setAttributeValue("color",QVector3D(1,1,0));
            glDrawArrays(GL_LINES, 0, 36); */




        }
        if (f2){

            drawSphere(x,y);
            vaoluz.bind();
            vaoSphere.bind();
            m_program->setAttributeValue("color",QVector3D(1,0,0));
            luces->bind();
            vbo1luz.bind();
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            glDrawArrays(GL_TRIANGLES,0,m_points.count()/3);
            update();

        }
        if(f3){

            vaoCono.bind();
            m_program->setAttributeValue("color",QVector3D(1,0,0));
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 50);

            vaoCono1.bind();
            m_program->setAttributeValue("color",QVector3D(1,0,0));
            glDrawArrays(GL_TRIANGLE_FAN, 0, 27);

        }
        if(f4){

            vaoCylinder.bind();
            m_program->setAttributeValue("color",QVector3D(1,0,0));
            glDrawArrays(GL_QUAD_STRIP,0,m_points.count()/3);

        }
        if(f5){
            toroide torus(100,100);
            vector<int> indices = torus.getIndices();
            vector<QVector3D> vertices = torus.getVertices();
            vector<QVector3D> normal = torus.getNormals();
            numgeneralInd= torus.getNumIndices();
            int numberVer = torus.getNumVertices();
            drawgeneral(indices,vertices,normal,numberVer);
            vaogeneral.bind();
            m_program->setAttributeValue("color",QVector3D(0,0,1));
            glDrawArrays(GL_TRIANGLES,0,numgeneralInd);
        }
    }
    if(wire){
        if (f1){

            vao1.bind();
            m_program->setAttributeValue("color",QVector3D(1,1,0));
            glDrawArrays(GL_LINES, 0, 36);




        }
        if (f2){

            drawSphere(x,y);
            m_program->bind();
            vaoluz.bind();
            vbo1luz.bind();
            m_program->enableAttributeArray("position");
            m_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);


            m_program->setAttributeValue("color",QVector3D(1,1,0));
            glDrawArrays(GL_LINES,0,m_points.count()/3);
            update();

        }
        if(f3){
            vaoCono.bind();
            m_program->setAttributeValue("color",QVector3D(1,1,0));
            glDrawArrays(GL_LINES, 0, 50);
            /*
            vaoCono.bind();
            m_program->setAttributeValue("color",QVector3D(1,0,0));
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 50);

            vaoCono1.bind();
            m_program->setAttributeValue("color",QVector3D(1,0,0));
            glDrawArrays(GL_TRIANGLE_FAN, 0, 27); */

        }
        if(f4){
            vaoCylinder.bind();
            m_program->setAttributeValue("color",QVector3D(1,0,0));
            glDrawArrays(GL_QUAD_STRIP,0,m_points.count()/3);

        }
        if(f5){
            /*drawTorus(x,y);
            vaoTorus.bind();
            m_program->setAttributeValue("color",QVector3D(1,0,0));
            glDrawArrays(GL_LINES,0,numTorusIndices);*/
            m_program->setAttributeValue("color",QVector3D(1,0,0));
            for(int i=0; i<numgeneralInd/3 ; i++){
                glDrawArrays(GL_LINE_LOOP, i*3,3 );
             }


        }
    }


}

