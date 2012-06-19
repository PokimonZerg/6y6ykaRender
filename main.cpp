#include <iostream>
#include "stdlib.h"
#include <crtdbg.h>
#include "render.h"
#include "vector_3d.h"
#include "Matrix_4x4.h"
#include "quaternion_camera.h"
#include "euler_camera.h"
#include "spherical_camera.h"
#include "uvn_camera.h"
#include "core.h"
#include "sphere.h"

Core *core;
Render *render;
QuaternionCamera *cameraq;
EulerCamera *camerae;
SphericalCamera *cameras;
UvnCamera *camerau;

void Update()
{
	const float cam_speed = 50.0f;
	const float cam_rotate_speed = 10.0f;
	Point old_mp = core->GetScreenCenter();

	Point mp = core->GetMousePos();
	core->SetMousePos();
	int rx = old_mp.x - mp.x;
	int ry = old_mp.y - mp.y;

	render->GetCamera()->RotateY(-rx * cam_rotate_speed * float(core->GetTime()));
	render->GetCamera()->RotateX(ry * cam_rotate_speed * float(core->GetTime()));

	if(core->GetKeyState(VK_ESCAPE))
		core->StopMe();

	if(core->GetKeyState(VK_LEFT))
		render->GetCamera()->MoveSide(cam_speed * (float)core->GetTime());

	if(core->GetKeyState(VK_RIGHT))
		render->GetCamera()->MoveSide(-cam_speed * (float)core->GetTime());

	if(core->GetKeyState(VK_UP))
		render->GetCamera()->MoveForward(-cam_speed * (float)core->GetTime());


	if(core->GetKeyState(VK_DOWN))
		render->GetCamera()->MoveForward(cam_speed * (float)core->GetTime());
}

LineObject *CreateNetwork()
{
	LineObject *lo = new LineObject();
	Color c(0, 255, 0);

	for(float i = -100; i < 100; i += 10)
	{
		lo->AddLine(Line(Vector3D(i, 0, -100), Vector3D(i, 0, 100), c));
	}

	for(float i = -100; i < 100; i += 10)
	{
		lo->AddLine(Line(Vector3D(-100, 0, i), Vector3D(100, 0, i), c));
	}

	return lo;
}

int main()
{
	core = new Core();
	core->Create();

	cameraq = new QuaternionCamera();
	camerae = new EulerCamera();
	cameras = new SphericalCamera();
	camerau = new UvnCamera();

	render = new Render(core->GetScreen(), camerae);

	LineObject line;
	line.AddLine(Line(Vector3D(0, 0, 10), Vector3D(100, 0, 10), Color(255, 0, 0)));
	line.AddLine(Line(Vector3D(0, 0, 10), Vector3D(0, 100, 10), Color(0, 255, 0)));
	line.AddLine(Line(Vector3D(0, 0, 10), Vector3D(0, 0, 100), Color(0, 0, 255)));

	LineObject *net = CreateNetwork();

	Model *cube = Model::Load("cube.brm");

	Object *o = Object::Construct(cube, Color(0, 255, 0), Vector3D(0, 0, 15));

	o->Move(Vector3D(0, 0, 50));
	o->Scale(Vector3D(10, 10, 10));
	o->Rotate(180, 1, 0, 0);

	Model *plane = Model::Load("plane.brm");

	Object *p = Object::Construct(plane, Color(200, 100, 0), Vector3D(0, 0, 0));

	p->Move(Vector3D(0, 0, 25));
	p->Scale(Vector3D(10, 10, 10));
	p->Rotate(180, 1, 0, 0);

	core->SetMousePos();

	float a = 0;

	while(!core->Stop())
	{
		render->Clear(Color(0, 0, 0));

		a = (float)core->GetTime() * 25;
		o->Rotate(a, 0, 1, 0);

		render->DrawObject(&line);
		render->DrawObject(net);
		render->DrawObject(o);
		render->DrawObject(p);

		Update();
	} 

	core->Delete();
	delete core;

	return 0;
}