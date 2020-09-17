#include "Torus.h"

Torus::Torus(){

}

void Torus::setupVertices(int sx,int sy){
    vertex.clear();
    index.clear();
    setXSegments(sx);
    setYSegments(sy);
    GLfloat twicePi=360.0f;
    GLfloat radioext=4.0f;
    GLfloat radioint=2.0f;

    //generate first ring
    QMatrix4x4 rotfirst;
    for (int i = 0; i < getYSegments()+1; i++){
        GLfloat angleint = (float)i*twicePi/(float)getYSegments();
        rotfirst.setToIdentity();
        rotfirst.rotate(angleint, 0.0f, 0.0f, 1.0f);
        QVector3D initpos = QVector3D(rotfirst * QVector4D(radioint, 0.0f, 0.0f, 1.0f));
        initpos = initpos + QVector3D(radioext, 0.0f, 0.0f);
        vertex.push_back(initpos.x());
        vertex.push_back(initpos.y());
        vertex.push_back(initpos.z());
    }

    //rotate first ring in y axis

    QMatrix4x4 rot;

    for (int i = 1; i < getXSegments()+1; i++){
        GLfloat angle = (float)(i)*twicePi/(float)getXSegments();
        rot.setToIdentity();
        rot.rotate(angle, 0.0f, 1.0f, 0.0f);
        for (int i = 0; i < getYSegments()+1; i++){
            QVector3D t = QVector3D(rot*QVector4D(vertex.at(3*i),vertex.at(3*i+1),vertex.at(3*i+2),1.0f));
            vertex.push_back(t.x());
            vertex.push_back(t.y());
            vertex.push_back(t.z());
        }
    }
    //generate index
    for (int j = 0; j < getXSegments(); j++) {
        for (int i = 0; i < getYSegments(); i++) {
                index.push_back(j*(getYSegments() + 1) + i);
                index.push_back((j + 1)*(getYSegments() + 1) + i);
                index.push_back(j*(getYSegments() + 1) + i + 1);
                index.push_back(j*(getYSegments() + 1) + i + 1);
                index.push_back((j + 1)*(getYSegments() + 1) + i);
                index.push_back((j + 1)*(getYSegments() + 1) + i + 1);
        }
    }
}

int Torus::getYSegments() const
{
    return ySegments;
}

void Torus::setYSegments(int value)
{
    ySegments = value;
}

int Torus::getXSegments() const
{
    return xSegments;
}

void Torus::setXSegments(int value)
{
    xSegments = value;
}
