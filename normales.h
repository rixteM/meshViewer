#pragma once


double NormSquare(float vect[3]);

double Norm(float vect[3]);

double DotProduct(float vect1[3], float vect2[3]);

void CrossProduct(float vect1[3], float vect2[3], float* result);

//calcul l'angle entre les vecteurs (point2,point1) et (point2,point3)
double Angle(float point1[3], float point2[3], float point3[3]);
