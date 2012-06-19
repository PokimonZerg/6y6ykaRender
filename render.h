#ifndef _RENDER_H_
#define _RENDER_H_

#include <vector>
#include "object.h"
#include "line_object.h"
#include "screen.h"
#include "camera.h"

class Render
{
public:
	Render(Screen *_screen, Camera *_camera);

	~Render();

	void Clear(Color &_c);

	void DrawDot(Point &_p, Color &_c);

	void DrawLine(Point &_p1, Point &_p2, Color &_c);

	void DrawObject(Object *_object);
	void DrawObject(LineObject * _object);

	void DrawTriangle(Point &_a, Point &_b, Point &_c, Color &_color);

	Camera *GetCamera();

private:
	Screen *screen;
	Camera *camera;

	float d;
	float ar;

	int screen_width;
	int screen_height;
	int screen_center_w;
	int screen_center_h;

	Vector3D tv[6];

	int Round(float _n);
	int Round(double _n);

	void InitScreen();

	enum ClipCode
	{
		null   = 0,
		bottom = 1,
		left   = 2,
		top    = 4,
		right  = 8,
		back   = 16,
		front  = 32
	};

	enum ClipResult
	{
		hide,
		good,
		cut,
		cut_cut
	};

	ClipResult ClippingLine(Vector3D &_p1, Vector3D &_p2);

	int GenClipCode(Vector3D &_p);

	Vector3D CutLineOnRight (Vector3D &_p1, Vector3D &_p2);
	Vector3D CutLineOnLeft  (Vector3D &_p1, Vector3D &_p2);
	Vector3D CutLineOnTop   (Vector3D &_p1, Vector3D &_p2);
	Vector3D CutLineOnBottom(Vector3D &_p1, Vector3D &_p2);
	Vector3D CutLineOnFront (Vector3D &_p1, Vector3D &_p2);
	Vector3D CutLineOnBack  (Vector3D &_p1, Vector3D &_p2);

	std::vector<Triangle> potato;
	std::vector<Vector3D> chips;

	void ClippingTriangle(Vector3D &_p1, Vector3D &_p2, Vector3D &_p3);

	template <typename ClipType>
	void ClipPlane(Vector3D (Render::*CutFunc) (Vector3D &, Vector3D &), ClipType _cond);

	int CutTriangleOnRight();
	int CutTriangleOnLeft();
	int CutTriangleOnTop();
	int CutTriangleOnBottom();
	int CutTriangleOnFront();
	int CutTriangleOnBack();

	void AddChips(Vector3D _p1, Vector3D _p2, Vector3D _p3);
	
	//bool ClippingLine2D(Point &_p1, Point &_p2);

	//int GenCohenSutherlandCode(Point &_p);

	void DrawHLine(Point &_p1, Point &_p2, Color &_color);

	void DrawTriangle(Vector3D &_a, Vector3D &_b, Vector3D &_c, Color &_color);

	void PaintTriangle(Point *_a, Point *_b, Point *_c, Color &_color);
	void PaintTopTriangle(Point *_a, Point *_b, Point *_c, Color &_color);
	void PaintBottomTriangle(Point *_a, Point *_b, Point *_c, Color &_color);
};

#endif