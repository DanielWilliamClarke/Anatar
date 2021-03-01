#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

class AngleConversion
{
public:
	static float ToDegrees(float radians)
	{
		return radians * (180.0f / (float)M_PI);
	}

	static float ToRadians(float degrees)
	{
		return degrees * ((float)M_PI / 180.0f);
	}
};

