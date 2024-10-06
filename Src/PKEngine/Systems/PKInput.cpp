#include <Systems/PKInput.h>

#include <glad/glad.h>

namespace pkengine
{
	containers::uset<EKeyCode> CInput::DownKeys = containers::uset<EKeyCode>();
	containers::uset<EKeyCode> CInput::HeldKeys = containers::uset<EKeyCode>();
	containers::uset<EKeyCode> CInput::UpKeys = containers::uset<EKeyCode>();

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

	void CInput::Update()
	{
		glfwPollEvents();
	}

	void CInput::FlushInput(GLFWwindow* Window)
	{
		DownKeys.clear();
		UpKeys.clear();

		// Verify/Remove held keys
		containers::uset<EKeyCode>::iterator it = HeldKeys.begin();
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