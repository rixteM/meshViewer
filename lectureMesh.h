#pragma once
#include "structures.h"

//Initialisation de la struture mesh
void InitializeMesh(Mesh* msh); 

//lecture du fichier au format mesh INRIA Gamma3
void ReadMesh(Mesh* msh, char** argv); 

//normalisation des coordonnees des sommets entre 0 et 1
void NormalizeMesh(Mesh* msh);

void SetTriangleNormals(Mesh* msh);

void SetVertexNormals(Mesh* msh);

void SetNormals(Mesh* msh);

void ModelDiscret(Mesh* msh, char** argv);

