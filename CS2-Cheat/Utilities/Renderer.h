#pragma once

#include "../Dependencies/ImGui/imgui.h"

namespace Renderer
{
	void BeginScene();

	void AddLine(const ImVec2& a, const ImVec2& b, const ImU32& Col, float flThickness = 1.f);
}