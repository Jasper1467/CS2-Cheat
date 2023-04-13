#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

#include "../SDK/Vectors.h"
#include "../Dependencies/ImGui/imgui.h"

namespace Math
{
	bool WorldToScreen(Vector& vecWorld, Vector2D& vecScreen);
	bool WorldToScreen(Vector& vecWorld, ImVec2& vecScreen);
}