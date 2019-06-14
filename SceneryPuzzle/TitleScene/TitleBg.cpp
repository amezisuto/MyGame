#include "../Game.h"
#include "TitleBg.h"
#include "../Scene/GameLi/GameManeger.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

// �R���X�g���N�^
TitleBg::TitleBg():m_scroll(0.0f)
{
}

// �f�X�g���N�^
TitleBg::~TitleBg()
{
}

// ������
void TitleBg::Initialize(Game* game)
{
	m_game = game;	// Game.cpp�̏��̎擾
	// �e�N�X�`���̓ǂݍ���
	CreateWICTextureFromFile(m_game->GetDevice(), L"Resources\\Textures\\title_tile2.png", nullptr, m_tileTexture.GetAddressOf());
}

// �X�V
bool TitleBg::Update(float elapsedTime)
{
	// �X�N���[��
	//m_scroll += 0.5f;
	if (m_scroll >= 100.0f) m_scroll -= 100.0f;
	return true;
}

// �`��
void TitleBg::Render()
{
	m_game->GetSpriteBatch()->Begin(SpriteSortMode_Deferred, m_game->GetStates()->NonPremultiplied());
	// ���̃^�C���̕`��
	for (int j = 0; j < 9; j++)
	{
		for (int i = 0; i < 14; i++)
		{
			m_game->GetSpriteBatch()->Draw(m_tileTexture.Get(), Vector2(i * 100.0f - m_scroll, (j - 1) * 100.0f + m_scroll));
		}
	}
	m_game->GetSpriteBatch()->End();
}
