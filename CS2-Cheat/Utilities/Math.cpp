#include "Math.h"

#include "SigScanner.h"

#include "Client.h"

bool Math::WorldToScreen(Vector& vecWorld, Vector2D& vecScreen)
{
	using Fn = bool(__fastcall*)(Vector&, Vector2D&);
	static Fn Func = SIGNATURE_SCAN(CLIENT_DLL, "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 1D ? ? ? ? 48 8B FA").Get<Fn>();

	bool bRet = !Func(vecWorld, vecScreen);

	vecScreen.x = static_cast<float>((vecScreen.x + 1.f) * 0.5f) * Client::m_nScreenWidth;
	vecScreen.y = Client::m_nScreenHeight - (static_cast<float>((vecScreen.y + 1.f) * 0.5f) * Client::m_nScreenHeight);

	return bRet;
}

bool Math::WorldToScreen(Vector& vecWorld, ImVec2& vecScreen)
{
	Vector2D tmp;
	bool bRet = WorldToScreen(vecWorld, tmp);

	vecScreen = ImVec2(tmp.x, tmp.y);

	return bRet;
}