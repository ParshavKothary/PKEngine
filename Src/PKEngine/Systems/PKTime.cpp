#include <Systems/PKTime.h>

namespace pkengine
{
	#define DurationDoubleMicro(a) (std::chrono::duration<double, std::micro>(a).count())
	#define MicroToSeconds (1.0/1000000)

	float CTime::DeltaTime = 0.0f;
	float CTime::CurrentGameTime = 0.0f;

	CTime::CTimePoint CTime::GameStartTimePoint;
	CTime::CTimePoint CTime::CachedTimePoint;

	void CTime::Start()
	{
		CTimePoint Now = std::chrono::high_resolution_clock::now();
		CachedTimePoint = Now;
		GameStartTimePoint = Now;

		DeltaTime = 0.0f;
		CurrentGameTime = 0.0f;
	}

	void CTime::Update()
	{
		CTimePoint Now = std::chrono::high_resolution_clock::now();
		DeltaTime = DurationDoubleMicro(Now - CachedTimePoint) * MicroToSeconds;
		CurrentGameTime = DurationDoubleMicro(Now - GameStartTimePoint) * MicroToSeconds;
		CachedTimePoint = Now;

#ifdef _DEBUG
		if (DeltaTime > 1.0f) // probably debugging
		{
			float correction = DeltaTime - 0.016f;
			DeltaTime -= correction;
			CurrentGameTime -= correction;
		}
#endif
	}
}