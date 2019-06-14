
#include "../pch.h"
#include "PlayGame.h"
#include "../Game.h"
#include "Stage.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

// ���E���h��
const int PlayGame::ROUND_MAX = 5;

// �����ɉ������p�x
const float PlayGame::DIR_ANGLE[] =
{
	XMConvertToRadians(45.0f * 0),	// �k
	XMConvertToRadians(45.0f * 2),	// ��
	XMConvertToRadians(45.0f * 4),	// ��
	XMConvertToRadians(45.0f * 6),	// ��
};
// �d�́i�n�����9.8m/s^2)
const float PlayGame::GRAVITY = 9.8f;

// �������x�i�P�b�ԂɈړ�����h�b�g���j
const float PlayGame::FALL_SPEED = 8.0f;


PlayGame::PlayGame()
	: m_game(nullptr), m_round(0), m_bgm(0)
{

}

void PlayGame::Initialize(Game * game)
{
	m_game = game;

	// �w�i�^�X�N�𐶐�
	m_bg = GetTaskManager()->AddTask<PlayBg>(this);
	m_bg->Initialize(this);

	// �X�e�[�W�^�X�N�𐶐�
	m_stage = GetTaskManager()->AddTask<Stage>(this);
	m_stage->Initialize(this);

	// �Փ˔���}�l�[�W���[�^�X�N�̓o�^
	// ���S�Ẵ^�X�N��Update�������I�������ɏՓ˔�����s�����߂����œo�^
	m_collisionManager = GetTaskManager()->AddTask<CollisionManager>(this);

	// �J�����̈ʒu���Œ肷��
	m_view = Matrix::CreateLookAt(Vector3(5.0f, 20.5f, 6.5f), Vector3(5.0f, 0, 5.5f), Vector3::Up);

	// �ˉe�s����쐬����
	m_projection = Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		SCREEN_W / (float)SCREEN_H,
		0.1f,
		200.0f
	);

	// �G�t�F�N�g�p���\�[�X�̏�����
	InitializeEffectResources(m_game);
}

bool PlayGame::Update(float elapsedTime)
{
	auto kb = Keyboard::Get().GetState();
	m_tracker.Update(kb);

	return true;
}

void PlayGame::Render()
{

}

void PlayGame::AddCollision(Object * object)
{
	m_collisionManager->AddObject(object);
}

wchar_t * PlayGame::GetStageFilename(int round)
{
	static wchar_t fname[32];

	wsprintfW(fname, L"StageData\\Stage%02d.csv", round);

	return fname;
}

void PlayGame::InitializeEffectResources(Game* game)
{
	// �G�t�F�N�g�̍쐬
	m_batchEffect = std::make_unique<BasicEffect>(game->GetDevice());
	m_batchEffect->SetTextureEnabled(true);
	m_batchEffect->SetVertexColorEnabled(true);

	// ���̓��C�A�E�g����
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	game->GetDevice()->CreateInputLayout(VertexPositionColorTexture::InputElements, VertexPositionColorTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf());

	// �v���~�e�B�u�o�b�`�̍쐬
	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(game->GetContext());

	// �q�b�g�G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
	CreateWICTextureFromFile(m_game->GetDevice(), L"Resources\\Textures\\hit_effect.png", nullptr, m_hitEffectTexture.GetAddressOf());

	// �W�����v�G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
	CreateWICTextureFromFile(m_game->GetDevice(), L"Resources\\Textures\\jump_effect.png", nullptr, m_jumpEffectTexture.GetAddressOf());

	// ���G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
	CreateWICTextureFromFile(m_game->GetDevice(), L"Resources\\Textures\\smoke_effect.png", nullptr, m_smokeEffectTexture.GetAddressOf());
}


