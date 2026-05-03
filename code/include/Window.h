#pragma once

#include <string>
#include <GLFW/glfw3.h>

class AWWindow
{
	public:
		
		bool Init(unsigned int width, unsigned int Height, const std::string& Title);

		void MainLoop();

		void Cleanup();

		void HandleKeyEvents(int Key, int ScanCode, int Action, int Mods);

	private:
		void HandleWindowCloseEvents();
		void HandleMouseButtonEvents(int Button, int Action, int Mods);

	private:

		GLFWwindow *mWindow = nullptr;
};