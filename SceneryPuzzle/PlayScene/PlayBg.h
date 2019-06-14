//---------------------------------------
// プレイ画面背景クラス
//---------------------------------------
#pragma once

#include "../TaskManager.h"
class PlayGame;

class PlayBg : public Task
{
	// ゲームウインドウへのポインタ
	PlayGame* m_playGame;

	// モデルデータへのポインタ
	std::unique_ptr<DirectX::Model> m_model;

	// 回転角
	float m_angle;

public:
	// コンストラクタ
	PlayBg();

	// 初期化関数
	void Initialize(PlayGame* playGame);

	// 更新関数
	bool Update(float elapsedTime) override;

	// 描画関数
	void Render() override;
}

