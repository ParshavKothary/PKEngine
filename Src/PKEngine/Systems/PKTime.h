#ifndef PKENGINE_PKTIME_H
#define PKENGINE_PKTIME_H

#include <chrono>

namespace pkengine
{
	class CTime
	{
		typedef std::chrono::time_point<std::chrono::high_resolution_clock> CTimePoint;

	public:
		inline static float GetDeltaTime() { return DeltaTime; }
		inline static float GetCurrentTime() { return CurrentGameTime; }

		static void Start();
		static void Update();

	private:
		static float DeltaTime;
		static float CurrentGameTime;

		static CTimePoint GameStartTimePoint;
		static CTimePoint CachedTimePoint;
	};
}

#endif // !PKENGINE_PKTIME_H
