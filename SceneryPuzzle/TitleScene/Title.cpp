#include "../Game.h"
#include "Title.h"
#include "../Scene/GameLi/GameManeger.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �R���X�g���N�^
Title::Title()
{
}

// �f�X�g���N�^
Title::~Title()
{
}

// ������
void Title::Initialize(Game* game)
{
	m_game = game;		// Game.cpp�̏��̎擾
	// �e�N�X�`���̓ǂݍ���
	CreateWICTextureFromFile(m_game->GetDevice(), L"Resources\\Textures\\title.png", nullptr, m_titleTexture.GetAddressOf());
}

// �X�V
bool Title::Update(float elapsedTime)
{
	return false;
}

// �`��
void Title::Render()
{
	// �^�C�g���̕`��
	RECT destRect = { 0, 0, 1280, 720 };
	m_game->GetSpriteBatch()->Begin(SpriteSortMode_Deferred, m_game->GetStates()->NonPremultiplied());
	m_game->GetSpriteBatch()->Draw(m_titleTexture.Get(), destRect);
	m_game->GetSpriteBatch()->End();
}
