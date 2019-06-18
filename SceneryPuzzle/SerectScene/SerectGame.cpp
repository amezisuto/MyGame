
#include "../pch.h"
#include "SerectGame.h"
#include "../Game.h"
#include "SerectStage.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

// ���E���h��
const int SerectGame::ROUND_MAX = 5;

// �����ɉ������p�x
const float SerectGame::DIR_ANGLE[] =
{
	XMConvertToRadians(45.0f * 0),	// �k
	XMConvertToRadians(45.0f * 2),	// ��
	XMConvertToRadians(45.0f * 4),	// ��
	XMConvertToRadians(45.0f * 6),	// ��
};
// �d�́i�n�����9.8m/s^2)
const float SerectGame::GRAVITY = 9.8f;

// �������x�i�P�b�ԂɈړ�����h�b�g���j
const float SerectGame::FALL_SPEED = 8.0f;


SerectGame::SerectGame()
	: m_game(nullptr), m_round(0), m_bgm(0), m_gameState(STATE_NONE)
{

}

void SerectGame::Initialize(Game * game)
{
	m_game = game;

	// �w�i�^�X�N�𐶐�
	m_bg = GetTaskManager()->AddTask<SerectBg>(this);
	m_bg->Initialize(this);

	// �X�e�[�W�^�X�N�𐶐�
	m_stage = GetTaskManager()->AddTask<SerectStage>(this);
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

bool SerectGame::Update(float elapsedTime)
{
	auto kb = Keyboard::Get().GetState();
	m_tracker.Update(kb);

	switch (m_gameState)
	{
	case STATE_NONE:	// �J�n
						// ���E���h����ݒ�
		m_gameState = InitializeGame(elapsedTime);
		break;
	case STATE_START:	// �J�n
						// �Q�[���X�^�[�g
		m_gameState = StartGame(elapsedTime);
		break;
	case STATE_GAME:	// �Q�[����
		m_gameState = GamePlay(elapsedTime);
		if (kb.Z)
		{
			// �X�e�[�W�����Z�b�g����
			m_gameState = STATE_AGAIN;
		}

		break;
	case STATE_AGAIN:
		// ��ʂ��^�����ɂȂ�܂ő҂�
			// �X�e�[�W�����Z�b�g����
			m_stage->ResetStageData();
			// �X�e�[�W�f�[�^�̓ǂݍ���
			m_stage->LoadStageData(GetStageFilename(m_round));
			// �X�e�[�W�f�[�^�̐ݒ�
			m_stage->SetStageData();
			// �����ăv���C
			m_gameState = STATE_START;
		break;
	case STATE_NEXT:	// ���̃X�e�[�W��
						// ��ʂ��^�����ɂȂ�܂ő҂�
			// ���̃X�e�[�W��
			m_gameState = NextGame(elapsedTime);

		break;
	}

	


	//if (m_stage->GetPlayer()->GetStateEnd() == Player::STATE_CLEAR)
	//{
	//	if (m_stage->GameEndCheck())
	//		state = STATE_NEXT;
	//	else
	//		state = STATE_AGAIN;// ���̃X�e�[�W��
	//}

	//// �v���C���[�����񂾂�
	//if (m_stage->GetPlayer()->GetState() == Player::STATE_DEAD)
	//{
	//	state = STATE_AGAIN;
	//}


	return true;
}

void SerectGame::Render()
{
}

SerectGame::GAME_STATE SerectGame::StartGame(float elapsedTime)
{
	// �G��S�ăA�N�e�B�u�ɂ���
	auto goalList = m_stage->GetGoalList();
	for (Object* p : goalList)
	{
		p->SetActive(true);
	}

	// �Q�[������
	return STATE_GAME;
}

SerectGame::GAME_STATE SerectGame::InitializeGame(float elapsedTime)
{


	// ���E���h����ݒ�
	m_round = 1;


	// �X�e�[�W�f�[�^�̓ǂݍ���
	m_stage->LoadStageData(GetStageFilename(m_round));

	// �X�e�[�W�f�[�^�̐ݒ�
	m_stage->SetStageData();


	// �p�[�c�I����ʂ�
	return 	STATE_START;
}

SerectGame::GAME_STATE SerectGame::GamePlay(float elapsedTime)
{
	GAME_STATE state = STATE_GAME;

	// �v���C���[�̈ړ�����
	m_stage->GetPlayer()->Move(elapsedTime, m_tracker);


	if (m_stage->GetPlayer()->GetStateEnd() == SerectPlayer::STATE_CLEAR)
	{
		if (m_stage->GameEndCheck())
			state = STATE_NEXT;
		else
			state = STATE_AGAIN;// ���̃X�e�[�W��
	}

	// �v���C���[�����񂾂�
	if (m_stage->GetPlayer()->GetState() == SerectPlayer::STATE_DEAD)
	{
		state = STATE_AGAIN;
	}

	return state;
}


SerectGame::GAME_STATE SerectGame::NextGame(float elapsedTime)
{

	// ���E���h�������Z
	m_round++;
	if (m_round > ROUND_MAX) m_round = 1;

	// �X�e�[�W�����Z�b�g����
	m_stage->ResetStageData();

	// �X�e�[�W�f�[�^�̓ǂݍ���
	m_stage->LoadStageData(GetStageFilename(m_round));

	// �X�e�[�W�f�[�^�̐ݒ�
	m_stage->SetStageData();

	// �p�[�c�I����
	return STATE_START;
}

void SerectGame::AddCollision(Object * object)
{
	m_collisionManager->AddObject(object);
}

wchar_t * SerectGame::GetStageFilename(int round)
{
	static wchar_t fname[32];

	wsprintfW(fname, L"Resources\\StageData\\Stage%02d.csv", round);

	return fname;
}

void SerectGame::InitializeEffectResources(Game* game)
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


