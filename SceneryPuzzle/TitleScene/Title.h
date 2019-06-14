//---------------------------------------
// ゲームタイトルクラス
//---------------------------------------
#pragma once

#include "../TaskManager.h"
class Game;

class Title :public Task
{
public:
	Title();
	~Title();
	void Initialize(Game* game);

	bool Update(float elapsedTime)override;
	void Render()override;

private:
	Game* m_game;

	// テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleTexture;
};
