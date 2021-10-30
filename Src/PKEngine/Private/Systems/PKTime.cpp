#include <Systems/PKTime.h>

namespace pkengine
{
	#define DurationDoubleMicro(a) (std::chrono::duration<double, std::micro>(a).count())
	#define MicroToSeconds (1.0/1000000)

	float CTime::DeltaTime = 0.0f;
	float CTime::CurrentGameTime = 0.0f;

	CTime::CPKTimePoint CTime::GameStartTimePoint;
	CTime::CPKTimePoint CTime::CachedTimePoint;

	void CTime::GameStarted()
	{
		CPKTimePoint Now = std::chrono::high_resolution_clock::now();
		CachedTimePoint = Now;
		GameStartTimePoint = Now;

		DeltaTime = 0.0f;
		CurrentGameTime = 0.0f;
	}

	void CTime::Tick()
	{
		CPKTimePoint Now = std::chrono::high_resolution_clock::now();
		DeltaTime = DurationDoubleMicro(Now - CachedTimePoint) * MicroToSeconds;
		CurrentGameTime = DurationDoubleMicro(Now - GameStartTimePoint) * MicroToSeconds;
		CachedTimePoint = Now;
	}
}