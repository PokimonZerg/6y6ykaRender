#include "line_object.h"

LineObject::LineObject()
{

}

LineObject::~LineObject()
{

}

bool LineObject::AddLine(Line &_line)
{
	lines.push_back(_line);

	return true;
}