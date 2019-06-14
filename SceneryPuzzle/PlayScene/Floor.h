//---------------------------------------
// 床クラス
//---------------------------------------
#pragma once

#include "../Livr/Object.h"
class Stage;

class Floor : public Object
{
public:
	// 床の状態
	enum State
	{
		NONE,		// 床なし
		NORMAL,		// 通常
		PILLER,	// 柱
		LODE,		// 移動した

		STATE_NUM
	};

	// ダメージの移行時間
	static const float LODE_DELAY_TIME;

private:
	// ステージへのポインタ
	Stage* m_stage;

	// モデルデータへのポインタ
	DirectX::Model* m_models[STATE_NUM];

	// 床の状態
	State m_state;

	// 位置
	DirectX::SimpleMath::Vector3 m_pos;

	// ダメージフラグ（１フレームに１回しかダメージが入らないようにするためのフラグ）
	bool m_lodeFlag;

	// ダメージが入って次の状態に移行するまでのタイマー
	float m_lodeTimer;

public:
	// コンストラクタ
	Floor();

	// 初期化関数
	void Initialize(Stage* stage, int x, int y);

	// 更新関数
	bool Update(float elapsedTime) override;

	// 描画関数
	void Render() override;

	// モデル設定関数
	void SetModel(State state, DirectX::Model* model);

	// 床の状態を設定する関数
	void SetState(Floor::State state) { m_state = state; }

	// 床の状態を取得する関数
	Floor::State GetState() { return m_state; }

	DirectX::SimpleMath::Vector3 GetPosion() { return m_pos; }

	// ダメージを与える関数
	void Lode();

	// リセット関数
	void Reset();
};
