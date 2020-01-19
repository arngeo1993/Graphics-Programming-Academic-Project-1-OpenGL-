#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include<unordered_map>
#include"GLFW/glfw3.h"

enum KEYBOARD_KEYS {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SPACE,
	M,
	ENTER,
	ESC,
	Q,
	E,
	W,
	S,
	A,
	D,
	V,
	NuM
};

class InputManager
{
public:
	InputManager();
	~InputManager();

	void Update();

	bool isPressed(unsigned int KeyScanCode);

	bool isTriggered(unsigned int KeyScanCode);
	bool isReleased(unsigned int KeyScanCode);

private:
	void UpdateStatesForKeyboardKeys();

	int keyCodes[NuM];

	std::unordered_map<KEYBOARD_KEYS, bool> keyStatePressed;
	std::unordered_map<KEYBOARD_KEYS, bool> keyStateReleased;
	std::unordered_map<KEYBOARD_KEYS, bool> keyStateTriggered;
};

#endif // !INPUT_MANAGER_H





