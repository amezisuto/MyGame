//--------------------------------------------------------------------------------------
// File: Floor.cpp
//
// ���N���X
//
// Date: 2018.11.4
// Author: Takeshi Yamaguthi
//--------------------------------------------------------------------------------------
#include "../pch.h"
#include "Floor.h"
#include "../Game.h"
#include "../Scene/GameScene.h"
#include "Stage.h"

// �_���[�W�̈ڍs����
const float Floor::LODE_DELAY_TIME = 0.2f;

using namespace DirectX;
using namespace DirectX::SimpleMath;

Floor::Floor()
	: m_stage(nullptr), m_models{ nullptr }, m_state(NONE), m_lodeFlag(false), m_lodeTimer(0.0f)
{
	// �`�揇�̐ݒ�
	SetOt(GameScene::OT_STAGE);
}

void Floor::Initialize(Stage * stage, int x, int y)
{
	m_stage = stage;
	m_pos = Vector3((float)x, 0.0f, (float)y);
}

bool Floor::Update(float elapsedTime)
{
	// ���t���O�𗎂Ƃ�
	m_lodeFlag = false;

	// �ڍs
	if (m_lodeTimer > 0.0f)
	{
		m_lodeTimer -= elapsedTime;
		if (m_lodeTimer <= 0.0f)
		{
			m_lodeTimer = 0.0f;
			switch (m_state)
			{
			case NORMAL:	// �ʏ�
				m_state = Floor::LODE;	// �ʉߍς�
				break;
			case LODE:	// �ʘH
				m_state = Floor::NORMAL;		// �߂�
				break;
			default:
				break;
			}
		}
	}

	//// ������Ԃ̏ꍇ�͏������ɗ��Ƃ�
	//if (m_state == Floor::FALL)
	//{
	//	m_pos.y -= 0.1f;

	//	// ������x�������������
	//	if (m_pos.y < -3.0f)
	//	{
	//		m_state = Floor::DEAD;
	//	}
	//}

	return true;
}

void Floor::Render()
{
	if (!m_stage || !m_models[m_state]) return;

	// ���[���h�s��̍쐬
	Matrix world = Matrix::CreateTranslation(m_pos);

	Game* game = m_stage->GetGame();

	// �ʂ����u�Ԃ��烂�f���؂�ւ�����
	State state = m_state;
	if (m_lodeTimer > 0) state = LODE;

	// ���f���̕`��
	m_models[state]->Draw(game->GetContext(), *game->GetStates()
		, world
		, m_stage->GetGameWindow()->GetViewMatrix()
		, m_stage->GetGameWindow()->GetProjectionMatrix(), false, [&]()
	{
		// ���͔������̉��Z�����i�������ňÂ��Ȃ��Ă��܂��̂Łj
		game->GetContext()->OMSetBlendState(game->GetStates()->Additive(), nullptr, 0xffffffff);
	});

}

void Floor::SetModel(State state, DirectX::Model * model)
{
	m_models[state] = model;
}

void Floor::Lode()
{
	// �P�t���[���Ɉړ��͂P�x����
	if (m_lodeFlag) return;
	m_lodeFlag = true;

	// �ڍs�^�C�}�[�Z�b�g
	m_lodeTimer = LODE_DELAY_TIME;
}

void Floor::Reset()
{
	m_pos.y = 0.0f;
	if (m_state != Floor::NONE)
	{
		m_state = Floor::NORMAL;
		m_lodeFlag = false;
		m_lodeTimer = 0.0f;
	}
}

