#include "../Game.h"
#include "TitleUi.h"
#include "../Scene/GameLi/GameManeger.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

// �R���X�g���N�^
TitleUi::TitleUi():m_displayFlag(false), m_interval(0.0f), m_counter(0.0f)
{
}

// �f�X�g���N�^
TitleUi::~TitleUi()
{
}

// ������
void TitleUi::Initialize(Game* game)
{
	m_interval = 0.5f;
	m_game = game;	// Game.cpp�̏��̎擾
	// �e�N�X�`���̓ǂݍ���
	CreateWICTextureFromFile(m_game->GetDevice(), L"Resources\\Textures\\push_space.png", nullptr, m_pushSpaceTexture.GetAddressOf());
}

// �X�V
bool TitleUi::Update(float elapsedTime)
{
	// �_��
	m_counter += elapsedTime;
	if (m_counter >= m_interval)
	{
		m_counter = 0.0f;
		if (m_displayFlag)
		{
			m_displayFlag = false;
		}
		else
		{
			m_displayFlag = true;
		}
	}
	return true;
}

// �`��
void TitleUi::Render()
{
	m_game->GetSpriteBatch()->Begin(SpriteSortMode_Deferred, m_game->GetStates()->NonPremultiplied());
	// PUSH START�̕`��
	if (m_displayFlag)
	{
		m_game->GetSpriteBatch()->Draw(m_pushSpaceTexture.Get(), Vector2(430, 570));
	}
	m_game->GetSpriteBatch()->End();
}
