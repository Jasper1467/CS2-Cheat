#pragma once

#include "../Dependencies/ImGui/imgui.h"

namespace Renderer
{
	void BeginScene();

	inline void AddLine(const ImVec2& a, const ImVec2& b, const ImU32& Col, float flThickness = 1.f)
	{
		ImGui::GetBackgroundDrawList()->AddLine(a, b, Col, flThickness);
	}

	inline void AddText(const ImVec2& Pos, ImU32 Col, const char* szText)
	{
		ImGui::GetBackgroundDrawList()->AddText(Pos, Col, szText);
	}

	inline void AddText(const ImFont* pFont, float flFontSize, const ImVec2& Pos, ImU32 Col, const char* szText)
	{
		ImGui::GetBackgroundDrawList()->AddText(pFont, flFontSize, Pos, Col, szText);
	}

	inline void AddCircle(const ImVec2& Center, float flRadius, const ImU32& Col, int nSegments/* = 32*/, float flThickness/* = 1.f*/)
	{
		ImGui::GetBackgroundDrawList()->AddCircle(Center, flRadius, Col, nSegments, flThickness);
	}

	inline void AddCircleFilled(const ImVec2& Center, float flRadius, const ImU32& Col, int nSegments/* = 32*/)
	{
		ImGui::GetBackgroundDrawList()->AddCircleFilled(Center, flRadius, Col, nSegments);
	}

	inline void AddRect(const ImVec2& Min, const ImVec2& Max, const ImU32& Col, float flRounding = 0.f,
		float flThickness = 1.f, const ImDrawFlags Flags = 0)
	{
		ImGui::GetBackgroundDrawList()->AddRect(Min, Max, Col, flRounding, Flags, flThickness);
	}

	inline void AddRectFilled(const ImVec2& Min, const ImVec2& Max, const ImU32& Col, float flRounding = 0.f,
		const ImDrawFlags Flags = 0)
	{
		ImGui::GetBackgroundDrawList()->AddRectFilled(Min, Max, Col, flRounding, Flags);
	}

	inline void AddImage(ImTextureID& TextureId, const ImVec2& Min, const ImVec2& Max,
		const ImVec2& UvMin = ImVec2(0, 0), const ImVec2& UvMax = ImVec2(1, 1))
	{
		ImGui::GetBackgroundDrawList()->AddImage(TextureId, Min, Max, UvMin, UvMax);
	}
}