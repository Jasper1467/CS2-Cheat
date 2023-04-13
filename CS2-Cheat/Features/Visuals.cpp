#include "Visuals.h"

#include "../Utilities/Renderer.h"

#include "../Dependencies/ImGui/imgui.h"
#include "../Dependencies/ImGui/imgui_impl_dx11.h"
#include "../Dependencies/ImGui/imgui_impl_win32.h"

void Features::Visuals::Run()
{
	// test
	Renderer::AddLine(ImVec2(0, 0), ImVec2(1920, 1080), IM_COL32(255, 255, 255, 255), 10.f);
}