#include "Menu.h"

#include "../Dependencies/ImGui/imgui.h"
#include "../Dependencies/ImGui/imgui_impl_dx11.h"

void Menu::Render()
{
	// Doesn't toggle without this for some reason...
	if (!m_bOpen)
		return;

	if (ImGui::Begin("CS2-Cheat", &m_bOpen))
	{
		ImGui::End();
	}
}