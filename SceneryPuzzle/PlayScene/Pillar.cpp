#include "Pillar.h"
#include "PlayGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// ���Ƃ̔���p�̕��ƍ���
const float Pillar::WIDTH = 0.2f;
const float Pillar::HEIGHT = 0.2f;


Pillar::Pillar()
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
	if (m_killFlag == true) return false;
	if (!m_activeFlag) return true;

	// �Փ˔���}�l�[�W���[�ɓo�^
	m_playgame->AddCollision(this);

	return true;
}


Object::OBJECT_ID Pillar::GetID()
{
	return Object::PILLAR;
}

void Pillar::Reset()
{
	// �Ăю���ĂȂ���Ԃɖ߂�
	m_dir = 0;
	m_pos = Vector3((float)m_x, 0.0f, (float)m_y);
	SetOt(PlayGame::OT_OBJECT);
}