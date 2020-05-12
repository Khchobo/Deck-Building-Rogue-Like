#include "easeInOut.h"

#define PI 3.14159265

float easeInOut(float x)
{
	return -(cos(PI*x) - 1) / 2;
}