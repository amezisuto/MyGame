//---------------------------------------
// タイトル背景クラス
//---------------------------------------
#pragma once

#include "../TaskManager.h"
class Game;

class TitleBg :public Task
{
public:
	TitleBg();
	~TitleBg();
	void Initialize();

	bool Update(float elapsedTime)override;
	void Render()override;

private:
	Game* m_game;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
};