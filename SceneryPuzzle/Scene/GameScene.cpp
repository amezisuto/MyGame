#include "GameScene.h"
#include "SceneManager.h"
#include "../Game.h"
#include "../InputManager.h"

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

// ���E���h��
const int GameScene::ROUND_MAX = 5;

// �����ɉ������p�x
const float GameScene::DIR_ANGLE[] =
{
	XMConvertToRadians(45.0f * 0),	// �k
	XMConvertToRadians(45.0f * 2),	// ��
	XMConvertToRadians(45.0f * 4),	// ��
	XMConvertToRadians(45.0f * 6),	// ��
};

// �d�́i�n�����9.8m/s^2)
const float GameScene::GRAVITY = 9.8f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager">�o�^����Ă���V�[���}�l�[�W���[</param>
GameScene::GameScene(SceneManager* sceneManager)
	: SceneBase(sceneManager)
{

	
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene()
{
	
}


/// <summary>
/// �Q�[���V�[���̏�����
/// </summary>
void GameScene::Initialize()
{
	// ���̏�����----------------------------------------
	m_floor = GetTaskManager()->AddTask<Floor>(this);
	//m_floor->Initialize();
	//---------------------------------------------------
	//// �M�~�b�N�̏�����----------------------------------
	//m_gimmick = GetTaskManager()->AddTask<Gimmick>(this);
	//m_gimmick->Initialize(m_sceneManager->GetGame());
	////---------------------------------------------------
	//// �w�i�̏�����--------------------------------------
	//m_playBg = GetTaskManager()->AddTask<PlayBg>(this);
	//m_playBg->Initialize(m_sceneManager->GetGame());
	////---------------------------------------------------
	//// �v���C���[�̏�����--------------------------------
	//m_player = GetTaskManager()->AddTask<Player>(this);
	//m_player->Initialize(m_sceneManager->GetGame());
	////---------------------------------------------------
	//// �X�e�[�W�̏�����----------------------------------
	//m_stage = GetTaskManager()->AddTask<Stage>(this);
	//m_stage->Initialize(this);
	////---------------------------------------------------
}


/// <summary>
/// �Q�[���V�[���̌�n������
/// </summary>
void GameScene::Finalize()
{
	// �|�C���^�[��j��------------------
	m_sceneManager->PtrDel(m_floor);
	m_sceneManager->PtrDel(m_gimmick);
	m_sceneManager->PtrDel(m_playBg);
	m_sceneManager->PtrDel(m_player);
	m_sceneManager->PtrDel(m_stage);
	//-----------------------------------
}






/// <summary>
/// �Q�[���V�[���̍X�V����
/// </summary>
/// <param name="timer">���ԏ��</param>
void GameScene::Update(DX::StepTimer const& timer)
{
	auto kb = System::InputManager::GetInstance().GetKeyState();
	float elapsedTime = float(timer.GetElapsedSeconds());
	// �X�V����--------------------------------------------------
	m_floor->Update(elapsedTime);		// ���̍X�V
	m_gimmick->Update(elapsedTime);		// �M�~�b�N�̍X�V
	m_playBg->Update(elapsedTime);		// �w�i�̍X�V
	m_player->Update(elapsedTime);		// �v���C���[�̍X�V
	m_stage->Update(elapsedTime);		// �X�e�[�W�̍X�V
	// ----------------------------------------------------------
}




/// <summary>
/// �Q�[���V�[���̕`�揈��
/// </summary>
void GameScene::Render()
{

	// �`�揈��-----------------------------------------
	m_floor->Render();		// ���̕`��
	m_gimmick->Render();	// �M�~�b�N�̕`��
	m_playBg->Render();		// �w�i�̕`��
	m_player->Render();		// �v���C���[�̕`��
	m_stage->Render();		// �X�e�[�W�̕`��
	//--------------------------------------------------
	
}

Game* GameScene::GetGame()
{
	return m_sceneManager->GetGame(); 
}

