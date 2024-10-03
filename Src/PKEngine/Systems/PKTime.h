#ifndef PKENGINE_PKTIME_H
#define PKENGINE_PKTIME_H

#include <chrono>

namespace pkengine
{
	class CTime
	{
		friend class CPKEngine;
		typedef std::chrono::time_point<std::chrono::high_resolution_clock> CPKTimePoint;

	public:
		inline static float GetDeltaTime() { return DeltaTime; }
		inline static float GetCurrentTime() { return CurrentGameTime; }

	private:
		static void GameStarted();
		static void Tick();

		static float DeltaTime;
		static float CurrentGameTime;

		static CPKTimePoint GameStartTimePoint;
		static CPKTimePoint CachedTimePoint;
	};
}

#endif // !PKENGINE_PKTIME_H
