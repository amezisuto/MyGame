#include "SerectPillar.h"
#include "SerectGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// °‚Æ‚Ì”»’è—p‚Ì•‚Æ‚‚³
const float SerectPillar::WIDTH = 0.2f;
const float SerectPillar::HEIGHT = 0.2f;


SerectPillar::SerectPillar()
{
}

void SerectPillar::Initialize(SerectGame* serectGame, Kind kind, int x, int y, DirectX::Model * model)
{
	m_serectgame = serectGame;
	m_model = model;
	m_x = x;
	m_y = y;
	m_pos = Vector3((float)x, 0.0f, (float)y);
	m_kind = kind;

	// ¿—Ê
	m_weight = 0.1f;

	// –€CŒW”
	m_coefficientOfFriction = 5.0f;

	// ”¼Œa
	m_radius = 0.4f;

	// •‚Æ‚‚³
	m_w = SerectPillar::WIDTH;
	m_h = SerectPillar::HEIGHT;
}

bool SerectPillar::Update(float elapsedTime)
{
	if (m_killFlag == true) return false;
	if (!m_activeFlag) return true;

	// Õ“Ë”»’èƒ}ƒl[ƒWƒƒ[‚É“o˜^
	m_serectgame->AddCollision(this);

	return true;
}


Object::OBJECT_ID SerectPillar::GetID()
{
	return Object::PILLAR;
}

void SerectPillar::Reset()
{
	// Ä‚Ñæ‚Á‚Ä‚È‚¢ó‘Ô‚É–ß‚·
	m_dir = 0;
	m_pos = Vector3((float)m_x, 0.0f, (float)m_y);
	SetOt(SerectGame::OT_OBJECT);
}