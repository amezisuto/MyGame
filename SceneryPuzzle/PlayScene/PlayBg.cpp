#include "../Game.h"
#include "PlayBg.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �R���X�g���N�^
PlayBg::PlayBg()
{
}

// �f�X�g���N�^
PlayBg::~PlayBg()
{
}

// ������
void PlayBg::Initialize(Game* game)
{
	m_game = game;// Game.cpp�̏��̎擾
}

// �X�V
bool PlayBg::Update(float elapsedTime)
{
	return false;
}

// �`��
void PlayBg::Render()
{
}
