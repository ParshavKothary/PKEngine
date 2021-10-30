#ifndef PKENGINE_PKINPUT_H
#define PKENGINE_PKINPUT_H

#include <Core/PKBase.h>
#include <GLFW/glfw3.h>

namespace pkengine
{
	class CInput
	{
		friend class CPKEngine;

	public:
		static bool GetKeyDown(EKeyCode KeyCode) { return DownKeys.find(KeyCode) != DownKeys.end(); }
		static bool GetKeyUp(EKeyCode KeyCode) { return UpKeys.find(KeyCode) != UpKeys.end(); }
		static bool GetKey(EKeyCode KeyCode) { return HeldKeys.find(KeyCode) != HeldKeys.end(); }

	private:
		static bool Init(GLFWwindow* Window);
		static void FlushInput(GLFWwindow* Window);
		static void GLKeyCallback(GLFWwindow* Window, int GLFWKey, int ScanCode, int GLFWAction, int Mods);

		static std::set<EKeyCode> DownKeys;
		static std::set<EKeyCode> HeldKeys;
		static std::set<EKeyCode> UpKeys;
	};
}

#endif // !PKENGINE_PKINPUT_H
