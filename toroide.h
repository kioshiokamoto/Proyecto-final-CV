#ifndef TOROIDE_H
#define TOROIDE_H
#include <cmath>
#include <vector>
#include <QVector3D>
#include <QVector2D>
#include <QMatrix4x4>
#include <QTransform>
using namespace std;
class toroide
{
    private:
        int numVertices;
        int numIndices;
        vector<int> indices;
        vector<QVector3D> vertices;
        vector<QVector3D> normals;
        vector<QVector3D> sTangents;
        vector<QVector3D> tTangents;
        void init(int,int);
        float toRadians(float degrees);
        QMatrix4x4 matriz1;
    public:
        toroide(int segx, int segy);
        toroide();
        int getNumVertices();
        int getNumIndices();
        vector<int> getIndices();
        vector<QVector3D> getVertices();
        vector<QVector3D> getNormals();
        vector<QVector3D> getStangents();
        vector<QVector3D> getTtangents();

};
#endif 
