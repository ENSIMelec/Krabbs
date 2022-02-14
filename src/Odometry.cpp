//
// Created by Tom on 10/02/2022.
//

#include "Odometry.h"

using namespace std;

Odometry::Odometry(SerialCodeurManager codeurs, Config conf) : codeurs(codeurs) {

    cout << "Initializing Odometry ... ";

    //Récupération des différents coef de PID configuré dans le fichier config
    CoeffGLong =  conf.getCoeffGLong();
    CoeffDLong =  conf.getCoeffDLong();

    CoeffAnglD = conf.getCoeffAnglD();
    CoeffAnglG = conf.getCoeffAnglG();

    cout << "done." << endl;
}

void Odometry::init() {
    if(initialized) return;

    x = 0;
    y = 0;
    angle = 0;

    initialized = true;
}

void Odometry::update() {
    // Initialize the values on the fist update
    init();

    codeurs.readAndReset();

    comptG = codeurs.getLeftTicks();
    comptD = codeurs.getRightTicks();

    ticksG += comptG;
    ticksD += comptD;

    //Temps entre deux appelle de ticks
    //Permet le calcul de la vitesse
    tempsLast = codeurs.getTime();

    //cout <<"Data codeur : "<<comptG<<" "<<comptD<<" "<<tempsLast<<endl;
    // Calcul vitesse
    if(tempsLast!=0){
        vitG = (comptG * CoeffGLong)/(tempsLast*0.000001);
        vitD = (comptD * CoeffDLong)/(tempsLast*0.000001);
    }else{
        vitG = 0;
        vitD = 0;
    }


    //Calcul de la distance parcourue
    mesure_dist = (comptD * CoeffDLong + comptG * CoeffGLong) / 2;
    //cout << "Distance: "<< mesure_dist<<endl;

    //Calcul des déplacements élémentaires
    dX = mesure_dist * sin(angle * M_PI / 180);
    dY = mesure_dist * cos(angle * M_PI / 180);

    //Intégration pour avoir la nouvelle position
    x = x + dX;
    y = y + dY;

    //Calcul de l'angle réalisé
    //mesure_angle = CoeffAnglG*comptG-CoeffAnglD*comptD;
    mesure_angle = CoeffGLong * comptG - CoeffDLong * comptD;
    angle += atan(mesure_angle/240) * 180 / M_PI;

    if(angle < -180) {
        angle += 360;
    }

    if(angle > 180) {
        angle -= 360;
    }
}

string Odometry::getPositionStr() {
    return "X: " + to_string(x) + "\tY: " + to_string(y) + "\tAngle: " + to_string(angle);

}

