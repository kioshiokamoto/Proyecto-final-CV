#include <cmath>
#include <vector>
#include <iostream>
#include <QVector4D>
#include <QVector3D>
#include <QVector2D>
#include <QMatrix4x4>
#include "Torus.h"
#include <QMainWindow>
#include <QOpenGLWindow>
#include <qopenglwidget.h>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QGLFunctions>
#include <QtOpenGL>
using namespace std;

Torus::Torus() {
    prec = 48;
    inner = 0.5f;
    outer = 0.2f;
    init();
}

Torus::Torus(float in, float out, int precIn) {
    prec = precIn;
    inner = in;
    outer = out;
    init();
}

float Torus::toRadians(float degrees) { return (degrees * 2.0f * 3.14159f) / 360.0f; }

void Torus::init() {
    numVertices = (prec + 1) * (prec + 1);
    numIndices = prec * prec * 6;
    for (int i = 0; i < numVertices; i++) { vertices.push_back(QVector3D()); }
    for (int i = 0; i < numVertices; i++) { texCoords.push_back(QVector2D()); }
    for (int i = 0; i < numVertices; i++) { normals.push_back(QVector3D()); }
    for (int i = 0; i < numVertices; i++) { sTangents.push_back(QVector3D()); }
    for (int i = 0; i < numVertices; i++) { tTangents.push_back(QVector3D()); }
    for (int i = 0; i < numIndices; i++) { indices.push_back(0); }

    // calculate first ring
    for (int i = 0; i < prec + 1; i++) {
        float amt = toRadians(i*360.0f / prec);

        QMatrix4x4 rMat;
        rMat = QTransform();
        rMat.rotate(amt, QVector3D(0.0f, 0.0f, 1.0f));
        QVector3D initPos(rMat * QVector4D(outer, 0.0f, 0.0f, 1.0f));

        vertices[i] = QVector3D(initPos + QVector3D(inner, 0.0f, 0.0f));
        texCoords[i] = QVector2D(0.0f, ((float)i / (float)prec));

        rMat.rotate(amt, QVector3D(0.0f, 0.0f, 1.0f));
        tTangents[i] = QVector3D(rMat * QVector4D(0.0f, -1.0f, 0.0f, 1.0f));

        sTangents[i] = QVector3D(QVector3D(0.0f, 0.0f, -1.0f));
        normals[i] = tTangents[i].operator*=(sTangents[i]);
    }
    // rotate the first ring about Y to get the other rings
    for (int ring = 1; ring < prec + 1; ring++) {
        for (int i = 0; i < prec + 1; i++) {
            float amt = (float)toRadians((float)ring * 360.0f / (prec));

            QMatrix4x4 rMat;
            rMat = QTransform();

            rMat.rotate(amt, QVector3D(0.0f, 1.0f, 0.0f));
            vertices[ring*(prec + 1) + i] = QVector3D(rMat * QVector4D(vertices[i], 1.0f));

            texCoords[ring*(prec + 1) + i] = QVector2D((float)ring*2.0f / (float)prec, texCoords[i].y());
            if (texCoords[ring*(prec + 1) + i].x() > 1.0) {
                texCoords[ring*(prec+1)+i].operator-=(QVector2D(-1.0,0));
             }
            rMat.rotate(amt, QVector3D(0.0f, 1.0f, 0.0f));
            sTangents[ring*(prec + 1) + i] = QVector3D(rMat * QVector4D(sTangents[i], 1.0f));

            rMat.rotate(amt, QVector3D(0.0f, 1.0f, 0.0f));
            tTangents[ring*(prec + 1) + i] = QVector3D(rMat * QVector4D(tTangents[i], 1.0f));

            rMat.rotate(amt, QVector3D(0.0f, 1.0f, 0.0f));
            normals[ring*(prec + 1) + i] = QVector3D(rMat * QVector4D(normals[i], 1.0f));
        }
    }
    // calculate triangle indices
    for (int ring = 0; ring < prec; ring++) {
        for (int i = 0; i < prec; i++) {
            indices[((ring*prec + i) * 2) * 3 + 0] = ring*(prec + 1) + i;
            indices[((ring*prec + i) * 2) * 3 + 1] = (ring + 1)*(prec + 1) + i;
            indices[((ring*prec + i) * 2) * 3 + 2] = ring*(prec + 1) + i + 1;
            indices[((ring*prec + i) * 2 + 1) * 3 + 0] = ring*(prec + 1) + i + 1;
            indices[((ring*prec + i) * 2 + 1) * 3 + 1] = (ring + 1)*(prec + 1) + i;
            indices[((ring*prec + i) * 2 + 1) * 3 + 2] = (ring + 1)*(prec + 1) + i + 1;
        }
    }
}
int Torus::getNumVertices() { return numVertices; }
int Torus::getNumIndices() { return numIndices; }
std::vector<int> Torus::getIndices() { return indices; }
std::vector<QVector3D> Torus::getVertices() { return vertices; }
std::vector<QVector2D> Torus::getTexCoords() { return texCoords; }
std::vector<QVector3D> Torus::getNormals() { return normals; }
std::vector<QVector3D> Torus::getStangents() { return sTangents; }
std::vector<QVector3D> Torus::getTtangents() { return tTangents; }
