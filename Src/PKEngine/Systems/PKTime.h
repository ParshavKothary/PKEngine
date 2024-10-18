#ifndef PKENGINE_PKTIME_H
#define PKENGINE_PKTIME_H

#include <chrono>

namespace pkengine
{
	class CTime
	{
	private:
		typedef std::chrono::time_point<std::chrono::high_resolution_clock> CTimePoint;

		float DeltaTime;
		float CurrentGameTime;

		CTimePoint CachedTimePoint;

		static CTime* Instance;

		CTime() :
			DeltaTime(0.0f),
			CurrentGameTime(0.0f)
		{}

	public:

		inline static float GetDeltaTime() { return Instance->DeltaTime; }
		inline static float GetCurrentTime() { return Instance->CurrentGameTime; }

		static void Init();
		static void Cleanup();
		static void Start();
		static void Update();
	};
}

#endif // !PKENGINE_PKTIME_H
