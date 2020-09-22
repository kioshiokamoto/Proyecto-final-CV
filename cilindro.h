#ifndef CILINDRO_H
#define CILINDRO_H
#include <cmath>
#include <vector>
#include <QVector3D>
#include <QVector2D>
using namespace std;
class cilindro
{
private:
    int numVertices;
    int numIndices;
    vector<int> indices;
    vector<QVector3D> vertices;
    vector<QVector3D> normals;
    void init(int,int);
public:
    cilindro(int segx, int segy);
    cilindro();
    int getNumVertices();
    int getNumIndices();
    vector<int> getIndices();
    vector<QVector3D> getVertices();
    vector<QVector3D> getNormals();
};

#endif // CILINDRO_H
