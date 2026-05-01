#include "Window.h"
#include "Logger.h"

bool AWWindow::Init(unsigned int Width, unsigned int Height, const std::string& Title)
{
	if (!glfwInit())
	{
		Logger::Log(1, "%s: glfwInit() error\n", __FUNCTION__);
		return false;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	mWindow = glfwCreateWindow(Width, Height, Title.c_str(), nullptr, nullptr);
	if (!mWindow)
	{
		Logger::Log(1, "%s: Could not create window\n", __FUNCTION__);
		glfwTerminate();
		return false;
	}

	Logger::Log(1, "%s: Window successfully initialized\n", __FUNCTION__);
	return true;
}

void AWWindow::MainLoop()
{
	while (!glfwWindowShouldClose(mWindow))
	{
		glfwPollEvents();
	}
}

void AWWindow::Cleanup()
{
	Logger::Log(1, "%s: Terminating Window\n", __FUNCTION__);
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

