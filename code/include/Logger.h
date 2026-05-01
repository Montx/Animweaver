#pragma once
#include <cstdio>

#define AW_LOG(Text) Logger::Log(1, "%s: %s\n", __FUNCTION__, Text);
#define AW_LOG_ERROR(Text) Logger::Log(1, "%s error: %s\n", __FUNCTION__, Text);

class Logger
{
	public:
		
		template <typename... Args>
		static void Log(unsigned int LogLevel, Args ... args)
		{
			if (LogLevel <= mLogLevel)
			{
				std::printf(args ...);
				std::fflush(stdout);
			}
		}

		static void SetLogLevel(unsigned int InLogLevel)
		{
			InLogLevel <= 9 ? mLogLevel = InLogLevel : mLogLevel = 9;
		}

	private:
		static unsigned int mLogLevel;
};