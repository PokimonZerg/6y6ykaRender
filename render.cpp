#include <xmmintrin.h>
#include <emmintrin.h>
#include <algorithm>
#include "goods.h"
#include "trigonometry.h"
#include "matrix_4x4.h"
#include "render.h"

Render::Render(Screen *_screen, Camera *_camera)
{
	screen = _screen;
	camera = _camera;

	InitScreen();
}

Render::~Render()
{
	// empty
}

void Render::InitScreen()
{
	screen_width = screen->GetWidth() - 1;
	screen_height = screen->GetHeight() - 1;
	screen_center_w = screen_width / 2;
	screen_center_h = screen_height / 2;
	d = float(screen_width / 2);
	ar = (float)screen_width / (float)screen_height;
}

void Render::Clear(Color &_c)
{
	screen->Clear(_c);

	InitScreen();
}

void Render::DrawDot(Point &_p, Color &_c)
{
	screen->SetPixel(_p, _c);
}

void Render::DrawLine(Point &_p1, Point &_p2, Color &_c)
{
	int dx = _p2.x - _p1.x;
	int dy = _p2.y - _p1.y;

	int lengthX = abs(dx);
	int lengthY = abs(dy);
	int length = max(lengthX, lengthY) + 1;

	dx = dx >= 0 ? 1 : -1;
	dy = dy >= 0 ? 1 : -1;

	int x = _p1.x;
    int y = _p1.y;

	lengthY *= 2;
	lengthX *= 2;
 
	if (lengthY < lengthX)
    {
        int d = -lengthX;

        while(length--)
        {
			screen->SetPixel(Point(x, y), _c);
            x += dx;
            d += lengthY;
			if(d > 0)
			{
				d -= lengthX;
				y += dy;
			}
		} 
	}
	else
	{
        int d = -lengthY;

	    while(length--)
        {
			screen->SetPixel(Point(x, y), _c);
            y += dy;
            d += lengthX;
            if(d > 0)
			{
				d -= lengthY;
                x += dx;
			}
		}
	}
}

void Render::DrawHLine(Point &_p1, Point &_p2, Color &_color)
{
	Color *line = screen->GetPixelLine(_p1.y);

	std::fill(line + _p1.x, line + _p2.x + 1, _color);
}

inline int Render::Round(float _n)
{
	return _mm_cvtss_si32(_mm_load_ss(&_n));
}

inline int Render::Round(double _n)
{
	return _mm_cvtsd_si32(_mm_load_sd(&_n));
}

/*int Render::GenCohenSutherlandCode(Point &_p)
{
	return (_p.x < 0 ? 1 : 0) + (_p.x > screen_width  ? 2 : 0) +
		   (_p.y < 0 ? 4 : 0) + (_p.y > screen_height ? 8 : 0) ;
}*/

/*bool Render::ClippingLine2D(Point &_p1, Point &_p2)
{
	int p1_code, p2_code, code;
	Point c;
 
    p1_code = GenCohenSutherlandCode(_p1);
    p2_code = GenCohenSutherlandCode(_p2);
 
    while(p1_code | p2_code) 
	{
		if(p1_code & p2_code) return false;
 
		code = p1_code ? p1_code : p2_code;
 
        if(code & 1)
		{
			c.y = _p1.y + (_p2.y - _p1.y) * (0 - _p1.x) / (_p2.x - _p1.x);
            c.x = 0;
        } 
		else if(code & 2)
		{
            c.y = _p1.y + (_p2.y - _p1.y) * (screen_width - _p1.x) / (_p2.x - _p1.x);
            c.x = screen_width;
        }
        else if(code & 4)
		{
            c.x = _p1.x + (_p2.x - _p1.x) * (0 - _p1.y) / (_p2.y - _p1.y);
            c.y = 0;
        } 
		else if(code & 8)
		{
            c.x = _p1.x + (_p2.x - _p1.x) * (screen_height - _p1.y) / (_p2.y - _p1.y);
            c.y = screen_height;
        }
 
        if(code == p1_code)
			p1_code = GenCohenSutherlandCode(_p1 = c);
		else
			p2_code = GenCohenSutherlandCode(_p2 = c);
	}
 
	return true;
}*/

int Render::GenClipCode(Vector3D &_p)
{
	int code = null;

	if(_p.y * ar > _p.z)          code |= top   ;
	if(-_p.y * ar > _p.z)         code |= bottom;
	if(_p.x > _p.z)               code |= right ;
	if(-_p.x > _p.z)              code |= left  ;
	if(_p.z > camera->far_plane)  code |= back  ;
	if(_p.z < camera->near_plane) code |= front ;

	return code;
}

Vector3D Render::CutLineOnRight(Vector3D &_p1, Vector3D &_p2) // x = z
{
	float t = (_p1.z - _p1.x) / (_p2.x - _p1.x - _p2.z + _p1.z);
	float z = _p1.z + (_p2.z - _p1.z) * t;

	return Vector3D(z, _p1.y + (_p2.y - _p1.y) * t, z);
}

Vector3D Render::CutLineOnLeft(Vector3D &_p1, Vector3D &_p2) // -x = z
{
	float t = -(_p1.z + _p1.x) / (_p2.z - _p1.z + _p2.x - _p1.x);
	float z = _p1.z + (_p2.z - _p1.z) * t;

	return Vector3D(-z, _p1.y + (_p2.y - _p1.y) * t, z);
}

Vector3D Render::CutLineOnTop(Vector3D &_p1, Vector3D &_p2) // y * ar = z
{
	float t = -(_p1.z - ar * _p1.y) / (_p2.z - _p1.z - ar * _p2.y + ar * _p1.y);
	float y = _p1.y + (_p2.y - _p1.y) * t;

	return Vector3D(_p1.x + (_p2.x - _p1.x) * t, y, y * ar);
}

Vector3D Render::CutLineOnBottom(Vector3D &_p1, Vector3D &_p2) // -y * ar = z
{ 
	float t = -(_p1.z + ar * _p1.y) / (_p2.z - _p1.z + ar * _p2.y - ar * _p1.y);
	float y = _p1.y + (_p2.y - _p1.y) * t;

	return Vector3D(_p1.x + (_p2.x - _p1.x) * t, y, -y * ar);
}

Vector3D Render::CutLineOnFront(Vector3D &_p1, Vector3D &_p2) // z = near_plane
{ 
	float t = -(_p1.z - camera->near_plane) / (_p2.z - _p1.z);

	return Vector3D(_p1.x + (_p2.x - _p1.x) * t, _p1.y + (_p2.y - _p1.y) * t, camera->near_plane);
}

Vector3D Render::CutLineOnBack(Vector3D &_p1, Vector3D &_p2) // z = far_plane
{ 
	float t = -(_p1.z - camera->far_plane) / (_p2.z - _p1.z);

	return Vector3D(_p1.x + (_p2.x - _p1.x) * t, _p1.y + (_p2.y - _p1.y) * t, camera->far_plane);
}

Render::ClipResult Render::ClippingLine(Vector3D &_p1, Vector3D &_p2)
{
	int code1, code2, code;
	Vector3D *c;

	code1 = GenClipCode(_p1);
	code2 = GenClipCode(_p2);

	while(code1 | code2)  // пока одна из точек выходит за пределы пирамиды
	{
		if(code1 & code2) return hide;

		code1 ? (code = code1, c = &_p1) : (code = code2, c = &_p2);
 
		if(code & front)
			*c = CutLineOnFront(_p1, _p2);
		else if(code & back)
			*c = CutLineOnBack(_p1, _p2);
		else if(code & left)
            *c = CutLineOnLeft(_p1, _p2);
		else if(code & right)
			*c = CutLineOnRight(_p1, _p2);
		else if(code & bottom)
			*c = CutLineOnBottom(_p1, _p2);
		else if(code & top)
            *c = CutLineOnTop(_p1, _p2);
 
		code == code1 ? code1 = GenClipCode(_p1) : code2 = GenClipCode(_p2);
	}

	return good;
}

void Render::AddChips(Vector3D _p1, Vector3D _p2, Vector3D _p3)
{
	potato.push_back(Triangle());
	potato.back().visible = true;
	chips.push_back(_p1); 
	potato.back().a = chips.size() - 1;
	chips.push_back(_p2);
	potato.back().b = chips.size() - 1;
	chips.push_back(_p3);
	potato.back().c = chips.size() - 1;
}

void Render::ClippingTriangle(Vector3D &_p1, Vector3D &_p2, Vector3D &_p3)
{
	AddChips(_p1, _p2, _p3);
	
	// ЭТО С++ ДЕТКА!!
	ClipPlane(&Render::CutLineOnTop,    [this](Vector3D &_p) { return  _p.y * ar  > _p.z;               });
	ClipPlane(&Render::CutLineOnBottom, [this](Vector3D &_p) { return -_p.y * ar  > _p.z;               });
	ClipPlane(&Render::CutLineOnLeft,   [    ](Vector3D &_p) { return -_p.x       > _p.z;               });
	ClipPlane(&Render::CutLineOnRight,  [    ](Vector3D &_p) { return  _p.x       > _p.z;               });
	ClipPlane(&Render::CutLineOnBack,   [this](Vector3D &_p) { return  _p.z       > camera->far_plane;  });
	ClipPlane(&Render::CutLineOnFront,  [this](Vector3D &_p) { return  _p.z       < camera->near_plane; });
}

template <typename ClipType>
void Render::ClipPlane(Vector3D (Render::*CutFunc) (Vector3D &, Vector3D &), ClipType _cond)
{
	size_t p[3] = {0, 1, 2};            // индексы вершин
	bool   v[3];                        // false - снаружи, true - внутри
	Vector3D extra_vertex;
	size_t potato_size = potato.size(); // чтобы не проверять созданные нами треугольники
	 
	// цикл по всем треугольникам.
	for(size_t i = 0, n = 0, h = 0; n < potato_size; n++, h = 0)
	{
		for(size_t k = 0; k < 3; k++) // индексы править, чтобы итераторы не тягать
				p[k] = i++;
		
		if(!potato[n].visible)        // если треугольник отсекли до нас, то ничего не делаем
			continue;

		for(size_t k = 0; k < 3; k++) // проверка видимости
			v[k] = _cond(chips[p[k]]) ? h++, false : true;

		switch(h)
		{
		case 3:   // треугольник полностью невидим
			potato[n].visible = false;

			continue;

		case 0:   // треугольник полностью видимый
			potato[n].visible = true;

			continue;

		case 2:   // 2 вершины снаружи и одна внутри
			potato[n].visible = true;

			if(v[1]) std::swap(p[1], p[0]);
			if(v[2]) std::swap(p[2], p[0]);
			
			chips[p[1]] = (this->*CutFunc)(chips[p[0]], chips[p[1]]);
			chips[p[2]] = (this->*CutFunc)(chips[p[0]], chips[p[2]]);

			break;

		case 1:   // одна вершина снаружи
			potato[n].visible = true;

			if(!v[1]) std::swap(p[1], p[0]);
			if(!v[2]) std::swap(p[2], p[0]);

			extra_vertex = (this->*CutFunc)(chips[p[0]], chips[p[1]]);

			size_t index = chips.size();
			potato.push_back(Triangle(index, index + 1, index + 2));
			chips.push_back(extra_vertex);
			chips.push_back(chips[p[1]]);
			chips.push_back(chips[p[2]]);
			potato.back().visible = true;

			chips[p[0]] = (this->*CutFunc)(chips[p[0]], chips[p[2]]);
			chips[p[1]] = extra_vertex;

			break;
		}
	}
}

void Render::DrawObject(LineObject *_object)
{
	Matrix4X4 CAM = Matrix4X4::Identity() * camera->CalcMatrix();

	for(auto i = _object->lines.begin(); i != _object->lines.end(); i++)
	{
		_object->cam_lines.push_back(Line(i->a * CAM, i->b * CAM, i->color));
	}

	Point sp[2];

	for(auto i = _object->cam_lines.begin(); i != _object->cam_lines.end(); i++)
	{
		if(ClippingLine(i->a, i->b))
		{
			sp[0].x = Round(i->a.x * d / i->a.z) + screen_center_w;
			sp[0].y = -Round(i->a.y * d / i->a.z) + screen_center_h;

			sp[1].x = Round(i->b.x * d / i->b.z) + screen_center_w;
			sp[1].y = -Round(i->b.y * d / i->b.z) + screen_center_h;

			DrawLine(sp[0], sp[1], i->color);
		}
	}

	_object->cam_lines.clear();
}

void Render::DrawObject(Object *_object)
{
	Matrix4X4 CAM = Matrix4X4::Translate(_object->position) * camera->CalcMatrix();

	for(size_t i = 0; i < _object->mesh.v_size; i++)
	{
		_object->mesh.cam_vertex[i] = _object->mesh.vertex[i] * CAM;
	}

	Triangle *t;

	for(size_t i = 0; i < _object->mesh.t_size; i++)
	{
		t = &_object->mesh.triangles[i];
		
		ClippingTriangle(_object->mesh.cam_vertex[t->a], _object->mesh.cam_vertex[t->b],
					     _object->mesh.cam_vertex[t->c]);

		for(auto i = potato.begin(); i < potato.end(); i++)
		{
			if(i->visible)
				DrawTriangle(chips[i->a], chips[i->b], chips[i->c], _object->color);
		}
		
		potato.clear();
		chips.clear();
	}
}

void Render::DrawTriangle(Vector3D &_a, Vector3D &_b, Vector3D &_c, Color &_color)
{
	Point sp[3];
	float z;

	z = d / _a.z;
	sp[0].x = Round(_a.x * d / _a.z) + screen_center_w;
	sp[0].y = -Round(_a.y * d / _a.z) + screen_center_h;

	z = d / _b.z;
	sp[1].x = Round(_b.x * d / _b.z) + screen_center_w;
	sp[1].y = -Round(_b.y * d / _b.z) + screen_center_h;

	z = d / _c.z;
	sp[2].x = Round(_c.x * d / _c.z) + screen_center_w;
	sp[2].y = -Round(_c.y * d / _c.z) + screen_center_h;

	//DrawLine(sp[0], sp[1], _color);
	//DrawLine(sp[1], sp[2], _color);
	//DrawLine(sp[2], sp[0], _color);

	DrawTriangle(sp[0], sp[1], sp[2], _color);
}

void Render::DrawTriangle(Point &_a, Point &_b, Point &_c, Color &_color)
{
	int A, B;

	if(_a.y > _b.y) std::swap(_a, _b);
	if(_b.y > _c.y) std::swap(_b, _c);
	if(_a.y > _b.y) std::swap(_a, _b);

	float At, Bt;

	if(_a.y != _b.y)
		At = float(_a.x - _b.x) / float(_a.y - _b.y);

	if(_a.y != _c.y)
		Bt = float(_a.x - _c.x) / float(_a.y - _c.y);

	for(int i = _a.y; i < _b.y; i++)
	{
		A = int(_b.x + (i - _b.y) * At);
		B = int(_c.x + (i - _c.y) * Bt);

		if(A > B) std::swap(A, B);

		DrawHLine(Point(A, i), Point(B, i), _color);
	}

	if(_b.y != _c.y)
		At = float(_b.x - _c.x) / float(_b.y - _c.y);

	if(_a.y - _c.y)
		Bt = float(_a.x - _c.x) / float(_a.y - _c.y);

	for(int i = _b.y; i < _c.y; i++)
	{
		A = int(_c.x + (i - _c.y) * At);
		B = int(_c.x + (i - _c.y) * Bt);

		if(A > B) std::swap(A, B);

		DrawHLine(Point(A, i), Point(B, i), _color);
	}
}

Camera *Render::GetCamera()
{
	return camera;
}