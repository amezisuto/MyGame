#pragma once

#include <Mouse.h>
#include <Keyboard.h>
#include "SingletonBase.h"


namespace System
{
	class InputManager : public Utility::SingletonBase<InputManager>
	{
	public:

		friend Utility::SingletonBase<InputManager>;

	private:

		InputManager();

	public:

		// マウスの状態取得
		DirectX::Mouse::State GetMouseState();

		// Trackerの取得
		DirectX::Mouse::ButtonStateTracker GetMouseTracker();

		// マウス座標の取得
		int GetMousePosX()
		{
			return GetMouseState().x;
		}
		int GetMousePosY()
		{
			return GetMouseState().y;
		}

		// 更新
		void Update();

	public:

		// キーボードの状態取得
		DirectX::Keyboard::State GetKeyState();

		// Trackerの取得
		DirectX::Keyboard::KeyboardStateTracker GetKeyTracker();

	private:

		// マウス
		std::unique_ptr<DirectX::Mouse> mpMouse;

		// Tracker
		DirectX::Mouse::ButtonStateTracker mMouseTracker;

		// キーボード
		std::unique_ptr<DirectX::Keyboard> mpKeyboard;

		// Tracker
		DirectX::Keyboard::KeyboardStateTracker mKeyTracker;
	};
}