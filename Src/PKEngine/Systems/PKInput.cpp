#include <Systems/PKInput.h>

#include <glad/glad.h>

namespace pkengine
{
	CInput* CInput::Instance = nullptr;

	bool CInput::Init(GLFWwindow* Window)
	{
		if (Window == nullptr)
		{
			std::cout << "Error initializing Input System. Window context null" << std::endl;
			return false;
		}

		glfwSetKeyCallback(Window, GLKeyCallback);
		Instance = new CInput();
		return true;
	}

	void CInput::CleanUp()
	{
		delete Instance;
	}

	void CInput::Update()
	{
		glfwPollEvents();
	}

	void CInput::FlushInput(GLFWwindow* Window)
	{
		Instance->DownKeys.clear();
		Instance->UpKeys.clear();

		// Verify/Remove held keys
		containers::uset<EKeyCode>::iterator it = Instance->HeldKeys.begin();
		while (it != Instance->HeldKeys.end())
		{
			if (glfwGetKey(Window, int(*it)) == GLFW_RELEASE)
			{
				it = Instance->HeldKeys.erase(it);
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
			Instance->DownKeys.insert(KeyCode);
			Instance->HeldKeys.insert(KeyCode);
			Instance->UpKeys.erase(KeyCode);
		}
		else if (GLFWAction == GLFW_RELEASE)
		{
			Instance->UpKeys.insert(KeyCode);
			Instance->DownKeys.erase(KeyCode);
			Instance->HeldKeys.erase(KeyCode);
		}
	}
}