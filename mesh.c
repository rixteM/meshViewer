/**********  structure mesh **********/

typedef struct mesh {
  int		number_of_vertices;		    /* nombre de sommets */
  float		*vertices;					/* liste des coordonnees des sommets*/
  float		*normal_v;					/* liste des normales aux sommets*/	
  int		number_of_triangles;		/* nombre de triangles */
  int		*triangles;					/* liste des sommets des triangles */
  float		*alpha_t;					/* liste des angles aux sommets*/
  float		*normal_t;					/* liste des normales aux faces triangulaires*/
  float		ccenter[3];					/* coordonnees du centre de la boite englobante */
  float		cmin[3], cmax[3];			/* coordonnees min et max de la boite englobante */
  float		delta;						/* taille maximale de la boite englobante suivant les axes */
  int		memory;						/* memoire allouee pour la structure mesh */
  int		error;						/* arret du programme si error est non nul */
} Mesh;


/********** Proc�dures pour la lecture et la normalisation du maillage et le calcul des normales **********/

double NormSquare(float vect[3])
{
  return((vect[0]*vect[0]) + (vect[1]*vect[1]) + (vect[2]*vect[2]));
}

double Norm(float vect[3])
{
  return(sqrt(NormSquare(vect)));
}


double DotProduct(float vect1[3], float vect2[3])
{
  return((vect1[0]*vect2[0]) + (vect1[1]*vect2[1]) + (vect1[2]*vect2[2]));
}


void CrossProduct(float vect1[3], float vect2[3], float *result)
{
  double        norme;
  
  result[0] = (vect1[1]*vect2[2]) - (vect1[2]*vect2[1]);
  result[1] = (vect1[2]*vect2[0]) - (vect1[0]*vect2[2]);
  result[2] = (vect1[0]*vect2[1]) - (vect1[1]*vect2[0]);
  norme = Norm(result); /*normalisation du produit vectoriel*/
  if (norme != 0.0)
  {
    result[0] = (float)(result[0]/norme);
    result[1] = (float)(result[1]/norme);
    result[2] = (float)(result[2]/norme);
  }
}


double Angle(float point1[3], float point2[3], float point3[3]) /* calcul l'angle entre les vecteurs (point2,point1) et (point2,point3) */
{
  double        angle, d;
  float         v1[3], v2[3];
  int           i;

  for (i=0; i<3; i++)
  {
    v1[i] = point1[i] - point2[i];
    v2[i] = point3[i] - point2[i];
  }
  d = DotProduct(v1, v2);
  if (d > 1.0)
    d = 1.0;
  else if (d < -1.0)
	d = -1.0;
  angle = acos(d / sqrt( NormSquare(v1) * NormSquare(v2)));
  return(angle);
}


void InitializeMesh(Mesh *msh)  /* Initialisation de la struture mesh */
{
  int		j;

  msh->number_of_vertices = 0;
  msh->number_of_triangles = 0;
  msh->vertices = NULL;
  msh->triangles = NULL;
  for (j=0; j<3; j++) 
  {
    msh->ccenter[j] = 0.0;
    msh->cmin[j] = 0.0;
    msh->cmax[j] = 0.0;
  }
  msh->delta = 0.0;
  msh->memory = 0;
  msh->error = 0;
}


void ReadMesh(Mesh *msh, char **argv) /* lecture du fichier au format mesh INRIA Gamma3*/
{
  FILE		*file;
  char		file_name[264], keyword[80];
  int           i, j, ii, dim;

  sprintf(file_name, "%s.mesh", argv[1]);   
  if ((file = fopen(file_name, "r")) == NULL) 
  {
    printf("error: file %s not found\n", file_name);
    msh->error = 100;
    return;
  }  
  for (;;) 
  {
    fscanf(file, "%s", keyword);
    if (strcmp(keyword, "EOF") == 0 || strcmp(keyword, "End") == 0 || strcmp(keyword, "end") == 0) /* fin du fichier */
      break;
    else if (strcmp(keyword, "Dimension") == 0 || strcmp(keyword, "dimension") == 0 ) /* mot cle dimension */
      fscanf(file, "%d", &dim);
    else if (strcmp(keyword, "Vertices") == 0 || strcmp(keyword, "vertices") == 0 )  /* mot cle Vertices */ 
    {
      fscanf(file, "%d", &(msh->number_of_vertices));
      msh->vertices = (float*)malloc((3*msh->number_of_vertices)*sizeof(float));
      if (!msh->vertices) 
      {
        printf("error: not enough memory for %d vertices (%ld bytes)\n", msh->number_of_vertices, 3*msh->number_of_vertices*sizeof(float));
	msh->error = 200;
	return;
      } 
      else 
        msh->memory += (3*msh->number_of_vertices)*sizeof(float);
      if (dim == 2) 
      {
        for (i=0; i<msh->number_of_vertices; i++) 
        {
	  ii = 3 * i;
	  fscanf(file, "%f %f %d", &(msh->vertices[ii]), &(msh->vertices[ii+1]), &j);
	  msh->vertices[ii+2] = 0.0;
	}
      } else if (dim == 3)
      {
        for (i=0; i<msh->number_of_vertices; i++) 
        {
          ii = 3 * i;
	  fscanf(file, "%f %f %f %d", &(msh->vertices[ii]), &(msh->vertices[ii+1]), &(msh->vertices[ii+2]), &j);
        }
      }
    } else if (strcmp(keyword, "Triangles") == 0 || strcmp(keyword, "triangles") == 0) /* mot cle Triangles */
    {
      fscanf(file, "%d", &(msh->number_of_triangles));
      msh->triangles = (int*)malloc((3*msh->number_of_triangles)*sizeof(int));
      if (!msh->triangles) 
      {
        printf("error: not enough memory for %d triangles (%ld bytes)\n", msh->number_of_triangles, 3*msh->number_of_triangles*sizeof(int));
	msh->error = 200;
	return;
      }
      else 
	msh->memory += (3*msh->number_of_triangles)*sizeof(int);
      for (i=0; i<msh->number_of_triangles; i++) 
      {
	ii = 3 * i;
	fscanf(file, "%d %d %d %d", &(msh->triangles[ii]), &(msh->triangles[ii+1]), &(msh->triangles[ii+2]), &j);
	for (j=0; j<3; j++)
	  msh->triangles[ii+j]--;
      }
    }
  }
  fclose(file);
  /* affichage a l'ecran des infos sur le maillage */
  printf("mesh : %d vertices -- %d triangles (%ld kbytes)\n", msh->number_of_vertices, msh->number_of_triangles, msh->memory/1024);
}

void NormalizeMesh(Mesh *msh) /* normalisation des coordonnees des sommets entre 0 et 1 */
{
  int	        i, ii, j;

  for (j=0; j<3; j++) 
  {
    msh->cmin[j] = msh->vertices[j];
    msh->cmax[j] = msh->vertices[j];
  }
  for (i=1; i<msh->number_of_vertices; i++)
  {
    ii = 3 * i;
    for (j=0; j<3; j++) 
    {
      if (msh->cmin[j] > msh->vertices[ii+j])
        msh->cmin[j] = msh->vertices[ii+j];
      if (msh->cmax[j] < msh->vertices[ii+j])
	msh->cmax[j] = msh->vertices[ii+j];
    }
  }
  for (j=0; j<3; j++)
    msh->ccenter[j] = (float)(0.5 * (msh->cmin[j] + msh->cmax[j]));
  msh->delta = msh->cmax[0] - msh->cmin[0];
  for (j=1; j<3; j++)
    if (msh->delta < msh->cmax[j] - msh->cmin[j])
      msh->delta = msh->cmax[j] - msh->cmin[j];
  for (i=0; i<msh->number_of_vertices; i++)
  {
    ii = 3 * i;
    for (j=0; j<3; j++)
    {
      //msh->vertices[ii+j] -= msh->cmin[j];
     // msh->vertices[ii+j] /= msh->delta; /*met les coordonn�es a l'�chelle*/
        msh->vertices[ii + j] = 0.5 + (msh->vertices[ii + j] - msh->ccenter[j]) / msh->delta;
    }
  }
  for (j=0; j<3; j++)
  {
    msh->ccenter[j] -= msh->cmin[j];
    msh->ccenter[j] /= msh->delta; /*met le centre a l'�chelle*/
    msh->cmax[j] /= msh->delta; /*met le max a l'�chelle*/
    msh->cmin[j] /= msh->delta; /*met le min a l'�chelle*/
  }
}


void SetTriangleNormals(Mesh *msh)
{
  int           i, ii, j; /*declaration des variables*/
  float         *v0, *v1, *v2, u[3], v[3], n[3];
  double        norme;

  msh->normal_t = (float*)malloc((3*msh->number_of_triangles)*sizeof(float)); /*allocation de la memoire pour les normales aux triangles*/
  if (!msh->normal_t) /*gestion de l'erreur d'allocation m�moire*/
  {
    printf("error: not enough memory for %d normales aux triangles (%ld bytes)\n", msh->number_of_triangles, 3*msh->number_of_triangles*sizeof(float));
    msh->error = 200;
    return;
  }
  else
    msh->memory += (3*msh->number_of_triangles)*sizeof(float);
 /*fin de l'allocation de la memoire pour les normales aux triangles*/

  msh->alpha_t = (float*)malloc((3*msh->number_of_triangles)*sizeof(float)); /*allocation de la memoire pour les angles des triangles*/
  if (!msh->alpha_t) /*gestion de l'erreur d'allocation m�moire*/
  {
    printf("error: not enough memory for %d angles aux triangles (%ld bytes)\n", msh->number_of_triangles, 3*msh->number_of_triangles*sizeof(float));
    msh->error = 200;
    return;
  }
  else
    msh->memory += (3*msh->number_of_triangles)*sizeof(float);
 /*fin de l'allocation de la memoire pour les angles des triangles*/
  
  for (i = 0; i < (msh->number_of_triangles); i++) /*boucle sur les triangles*/
  {
    ii = 3 * i;
    v0 = &(msh->vertices[3 * msh->triangles[ii]]); /*premiere coordonnee du premier point du triangle ii*/
    v1 = &(msh->vertices[3 * msh->triangles[ii+1]]); /*premiere coordonnee du deuxieme point du triangle ii*/
    v2 = &(msh->vertices[3 * msh->triangles[ii+2]]); /*premiere coordonnee du troisieme point du triangle ii*/
    for (j = 0; j < 3; j++) /*calcul des vecteurs du triangles*/
    {
      u[j] = v1[j] - v0[j];
      v[j] = v2[j] - v0[j];
    }
    CrossProduct(u, v, n); /*effectue le produit vectoriel de u et v, le r�sultats est le tableau n*/
    norme = NormSquare(n); /*effectue la norme au carre de n (n est un tableau de 3 float)*/
    if (norme != 0)
    {
      norme = 1.0 / sqrt(norme);
      msh->normal_t[ii] = (float)(norme * n[0]);
      msh->normal_t[ii+1] = (float)(norme * n[1]);
      msh->normal_t[ii+2] = (float)(norme * n[2]);
    }
    else
    {
      msh->normal_t[ii] = n[0];
      msh->normal_t[ii+1] = n[1];
      msh->normal_t[ii+2] = n[2];
    }
    /* calcul des angles associ�s �chaque sommet de chaque triangle*/
    msh->alpha_t[ii] = (float)Angle(v2, v0, v1); /*calcul du premier angle du triangle*/
    msh->alpha_t[ii+1] = (float)Angle(v0, v1, v2); /*calcul du deuxieme angle du triangle*/
    msh->alpha_t[ii+2] =  (float)Angle(v1, v2, v0); /*calcul du troisieme angle du triangle*/
  }
}


void SetVertexNormals(Mesh *msh)
{
  int           i, ii, j, k;
  double        norme;

  msh->normal_v = (float*)malloc((3*msh->number_of_vertices)*sizeof(float)); /*allocation de la memoire des normales aux sommets*/
  if (!msh->normal_v)/*gestion de l'erreur d'allocation m�moire*/
  {
    printf("error: not enough memory for %d normales aux sommets (%ld bytes)\n", 
    msh->number_of_vertices, 3*msh->number_of_vertices*sizeof(float));
    msh->error = 200;
    return;
  }
  else
    msh->memory += (3*msh->number_of_vertices)*sizeof(float);
  /*fin de l'allocation de la memoire des normales aux sommets*/

  for (i = 0; i < (msh->number_of_vertices); i++) /* d�but du calcul des normales aux sommets (initialistation a 0) */
  {
    ii = 3 * i;
    msh->normal_v[ii] = 0.0;
    msh->normal_v[ii+1] = 0.0;
    msh->normal_v[ii+2] = 0.0;
  }
  if (msh->number_of_triangles != 0) /*test si il y a des triangles*/
  {
    for (i = 0; i < (msh->number_of_triangles); i++) /*calcul des normales aux sommets des triangles*/
    {
      ii = 3 * i;
      for (j = 0; j < 3; j++) /*boucle sur les sommets*/
	for (k = 0; k < 3; k++) /*boucle sur les coordonnes*/
	  msh->normal_v[3*msh->triangles[ii+j]+k] += msh->alpha_t[ii+j] * msh->normal_t[ii+k]; /*incr�mentation pour chaque sommet*/
    }
  }
  for (i = 0; i < (msh->number_of_vertices); i++) /*normalisations des normales*/
  {
    ii = 3 * i;
    norme = NormSquare(&(msh->normal_v[ii]));
    if (norme != 0)
    {
      norme = 1.0 / sqrt(norme);
      for (j = 0; j < 3; j++)
	msh->normal_v[ii+j] = (float)(norme * msh->normal_v[ii+j]);
    }
    else
      for (j = 0; j < 3; j++)
	msh->normal_v[ii+j] = 0.0;
  }
}

void SetNormals(Mesh *msh)
{
  if (msh->number_of_triangles != 0) /*test si il y a des triangles*/
  {
	SetTriangleNormals(msh);
    SetVertexNormals(msh);
  }
}
