#include "../pch.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "../InputManager.h"
#include "../Game.h"
#include "GameLi/GameManeger.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

extern void ExitGame();
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager">�o�^����Ă���V�[���}�l�[�W���[</param>
TitleScene::TitleScene(SceneManager* sceneManager)
	: SceneBase(sceneManager)
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleScene::~TitleScene()
{

}


/// <summary>
/// �^�C�g���V�[���̏�����
/// </summary>
void TitleScene::Initialize()
{
	// �Q�[���^�C�g���̏�����----------------------------
	m_title = GetTaskManager()->AddTask<Title>(this);
	m_title->Initialize(m_sceneManager->GetGame());
	//---------------------------------------------------
	// �^�C�g���w�i�̏�����------------------------------
	m_titleBg = GetTaskManager()->AddTask<TitleBg>(this);
	m_titleBg->Initialize(m_sceneManager->GetGame());
	//---------------------------------------------------
	// �^�C�g��UI�̏�����--------------------------------
	m_titleUi = GetTaskManager()->AddTask<TitleUi>(this);
	m_titleUi->Initialize(m_sceneManager->GetGame());
	//---------------------------------------------------
}


/// <summary>
/// �^�C�g���V�[���̌�n������
/// </summary>
void TitleScene::Finalize()
{
	// �|�C���^�[��j��------------------
	m_sceneManager->PtrDel(m_title);
	m_sceneManager->PtrDel(m_titleBg);
	m_sceneManager->PtrDel(m_titleUi);
	//-----------------------------------
}


/// <summary>
/// �^�C�g���V�[���̍X�V����
/// </summary>
/// <param name="timer">���ԏ��</param>
void TitleScene::Update(DX::StepTimer const& timer)
{
	auto kb = System::InputManager::GetInstance().GetKeyState();
	float elapsedTime = float(timer.GetElapsedSeconds());

	// �X�V����--------------------------------------------------
	m_title->Update(elapsedTime);		// �Q�[���^�C�g���̍X�V
	m_titleBg->Update(elapsedTime);		// �^�C�g���w�i�̍X�V
	m_titleUi->Update(elapsedTime);		// �^�C�g��UI�̍X�V
	// ----------------------------------------------------------

	if (kb.Space)
	{
		m_sceneManager->RequestToChangeScene(SCENE_PLAY);
	}
}


/// <summary>
/// �^�C�g���V�[���̕`�揈��
/// </summary>
void TitleScene::Render()
{
	// �`�揈��-----------------------------------------
	m_titleBg->Render();		// �^�C�g���w�i�̕`��
	m_title->Render();			// �Q�[���^�C�g���̕`��
	m_titleUi->Render();		// �^�C�g��UI�̕`��
	//--------------------------------------------------
}

