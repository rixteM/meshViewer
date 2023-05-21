#include "normales.h"
#include <math.h>

double NormSquare(float vect[3])
{
	return((vect[0] * vect[0]) + (vect[1] * vect[1]) + (vect[2] * vect[2]));
}
double Norm(float vect[3])
{
	return(sqrt(NormSquare(vect)));
}
double DotProduct(float vect1[3], float vect2[3])
{
	return((vect1[0] * vect2[0]) + (vect1[1] * vect2[1]) + (vect1[2] * vect2[2]));
}
void CrossProduct(float vect1[3], float vect2[3], float* result)
{
	double        norme;

	result[0] = (vect1[1] * vect2[2]) - (vect1[2] * vect2[1]);
	result[1] = (vect1[2] * vect2[0]) - (vect1[0] * vect2[2]);
	result[2] = (vect1[0] * vect2[1]) - (vect1[1] * vect2[0]);
	norme = Norm(result); /*normalisation du produit vectoriel*/
	if (norme != 0.0)
	{
		result[0] = (float)(result[0] / norme);
		result[1] = (float)(result[1] / norme);
		result[2] = (float)(result[2] / norme);
	}
}
double Angle(float point1[3], float point2[3], float point3[3]) /* calcul l'angle entre les vecteurs (point2,point1) et (point2,point3) */
{
	double        angle, d;
	float         v1[3], v2[3];
	int           i;

	for (i = 0; i < 3; i++)
	{
		v1[i] = point1[i] - point2[i];
		v2[i] = point3[i] - point2[i];
	}
	d = DotProduct(v1, v2);
	if (d > 1.0)
		d = 1.0;
	else if (d < -1.0)
		d = -1.0;
	angle = acos(d / sqrt(NormSquare(v1) * NormSquare(v2)));
	return(angle);
}
