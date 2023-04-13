#pragma once
#include <cstdint>
#include <Windows.h>
#include <dxgi.h>
#include <d3d11.h>

//#include "../Dependencies/dynohook/hook.hpp"
//#include "../Dependencies/dynohook/manager.hpp"

class CUserCmd;

namespace Hooks
{
	void Initialize();

	namespace Managers
	{
		//inline dyno::Hook* m_pFrameStageNotify = nullptr;
	}

	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height,
		DXGI_FORMAT NewFormat, UINT SwapChainFlag);

	using FrameStageNotifyFn = void(__fastcall*)(void*, int);
	inline FrameStageNotifyFn m_oFrameStageNotify;
	void __fastcall hkFrameStageNotify(void* ecx, int nStage);
}