#include "../Game.h"
#include "Gimmick.h"
#include "../Scene/GameScene.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// コンストラクタ
Gimmick::Gimmick()
{
}

// デストラクタ
Gimmick::~Gimmick()
{
}

// 初期化
void Gimmick::Initialize(GameScene* gameScene, Kind kind, int x, int y, DirectX::Model * model)
{
	m_gameScene = gameScene;
	m_model = model;
	m_x = x;
	m_y = y;
	m_pos = Vector3((float)x, 0.0f, (float)y);
	m_kind = kind;

	// 半径
	m_radius = 0.4f;

	// 幅と高さ
	m_w = Pillar::WIDTH;
	m_h = Pillar::HEIGHT;
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
	SetOt(GameScene::OT_OBJECT);
}

Object::OBJECT_ID Gimmick::GetID()
{
	if (m_kind == GOAL) return Object::GOAL;
	return Object::NONE;
}
