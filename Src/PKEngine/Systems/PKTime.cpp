#include <Systems/PKTime.h>

namespace pkengine
{
	#define DurationDoubleMicro(a) (std::chrono::duration<double, std::micro>(a).count())
	#define MicroToSeconds (1.0/1000000)

	CTime* CTime::Instance = nullptr;

	void CTime::Init()
	{
		Instance = new CTime();
	}

	void CTime::Cleanup()
	{
		delete Instance;
	}

	void CTime::Start()
	{
		CTimePoint Now = std::chrono::high_resolution_clock::now();
		Instance->CachedTimePoint = Now;

		Instance->DeltaTime = 0.0f;
		Instance->CurrentGameTime = 0.0f;
	}

	void CTime::Update()
	{
		CTimePoint Now = std::chrono::high_resolution_clock::now();
		Instance->DeltaTime = DurationDoubleMicro(Now - Instance->CachedTimePoint) * MicroToSeconds;
		Instance->CurrentGameTime += Instance->DeltaTime;
		Instance->CachedTimePoint = Now;

#ifdef _DEBUG
		if (Instance->DeltaTime > 1.0f) // probably debugging
		{
			float correction = Instance->DeltaTime - 0.016f;
			Instance->DeltaTime -= correction;
		}
#endif
	}
}