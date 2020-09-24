#ifndef CONO_H
#define CONO_H
#include <cmath>
#include <vector>
#include <QVector3D>
#include <QVector2D>
using namespace std;
class cono
{
    private:
        int numVertices;
        int numIndices;
        vector<int> indices;
        vector<QVector3D> vertices;
        vector<QVector3D> normals;
        void init(int,int);
        float toRadians(float degrees);
    public:
        cono(int segx, int segy);
        cono();
        int getNumVertices();
        int getNumIndices();
        vector<int> getIndices();
        vector<QVector3D> getVertices();
        vector<QVector3D> getNormals();
};
#endif 
