#include "../Game.h"
#include "Gimmick.h"
#include "PlayGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 床との判定用の幅と高さ
const float Gimmick::WIDTH = 0.2f;
const float Gimmick::HEIGHT = 0.2f;

// コンストラクタ
Gimmick::Gimmick()
{
}

// デストラクタ
Gimmick::~Gimmick()
{
}

// 初期化
void Gimmick::Initialize(PlayGame* playGame, Kind kind, int x, int y, DirectX::Model * model)
{
	m_playgame = playGame;
	m_model = model;
	m_x = x;
	m_y = y;
	m_pos = Vector3((float)x, 0.0f, (float)y);
	m_kind = kind;

	// 半径
	m_radius = 0.4f;

	// 幅と高さ
	m_w = Gimmick::WIDTH;
	m_h = Gimmick::HEIGHT;
}

// 更新
bool Gimmick::Update(float elapsedTime)
{
	return true;
}

// 描画
void Gimmick::Render()
{
}

void Gimmick::Reset()
{
	// 再び取ってない状態に戻す
	SetActive(true);
	SetDisplayFlag(true);
	m_dir = 0;
	m_pos = Vector3((float)m_x, 0.0f, (float)m_y);
	SetOt(PlayGame::OT_OBJECT);
}

Object::OBJECT_ID Gimmick::GetID()
{
	if (m_kind == GOAL) return Object::GOAL;
	return Object::NONE;
}
