#include "Window.h"
#include "Logger.h"

#define ACTION_NAME_PRESSED		"Pressed"
#define ACTION_NAME_RELEASED	"Released"
#define ACTION_NAME_REPEATED	"Repeated"
#define ACTION_NAME_INVALID		"Invalid"

#define BUTTON_NAME_LEFT		"Left"
#define BUTTON_NAME_MIDDLE		"Middle"
#define BUTTON_NAME_RIGHT		"Right"
#define BUTTON_NAME_OTHER		"Other"

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

	glfwMakeContextCurrent(mWindow);

	/*
	* Store pointer to this class inside glfw se we can use it insinde passed lambda to glfwSetWindowCloseCallback
	* This is due to lamda capturing not being supported for c-style function pointers wich glfwSetWindowCloseCallback uses.
	*/ 
	glfwSetWindowUserPointer(mWindow, this);

	glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* Window) {
		AWWindow* ThisWindow = static_cast<AWWindow*>(glfwGetWindowUserPointer(Window));
		if (!ThisWindow)
		{
			AW_LOG_ERROR("GLFW user pointer contains a wrong window type or is missing");
			return;
		}

		ThisWindow->HandleWindowCloseEvents();
	});

	glfwSetKeyCallback(mWindow, [](GLFWwindow* Window, int Keys, int ScanCode, int Action, int Mods) {
		AWWindow* ThisWindow = static_cast<AWWindow*>(glfwGetWindowUserPointer(Window));
		if (!ThisWindow)
		{
			AW_LOG_ERROR("GLFW user pointer contains a wrong window type or is missing");
			return;
		}

		ThisWindow->HandleKeyEvents(Keys, ScanCode, Action, Mods);
	});

	glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* Window, int Button, int Action, int Mods) { 
		AWWindow* ThisWindow = static_cast<AWWindow*>(glfwGetWindowUserPointer(Window));
		if (!ThisWindow)
		{
			AW_LOG_ERROR("GLFW user pointer contains a wrong window type or is missing");
			return;
		}

		ThisWindow->HandleMouseButtonEvents(Button, Action, Mods);
	});

	Logger::Log(1, "%s: Window successfully initialized\n", __FUNCTION__);
	return true;
}

void AWWindow::MainLoop()
{
	glfwSwapInterval(1);
	float Color = 0.f;
	while (!glfwWindowShouldClose(mWindow))
	{
		Color >= 1.f ? Color = 0.f : Color += 0.01f;
		glClearColor(Color, Color, Color, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mWindow);

		glfwPollEvents();
	}
}

void AWWindow::Cleanup()
{
	Logger::Log(1, "%s: Terminating Window\n", __FUNCTION__);
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

void AWWindow::HandleKeyEvents(int Key, int ScanCode, int Action, int Mods)
{
	std::string ActionName;
	switch (Action)
	{
		case GLFW_PRESS:
			ActionName = ACTION_NAME_PRESSED;
			break;

		case GLFW_RELEASE:
			ActionName = ACTION_NAME_RELEASED;
			break;

		case GLFW_REPEAT:
			ActionName = ACTION_NAME_REPEATED;
			break;

		default:
			ActionName = ACTION_NAME_INVALID;
			break;
	}

	const char* KeyName = glfwGetKeyName(Key, 0);
	Logger::Log(1, "%s: key %s (key %i, ScanCode %i) %s\n", __FUNCTION__, KeyName, Key, ScanCode, ActionName.c_str());
}

void AWWindow::HandleMouseButtonEvents(int Button, int Action, int Mods)
{
	std::string ActionName;
	switch (Action)
	{
		case GLFW_PRESS:
			ActionName = ACTION_NAME_PRESSED;
			break;

		case GLFW_RELEASE:
			ActionName = ACTION_NAME_RELEASED;
			break;

		default:
			ActionName = ACTION_NAME_INVALID;
			break;
	}

	std::string MouseButtonName;
	switch (Button)
	{
		case GLFW_MOUSE_BUTTON_LEFT:
			MouseButtonName = BUTTON_NAME_LEFT;
			break;

		case GLFW_MOUSE_BUTTON_MIDDLE:
			MouseButtonName = BUTTON_NAME_MIDDLE;
			break;

		case GLFW_MOUSE_BUTTON_RIGHT:
			MouseButtonName = BUTTON_NAME_RIGHT;
			break;

		default:
			MouseButtonName = BUTTON_NAME_OTHER;
			break;
	}
	Logger::Log(1, "%s: %s mouse button (%i) %s\n",__FUNCTION__, MouseButtonName.c_str(), Button, ActionName.c_str());
}

void AWWindow::HandleWindowCloseEvents()
{
	AW_LOG("Window got close event... see ya.");
}
