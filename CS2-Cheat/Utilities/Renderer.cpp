#include "Renderer.h"

#include "../Features/Visuals.h"

void Renderer::BeginScene()
{
	Features::Visuals::Run();
}

// !!!!!!!!!IMPORTANT: Staging changes (git) takes too long cause of boostlib, reduce amount of files in directory

void Renderer::AddLine(const ImVec2& a, const ImVec2& b, const ImU32& Col, float flThickness/*=1.f*/)
{
	ImGui::GetBackgroundDrawList()->AddLine(a, b, Col, flThickness);
}