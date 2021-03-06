//---------------------------------------
// プレイヤークラス
//---------------------------------------
#pragma once

#include "../Livr/Object.h"
#include "../TaskManager.h"
class Player : public Object
{
public:
	// プレイヤーのタイプ別モデル
	enum ModelType
	{
		NORMAL,	// 通常
		MODEL_TYPE_NUM
	};

	// プレイヤーの状態
	enum STATE
	{
		STATE_NORMAL,	// 通常
		STATE_JUMP,		// ジャンプ中
		STATE_HIT,	
		STATE_DEAD,
		STATE_SERECTJUMP,
		STATE_NEXTJUMP,
	};

	// 
	enum STATE_END
	{
		NONE,	// 通常
		STATE_CLEAR,		// ジャンプ中
		STATE_NOTCLAER,		// 吹き飛ばされ状態
	};

	struct Pos
	{
		int x;
		int y;
	};


	// 床との判定用の幅と高さ
	static const float WIDTH;
	static const float HEIGHT;

	// オブジェクト同士の判定用の半径
	static const float RADIUS;

	// プレイヤーの最大移動速度
	static const float MAX_SPEED;

	// プレイヤーの重さ
	static const float WEIGHT;

	// 床に対する摩擦係数
	static const float FRICTION;

private:
	// ジャンプしているフレーム数
	static const int JUMP_FRAME;

	// ジャンプの高さ
	static const float JUMP_HEIGHT;

	// モデルデータへのポインタ
	DirectX::Model* m_models[MODEL_TYPE_NUM];

	// プレイヤーの状態
	STATE m_state;

	// パワーアップ
	int m_powerupParts;

	// ジャンプパーツを装着しているか？
	bool m_jumpParts;

	// ジャンプカウンター
	int m_jumpCounter;

	// 落下時の回転
	float m_fallRotateAngle;

	// 移動時に呼ばれる関数
	std::function<void(Object*)> m_floorMove;

	// 戻る時に呼ばれる関数
	std::function<void(Object*)> m_floorBackMove;

	// 戻る時に呼ばれる関数
	std::function<void(Object*)> m_floorCheckBack;

	// 戻る時に呼ばれる関数
	std::function<void(Object*)> m_floorCheng;

	// 戻る時に呼ばれる関数
	std::function<void(Object*)> m_playerKey;

	STATE_END m_clear;

	bool m_floorCheck;

	Pos m_nextPos;

	bool m_notMoveFlag;

	Pos m_serectNextPos;

	Pos m_chengeFloortPos;

	bool m_floorChengeFlag;


	DirectX::SimpleMath::Vector3 m_target; // 移動先
	float   m_speed = 5;
	float   m_attenuation = 0.5f;

	DirectX::SimpleMath::Vector3 m_velocity;

	bool m_moveFlag;


public:
	// コンストラクタ
	Player();

	// 初期化関数
	void Initialize(PlayGame* playGame, int x, int y);

	// モデル設定関数
	void SetModel(ModelType modelType, DirectX::Model* model);

	// オブジェクトＩＤを取得する関数
	Object::OBJECT_ID GetID() { return Object::PLAYER; }

	// 更新関数
	bool Update(float elapsedTime) override;

	// 描画関数
	void Render() override;

	// 更新処理（衝突して制御不能中）
	void State_Hit(float elapsedTime);

	// 衝突したら呼ばれる関数
	void OnHit(Object* object) override;

	// プレイヤーの状態を取得する関数
	Player::STATE GetState();

	Player::STATE_END GetStateEnd();

	// プレイヤーの移動関数
	void Move(float elapsedTime, const DirectX::Keyboard::KeyboardStateTracker& tracker);

	// ステージ選択中の移動関数
	void SerectMove(float elapsedTime, const DirectX::Keyboard::KeyboardStateTracker& tracker);

	// 移動時に呼ばれる関数を設定する関数
	void SetFloorMove(std::function<void(Object*)> func);

	// ジャンプ終了時に呼ばれる関数を設定する関数
	void SetFloorBackMove(std::function<void(Object*)> func);

	// ジャンプ終了時に呼ばれる関数を設定する関数
	void SetFloorCheckBack(std::function<void(Object*)> func);

	// 床替え時に呼ばれる関数を設定する関数
	void SetChengeFloor(std::function<void(Object*)> func);

	// リセット関数
	void Reset();
	void SetFloorCheck(bool flag);

	void SetNotMoveFlag(bool flag);

	void SetNextPosX(int x);
	void SetNextPosY(int y);

	void SetChengPosX(int x);
	void SetChengPosY(int y);

	int GetNextPosX();
	int GetNextPosY();

	int GetChengPosX();
	int GetChengPosY();

	void SetFloorChengFlag(bool flag) { m_floorChengeFlag = flag; }
	bool GetFloorChengFlag() { return m_floorChengeFlag; }



	void SetNextFloorPos(DirectX::SimpleMath::Vector3 pos);

	void State_Jump(float elapsedTime);
	void Serect_Jump(float elapsedTime);
	void Next_Jump(float elapsedTime);

	void SetJumpConter() { m_jumpCounter = JUMP_FRAME; }

	void SerectNextPos(int x,int y);

	void SetNextState() { m_state = STATE_NEXTJUMP; }


private:
	// キー入力から方向を求める関数
	int GetKeyToDir(int key);

	// ENEMY_1と衝突した時の処理関数
	void OnHit_Piller(Object* object);
};
