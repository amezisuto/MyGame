//--------------------------------------------------------------------------------------
// File: Player.cpp
//
// プレイヤークラス
//
// Date: 2018.12.5
// Author: Takeshi Yamaguthi
//--------------------------------------------------------------------------------------
#include "../pch.h"
#include "Player.h"
#include "../Game.h"
#include "PlayGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// プレイヤーの重さ
const float Player::WEIGHT = 1.0f;

// 床に対する摩擦係数
const float Player::FRICTION = 0.1f;

// 床との判定用の幅と高さ
const float Player::WIDTH = 0.2f;
const float Player::HEIGHT = 0.2f;

// オブジェクト同士の判定用の半径
const float Player::RADIUS = 0.4f;

// ジャンプしているフレーム数
const int Player::JUMP_FRAME = 30;

// ジャンプの高さ
const float Player::JUMP_HEIGHT = 2.0f;

// プレイヤーの最大移動速度
const float Player::MAX_SPEED = 0.05f;

Player::Player()
	: m_models{ nullptr }, m_powerupParts(0), m_jumpParts(false), m_state(STATE_NORMAL),  m_jumpCounter(0), m_fallRotateAngle(0.0f), m_floorCheck(false), m_moveFlag(false)
{
	m_nextPos.x = 0;
	m_nextPos.y = 0;
	m_chengeFloortPos.x = 0;
	m_chengeFloortPos.y = 0;
}

void Player::Initialize(PlayGame* playGame, int x, int y)
{
	m_playgame = playGame;
	m_x = x;
	m_y = y;
	m_pos = Vector3((float)x, 0.0f, (float)y);
	// 摩擦係数
	m_coefficientOfFriction = FRICTION;

	// 半径
	m_radius = RADIUS;
	m_notMoveFlag = false;

	// 幅と高さ
	m_w = Player::WIDTH;
	m_h = Player::HEIGHT;

	Reset();
}

void Player::SetModel(ModelType modelType, DirectX::Model * model)
{
	m_models[modelType] = model;
}

bool Player::Update(float elapsedTime)
{
	// 削除リクエストがあればタスクを削除
	if (m_killFlag == true) return false;

	// アクティブフラグがfalseの場合は何もしない
	if (!m_activeFlag) return true;

	// 摩擦により速度を落とす
	Friction(elapsedTime);
	// ヒット中は速度制限をかけない
	if (m_state != STATE_HIT)
	{
		// 最大速度以上にならないよう調整
		if (m_v.LengthSquared() > MAX_SPEED * MAX_SPEED)
		{
			m_v.Normalize();
			m_v *= MAX_SPEED;
		}
	}
	// 位置に速度を足す
	m_pos += m_v;

	// 状態によって処理を分岐させる
	switch (m_state)
	{
	case STATE_JUMP:
		State_Jump(elapsedTime);
		break;

	case STATE_NORMAL:	// 通常
		break;
	case STATE_HIT:		// ヒット中
		State_Hit(elapsedTime);
		break;
	case STATE_SERECTJUMP:
		Serect_Jump(elapsedTime);
		break;
	case STATE_NEXTJUMP:
		Next_Jump(elapsedTime);
		break;
	default:
		break;
	}

	// 衝突判定マネージャーに登録
	m_playgame->AddCollision(this);

	return true;
}

void Player::Render()
{
	if (!m_playgame || !m_models[NORMAL] || !m_displayFlag) return;

	Game* game = m_playgame->GetGame();

	// 向いている角度を角度テーブルから取得
	float angle = PlayGame::DIR_ANGLE[m_dir];

	// 落下中の回転を加える
	angle += m_fallRotateAngle;

	// ワールド行列を作成
	Matrix world = Matrix::CreateRotationY(angle) * Matrix::CreateTranslation(m_pos);

	// モデルの描画
	m_models[NORMAL]->Draw(game->GetContext(), *game->GetStates()
		, world, m_playgame->GetViewMatrix(), m_playgame->GetProjectionMatrix());
}

void Player::State_Hit(float elapsedTime)
{
	// 摩擦により停止したら
	if (m_v == Vector3::Zero)
	{
		if (m_jumpCounter != 0)
		{
			m_state = STATE_JUMP;
		}
		else
		{
			m_state = STATE_NORMAL;
		}
	}
}

void Player::OnHit(Object * object)
{
	// 衝突した相手によって処理を変える
	switch (object->GetID())
	{
	case Object::NOTB:	// 進入禁止
		OnHit_Piller(object);
		break;
		//case Object::BALL:	// ボール
		//	m_gameWindow->GetPowerupParts();
		//	break;
	case Object::TRY:	// △
		OnHit_Piller(object);
		break;
	case Object::GOAL:	// ゴール
		m_clear = STATE_END::STATE_CLEAR;
		break;
	case Object::PILLAR:	// 柱
		OnHit_Piller(object);
		break;
	}
}

Player::STATE Player::GetState()
{
	return m_state;
}

Player::STATE_END Player::GetStateEnd()
{
	return m_clear;
}
void Player::SetFloorCheck(bool flag)
{
	m_floorCheck = flag;
}

void Player::SetNotMoveFlag(bool flag)
{
	m_notMoveFlag = flag;
}

void Player::SetNextPosX(int x)
{
	m_nextPos.x = x;
}

void Player::SetNextPosY(int y)
{
	m_nextPos.y = y;
}

void Player::SetChengPosX(int x)
{
	m_chengeFloortPos.x = x;
}

void Player::SetChengPosY(int y)
{
	m_chengeFloortPos.y = y;
}

int Player::GetNextPosX()
{
	return m_nextPos.x;
}

int Player::GetNextPosY()
{
	return m_nextPos.y;
}

int Player::GetChengPosX()
{
	return m_chengeFloortPos.x;
}

int Player::GetChengPosY()
{
	return m_chengeFloortPos.y;
}


void Player::Move(float elapsedTime, const DirectX::Keyboard::KeyboardStateTracker& tracker)
{
	// プレイヤーが通常、ジャンプ時のみ移動する
	if (m_state != STATE_NORMAL && m_state != STATE_JUMP) return;

	// キー入力を取得
	auto kb = Keyboard::Get().GetState();

	// 方向キーが押されたら
	if (kb.Up || kb.Down || kb.Left || kb.Right)
	{
		if (m_state != STATE_JUMP)
		{
			// 押された方向キーのビットを立てる
			if (kb.Up) m_nextPos.y = -1;
			else if (kb.Down) m_nextPos.y = 1;
			else if (kb.Left) m_nextPos.x = -1;
			else if (kb.Right) m_nextPos.x = 1;
			if (m_floorMove) m_floorMove(this);
			m_state = STATE_JUMP;
			m_jumpCounter = JUMP_FRAME;
		}
	}
	if (m_floorCheck)
	{
		m_nextPos.x = 0;
		m_nextPos.y = 0;
		m_velocity += (m_target - this->GetPosition()) * m_speed;
		m_velocity *= m_attenuation;
		m_pos += m_velocity*elapsedTime;
		//if (m_target.x+0.2f >= m_pos.x&&m_target.x - 0.2f <= m_pos.x&&m_target.z + 0.2f >= m_pos.z&&m_target.z - 0.2f <= m_pos.z)
		//	m_floorCheck=false;
	}
}

void Player::SerectMove(float elapsedTime, const DirectX::Keyboard::KeyboardStateTracker & tracker)
{
	// プレイヤーが通常、ジャンプ時のみ移動する
	if (m_state != STATE_NORMAL && m_state != STATE_JUMP) return;

	// キー入力を取得
	auto kb = Keyboard::Get().GetState();

	// 方向キーが押されたら
	if ( tracker.pressed.Left || tracker.pressed.Right)
	{
		// 押された方向キーのビットを立てる
		m_state = STATE_SERECTJUMP;
		m_jumpCounter = JUMP_FRAME;
	}
	//if (m_floorCheck)
	//{
	//	m_nextPos.x = 0;
	//	m_nextPos.y = 0;
	//	m_velocity += (m_target - this->GetPosition()) * m_speed;
	//	m_velocity *= m_attenuation;
	//	m_pos += m_velocity*elapsedTime;
	//	//if (m_target.x+0.2f >= m_pos.x&&m_target.x - 0.2f <= m_pos.x&&m_target.z + 0.2f >= m_pos.z&&m_target.z - 0.2f <= m_pos.z)
	//	//	m_floorCheck=false;
	//}
}


void Player::SetFloorMove(std::function<void(Object*)> func)
{
	// 移動時に呼ばれる関数を登録する
	m_floorMove = func;
}

void Player::SetFloorBackMove(std::function<void(Object*)> func)
{
	// 移動時に呼ばれる関数を登録する
	m_floorBackMove = func;
}

void Player::SetFloorCheckBack(std::function<void(Object*)> func)
{
	// 移動時に呼ばれる関数を登録する
	m_floorCheckBack = func;
}
void Player::SetChengeFloor(std::function<void(Object*)> func)
{
	m_floorCheng = func;
}
void Player::Reset()
{
	// プレイヤーを元の状態に戻す
	m_dir = 0;
	m_pos = Vector3((float)m_x, 0.0f, (float)m_y);
	m_state = STATE_NORMAL;
	m_clear = NONE;
	SetDisplayFlag(true);
	SetOt(PlayGame::OT_OBJECT);
}

void Player::SetNextFloorPos(DirectX::SimpleMath::Vector3 pos)
{
	m_target = pos;
}

int Player::GetKeyToDir(int key)
{
	// ビットフィールドのキー情報を８方向(0〜7）に変換するテーブル
	int table[16] = { -1, 0, 2, 1, 4, -1, 3, -1, 6, 7, -1, -1, 5, -1, -1, -1 };
	return table[key];
}

void Player::OnHit_Piller(Object * object)
{
	Vector3 playerDir = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 v;
	Matrix rotY;
	float playerAngle;

	// ヒット音
	//ADX2::GetInstance().Play(CRI_PZULE_HIT);

	// 停止させる
	m_v = Vector3::Zero;

	// プレイヤーから敵方向へのベクトルを求める
	v = object->GetPosition() - this->GetPosition();

	// プレイヤーの向きベクトルを作成
	playerAngle = PlayGame::DIR_ANGLE[m_dir];
	rotY = Matrix::CreateRotationY(playerAngle);
	playerDir = Vector3::Transform(playerDir, rotY);

	// ジャンプ時の衝突などで敵の前に落下することがあるので吹っ飛ばす方向が前か後ろかを判断する
	if (v.Dot(playerDir) > 0)
	{
		// 進行方向の逆方向に力を加える
		playerAngle += XMConvertToRadians(180.0f);
	}

	// 通常時とジャンプ時で跳ね返りの力を変える
	if (m_state == STATE_NORMAL)
	{
		AddForce(playerAngle, object->GetHitForce());	// 通常
	}
	else
	{
		AddForce(playerAngle, object->GetHitForce() / 2.0f);	// ジャンプ中
	}

	//// ヒット時のエフェクトを出す（表示位置は衝突した相手との中間地点）
	//v = object->GetPosition() - this->GetPosition();
	//v.x /= 2.0f;
	//v.z /= 2.0f;
	//Vector3 pos = m_pos + v;
	//HitEffect* hitEffect = GetTaskManager()->AddTask<HitEffect>();
	//hitEffect->Initialize(m_gameWindow, pos);

	// 衝突状態へ
	m_state = STATE_HIT;
}

void Player::State_Jump(float elapsedTime)
{
	// ジャンプの処理
	if (m_jumpCounter != 0)
	{
		// ゲームっぽいジャンプにするため、サイン波でジャンプ時の高さを算出する
		m_jumpCounter--;
		int cnt = JUMP_FRAME - m_jumpCounter;
		float angle = 180.0f / (float)JUMP_FRAME * cnt;
		m_pos.y = sinf(XMConvertToRadians(angle)) * JUMP_HEIGHT;

		if (m_jumpCounter == 0)
		{
			// 床に着地した
			m_pos.y = 0.0f;
			// 通常の状態へ
			m_state = STATE_NORMAL;
			if (m_floorCheng) m_floorCheng(this);
		}
	}
}

void Player::Serect_Jump(float elapsedTime)
{
	// ジャンプの処理
	if (m_jumpCounter != 0)
	{
		// ゲームっぽいジャンプにするため、サイン波でジャンプ時の高さを算出する
		m_jumpCounter--;
		int cnt = JUMP_FRAME - m_jumpCounter;
		float angle = 180.0f / (float)JUMP_FRAME * cnt;
		m_pos.y = sinf(XMConvertToRadians(angle)) * 10.0f;

		if (m_jumpCounter == 0)
		{
			// 床に着地した
			m_pos.y = 0.0f;
			// 通常の状態へ
			m_state = STATE_NORMAL;
		}
	}
}

void Player::Next_Jump(float elapsedTime)
{
	// ジャンプの処理
	if (m_jumpCounter != 0)
	{
		// ゲームっぽいジャンプにするため、サイン波でジャンプ時の高さを算出する
		m_jumpCounter--;
		int cnt = JUMP_FRAME - m_jumpCounter;
		float angle = 180.0f / (float)JUMP_FRAME * cnt;
		m_pos.y = sinf(XMConvertToRadians(angle)) * 10.0f;

		if (m_jumpCounter == 0)
		{
			// 床に着地した
			m_pos.y = 0.0f;
			// 通常の状態へ
			m_state = STATE_NORMAL;
		}
	}
}

void Player::SerectNextPos(int x, int y)
{
	m_serectNextPos.x = x;
	m_serectNextPos.y = y;
}


