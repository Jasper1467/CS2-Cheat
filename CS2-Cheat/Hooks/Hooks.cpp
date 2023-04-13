#include "Hooks.h"

#include "../Utilities/SigScanner.h"

#include "../Dependencies/dynohook/conventions/x64/x64MsFastcall.hpp"

#include "../Dependencies/kiero/kiero.h"
#include "../Dependencies/kiero/minhook/include/MinHook.h"

#include "../Menu/Menu.h"

#include "../Features/Visuals.h"

#include <intrin.h>
#include "../Dependencies/ImGui/imgui_impl_dx11.h"
#include "../Dependencies/ImGui/imgui_impl_win32.h"

#include "../Utilities/Renderer.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef HRESULT(__stdcall* PresentFn) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

typedef HRESULT(__stdcall* ResizeBuffersFn) (IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height,
	DXGI_FORMAT NewFormat, UINT SwapChainFlag);

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

PresentFn oPresent;
ResizeBuffersFn oResizeBuffers;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void Hooks::Initialize()
{
	//dyno::HookManager& Manager = dyno::HookManager::Get();

	//Managers::m_pFrameStageNotify = Manager.hook((SIGNATURE_SCAN("client.dll", "48 89 5C 24 10 56 48 83 EC 30 8B 05 ? ? ? ?").Get<void*>()),
		//new dyno::x64MsFastcall({dyno::DATA_TYPE_POINTER, dyno::DATA_TYPE_INT}, dyno::DATA_TYPE_VOID));

	bool init_kiero_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11))
		{
			// TODO: make these indexes obfuscated using oxorany
			kiero::bind(8, (void**)&oPresent, hkPresent);
			kiero::bind(13, (void**)& oResizeBuffers, hkResizeBuffers);

			init_kiero_hook = true;
		}
	} while (!init_kiero_hook);

	MH_Initialize();

	MH_CreateHook(SIGNATURE_SCAN("client.dll", "48 89 5C 24 10 56 48 83 EC 30 8B 05 ? ? ? ?").Get<void*>(), hkFrameStageNotify,
		(void**)m_oFrameStageNotify);

	MH_EnableHook(MH_ALL_HOOKS);
}

LRESULT __stdcall Hooks::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN && LOWORD(wParam) == VK_INSERT)
		Menu::m_bOpen = !Menu::m_bOpen;

	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
	if (Menu::m_bOpen)
	{
		switch (uMsg)
		{
		case WM_MOUSEMOVE:
		case WM_NCMOUSEMOVE:
		case WM_MOUSELEAVE:
		case WM_NCMOUSELEAVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONDBLCLK:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONDBLCLK:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_XBUTTONUP:
		case WM_MOUSEWHEEL:
		case WM_MOUSEHWHEEL:
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_SETFOCUS:
		case WM_KILLFOCUS:
		case WM_CHAR:
		case WM_DEVICECHANGE:
			return 1;
		}
	}

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

bool init = false;
HRESULT __stdcall Hooks::hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();

			init = true;
		}
		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Renderer::BeginScene();

	Menu::Render();

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

HRESULT __stdcall Hooks::hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height,
	DXGI_FORMAT NewFormat, UINT SwapChainFlag)
{
	if (mainRenderTargetView)
	{
		mainRenderTargetView->Release();
		mainRenderTargetView = nullptr;
	}

	if (pContext)
	{
		pContext->Release();
		pContext = nullptr;
	}

	if (pDevice)
	{
		pDevice->Release();
		pDevice = nullptr;
	}

	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();

	return oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlag);
}

void __fastcall Hooks::hkFrameStageNotify(void* ecx, int nStage)
{
	//Managers::m_pFrameStageNotify->getReturnValue<decltype(&hkFrameStageNotify)>()(ecx, nStage);
	m_oFrameStageNotify(ecx, nStage);
}