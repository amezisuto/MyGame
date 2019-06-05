#include "InputManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
System::InputManager::InputManager()
{
	mpMouse = std::make_unique<DirectX::Mouse>();
	mpKeyboard = std::make_unique<DirectX::Keyboard>();
}

/// <summary>
/// マウスの入力状態の取得
/// </summary>
/// <returns>入力状態</returns>
DirectX::Mouse::State System::InputManager::GetMouseState()
{
	return mpMouse->GetState();
}

/// <summary>
/// MouseTrackerの取得
/// </summary>
/// <returns>Tracker</returns>
DirectX::Mouse::ButtonStateTracker System::InputManager::GetMouseTracker()
{
	return mMouseTracker;
}

/// <summary>
/// マウスの入力状態の取得
/// </summary>
/// <returns>入力状態</returns>
DirectX::Keyboard::State System::InputManager::GetKeyState()
{
	return mpKeyboard->GetState();
}

/// <summary>
/// KeyboardTrackerの取得
/// </summary>
/// <returns>Tracker</returns>
DirectX::Keyboard::KeyboardStateTracker System::InputManager::GetKeyTracker()
{
	return mKeyTracker;
}

/// <summary>
/// 更新処理
/// </summary>
void System::InputManager::Update()
{
	DirectX::Mouse::State mouseState = GetMouseState();
	mMouseTracker.Update(mouseState);

	DirectX::Keyboard::State keyboardState = GetKeyState();
	mKeyTracker.Update(keyboardState);
}

