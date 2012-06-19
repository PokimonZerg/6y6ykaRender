#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include "mesh.h"
#include "model.h"

Model::Model()
{
	v_size = 0;
	t_size = 0;
}

Model::~Model()
{
	if(v_size)
		delete[] v;

	if(t_size)
		delete[] t;
}

Model *Model::Load(char *_filename)
{
	FILE  *file;
	Model *model = new Model();

	file = fopen(_filename, "r + b");

	fread(&model->v_size, 4, 1, file);
	fread(&model->t_size, 4, 1, file);
	
	model->v = new float[model->v_size];
	model->t = new size_t[model->t_size];

	size_t s1 = fread(model->v, model->v_size * sizeof(float), 1, file);
	size_t s2 = fread(model->t, model->t_size * sizeof(size_t), 1, file);

	//model->t_size = 3;

	fclose(file);

	return model;
}