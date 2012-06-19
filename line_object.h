#ifndef _LINE_OBJECT_H_
#define _LINE_OBJECT_H_

#include <vector>
#include "line.h"

class LineObject
{
	friend class Render;

public:
	LineObject();

	~LineObject();

	bool AddLine(Line &_line);

private:
	std::vector<Line> lines;
	std::vector<Line> cam_lines;
};

#endif