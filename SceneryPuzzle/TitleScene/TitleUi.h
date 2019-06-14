//---------------------------------------
// タイトルUIクラス
//---------------------------------------
#pragma once

#include "../TaskManager.h"
class Game;

class TitleUi :public Task
{
public:
	TitleUi();
	~TitleUi();
	void Initialize(Game* game);

	bool Update(float elapsedTime)override;
	void Render()override;

private:
	Game* m_game;
	// テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pushSpaceTexture;

	// 表示フラグ
	bool m_displayFlag;

	// 点滅間隔
	float m_interval;

	// 点滅カウンタ
	float m_counter;
};