#include "Visuals.h"

#include "../Utilities/Renderer.h"

#include "../Dependencies/ImGui/imgui.h"
#include "../Dependencies/ImGui/imgui_impl_dx11.h"
#include "../Dependencies/ImGui/imgui_impl_win32.h"

#include "../Utilities/Client.h"
#include "../SDK/CPlayer.h"

#include "../Utilities/Math.h"

void Features::Visuals::Run()
{
	// test
	//Renderer::AddLine(ImVec2(0, 0), ImVec2(1920, 1080), IM_COL32(255, 255, 255, 255), 10.f);

	for (auto Ent : Client::m_Entities)
	{
		auto pEntity = (C_BaseEntity*)Ent.first;

		Vector vecAbsOrigin = pEntity->m_pGameSceneNode()->m_vecAbsOrigin();
		ImVec2 Screen{};
		if (Math::WorldToScreen(vecAbsOrigin, Screen))
			Renderer::AddLine(ImVec2(Client::m_nScreenWidth / 2, Client::m_nScreenHeight), Screen, IM_COL32(255, 255, 255, 255));
	}
}