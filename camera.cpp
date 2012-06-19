#include "trigonometry.h"
#include "camera.h"

Camera::Camera(Vector3D &_pos) : position(_pos), fov(90)
{
	far_plane = 250.0f;
	near_plane = 0.1f;
}

Camera::~Camera()
{

}