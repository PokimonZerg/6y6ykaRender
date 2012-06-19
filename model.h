#ifndef _MODEL_H_
#define _MODEL_H_

class Model
{
public:
	Model();

	~Model();

	static Model *Load(char *_filename);

	// vertex coords
	size_t v_size;
	float *v;
	// triangles
	size_t t_size;
	size_t *t;
};

#endif