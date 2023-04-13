#include "Renderer.h"

#include "../Features/Visuals.h"

void Renderer::BeginScene()
{
	Features::Visuals::Run();
}