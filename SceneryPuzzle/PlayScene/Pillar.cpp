#include "Pillar.h"
#include "PlayGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Pillar::Pillar()
{
}

Pillar::~Pillar()
{
}

void Pillar::Initialize(PlayGame* playGame, Kind kind, int x, int y, DirectX::Model * model)
{
	m_playgame = playGame;
	m_model = model;
	m_x = x;
	m_y = y;
	m_pos = Vector3((float)x, 0.0f, (float)y);
	m_kind = kind;

	// ����
	m_weight = 0.1f;

	// ���C�W��
	m_coefficientOfFriction = 5.0f;

	// ���a
	m_radius = 0.4f;

	// ���ƍ���
	m_w = Pillar::WIDTH;
	m_h = Pillar::HEIGHT;
}

bool Pillar::Update(float elapsedTime)
{
	return true;
}

void Pillar::Render()
{
}
