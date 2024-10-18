#include <Systems/PKSound.h>

#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>

namespace pkengine
{
	CAudioPlayer* CAudioPlayer::Instance = nullptr;

	void CAudioPlayer::Init()
	{
		Instance = new CAudioPlayer();
		Instance->engine = new SoLoud::Soloud();
		Instance->engine->init();
	}

	void CAudioPlayer::CleanUp()
	{
		for (CAudioClip* clip : Instance->loadedClips)
		{
			delete clip->file;
			delete clip;
		}

		Instance->engine->deinit();
		delete Instance->engine;
		delete Instance;
	}

	void CAudioPlayer::Play(const CAudioClip* clip)
	{
		Instance->engine->play(*(clip->file));
	}

	const CAudioClip* CAudioPlayer::Load(const char* clipPath)
	{
		CAudioClip* clip = new CAudioClip();
		clip->file = new SoLoud::Wav();
		clip->file->load(clipPath);

		Instance->loadedClips.push_back(clip);

		return clip;
	}
}