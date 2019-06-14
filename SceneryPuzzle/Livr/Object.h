//--------------------------------------------------------------------------------------
// File: Object.h
//
// オブジェクトクラス
//
// Date: 2018.12.5
// Author: Takeshi Yamaguthi
//--------------------------------------------------------------------------------------
#pragma once

#include "../TaskManager.h"

class GameScene;

// オブジェクトクラス
class Object : public Task
{
public:

	// オブジェクトＩＤ
	enum OBJECT_ID
	{
		NONE,		// なし
		BALL,		// ボール
		TRY,		// △
		NOTB,		// 進入禁止
		GOAL,		// ゴール
		PLAYER,		// プレイヤー
		PILLAR      //	柱
	};

protected:

	// ゲームウインドウへのポインタ
	GameScene* m_gameScene;

	// モデルデータへのポインタ
	DirectX::Model* m_model;

	// 向いている方向（８方向で表す。各ビットで押された方向を表す。）
	int m_dir;

	// 質量
	float m_weight;

	// 床との摩擦係数（μ）
	float m_coefficientOfFriction;

	// 加速度
	DirectX::SimpleMath::Vector3 m_a;

	// 速度
	DirectX::SimpleMath::Vector3 m_v;

	// 位置
	DirectX::SimpleMath::Vector3 m_pos;

	// タスク消去フラグ
	bool m_killFlag;

	// 半径
	float m_radius;

	// 幅と高さ
	float m_w, m_h;

	// 衝突フラグ
	bool m_hitFlag;

	// 床のチェック関数
	std::function<bool(Object*)> m_floorCheckFunction;

	// 得点を加算する関数
	std::function<void(int score)> m_addScoreFunction;

	// 表示フラグ
	bool m_displayFlag;

	// 更新関数を実行するかどうか判断するフラグ
	bool m_activeFlag;

	// ステージ上の位置
	int m_x, m_y;

public:
	// コンストラクタ
	Object();

	// 更新
	bool Update(float elapsedTime) override;

	// 描画
	void Render() override;

	// タスク消去関数
	virtual void Kill() { m_killFlag = true; }

	// オブジェクトＩＤを取得する関数
	virtual Object::OBJECT_ID GetID() = 0;

	// 衝突したら呼ばれる関数
	virtual void OnHit(Object* obj) {};

	// 位置を取得する関数
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_pos; }

	// 半径を取得する関数
	float GetRadius() { return m_radius; }

	// 衝突フラグの設定関数
	void SetHitFlag(bool flag) { m_hitFlag = flag; }

	// 衝突フラグの取得関数
	bool GetHitFlag() { return m_hitFlag; }

	// 幅を取得する関数
	float GetWidth() { return m_w; }

	// 高さを取得する関数
	float GetHeight() { return m_h; }

	// 質量を取得する関数
	float GetWeight() { return m_weight; }

	// 床のチェック関数の登録関数
	void SetCheckFloorFunction(std::function<bool(Object* object)> func);

	// 得点を加算する関数の登録関数
	void SetAddScoreFunction(std::function<void(int score)> func);

	// 表示のON/OFFする関数
	void SetDisplayFlag(bool flag) { m_displayFlag = flag; }

	// 表示のON/OFFを取得する関数
	bool GetDisplayFlag() { return m_displayFlag; }

	// 更新関数を実行するかどうか設定する関数
	void SetActive(bool flag) { m_activeFlag = flag; }

	// 衝突した時に相手に与える力を取得する関数
	virtual float GetHitForce();

	// リセット関数
	virtual void Reset() {}

protected:
	// 力を加える関数
	void AddForce(float angle, float force);

	// 摩擦により速度を減速する関数
	void Friction(float elapsedTime);

	// 床のチェック関数（false：通路）
	bool CheckFloor();

	// ターゲットの方向を返す関数（真上を０として、逆時計回転で８方向）
	int GetDir(Object* object);

	// 得点を加算する関数
	void AddScore(int score);
};
