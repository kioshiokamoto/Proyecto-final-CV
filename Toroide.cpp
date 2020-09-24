#include "toroide.h"
#include <iostream>
#include <QVector3D>
using namespace std;
toroide::toroide(int segx, int segy)
{
    init(segx,segy);
}

toroide::toroide()
{
    init(3,3);
}
float toroide::toRadians(float degrees) 
{ 
    return (degrees * 2.0f * 3.14159f) / 360.0f; 
}

void toroide::init(int segx, int segy)
{
    numVertices = segx * segy;
    numIndices = 6*segx * segy;
    for (int i = 0; i < numVertices; i++) { vertices.push_back(QVector3D()); } 
    for (int i = 0; i < numVertices; i++) { normals.push_back(QVector3D()); } 
    for (int i = 0; i < numVertices+segx; i++) { sTangents.push_back(QVector3D()); }
    for (int i = 0; i < numVertices+segx; i++) { tTangents.push_back(QVector3D()); }
    for (int i = 0; i < numIndices; i++) { indices.push_back(0); } 
    float alpha=0 , beta =0;
    float rad1 = 0.9, rad2=0.4;
    int cont =0;
    int n=0,s=2;
    
    while(cont< numVertices)
    {
        for(int i=cont;i<cont+segx; i++ )
        {
            float x = (float)((rad1+rad2*cos(alpha))*cos(beta));
            float y = (float)((rad1+rad2*cos(alpha))*sin(beta));
            float z = (float)(rad2*sin(alpha));
            alpha = alpha + 2*(M_PI)/segx;
            vertices[i] = QVector3D(x, y, z);
            normals[i]=QVector3D(x, y, z);
        }
        cont = cont+segx;
        beta = beta + 2*(M_PI)/segy;
        alpha = 0;
        n=0;
        s++;
    }
    cont = 0; 
    int j=segx; 
    int aux = 0;
    int aux1=0;
    int cont1=0;
    while(cont< numIndices)
    {
        segy--;
        for(int i=aux; i<aux+segx; i++)
        {
            if(segy==0)
            {
                if(i==aux+segx-1)
                {
                    
                    indices[6 *(i-aux)+cont] = i;
                    indices[6 * (i-aux)+cont + 1] = 0;
                    indices[6 * (i-aux)+cont + 2] = segx-1;
                    indices[6 * (i-aux)+cont + 3] = i;
                    indices[6 * (i-aux)+cont + 4] = 0;
                    indices[6 * (i-aux)+cont + 5] = aux;
                    cont1= cont1+6;
                }
                else
                {
                    
                    indices[6 *(i-aux)+cont] = i;
                    indices[6 * (i-aux)+cont + 1] = aux1;
                    indices[6 * (i-aux)+cont + 2] = aux1+1;
                    indices[6 * (i-aux)+cont + 3] = i;
                    indices[6 * (i-aux)+cont + 4] = aux1+1;
                    indices[6 * (i-aux)+cont + 5] = i+1;
                    cont1= cont1+6;
                    aux1++;
                }
            }
            else
            {
                if(j+1==aux+2*segx)
                {
                  
                    indices[6 *(i-aux)+cont] = i;
                    indices[6 * (i-aux)+cont + 1] = j;
                    indices[6 * (i-aux)+cont + 2] = i+1;
                    indices[6 * (i-aux)+cont + 3] = i;
                    indices[6 * (i-aux)+cont + 4] = i+1;
                    indices[6 * (i-aux)+cont + 5] = aux;
                    j++;
                    cont1 = cont1+6;
                }
                else
                {
                    indices[6 *(i-aux)+cont] = i;
                    indices[6 * (i-aux)+cont + 1] = j;
                    indices[6 * (i-aux)+cont + 2] = j+1;
                    indices[6 * (i-aux)+cont + 3] = i;
                    indices[6 * (i-aux)+cont + 4] = j + 1;
                    indices[6 * (i-aux)+cont + 5] = i+1;
                    j++;
                    cont1 = cont1+6;
                }
            }
        }
        aux = aux+segx;
        cont = cont + cont1;
        cont1=0;
    }
}

int toroide::getNumVertices() { return numVertices; }
int toroide::getNumIndices() { return numIndices; }
std::vector<int> toroide::getIndices() { return indices; }
std::vector<QVector3D> toroide::getVertices() { return vertices; }
std::vector<QVector3D> toroide::getNormals() { return normals; }

