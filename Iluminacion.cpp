#include <Iluminacion.h>
using namespace std;
lighting::lighting()
{
    global_Ambient = { 0.7f, 0.7f, 0.7f, 1.0f};
    light.Ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
    light.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
    light.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
    lightLoc = QVector3D(5.0f, 2.0f, 1.0f);
}

void lighting::goldMaterial()
{
    material.Ambient= { 0.2473f, 0.1995f, 0.0745f, 1 };
    material.Diffuse= { 0.7516f, 0.6065f, 0.2265f, 1 };
    material.Specular= { 0.6283f, 0.5559f, 0.3661f, 1 };
    material.shininess= 51.2f;
}

void lighting::silverMaterial()
{
    material.Ambient= { 0.1923f, 0.1923f, 0.1923f, 1 };
    material.Diffuse= { 0.5075f, 0.5075f, 0.5075f, 1 };
    material.Specular= { 0.5083f, 0.5083f, 0.5083f, 1 };
    material.shininess= 51.2f;
}

void lighting::bronzeMaterial()
{
    material.Ambient= { 0.2125f, 0.1275f, 0.0540f, 1 };
    material.Diffuse= { 0.7140f, 0.4284f, 0.1814f, 1 };
    material.Specular= { 0.3936f, 0.2719f, 0.1667f, 1 };
    material.shininess= 25.6f;
}

void lighting::differentMaterial(int index)
{
    QVector3D ambient,diffuse,specular;
    float shinisses;
    switch (index) 
    {
        case 3:
            ambient = QVector3D(0.0215,0.1745,0.0215);
            diffuse = QVector3D(0.07568,0.61424,0.07568);
            specular = QVector3D(0.633,0.727811,0.633);
            shinisses = 0.6;
            break;
        case 4:
            ambient = QVector3D(0.135,0.2225,0.1575);
            diffuse = QVector3D(0.54,0.89,0.63);
            specular = QVector3D(0.316228,0.316228,0.316228);
            shinisses = 0.1;
            break;
        case 5:
            ambient = QVector3D(0.05375,0.05,0.06625);
            diffuse = QVector3D(0.18275,0.17,0.22525);
            specular = QVector3D(0.332741,0.328634,0.346435);
            shinisses = 0.3;
            break;
        case 6:
            ambient = QVector3D(0.25,0.20725,0.20725);
            diffuse = QVector3D(1,0.829,0.829);
            specular = QVector3D(0.296648,0.296648,0.296648);
            shinisses = 0.088;
            break;
        case 7:
            ambient = QVector3D(0.1745,0.01175,0.01175);
            diffuse = QVector3D(0.61424,0.04136,0.04136);
            specular = QVector3D(0.727811,0.626959,0.626959);
            shinisses = 0.6;
            break;
        case 8:
            ambient = QVector3D(0.1,0.18725,0.1745);
            diffuse = QVector3D(0.396,0.74151,0.69102);
            specular = QVector3D(0.297254,0.30829,0.306678);
            shinisses = 0.1;
            break;
        case 9:
            ambient = QVector3D(0.329412,0.223529,0.027451);
            diffuse = QVector3D(0.780392,0.568627,0.113725);
            specular = QVector3D(0.992157,0.941176,0.807843);
            shinisses = 0.21794872;
            break;
        case 10:
            ambient = QVector3D(0.25,0.25,0.25);
            diffuse = QVector3D(0.4,0.4,0.4);
            specular = QVector3D(0.774597,0.774597,0.774597);
            shinisses = 0.6;
            break;
        case 11:
            ambient = QVector3D(0.19125,0.0735,0.0225);
            diffuse = QVector3D(0.7038,0.27048,0.0828);
            specular = QVector3D(0.256777,0.137622,0.086014);
            shinisses = 0.1;
            break;
        case 12:
            ambient = QVector3D(0.0,0.0,0.0);
            diffuse = QVector3D(0.01,0.01,0.01);
            specular = QVector3D(0.50,0.50,0.50);
            shinisses = 0.25;
            break;
        case 13:
            ambient = QVector3D(0.0,0.1,0.06);
            diffuse = QVector3D(0.0,0.50980392,0.50980392);
            specular = QVector3D(0.50196078,0.50196078,0.50196078);
            shinisses = 0.25;
            break;
        case 14:
            ambient = QVector3D(0.0,0.0,0.0);
            diffuse = QVector3D(0.1,0.35,0.1);
            specular = QVector3D(0.45,0.55,0.45);
            shinisses = 0.25;
            break;
        case 15:
            ambient = QVector3D(0.0,0.0,0.0);
            diffuse = QVector3D(0.5,0.0,0.0);
            specular = QVector3D(0.7,0.6,0.6);
            shinisses = 0.25;
            break;
        case 16:
            ambient = QVector3D(0.0,0.0,0.0);
            diffuse = QVector3D(0.55,0.55,0.55);
            specular = QVector3D(0.70,0.70,0.70);
            shinisses = 0.25;
            break;
        case 17:
            ambient = QVector3D(0.0,0.0,0.0);
            diffuse = QVector3D(0.5,0.5,0.0);
            specular = QVector3D(0.60,0.60,0.50);
            shinisses = 0.25;
            break;
        case 18:
            ambient = QVector3D(0.02,0.02,0.02);
            diffuse = QVector3D(0.01,0.01,0.01);
            specular = QVector3D(0.4,0.4,0.4);
            shinisses = 0.078125;
            break;
        case 19:
            ambient = QVector3D(0.0,0.05,0.05);
            diffuse = QVector3D(0.4,0.5,0.5);
            specular = QVector3D(0.04,0.7,0.7);
            shinisses = 0.078125;
            break;
        case 20:
            ambient = QVector3D(0.0,0.05,0.0);
            diffuse = QVector3D(0.4,0.5,0.4);
            specular = QVector3D(0.04,0.7,0.04);
            shinisses = 0.078125;
            break;
        case 21:
            ambient = QVector3D(0.05,0.0,0.0);
            diffuse = QVector3D(0.5,0.4,0.4);
            specular = QVector3D(0.7,0.04,0.04);
            shinisses = 0.078125;
            break;
        case 22:
            ambient = QVector3D(0.05,0.05,0.05);
            diffuse = QVector3D(0.5,0.5,0.5);
            specular = QVector3D(0.7,0.7,0.7);
            shinisses = 0.078125;
            break;
        default:
            ambient = QVector3D(0.05,0.05,0.0);
            diffuse = QVector3D(0.5,0.5,0.4);
            specular = QVector3D(0.7,0.7,0.04);
            shinisses = 0.078125;
            break;

    }
    material.Ambient=ambient;
    material.Diffuse=diffuse;
    material.Specular=specular;
    material.shininess=shinisses*50;

}
void lighting::install_Lights()
{
    currentLightPos = QVector3D(QVector4D(lightLoc,1.0));
   
}
QVector3D lighting::getLightLoc()
{
    return lightLoc;
}
void lighting::setLightPosition(QVector3D posicion)
{
    light.position = posicion;
}

QVector4D lighting::getLightAmbient()
{
    return light.Ambient;
}

QVector4D lighting::getLightDiffuse()
{
    return light.Diffuse;
}

QVector4D lighting::getLightSpecular()
{
    return light.Specular;
}

QVector3D lighting::getLightPosition()
{
    return light.position;
}

QVector4D lighting::getMaterialAmbient()
{
    return material.Ambient;
}

QVector4D lighting::getMaterialDiffuse()
{
    return material.Diffuse;
}

QVector4D lighting::getMaterialSpecular()
{
    return material.Specular;
}

float lighting::getMaterialShininess()
{
    return material.shininess;
}

QVector4D lighting::getGlobalAmbient()
{
    return global_Ambient;
}

QVector3D lighting::getCurrentLightPos()
{
    return currentLightPos;
}
