
#include "InputManager.h"
#include "GLFW/glfw3.h"

extern GLFWwindow* gpWindow;

InputManager::~InputManager()
{
}

void InputManager::Update()
{
	UpdateStatesForKeyboardKeys();
}

void InputManager::UpdateStatesForKeyboardKeys() {
	int state = 0;
	for (int i = 0; i < NuM; ++i) {
		state = glfwGetKey(gpWindow, keyCodes[i]);

		if (state == GLFW_PRESS) {
			// check for triggered
			if (keyStateReleased[static_cast<KEYBOARD_KEYS>(i)]) {
				keyStateTriggered[static_cast<KEYBOARD_KEYS>(i)] = true;
			}
			else {
				keyStateTriggered[static_cast<KEYBOARD_KEYS>(i)] = false;
			}

			keyStatePressed[static_cast<KEYBOARD_KEYS>(i)] = true;
			keyStateReleased[static_cast<KEYBOARD_KEYS>(i)] = false;

		}
		else if (state == GLFW_RELEASE) {
			keyStatePressed[static_cast<KEYBOARD_KEYS>(i)] = false;
			keyStateTriggered[static_cast<KEYBOARD_KEYS>(i)] = false;
			keyStateReleased[static_cast<KEYBOARD_KEYS>(i)] = true;
		}
	}
}

bool InputManager::isPressed(unsigned int KeyScanCode) {
	return keyStatePressed[static_cast<KEYBOARD_KEYS>(KeyScanCode)];
}


bool InputManager::isTriggered(unsigned int KeyScanCode) {
	return keyStateTriggered[static_cast<KEYBOARD_KEYS>(KeyScanCode)];
}

bool InputManager::isReleased(unsigned int KeyScanCode) {
	return keyStateReleased[static_cast<KEYBOARD_KEYS>(KeyScanCode)];
}

InputManager::InputManager()
{
	// set all keycodes for keys used in game
	keyCodes[0] = GLFW_KEY_UP;
	keyCodes[1] = GLFW_KEY_DOWN;
	keyCodes[2] = GLFW_KEY_LEFT;
	keyCodes[3] = GLFW_KEY_RIGHT;
	keyCodes[4] = GLFW_KEY_SPACE;
	keyCodes[5] = GLFW_KEY_M;
	keyCodes[6] = GLFW_KEY_ENTER;
	keyCodes[7] = GLFW_KEY_ESCAPE;
	keyCodes[8] = GLFW_KEY_Q;
	keyCodes[9] = GLFW_KEY_E;
	keyCodes[10] = GLFW_KEY_W;
	keyCodes[11] = GLFW_KEY_S;
	keyCodes[12] = GLFW_KEY_A;
	keyCodes[13] = GLFW_KEY_D;
	keyCodes[14] = GLFW_KEY_V;

	for (int i = 0; i < NuM; ++i) {
		keyStatePressed[static_cast<KEYBOARD_KEYS>(i)] = false;
		keyStateTriggered[static_cast<KEYBOARD_KEYS>(i)] = false;
		keyStateReleased[static_cast<KEYBOARD_KEYS>(i)] = true;
	}
}