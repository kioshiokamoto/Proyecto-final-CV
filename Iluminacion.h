#ifndef ILUMINACION_H
#define ILUMINACION_H
#include <QMatrix4x4>

using namespace std;
class lighting
{
    private:
        QVector3D lightLoc;
        struct light{
            QVector4D Ambient;
            QVector4D Diffuse;
            QVector4D Specular;
            QVector3D position;
        };
        struct material{
            QVector4D Ambient;
            QVector4D Diffuse;
            QVector4D Specular;
            float shininess;
        };
    public:
        QVector4D global_Ambient;
        QVector3D currentLightPos;
        material material;
        light light;
        lighting();
        void bronzeMaterial();
        void silverMaterial();
        void goldMaterial();
        void differentMaterial(int);
        void install_Lights();
        void setLightPosition(QVector3D);
        QVector3D getLightLoc();
        QVector4D getGlobalAmbient();
        QVector3D getCurrentLightPos();
        QVector4D getLightAmbient();
        QVector4D getLightDiffuse();
        QVector4D getLightSpecular();
        QVector3D getLightPosition();
        QVector4D getMaterialAmbient();
        QVector4D getMaterialDiffuse();
        QVector4D getMaterialSpecular();
        float getMaterialShininess();
};
#endif 
