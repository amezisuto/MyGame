#include "SerectScene.h"
#include "SceneManager.h"
#include "../Game.h"
#include "../InputManager.h"

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager">�o�^����Ă���V�[���}�l�[�W���[</param>
SerectScene::SerectScene(SceneManager* sceneManager)
	: SceneBase(sceneManager)
{


}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SerectScene::~SerectScene()
{

}


/// <summary>
/// �Q�[���V�[���̏�����
/// </summary>
void SerectScene::Initialize()
{
	// �Q�[���̏�����----------------------------------------
	m_serectGmae = m_gameTM.AddTask<SerectGame>();
	m_serectGmae->Initialize(m_sceneManager->GetGame());
	//---------------------------------------------------
	// ���̏�����----------------------------------------
	//m_floor = GetTaskManager()->AddTask<Floor>(this);
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
void SerectScene::Finalize()
{
	// �|�C���^�[��j��------------------
	m_sceneManager->PtrDel(m_serectGmae);
	//m_sceneManager->PtrDel(m_gimmick);
	//m_sceneManager->PtrDel(m_playBg);
	//m_sceneManager->PtrDel(m_player);
	//m_sceneManager->PtrDel(m_stage);
	//-----------------------------------
}






/// <summary>
/// �Q�[���V�[���̍X�V����
/// </summary>
/// <param name="timer">���ԏ��</param>
void SerectScene::Update(DX::StepTimer const& timer)
{
	auto kb = System::InputManager::GetInstance().GetKeyState();
	float elapsedTime = float(timer.GetElapsedSeconds());
	// �X�V����--------------------------------------------------
	m_gameTM.Update(elapsedTime);	// ���̍X�V
									//m_gimmick->Update(elapsedTime);		// �M�~�b�N�̍X�V
									//m_playBg->Update(elapsedTime);		// �w�i�̍X�V
									//m_player->Update(elapsedTime);		// �v���C���[�̍X�V
									//m_stage->Update(elapsedTime);		// �X�e�[�W�̍X�V
									// ----------------------------------------------------------
}




/// <summary>
/// �Q�[���V�[���̕`�揈��
/// </summary>
void SerectScene::Render()
{

	// �`�揈��-----------------------------------------
	m_gameTM.Render();
	//m_floor->Render();		// ���̕`��
	//m_gimmick->Render();	// �M�~�b�N�̕`��
	//m_playBg->Render();		// �w�i�̕`��
	//m_player->Render();		// �v���C���[�̕`��
	//m_stage->Render();		// �X�e�[�W�̕`��
	//--------------------------------------------------

}

Game* SerectScene::GetGame()
{
	return m_sceneManager->GetGame();
}

