#pragma once

#include <string>
#include <GLFW/glfw3.h>

class AWWindow
{
	public:
		
		bool Init(unsigned int width, unsigned int Height, const std::string& Title);

		void MainLoop();

		void Cleanup();

	private:

		GLFWwindow *mWindow = nullptr;
};