#include <memory>
#include "Window.h"
#include "Logger.h"

int main(int argc, char *argv[]) 
{

	std::unique_ptr<AWWindow> Window = std::make_unique<AWWindow>();
	if (!Window->Init(640, 480, "AnimWeaver Test Window"))
	{
		AW_LOG_ERROR("Window init error");
		return -1;
	}

	Window->MainLoop();
	Window->Cleanup();

	return 0;
}