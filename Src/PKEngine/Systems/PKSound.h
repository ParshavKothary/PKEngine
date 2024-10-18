#pragma once
#ifndef PKENGINE_PKSOUND_H
#define PKENGINE_PKSOUND_H

#include <Core/PKBase.h>

namespace SoLoud
{
	class Soloud;
	class Wav;
}

namespace pkengine
{
	class CAudioClip
	{
		friend class CAudioPlayer;

	private:
		SoLoud::Wav* file;

		CAudioClip()
		{
			file = nullptr;
		}
	};

	class CAudioPlayer
	{
	private:
		static CAudioPlayer* Instance;
		SoLoud::Soloud* engine;
		containers::list<CAudioClip*> loadedClips;

		CAudioPlayer()
		{
			engine = nullptr;
			loadedClips = containers::list<CAudioClip*>();
		}

	public:

		static void Init();
		static void CleanUp();
		static void Play(const CAudioClip* clip);
		static const CAudioClip* Load(const char* clipPath);
	};
}

#endif