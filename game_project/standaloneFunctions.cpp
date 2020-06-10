#include "standaloneFunctions.h"

#define PI 3.14159265

Json::Value standaloneFunctions::loadJsonFile(const char* filename)
{
	std::ifstream file;
	Json::Value data;
	file.open(filename);
	if (file.fail())
	{
		std::stringstream errMsg;
		errMsg << "loading file failed";
		throw std::exception(errMsg.str().c_str());

	}
	file >> data;
	return data;
}

float standaloneFunctions::quadraticHop(float a, float x)
{
	if (x>1 || x<0)
	{
		throw std::invalid_argument("dvalue must be between 0 and 1");
	}
	return -a * x*x + a * x;
}

float standaloneFunctions::easeInOut(float x)
{
	return -(cos(PI*x) - 1) / 2;
}

std::vector<sf::Vector2i> standaloneFunctions::lineOfSight(int x1, int y1, int x2, int y2)
{
	std::vector<sf::Vector2i> v;

	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = fabs(dx);
	dy1 = fabs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	sf::Vector2i point;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}
		point.x = x; point.y = y; v.push_back(point);
		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0)
			{
				px = px + 2 * dy1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					y = y + 1;
				}
				else
				{
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}

			point.x = x; point.y = y; v.push_back(point);
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}
		point.x = x; point.y = y; v.push_back(point);
		for (i = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0)
			{
				py = py + 2 * dx1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}

			point.x = x; point.y = y; v.push_back(point);
		}
	}

	return v;
}

float standaloneFunctions::setWindowSize(Axis axis, WindowInfo windowInfo)
{
	switch (windowInfo.fullscreen)
	{
	case(1):
		switch (axis)
		{
		case(Axis::x):
			return sf::VideoMode::getDesktopMode().width;
			break;
		case(Axis::y):
			return sf::VideoMode::getDesktopMode().height;
			break;
		default:
			throw std::invalid_argument("You must use Axis enum");
		}
		break;
	case(0):
		switch (axis)
		{
		case(Axis::x):
			return windowInfo.windowedWidthPixels;
			break;
		case(Axis::y):
			return windowInfo.windowedHeightPixels;
			break;
		default:
			throw std::invalid_argument("You must use Axis enum");
		}
		break;
	default:
		throw std::invalid_argument("Somehow you have a fullscreen value other than 1 or 0");
		break;
	}
}

float standaloneFunctions::setPosition(Alignment alignment, Axis axis, float offset, WindowInfo windowInfo)
{
	float alignmentPosition;
	float windowSize = setWindowSize(axis, windowInfo);

	switch (alignment)
	{
	case(Alignment::left):
		leftCase:
		alignmentPosition = 0;
		break;
	case (Alignment::top):
		goto leftCase;
		break;
	case (Alignment::right):
		rightCase:
		alignmentPosition = windowSize;
		break;
	case (Alignment::bottom):
		goto rightCase;
		break;
	case (Alignment::centre):
		alignmentPosition = windowSize / 2;
		break;
	default:
		throw std::invalid_argument("You must use Alignment enum");
	}
	
	return alignmentPosition + offset;

}

float standaloneFunctions::setPosition(float alignment, Axis axis, float offset, WindowInfo windowInfo)
{
	float alignmentPosition = alignment;
	float windowSize = setWindowSize(axis, windowInfo);
	return alignmentPosition + offset;

}
