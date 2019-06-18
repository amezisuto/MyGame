#include "../Game.h"
#include "SerectGimmick.h"
#include "SerectGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 床との判定用の幅と高さ
const float SerectGimmick::WIDTH = 0.2f;
const float SerectGimmick::HEIGHT = 0.2f;

// コンストラクタ
SerectGimmick::SerectGimmick()
{
}

// 初期化
void SerectGimmick::Initialize(SerectGame* serectGame, Kind kind, int x, int y, DirectX::Model * model)
{
	m_serectgame = serectGame;
	m_model = model;
	m_x = x;
	m_y = y;
	m_pos = Vector3((float)x, 0.0f, (float)y);
	m_kind = kind;

	// 半径
	m_radius = 0.4f;

	// 幅と高さ
	m_w = SerectGimmick::WIDTH;
	m_h = SerectGimmick::HEIGHT;
	Reset();
}

// 更新
bool SerectGimmick::Update(float elapsedTime)
{
	if (m_killFlag == true) return false;
	if (!m_activeFlag) return true;

	// 衝突判定マネージャーに登録
	m_serectgame->AddCollision(this);
	return true;
}

void SerectGimmick::OnHit(Object* object)
{
	OBJECT_ID id = object->GetID();

}

void SerectGimmick::Reset()
{
	// 再び取ってない状態に戻す
	SetActive(true);
	//SetDisplayFlag(true);
	m_dir = 0;
	m_pos = Vector3((float)m_x, 0.0f, (float)m_y);
	SetOt(SerectGame::OT_OBJECT);
}

Object::OBJECT_ID SerectGimmick::GetID()
{
	if (m_kind == GOAL) return Object::GOAL;
	return Object::NONE;
}
