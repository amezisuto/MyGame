#include "InputManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
System::InputManager::InputManager()
{
	mpMouse = std::make_unique<DirectX::Mouse>();
	mpKeyboard = std::make_unique<DirectX::Keyboard>();
}

/// <summary>
/// �}�E�X�̓��͏�Ԃ̎擾
/// </summary>
/// <returns>���͏��</returns>
DirectX::Mouse::State System::InputManager::GetMouseState()
{
	return mpMouse->GetState();
}

/// <summary>
/// MouseTracker�̎擾
/// </summary>
/// <returns>Tracker</returns>
DirectX::Mouse::ButtonStateTracker System::InputManager::GetMouseTracker()
{
	return mMouseTracker;
}

/// <summary>
/// �}�E�X�̓��͏�Ԃ̎擾
/// </summary>
/// <returns>���͏��</returns>
DirectX::Keyboard::State System::InputManager::GetKeyState()
{
	return mpKeyboard->GetState();
}

/// <summary>
/// KeyboardTracker�̎擾
/// </summary>
/// <returns>Tracker</returns>
DirectX::Keyboard::KeyboardStateTracker System::InputManager::GetKeyTracker()
{
	return mKeyTracker;
}

/// <summary>
/// �X�V����
/// </summary>
void System::InputManager::Update()
{
	DirectX::Mouse::State mouseState = GetMouseState();
	mMouseTracker.Update(mouseState);

	DirectX::Keyboard::State keyboardState = GetKeyState();
	mKeyTracker.Update(keyboardState);
}

