#ifndef PKENGINE_PKINPUT_H
#define PKENGINE_PKINPUT_H

#include <Core/PKBase.h>

namespace pkengine
{
	class CInput
	{
	public:
		static bool GetKeyDown(EKeyCode KeyCode) { return Instance->DownKeys.find(KeyCode) != Instance->DownKeys.end(); }
		static bool GetKeyUp(EKeyCode KeyCode) { return Instance->UpKeys.find(KeyCode) != Instance->UpKeys.end(); }
		static bool GetKey(EKeyCode KeyCode) { return Instance->HeldKeys.find(KeyCode) != Instance->HeldKeys.end(); }

		static bool Init(GLFWwindow* Window);
		static void CleanUp();
		static void Update();
		static void FlushInput(GLFWwindow* Window);

	private:
		typedef containers::uset<EKeyCode> IKeySet;

		static void GLKeyCallback(GLFWwindow* Window, int GLFWKey, int ScanCode, int GLFWAction, int Mods);
		
		static CInput* Instance;

		IKeySet DownKeys;
		IKeySet HeldKeys;
		IKeySet UpKeys;
	};
}

#endif // !PKENGINE_PKINPUT_H
