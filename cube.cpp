/* LO13-Marine-Rixte.cpp */

#include<GL/glut.h>
#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "structures.h"
#include "normales.h"
#include "lectureMesh.h"

#define PIXEL_TO_RADIAN 0.005

/* Variable globale msh pour le cube */
Mesh msh;
opengl ogl;

/*void Cube(void)
{
	//définition des sommets 
	msh.sommets[0][0] = 0.0;
	msh.sommets[0][1] = 0.0;
	msh.sommets[0][2] = 0.0;

	msh.sommets[1][0] = 1.0;
	msh.sommets[1][1] = 0.0;
	msh.sommets[1][2] = 0.0;

	msh.sommets[2][0] = 1.0;
	msh.sommets[2][1] = 1.0;
	msh.sommets[2][2] = 0.0;

	msh.sommets[3][0] = 0.0;
	msh.sommets[3][1] = 1.0;
	msh.sommets[3][2] = 0.0;

	msh.sommets[4][0] = 0.0;
	msh.sommets[4][1] = 0.0;
	msh.sommets[4][2] = 1.0;

	msh.sommets[5][0] = 1.0;
	msh.sommets[5][1] = 0.0;
	msh.sommets[5][2] = 1.0;

	msh.sommets[6][0] = 1.0;
	msh.sommets[6][1] = 1.0;
	msh.sommets[6][2] = 1.0;

	msh.sommets[7][0] = 0.0;
	msh.sommets[7][1] = 1.0;
	msh.sommets[7][2] = 1.0;

	//définition de triangles

	msh.triangles[0][0] = 1;
	msh.triangles[0][1] = 2;
	msh.triangles[0][2] = 5;

	msh.triangles[1][0] = 2;
	msh.triangles[1][1] = 6;
	msh.triangles[1][2] = 5;

	msh.triangles[2][0] = 2;
	msh.triangles[2][1] = 7;
	msh.triangles[2][2] = 6;

	msh.triangles[3][0] = 2;
	msh.triangles[3][1] = 3;
	msh.triangles[3][2] = 7;

	msh.triangles[4][0] = 0;
	msh.triangles[4][1] = 4;
	msh.triangles[4][2] = 3;

	msh.triangles[5][0] = 3;
	msh.triangles[5][1] = 4;
	msh.triangles[5][2] = 7;

	msh.triangles[6][0] = 0;
	msh.triangles[6][1] = 1;
	msh.triangles[6][2] = 4;

	msh.triangles[7][0] = 1;
	msh.triangles[7][1] = 5;
	msh.triangles[7][2] = 4;

	msh.triangles[8][0] = 0;
	msh.triangles[8][1] = 3;
	msh.triangles[8][2] = 1;

	msh.triangles[9][0] = 3;
	msh.triangles[9][1] = 2;
	msh.triangles[9][2] = 1;

	msh.triangles[10][0] = 5;
	msh.triangles[10][1] = 7;
	msh.triangles[10][2] = 6;

	msh.triangles[11][0] = 5;
	msh.triangles[11][1] = 7;
	msh.triangles[11][2] = 4;
}*/

void InitParametresOpenGL()
{
	/*initialisation de la fenêtre graphique*/
	ogl.cfgx = 100;
	ogl.cfgy = 100;
	ogl.lfg = 500;
	ogl.hfg = 500;

	/*LookAt*/
	ogl.ox = 3.0;
	ogl.oy = 4.0;
	ogl.oz = 2.0;
	ogl.fx = 0.5;
	ogl.fy = 0.5;
	ogl.fz = 0.5;
	ogl.vx = 0.0;
	ogl.vy = 0.0;
	ogl.vz = 1.0;

	/*gjFrustrum*/

	ogl.umin = -2;
	ogl.umax = 2;
	ogl.vmin = -2;
	ogl.vmax = 2;
	ogl.dmin = 3.0;
	ogl.dmax = 100.0;

	/*Reshap*/

	ogl.fu = 1.0;
	ogl.fv = 1.0;

	/*Zoom*/

	ogl.fzoom = 1.0;

	/*Matrice*/

	ogl.theta_u = 0.;
	ogl.theta_v = 0.;
	ogl.trans_u = 0.;
	ogl.trans_v = 0.;

	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			int k = 4 * i + j;
			if (i == j)
			{
				ogl.tg[k] = 1;
			}
			else
			{
				ogl.tg[k] = 0;
			}
		}
	}
	/*Tansformation*/
	ogl.focalu = 0.;
	ogl.focalv = 0.;

	float OvFx, OvFy, OvFz;
	OvFx = ogl.fx - ogl.ox;
	OvFy = ogl.fy - ogl.oy;
	OvFz = ogl.fz - ogl.oz;

	ogl.focaln = -sqrtf(OvFx * OvFx + OvFy * OvFy + OvFz * OvFz);

	/*Mode vue*/
	ogl.mode_trace = 0;

	//Source lumière
	ogl.src.position[0]= 1.0;
	ogl.src.position[1] = 1.0;
	ogl.src.position[2] = 1.0;
	ogl.src.position[3] = 0.0;
	//Sa
	ogl.src.ambient[0] = 1.0;
	ogl.src.ambient[1] = 1.0;
	ogl.src.ambient[2] = 1.0;
	ogl.src.ambient[3] = 1.0;
	//Sd
	ogl.src.diffuse[0] = 1.0;
	ogl.src.diffuse[1] = 1.0;
	ogl.src.diffuse[2] = 1.0;
	ogl.src.diffuse[3] = 1.0;
	//Ss
	ogl.src.specular[0] = 1.0;
	ogl.src.specular[1] = 1.0;
	ogl.src.specular[2] = 1.0;
	ogl.src.specular[3] = 1.0;

	//------------ Définition des matérieux-----------------

	//Chrome (je n'ai pas réussit à trouver la valeur pour l'acier)

	ogl.steel.ambient[0] = 0.25;
	ogl.steel.ambient[1] = 0.25;
	ogl.steel.ambient[2] = 0.25;
	ogl.steel.ambient[3] = 1.0;

	ogl.steel.diffuse[0] = 0.4;
	ogl.steel.diffuse[1] = 0.4;
	ogl.steel.diffuse[2] = 0.4;
	ogl.steel.diffuse[3] = 1.0;

	ogl.steel.specular[0] = 0.774597;
	ogl.steel.specular[1] = 0.774597;
	ogl.steel.specular[2] = 0.774597;
	ogl.steel.specular[3] = 1.0;

	ogl.steel.shininess = 76.8;

	//Cuivre

	ogl.copper.ambient[0] = 0.256777;
	ogl.copper.ambient[1] = 0.13762;
	ogl.copper.ambient[2] = 0.086014;
	ogl.copper.ambient[3] = 1.0;
	   	 
	ogl.copper.diffuse[0] = 0.19125;
	ogl.copper.diffuse[1] = 0.0735;
	ogl.copper.diffuse[2] = 0.0225;
	ogl.copper.diffuse[3] = 1.0;
	   	 
	ogl.copper.specular[0] = 0.7038;
	ogl.copper.specular[1] = 0.27048;
	ogl.copper.specular[2] = 0.0828;
	ogl.copper.specular[3] = 1.0;
	   
	ogl.copper.shininess = 12.8;

	//Red plastic

	ogl.plastic.ambient[0] = 0.0;
	ogl.plastic.ambient[1] = 0.0;
	ogl.plastic.ambient[2] = 0.0;
	ogl.plastic.ambient[3] = 1.0;
		
	ogl.plastic.diffuse[0] = 0.5;
	ogl.plastic.diffuse[1] = 0.0;
	ogl.plastic.diffuse[2] = 0.0;
	ogl.plastic.diffuse[3] = 1.0;

	ogl.plastic.specular[0] = 0.7;
	ogl.plastic.specular[1] = 0.6;
	ogl.plastic.specular[2] = 0.6;
	ogl.plastic.specular[3] = 0.0;
		
	ogl.plastic.shininess = 32.0;

	//Initialisation des matériaux

	ogl.mat = &(ogl.plastic);
	ogl.materiau = 0;
}
void EffacerEcran(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void ViderMemoireGraphique(){
		glutSwapBuffers();
}											  
void MatriceProjection(void)				  
{											  
	glMatrixMode(GL_PROJECTION);			  
	glLoadIdentity();						  
	glFrustum(								  
		(double)ogl.fzoom *(double) ogl.fu * (double)ogl.umin, 
		(double)ogl.fzoom *(double) ogl.fu * (double)ogl.umax, 
		(double)ogl.fzoom *(double) ogl.fv * (double)ogl.vmin,
		(double)ogl.fzoom *(double) ogl.fv * (double)ogl.vmax,
		ogl.dmin, ogl.dmax);
}
void InitialisationEnvironnementOpenGL(void)
{
	/* définition de la couleur du fond */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	/* définition de la couleur courante */
	glColor3f(0.0, 0.0, 1.0);
	/* définition de l’instance GL_PROJECTION via une procédure utilisateur */
	MatriceProjection();
}
void MatriceModelVue(void)
{
	/* pointer la matrice courante sur l’instance GL_MODELVIEW */
	glMatrixMode(GL_MODELVIEW);
	/* Initialiser la matrice courante avec l’identité */
	glLoadIdentity();
	/* Appliquer la dernière transformation géométrique */
	if (ogl.flag_geom == 1)
	{
		glTranslatef(ogl.focalu, ogl.focalv, ogl.focaln); //transaltion de F à sa position d'origine dans le repère de vue
		glRotatef(ogl.theta_u, 1., 0., 0.);
		glRotatef(ogl.theta_v, 0., 1., 0.);
		glTranslatef(-ogl.focalu, -ogl.focalv, -ogl.focaln); //translation de F sur Ov dans le repère de vue
	}
	else if (ogl.flag_geom == 2)
	{
		glTranslatef(ogl.trans_u, ogl.trans_v, 0.0); /* translation dans le plan de vue */
		/* mise à jour des coordonnées du point focal dans le repère de vue */
		ogl.focalu += ogl.trans_u;
		ogl.focalv += ogl.trans_v;
	}
	
	/* Appliquer toutes les transformations géométriques antécédentes */
	glMultMatrixf(ogl.tg);
	/* Mettre à jour l’historique des transformations géométriques */
	glGetFloatv(GL_MODELVIEW_MATRIX, ogl.tg);
	/* Appliquer le changement de repère */
	gluLookAt(ogl.ox, ogl.oy, ogl.oz, ogl.fx, ogl.fy, ogl.fz, ogl.vx, ogl.vy, ogl.vz);
}

//Triatement de sources de lumière
void ActivationSource(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, ogl.src.position);
	glPopMatrix();
	glLightfv(GL_LIGHT0, GL_AMBIENT, ogl.src.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, ogl.src.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, ogl.src.specular);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}
void DesactivationSource(void)
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
}
void AffectationMateriau(void)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (ogl.mat)->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (ogl.mat)->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (ogl.mat)->specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, (ogl.mat)->shininess);
}

// Mode de tracés filaire avec traitement des parties cachées
void ZbufferActivation(void)
{
	glEnable(GL_DEPTH_TEST);
}
void ZbufferDesactivation(void)
{
	glDisable(GL_DEPTH_TEST);
}
void DecalageArriereActivation(void)
{
	glPolygonOffset(1.0, 1.0);

	//décalage arrière pour le remplissage
	glEnable(GL_POLYGON_OFFSET_FILL);
}
void DecalageArriereDesactivation(void)
{
	glDisable(GL_POLYGON_OFFSET_FILL);
}

//---------------------------Tracé avec ombrage --------------------------------------------------------

void ObjetOmbrageConstant(void)
{
	int i, j;
	float xn, yn, zn, x, y ,z;
	
	glShadeModel(GL_FLAT); /* mode ombrage constant */
	glBegin(GL_TRIANGLES);
	for (j = 0; j < msh.number_of_triangles; j++)
	{
		xn = msh.normal_t[3*j];
		yn = msh.normal_t[3*j + 1];
		zn = msh.normal_t[3*j + 2];
		glNormal3f(xn, yn, zn); //les coordonnées de la normale au triangle j 

		for (i = 0; i < 3; i++)
		{
			x = msh.vertices[3 * msh.triangles[3 * j + i] + 0];
			y = msh.vertices[3 * msh.triangles[3 * j + i] + 1];
			z = msh.vertices[3 * msh.triangles[3 * j + i] + 2];
			glVertex3f(x, y, z); //les coordonnées du sommet i du triangle j 
		}
	}
	glEnd();
	DesactivationSource();
}
void ObjetOmbragePhong(void)
{
	int i, j;
	float xn, yn, zn, x, y, z;
	
	glShadeModel(GL_SMOOTH); /* mode ombrage de Phong */
	glBegin(GL_TRIANGLES);
	for (j = 0; j < msh.number_of_triangles; j++)
	{
		for (i = 0; i < 3; i++)
		{
			xn = msh.normal_v[3 * msh.triangles[3 * j + i] + 0];
			yn = msh.normal_v[3 * msh.triangles[3 * j + i] + 1];
			zn = msh.normal_v[3 * msh.triangles[3 * j + i] + 2];
			glNormal3f(xn, yn, zn); // coordonnées de la normale du sommet i du triangle j 

			x = msh.vertices[3 * msh.triangles[3 * j + i] + 0];
			y = msh.vertices[3 * msh.triangles[3 * j + i] + 1];
			z = msh.vertices[3 * msh.triangles[3 * j + i] + 2];
			glVertex3f(x, y, z); //les coordonnées du sommet i du triangle j 
		}
	}
	glEnd();
	DesactivationSource();
}
void TraceObjetOmbrage(int mode) {	// mode = 1 -> Ombrage constant sur les arrêtes
									// mode = 2 -> Ombrage contant remplissage
									// mode = 3 -> Ombrage Phong sur les arrêtes 
									// mode = 4 -> Ombrage Phong remplissage

	ActivationSource();
	AffectationMateriau();

	if (mode == 1) {

		/*Ombrage constant*/
		glShadeModel(GL_FLAT);
		/*Mode de tracer*/
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		ObjetOmbrageConstant();
	}
	else if (mode == 2)
	{
		/*Ombrage constant*/
		glShadeModel(GL_FLAT);
		/*Mode de tracer*/
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		ObjetOmbrageConstant();
	}
	else if (mode == 3)
	{
		/*Ombrage de Phong*/
		glShadeModel(GL_SMOOTH);
		/*Mode de tracer*/
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		ObjetOmbragePhong();
	}
	else if (mode == 4)
	{
		/*Ombrage de Phong*/
		glShadeModel(GL_SMOOTH);
		/*Mode de tracer*/
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		ObjetOmbragePhong();
	}
}

//--------------------------Tracé basiques--------------------------------------------------------------

void Palette()
{
	int i, j;
	float x, y, z;

	// Tracé des triangles 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// mode GL_TRIANGLES : trois sommets consécutives sont connectés pour former un triangle 
	glBegin(GL_TRIANGLES);

	for (j = 0; j < msh.number_of_triangles; j++)
	{
		/* groupe des trois sommets du triangles i pour former un triangle */
		for (i = 0; i < 3; i++)
		{
			//coordonnée du sommet i du triangle j
			x = msh.vertices[3 * msh.triangles[3 * j + i] + 0];
			y = msh.vertices[3 * msh.triangles[3 * j + i] + 1];
			z = msh.vertices[3 * msh.triangles[3 * j + i] + 2];
			glVertex3f(x, y, z);
			glColor3f(x, y, z);
		}
	}
	glEnd();
}
void TraceObjetBase()
{
	int i, j, k;
	float x, y, z;

	/* Tracé des triangles */
	/* mode GL_TRIANGLES : trois sommets consécutives sont connectés pour former un
   triangle */
	glBegin(GL_TRIANGLES);

	for (j = 0; j < msh.number_of_triangles; j++)
	{
		/* groupe des trois sommets du triangles j pour former un triangle */
		for (i = 0; i < 3; i++)
		{
				x = msh.vertices[3 * msh.triangles[3 * j + i] + 0];
				y = msh.vertices[3 * msh.triangles[3 * j + i] + 1];
				z = msh.vertices[3 * msh.triangles[3 * j + i] + 2];
				glVertex3f(x, y, z);		
		}
	}
	glEnd();
}
void TraceObjet(float R, float G, float B, int mode) { // mode : "1" pour contour et "2" pour remplissage

	if (mode == 1) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(R, G, B);
		TraceObjetBase();
	}
	else if (mode == 2)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(R, G, B);
		TraceObjetBase();
	}
}

/*évènement recadrage de la fenêtre graphique*/
void reshape(int lfg, int hfg)
{
	double ratio = (double) hfg / (double)lfg;
	if (ratio > 1) {
		ogl.fu = 1.;
		ogl.fv = ratio;

	}else{
		ogl.fu = 1./ratio;
		ogl.fv = 1.;
	}

	MatriceProjection();
	glutPostRedisplay();
	glViewport(0, 0, lfg, hfg);
}

/*évènement clavier*/
void keyboard(unsigned char c, int x, int y)
{
	
	if (c == 'm') {
		
		ogl.materiau++;
		if (ogl.materiau == 0) {
			ogl.mat = &(ogl.plastic);
			glutPostRedisplay();
		}
		else if (ogl.materiau == 1) {
			ogl.mat = &(ogl.copper);
			glutPostRedisplay();
		}
		if (ogl.materiau == 2) {
			ogl.mat = &(ogl.steel);
			glutPostRedisplay();
			ogl.materiau = -1;
		}

	}
	else if (c == 'q' || c == 'Q')
	{		
		exit(0);
	}
	else if (c == 'z')
	{
		/*diminuer ogl.fzoom*/
		ogl.fzoom -= 0.1;
		MatriceProjection();
		glutPostRedisplay();
	}
	else if (c == 'd')
	{
		//augmenter ogl.fzoom

		ogl.fzoom += 0.1;
		MatriceProjection();
		glutPostRedisplay();
		
	}
	else if (c == 'i')
	{
		/*initialisation de la fenêtre graphique*/
		ogl.cfgx = 100;
		ogl.cfgy = 100;
		ogl.lfg = 500;
		ogl.hfg = 500;

		/*gjFrustrum*/

		ogl.umin = -2;
		ogl.umax = 2;
		ogl.vmin = -2;
		ogl.vmax = 2;
		ogl.dmin = 3.0;
		ogl.dmax = 100.0;

		/*Zoom*/

		ogl.fzoom = 1.0;

		/*Matrice*/

		ogl.theta_u = 0.;
		ogl.theta_v = 0.;
		ogl.trans_u = 0.;
		ogl.trans_v = 0.;

		int i, j;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				int k = 4 * i + j;
				if (i == j)
				{
					ogl.tg[k] = 1;
				}
				else
				{
					ogl.tg[k] = 0;
				}
			}
		}
		/*Tansformation*/
		ogl.focalu = 0.;
		ogl.focalv = 0.;

		float OvFx, OvFy, OvFz;
		OvFx = ogl.fx - ogl.ox;
		OvFy = ogl.fy - ogl.oy;
		OvFz = ogl.fz - ogl.oz;

		ogl.focaln = -sqrtf(OvFx * OvFx + OvFy * OvFy + OvFz * OvFz);

		MatriceProjection();
		glutPostRedisplay();
	}
	else if (c == '0')
	{
		ogl.mode_trace = 0;
		glutPostRedisplay();
	}
	else if (c == '1')
	{
		ogl.mode_trace = 1;
		glutPostRedisplay();
	}
	else if (c == '2')
	{
		ogl.mode_trace = 2;
		glutPostRedisplay();
	}
	else if (c == '3')
	{
		ogl.mode_trace = 3;
		glutPostRedisplay();
	}
	else if (c == '4')
	{
		ogl.mode_trace = 4;
		glutPostRedisplay();
	}
	else if (c == '5')
	{
		ogl.mode_trace = 5;
		glutPostRedisplay();
	}
	else if (c == '6')
	{
		ogl.mode_trace = 6;
		glutPostRedisplay();
	}
	else if (c == '7')
	{
		ogl.mode_trace = 7;
		glutPostRedisplay();
	}
	else if (c == '8')
	{
		ogl.mode_trace = 8;
		glutPostRedisplay();
	}
	else if (c == '9')
	{
		ogl.mode_trace = 9;
		glutPostRedisplay();
	}
}

/*évènement souris statique*/
void mouse(int button, int state, int x, int y)
{
	/* positionner le flag flag_geom */
	if (state == GLUT_UP)
	{
		ogl.flag_geom = 0;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		ogl.flag_geom = 1;
		// stocker la position de la souris 
		ogl.six = x;
		ogl.siy = y;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		/* translation */
		ogl.flag_geom = 2;
		/* stocker la position de la souris */
		ogl.six = x;
		ogl.siy = y;
	}
}

/*évènement souris dynamique*/
void motion(int x, int y)
{
	/* déclaration du vecteur de déplacement de la souris */
	int vx, vy;
	/* calcule du vecteur de déplacement */
	vx = x - ogl.six;
	vy = ogl.siy - y; /* pourquoi ? */
	/* mettre à jour la position initiale de la souris */
	ogl.six = x;
	ogl.siy = y;
	/* cas échéant déclencher la rotation */
	if (ogl.flag_geom == 1)
	{
		/* transformer vx et vy en theta_v et theta_u */
		ogl.theta_u +=PIXEL_TO_RADIAN * vx;
		ogl.theta_v += PIXEL_TO_RADIAN * vy;

		/* redessiner */
			glutPostRedisplay();
	}
	else if (ogl.flag_geom == 2)
	{
		float tu, tv;
		/* transformer vx et vy en trans_u et trans_v */
		
		tu = (vx * ogl.fu * (ogl.umin - ogl.umax)) / (ogl.lfg * ogl.fzoom);
		tv = (vy * ogl.fv * (ogl.vmin - ogl.vmax)) / (ogl.hfg * ogl.fzoom);

		ogl.trans_u = 0.01 * (tu * ogl.focaln) / ogl.dmin;
		ogl.trans_v = 0.01 * (tv * ogl.focaln) / ogl.dmin;
		
		/* redessiner */
			glutPostRedisplay();
	}
}

void display(void)
{
	/* effacer l’écran */
	EffacerEcran();
	/* Définir l’instance GL_MODELVIEW via une procédure utilisateur */
	MatriceModelVue();
	/* Tracé du modèle en mémoire via une procédure utilisateur */
	
	//Tracé fillaire couleur unie sans traitement des parties cachées
	if (ogl.mode_trace == 0) {
		TraceObjet(1.0, 0.0, 0.0, 1);
	}
	
	//Tracé filaire couleur unie avec traitement des parties cachées
	else if (ogl.mode_trace == 1)
	{
		ZbufferActivation();
		TraceObjet(1.0, 0.0, 0.0, 1);
		DecalageArriereActivation();
		TraceObjet(0.0, 0.0, 0.0, 2);
		DecalageArriereDesactivation();
		ZbufferDesactivation();
	}

	//remplissage couleurs en dégradé avec traitement des paries cachée
	else if (ogl.mode_trace == 2)
	{
		ZbufferActivation();
		Palette();
		ZbufferDesactivation();
	}

	//remplissage couleurs unie, contour dans une autre couleur unie, avec le traitement des parties cachées
	else if (ogl.mode_trace == 3)
	{
		ZbufferActivation();
		TraceObjet(0.0, 0.0, 0.0, 1);
		DecalageArriereActivation();
		TraceObjet(1.0, 0.0, 0.0, 2);
		DecalageArriereDesactivation();
		ZbufferDesactivation();
	}
	//Ombrage constant sur les éléments avec traitement des parties cachées
	else if (ogl.mode_trace == 4)
	{
		ZbufferActivation();
		TraceObjetOmbrage(2);
		ZbufferDesactivation();
	}
	//Ombrage constant uniquement sur les arêtes avec le traîtement des parties cachées
	else if (ogl.mode_trace == 5)
	{
		ZbufferActivation();
		TraceObjetOmbrage(1);
		DecalageArriereActivation();
		TraceObjet(0.0, 0.0, 0.0, 2);
		DecalageArriereDesactivation();
		ZbufferDesactivation();
	}
	//Ombrage constant sur les éléments et couleur unie pour les arêtes avec traîtement des parties cachées
	else if (ogl.mode_trace == 6)
	{
		ZbufferActivation();
		TraceObjet(0.0, 0.0, 0.0, 1);
		DecalageArriereActivation();
		TraceObjetOmbrage(2);
		DecalageArriereDesactivation();
		ZbufferDesactivation();
	}
	// Ombrage de Phong sur les éléments avec traitement des parties cachées
	else if (ogl.mode_trace == 7)
	{
		ZbufferActivation();
		TraceObjetOmbrage(4);
		ZbufferDesactivation();
	}
	//Ombrage de Phong uniquement sur les arêtes avec le traitement des parties cachées
	else if (ogl.mode_trace == 8)
	{
		ZbufferActivation();
		TraceObjetOmbrage(3);
		DecalageArriereActivation();
		TraceObjet(0.0, 0.0, 0.0, 2);
		DecalageArriereDesactivation();
		ZbufferDesactivation();
	}
	// Ombrage de Phong sue les éléments et couleur unie pour les arêtes avec le traitement des parties cachées
	else if (ogl.mode_trace == 9)
	{
		ZbufferActivation();
		TraceObjet(0.0, 0.0, 0.0, 1);
		DecalageArriereActivation();
		TraceObjetOmbrage(4);
		DecalageArriereDesactivation();
		ZbufferDesactivation();
	}

	//Envoie de la mémoire sur l’écran 
	ViderMemoireGraphique();
}

int main(int argc, char** argv)
{
	/* Initialiser la librairie graphique */
	glutInit(&argc, argv);
	/* Définir la géométrie */
	//Cube();
	ModelDiscret(&msh, argv);
	InitParametresOpenGL();
	/* Définir la fenêtre graphique */
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ogl.lfg, ogl.hfg);
	glutInitWindowPosition(ogl.cfgx, ogl.cfgy);
	/* initialiser l’environnement OpenGL */

	glutCreateWindow("Mesh");
	InitialisationEnvironnementOpenGL();
	
	/* Liste des événements */
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	/* Boucle infinie */
	glutMainLoop();

	return(0);

}