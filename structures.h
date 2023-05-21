#pragma once

#include<GL/glut.h>

/*typedef struct mesh
{
	float sommets[8][3];
	int triangles[12][3];
} Mesh;*/

typedef struct source {
	float position[4];
	float ambient[4];
	float diffuse[4];
	float specular[4];
} Source;

typedef struct material
{
	float ambient[4]; //Ka
	float diffuse[4]; //Kd
	float specular[4]; //ks
	float shininess; //ns
} Material;

typedef struct opengl
{
	/*fenêtre graphique*/
	int cfgx, cfgy, lfg, hfg;

	/*Système de vue*/
	float umin, umax, vmin, vmax, dmin, dmax; //glFrustrum
	float ox, oy, oz, fx, fy, fz, vx, vy, vz; //gluLookAt
	float fu, fv; //reshape
	float fzoom;
	float tg[16];

	/*Transformations géométriques*/
	float theta_u, theta_v, tu, tv, tn;

	/*Mouse*/
	int flag_geom, six, siy; //statique

	/*Pooint focal*/
	float focalu, focalv, focaln;

	/*Translation*/
	float trans_u, trans_v;

	/*Tracé*/
	int mode_trace;

	// Source lumière
	Source src;

	//matérieux
	Material steel, copper, plastic, * mat;
	int materiau;

} Opengl;

typedef struct mesh {
	int		number_of_vertices;		    /* nombre de sommets */
	float* vertices;					/* liste des coordonnees des sommets*/
	float* normal_v;					/* liste des normales aux sommets*/
	int		number_of_triangles;		/* nombre de triangles */
	int* triangles;					/* liste des sommets des triangles */
	float* alpha_t;					/* liste des angles aux sommets*/
	float* normal_t;					/* liste des normales aux faces triangulaires*/
	float	ccenter[3];					/* coordonnees du centre de la boite englobante */
	float	cmin[3], cmax[3];			/* coordonnees min et max de la boite englobante */
	float	delta;						/* taille maximale de la boite englobante suivant les axes */
	int		memory;						/* memoire allouee pour la structure mesh */
	int		error;						/* arret du programme si error est non nul */
} Mesh;