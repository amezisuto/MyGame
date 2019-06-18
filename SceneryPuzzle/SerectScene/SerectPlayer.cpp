//--------------------------------------------------------------------------------------
// File: Player.cpp
//
// �v���C���[�N���X
//
// Date: 2018.12.5
// Author: Takeshi Yamaguthi
//--------------------------------------------------------------------------------------
#include "../pch.h"
#include "SerectPlayer.h"
#include "../Game.h"
#include "SerectGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �v���C���[�̏d��
const float SerectPlayer::WEIGHT = 1.0f;

// ���ɑ΂��門�C�W��
const float SerectPlayer::FRICTION = 0.1f;

// ���Ƃ̔���p�̕��ƍ���
const float SerectPlayer::WIDTH = 0.2f;
const float SerectPlayer::HEIGHT = 0.2f;

// �I�u�W�F�N�g���m�̔���p�̔��a
const float SerectPlayer::RADIUS = 0.4f;

// �W�����v���Ă���t���[����
const int SerectPlayer::JUMP_FRAME = 30;

// �W�����v�̍���
const float SerectPlayer::JUMP_HEIGHT = 1.5f;

// �v���C���[�̍ő�ړ����x
const float SerectPlayer::MAX_SPEED = 0.05f;

SerectPlayer::SerectPlayer()
	: m_models{ nullptr }, m_powerupParts(0), m_jumpParts(false), m_state(STATE_NORMAL),  m_jumpCounter(0), m_fallRotateAngle(0.0f), m_floorCheck(false), m_moveFlag(false)
{
	m_nextPos.x = 0;
	m_nextPos.y = 0;
}

void SerectPlayer::Initialize(SerectGame* serectGame, int x, int y)
{
	m_serectgame = serectGame;
	m_x = x;
	m_y = y;
	m_pos = Vector3((float)x, 0.0f, (float)y);
	// ���C�W��
	m_coefficientOfFriction = FRICTION;

	// ���a
	m_radius = RADIUS;
	m_notMoveFlag = false;

	// ���ƍ���
	m_w = SerectPlayer::WIDTH;
	m_h = SerectPlayer::HEIGHT;

	Reset();
}

void SerectPlayer::SetModel(ModelType modelType, DirectX::Model * model)
{
	m_models[modelType] = model;
}

bool SerectPlayer::Update(float elapsedTime)
{
	// �폜���N�G�X�g������΃^�X�N���폜
	if (m_killFlag == true) return false;

	// �A�N�e�B�u�t���O��false�̏ꍇ�͉������Ȃ�
	if (!m_activeFlag) return true;

	// ���C�ɂ�葬�x�𗎂Ƃ�
	Friction(elapsedTime);
	// �q�b�g���͑��x�����������Ȃ�
	if (m_state != STATE_HIT)
	{
		// �ő呬�x�ȏ�ɂȂ�Ȃ��悤����
		if (m_v.LengthSquared() > MAX_SPEED * MAX_SPEED)
		{
			m_v.Normalize();
			m_v *= MAX_SPEED;
		}
	}
	// �ʒu�ɑ��x�𑫂�
	m_pos += m_v;

	// ��Ԃɂ���ď����𕪊򂳂���
	switch (m_state)
	{
	case STATE_JUMP:
		State_Jump(elapsedTime);
		break;
	case STATE_NORMAL:	// �ʏ�
		break;
	case STATE_HIT:		// �q�b�g��
		State_Hit(elapsedTime);
		break;
	default:
		break;
	}


	// �v���C���[�����S�܂��͗������ȊO�͏Փ˂���
	if (m_state != SerectPlayer::STATE::STATE_DEAD && m_state != SerectPlayer::STATE::STATE_FALL)
	{
		// �Փ˔���}�l�[�W���[�ɓo�^
		m_serectgame->AddCollision(this);
	}


	return true;
}

void SerectPlayer::Render()
{
	if (!m_playgame || !m_models[NORMAL] || !m_displayFlag) return;

	Game* game = m_serectgame->GetGame();

	// �����Ă���p�x���p�x�e�[�u������擾
	float angle = SerectGame::DIR_ANGLE[m_dir];

	// �������̉�]��������
	angle += m_fallRotateAngle;

	// ���[���h�s����쐬
	Matrix world = Matrix::CreateRotationY(angle) * Matrix::CreateTranslation(m_pos);

	// ���f���̕`��
	m_models[NORMAL]->Draw(game->GetContext(), *game->GetStates()
		, world, m_serectgame->GetViewMatrix(), m_serectgame->GetProjectionMatrix());
}

void SerectPlayer::State_Hit(float elapsedTime)
{
	// ���C�ɂ���~������
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

void SerectPlayer::OnHit(Object * object)
{
	// �Փ˂�������ɂ���ď�����ς���
	switch (object->GetID())
	{
	case Object::NOTB:	// �i���֎~
		OnHit_Piller(object);
		break;
		//case Object::BALL:	// �{�[��
		//	m_gameWindow->GetPowerupParts();
		//	break;
	case Object::TRY:	// ��
		OnHit_Piller(object);
		break;
	case Object::GOAL:	// �S�[��
		m_clear = STATE_END::STATE_CLEAR;
		break;
	case Object::PILLAR:	// ��
		OnHit_Piller(object);
		break;
	}
}

SerectPlayer::STATE SerectPlayer::GetState()
{
	return m_state;
}

SerectPlayer::STATE_END SerectPlayer::GetStateEnd()
{
	return m_clear;
}
void SerectPlayer::SetFloorCheck(bool flag)
{
	m_floorCheck = flag;
}

void SerectPlayer::SetNotMoveFlag(bool flag)
{
	m_notMoveFlag = flag;
}

void SerectPlayer::SetNextPosX(int x)
{
	m_nextPos.x = x;
}

void SerectPlayer::SetNextPosY(int y)
{
	m_nextPos.y = y;
}

int SerectPlayer::GetNextPosX()
{
	return m_nextPos.x;
}

int SerectPlayer::GetNextPosY()
{
	return m_nextPos.y;
}


void SerectPlayer::Move(float elapsedTime, const DirectX::Keyboard::KeyboardStateTracker& tracker)
{
	// �v���C���[���ʏ�A�W�����v���݈̂ړ�����
	if (m_state != STATE_NORMAL && m_state != STATE_JUMP) return;

	// �L�[���͂��擾
	auto kb = Keyboard::Get().GetState();

	// �����L�[�������ꂽ��
	if (tracker.pressed.Up || tracker.pressed.Down || tracker.pressed.Left || tracker.pressed.Right)
	{
		// �����ꂽ�����L�[�̃r�b�g�𗧂Ă�
		if (tracker.pressed.Up) m_nextPos.y = -1;
		else if (tracker.pressed.Down) m_nextPos.y = 1;
		else if (tracker.pressed.Left) m_nextPos.x = -1;
		else if (tracker.pressed.Right) m_nextPos.x = 1;
		if (m_floorMove) m_floorMove(this);
		m_state = STATE_JUMP;
		m_jumpCounter = JUMP_FRAME;
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


void SerectPlayer::SetFloorMove(std::function<void(Object*)> func)
{
	// �ړ����ɌĂ΂��֐���o�^����
	m_floorMove = func;
}

void SerectPlayer::SetFloorBackMove(std::function<void(Object*)> func)
{
	// �ړ����ɌĂ΂��֐���o�^����
	m_floorBackMove = func;
}

void SerectPlayer::SetFloorCheckBack(std::function<void(Object*)> func)
{
	// �ړ����ɌĂ΂��֐���o�^����
	m_floorCheckBack = func;
}
void SerectPlayer::Reset()
{
	// �v���C���[�����̏�Ԃɖ߂�
	m_dir = 0;
	m_pos = Vector3((float)m_x, 0.0f, (float)m_y);
	m_state = STATE_NORMAL;
	m_clear = NONE;
	SetDisplayFlag(true);
	SetOt(SerectGame::OT_OBJECT);
}

void SerectPlayer::SetNextFloorPos(DirectX::SimpleMath::Vector3 pos)
{
	m_target = pos;
}

int SerectPlayer::GetKeyToDir(int key)
{
	// �r�b�g�t�B�[���h�̃L�[�����W����(0�`7�j�ɕϊ�����e�[�u��
	int table[16] = { -1, 0, 2, 1, 4, -1, 3, -1, 6, 7, -1, -1, 5, -1, -1, -1 };
	return table[key];
}

void SerectPlayer::OnHit_Piller(Object * object)
{
	Vector3 playerDir = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 v;
	Matrix rotY;
	float playerAngle;

	// �q�b�g��
	//ADX2::GetInstance().Play(CRI_PZULE_HIT);

	// ��~������
	m_v = Vector3::Zero;

	// �v���C���[����G�����ւ̃x�N�g�������߂�
	v = object->GetPosition() - this->GetPosition();

	// �v���C���[�̌����x�N�g�����쐬
	playerAngle = SerectGame::DIR_ANGLE[m_dir];
	rotY = Matrix::CreateRotationY(playerAngle);
	playerDir = Vector3::Transform(playerDir, rotY);

	// �W�����v���̏Փ˂ȂǂœG�̑O�ɗ������邱�Ƃ�����̂Ő�����΂��������O����납�𔻒f����
	if (v.Dot(playerDir) > 0)
	{
		// �i�s�����̋t�����ɗ͂�������
		playerAngle += XMConvertToRadians(180.0f);
	}

	// �ʏ펞�ƃW�����v���Œ��˕Ԃ�̗͂�ς���
	if (m_state == STATE_NORMAL)
	{
		AddForce(playerAngle, object->GetHitForce());	// �ʏ�
	}
	else
	{
		AddForce(playerAngle, object->GetHitForce() / 2.0f);	// �W�����v��
	}

	//// �q�b�g���̃G�t�F�N�g���o���i�\���ʒu�͏Փ˂�������Ƃ̒��Ԓn�_�j
	//v = object->GetPosition() - this->GetPosition();
	//v.x /= 2.0f;
	//v.z /= 2.0f;
	//Vector3 pos = m_pos + v;
	//HitEffect* hitEffect = GetTaskManager()->AddTask<HitEffect>();
	//hitEffect->Initialize(m_gameWindow, pos);

	// �Փˏ�Ԃ�
	m_state = STATE_HIT;
}

void SerectPlayer::State_Jump(float elapsedTime)
{
	// �W�����v�̏���
	if (m_jumpCounter != 0)
	{
		// �Q�[�����ۂ��W�����v�ɂ��邽�߁A�T�C���g�ŃW�����v���̍������Z�o����
		m_jumpCounter--;
		int cnt = JUMP_FRAME - m_jumpCounter;
		float angle = 180.0f / (float)JUMP_FRAME * cnt;
		m_pos.y = sinf(XMConvertToRadians(angle)) * JUMP_HEIGHT;

		if (m_jumpCounter == 0)
		{
			// ���ɒ��n����
			m_pos.y = 0.0f;
			// �ʏ�̏�Ԃ�
			m_state = STATE_NORMAL;
			// ���Ƀ_���[�W��^����
			if (m_floorMove) m_floorMove(this);
		}
	}
}


