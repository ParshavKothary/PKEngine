#ifndef PKENGINE_PKTIME_H
#define PKENGINE_PKTIME_H

#include <chrono>

namespace pkengine
{
	class CTime
	{
		friend class CPKEngine;

	public:
		inline static float GetDeltaTime() { return DeltaTime; }
		inline static float GetCurrentTime() { return CurrentGameTime; }

	private:
		static void GameStarted();
		static void Tick();

		static float MicroToSeconds(const double& MicroSeconds);
		
		static float GameStartTime;
		static float DeltaTime;
		static float CurrentGameTime;

		static std::chrono::time_point<std::chrono::high_resolution_clock> GameStartTimePoint;
		static std::chrono::time_point<std::chrono::high_resolution_clock> CachedTimePoint;
	};
}

#endif // !PKENGINE_PKTIME_H
