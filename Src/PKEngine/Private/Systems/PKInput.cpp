#include <Systems/PKInput.h>
#include <Core/PKCommon.h>

#include <glad/glad.h>

namespace pkengine
{
	std::set<EKeyCode> CInput::DownKeys = std::set<EKeyCode>();
	std::set<EKeyCode> CInput::HeldKeys = std::set<EKeyCode>();
	std::set<EKeyCode> CInput::UpKeys = std::set<EKeyCode>();

	bool CInput::Init(GLFWwindow* Window)
	{
		if (Window == nullptr)
		{
			std::cout << "Error initializing Input System. Window context null" << std::endl;
			return false;
		}

		glfwSetKeyCallback(Window, GLKeyCallback);
		return true;
	}

	void CInput::FlushInput(GLFWwindow* Window)
	{
		DownKeys.clear();
		UpKeys.clear();

		// Verify/Remove held keys
		std::set<EKeyCode>::iterator it = HeldKeys.begin();
		while (it != HeldKeys.end())
		{
			if (glfwGetKey(Window, int(*it)) == GLFW_RELEASE)
			{
				it = HeldKeys.erase(it);
				continue;
			}

			++it;
		}
	}

	void CInput::GLKeyCallback(GLFWwindow* Window, int GLFWKey, int ScanCode, int GLFWAction, int Mods)
	{
		EKeyCode KeyCode = EKeyCode(GLFWKey);

		if (GLFWAction == GLFW_PRESS)
		{
			DownKeys.insert(KeyCode);
			HeldKeys.insert(KeyCode);
			UpKeys.erase(KeyCode);
		}
		else if (GLFWAction == GLFW_RELEASE)
		{
			UpKeys.insert(KeyCode);
			DownKeys.erase(KeyCode);
			HeldKeys.erase(KeyCode);
		}
	}
}