//---------------------------------------
// プレイ画面背景クラス
//---------------------------------------
#pragma once

#include "../TaskManager.h"
class SerectGame;

class SerectBg : public Task
{
	// ゲームウインドウへのポインタ
	SerectGame* m_serectGame;

	// モデルデータへのポインタ
	std::unique_ptr<DirectX::Model> m_model;

	// 回転角
	float m_angle;

public:
	// コンストラクタ
	SerectBg();

	// 初期化関数
	void Initialize(SerectGame* serectGame);

	// 更新関数
	bool Update(float elapsedTime) override;

	// 描画関数
	void Render() override;
};

