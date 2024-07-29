#include "Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[]) {
	g_engine.Initialize();

	while (!g_engine.IsQuit())
	{
		g_engine.Update();

		RENDERER.SetColor(0, 0, 0);
		RENDERER.BeginFrame();

		PARTICLESYSTEM.Draw(RENDERER);

		RENDERER.EndFrame();

	}

	g_engine.Shutdown();

	return 0;
}