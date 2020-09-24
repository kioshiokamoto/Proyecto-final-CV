#include "cono.h"
#include <iostream>
using namespace std;
float twicePi = 2.0f * M_PI;
float radio= 1.0;
cono::cono(int segx, int segy)
{
    init(segx,segy);
}

cono::cono()
{
    init(3,1);
}
float cono::toRadians(float degrees)
{
    return (degrees * 2.0f * 3.14159f) / 360.0f;
}
void cono::init(int segx, int segy)
{
    numVertices = segx * segy + 2;
               
    numIndices = 6*segx * segy;
    for (int i = 0; i < numVertices; i++) 
    { 
        vertices.push_back(QVector3D()); 
    } 

    for (int i = 0; i < numVertices; i++) 
    { 
        normals.push_back(QVector3D()); 
    } 

    for (int i = 0; i < numIndices; i++) 
    { 
        indices.push_back(0); 
    } 

    //vertices de las bases:
    vertices[0]=QVector3D(0.0,-1.0,0.0); 
    normals[0] = QVector3D(0.0,-1.0,0.0);
    vertices[1]=QVector3D(0.0,1.0,0.0); 
    normals[1] = QVector3D(0.0,1.0,0.0);
    int cont=2; 
    float escala = 1.0;
    float altura = -1.0;
    while(cont< numVertices)
    {
        for(int i=cont; i<cont+segx; i++)
        {
            float x = radio*(cos((i-2) * twicePi / segx))*escala;
            float y = altura;
            float z = radio*(sin((i-2) * twicePi / segx))*escala;
            vertices[i] = QVector3D(x, y, z);
            normals[i] = QVector3D(x, y, z);
        }
        altura = altura +(2.0/segy);
        escala = escala - (1.0/segy); 
        cont = cont +segx; 
    }
    cont = 2;
    for(int i=cont; i<cont+segx; i++)
    {
        if(i==cont+segx-1)
        {
            indices[3*(i-2)]=0;
            indices[3*(i-2)+1]=i;
            indices[3*(i-2)+2]=cont;
        }
        else
        {
            indices[3*(i-2)]=0;
            indices[3*(i-2)+1]=i;
            indices[3*(i-2)+2]=i+1;
        }
    }
    cont = segx*3; 
    int j=2+segx; 
    int aux = 2;
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
                    indices[3 *(i-aux)+cont] = 1;
                    indices[3 * (i-aux)+cont + 1] = i;
                    indices[3 * (i-aux)+cont + 2] = aux;
                    cont1= cont1+3;
                }
                else
                {
                    indices[3 *(i-aux)+cont] = 1;
                    indices[3 * (i-aux)+cont + 1] = i;
                    indices[3 * (i-aux)+cont + 2] = i+1;
                    cont1= cont1+3;
                }

            }
            else
            {
                if(j+1==aux+2*segx)
                {

                    indices[6 *(i-aux)+cont] = aux;
                    indices[6 * (i-aux)+cont + 1] = i;
                    indices[6 * (i-aux)+cont + 2] = j;
                    indices[6 * (i-aux)+cont + 3] = aux;
                    indices[6 * (i-aux)+cont + 4] = i + 1;
                    indices[6 * (i-aux)+cont + 5] = j;
                    j++;
                    cont1 = cont1+6;
                }
                else
                {
                    indices[6 *(i-aux)+cont] = i;
                    indices[6 * (i-aux)+cont + 1] = i + 1;
                    indices[6 * (i-aux)+cont + 2] = j;
                    indices[6 * (i-aux)+cont + 3] = j + 1;
                    indices[6 * (i-aux)+cont + 4] = i + 1;
                    indices[6 * (i-aux)+cont + 5] = j;
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

int cono::getNumVertices() { return numVertices; }
int cono::getNumIndices() { return numIndices; }
std::vector<int> cono::getIndices() { return indices; }
std::vector<QVector3D> cono::getVertices() { return vertices; }
std::vector<QVector3D> cono::getNormals() { return normals; }
