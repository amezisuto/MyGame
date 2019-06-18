//--------------------------------------------------------------------------------------
// File: Object.cpp
//
// �I�u�W�F�N�g�N���X
//
// Date: 2018.12.5
// Author: Takeshi Yamaguthi
//--------------------------------------------------------------------------------------
#include "../pch.h"
#include "Object.h"
#include "../Game.h"
#include"../PlayScene/PlayGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Object::Object()
	: m_playgame(nullptr), m_model(nullptr), m_dir(0), m_weight(0.0f), m_coefficientOfFriction(0.0f), m_radius(0.0f), m_w(0.0f), m_h(0.0f), m_killFlag(false), m_hitFlag(false), m_displayFlag(true), m_activeFlag(true), m_x(0), m_y(0)
{
	// �`�揇�̐ݒ�
	SetOt(PlayGame::OT_OBJECT);
}

bool Object::Update(float elapsedTime)
{
	if (!m_activeFlag) return !m_killFlag;

	// �ʒu�ɑ��x�𑫂�
	m_pos += m_v;

	return !m_killFlag;
}

void Object::Render()
{
	if (!m_playgame || !m_model || !m_displayFlag) return;
	
	Game* game = m_playgame->GetGame();

	// ���[���h�s����쐬
	Matrix world = Matrix::CreateTranslation(m_pos);

	// ���f���̕`��
	m_model->Draw(game->GetContext(), *game->GetStates()
		, world, m_playgame->GetViewMatrix(), m_playgame->GetProjectionMatrix());
}

float Object::GetHitForce()
{
	float force = 0.1f;

	// �A���q�b�g���̑��x�̉e�����傫�����̂ő��x��}����
	float v = m_v.Length();
	if (v >= 0.1f) v = 0.1f;
	force += m_weight * v;

	return force;
}

void Object::AddForce(float angle, float force)
{
	// �i�s�����x�N�g��
	Vector3 dir(0.0f, 0.0f, -1.0f);

	// ���@�̌����x�N�g�������߂�
	Matrix rotY = Matrix::CreateRotationY(angle);
	dir = Vector3::Transform(dir, rotY);

	// �����x
	m_a = dir * (force / m_weight);

	// ���x�ɉ����x�𑫂�
	m_v += m_a;
}

void Object::Friction(float elapsedTime)
{
	// ���C�� = ���C�W�� �~ �d�͉����x �~ ����
	float frictionForce = m_coefficientOfFriction * m_weight * PlayGame::GRAVITY;

	// ���C�͂ɂ���đ��x�𗎂Ƃ�
	float v = (frictionForce / m_weight) * elapsedTime;

	if (m_v.LengthSquared() > v * v)
	{
		v = m_v.Length() - v;
		m_v.Normalize();
		m_v *= v;
	}
	else
	{
		m_v = Vector3::Zero;
	}
}

bool Object::CheckFloor()
{
	if (m_floorCheckFunction)
	{
		return m_floorCheckFunction(this);
	}
	return true;
}

int Object::GetDir(Object * object)
{
	// �^�[�Q�b�g�ւ̃x�N�g�������߂�
	Vector3 v = object->GetPosition() - m_pos;

	// ���ς��g����ԋ߂��p�x�����߂�
	Matrix rotY = Matrix::CreateRotationY(XMConvertToRadians(45.0f));
	Vector3 dirVec(0.0f, 0.0f, -1.0f);
	int dir = 0;
	float maxVal = dirVec.Dot(v);
	// ���ς���ԑ傫���������߂�
	for (int i = 0; i < 7; i++)
	{
		dirVec = Vector3::Transform(dirVec, rotY);
		float val = dirVec.Dot(v);
		if (val > maxVal)
		{
			dir = i + 1;
			maxVal = val;
		}
	}
	return dir;
}

void Object::AddScore(int score)
{
	if (m_addScoreFunction)
	{
		m_addScoreFunction(score);
	}
}

void Object::SetCheckFloorFunction(std::function<bool(Object*)> func)
{
	m_floorCheckFunction = func;
}

void Object::SetAddScoreFunction(std::function<void(int score)> func)
{
	m_addScoreFunction = func;
}

