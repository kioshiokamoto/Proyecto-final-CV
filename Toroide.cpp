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
float toroide::toRadians(float degrees) { return (degrees * 2.0f * 3.14159f) / 360.0f; }
void toroide::init(int segx, int segy)
{
    numVertices = segx * segy;
    numIndices = 6*segx * segy;
    for (int i = 0; i < numVertices; i++) { vertices.push_back(QVector3D()); } // std::vector::push_back()
    for (int i = 0; i < numVertices; i++) { normals.push_back(QVector3D()); } // the end of a vector and
    for (int i = 0; i < numVertices+segx; i++) { sTangents.push_back(QVector3D()); }
    for (int i = 0; i < numVertices+segx; i++) { tTangents.push_back(QVector3D()); }
    for (int i = 0; i < numIndices; i++) { indices.push_back(0); } // increases the vector size by 1
    float alpha=0 , beta =0;
    float rad1 = 0.9, rad2=0.4;
    int cont =0;
    int m=0, n=0,s=2;
    /*for(m=0; m<segx; m++){
        float amt = toRadians(m*360.0f / segx);
        matriz1 = QTransform();
        matriz1.rotate(amt,0.0f,0.0f,1.0f);
        tTangents[m] = QVector3D(matriz1 * QVector4D(0.0f, -1.0f, 0.0f, 1.0f));
        sTangents[m] = QVector3D(QVector3D(0.0f, 0.0f, -1.0f));
        normals[m] = QVector3D::crossProduct(tTangents[m], sTangents[m]);
    }*/
    //vertices
    int auxNormal=m;
    while(cont< numVertices){
        for(int i=cont;i<cont+segx; i++ ){
            float x = (float)((rad1+rad2*cos(alpha))*cos(beta));
            float y = (float)((rad1+rad2*cos(alpha))*sin(beta));
            float z = (float)(rad2*sin(alpha));
            alpha = alpha + 2*(M_PI)/segx;
            vertices[i] = QVector3D(x, y, z);
            /*if(i>0){
                normals[i] = QVector3D::normal(vertices[i-1],vertices[i]);
            }*/
            normals[i]=QVector3D(x, y, z);

            /*
            float amt = toRadians(s*360.0f / segy);
            if(n==auxNormal-1){
                n=0;
            }
            // rotate the tangent and bitangent vectors around the Y axis
            matriz1 = QTransform();
            matriz1.rotate(amt,0.0f,1.0f,0.0f);
            sTangents[m] = QVector3D(matriz1 * QVector4D(sTangents[n], 1.0f));
            matriz1.rotate(amt, QVector3D(0.0f, 1.0f, 0.0f));
            tTangents[m] = QVector3D(matriz1 *QVector4D(tTangents[n], 1.0f));
             // rotate the normal vector around the Y axis
            matriz1.rotate(amt, QVector3D(0.0f, 1.0f, 0.0f));
            normals[m] = QVector3D(matriz1 * QVector4D(normals[n], 1.0f));
            m++;
            n++;*/

        }
        cont = cont+segx;
        beta = beta + 2*(M_PI)/segy;
        alpha = 0;
        n=0;
        s++;
    }
    cont = 0; //se han llenado cont indices
    int j=segx; //indice de la siguiente base
    int aux3= segx*segy-1-segx;
    int aux = 0;
    int aux1=0;
    int cont1=0;
    while(cont< numIndices){
        segy--;
        for(int i=aux; i<aux+segx; i++){
            if(segy==0){
                if(i==aux+segx-1){
                    //cout<<aux<<endl;
                    indices[6 *(i-aux)+cont] = i;
                    indices[6 * (i-aux)+cont + 1] = 0;
                    indices[6 * (i-aux)+cont + 2] = segx-1;
                    indices[6 * (i-aux)+cont + 3] = i;
                    indices[6 * (i-aux)+cont + 4] = 0;
                    indices[6 * (i-aux)+cont + 5] = aux;
                    cont1= cont1+6;
                }else{
                    //cout<<aux1<<endl;
                    indices[6 *(i-aux)+cont] = i;
                    indices[6 * (i-aux)+cont + 1] = aux1;
                    indices[6 * (i-aux)+cont + 2] = aux1+1;
                    indices[6 * (i-aux)+cont + 3] = i;
                    indices[6 * (i-aux)+cont + 4] = aux1+1;
                    indices[6 * (i-aux)+cont + 5] = i+1;
                    cont1= cont1+6;
                    aux1++;
                }

            }else{
                if(j+1==aux+2*segx){
                    //cout<<aux<<endl;
                    indices[6 *(i-aux)+cont] = i;
                    indices[6 * (i-aux)+cont + 1] = j;
                    indices[6 * (i-aux)+cont + 2] = i+1;
                    indices[6 * (i-aux)+cont + 3] = i;
                    indices[6 * (i-aux)+cont + 4] = i+1;
                    indices[6 * (i-aux)+cont + 5] = aux;
                    j++;
                    cont1 = cont1+6;
                }else{
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
    /*vector<int> ind = getIndices();
    for(int m=0; m<numVertices;m++){
       normals[m] = QVector3D::normal(vertices[ind[m]],vertices[ind[m+1]]);
    }*/


}
int toroide::getNumVertices() { return numVertices; }
int toroide::getNumIndices() { return numIndices; }
std::vector<int> toroide::getIndices() { return indices; }
std::vector<QVector3D> toroide::getVertices() { return vertices; }
std::vector<QVector3D> toroide::getNormals() { return normals; }

