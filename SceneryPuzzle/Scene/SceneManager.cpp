/// <summary>
/// SceneManager.cpp
/// </summary>



// �w�b�_�t�@�C���̃C���N���[�h ===============================================
#include "SceneManager.h"
#include "SceneBase.h"
#include "../Game.h"
//#include "LogoScene.h"
#include "SerectScene.h"
#include "GameScene.h"
#include "TitleScene.h"

// using�f�B���N�e�B�u ========================================================
//using namespace MyLibrary;

// �����o�֐��̒�` ===========================================================
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="startSceneId">�J�n�V�[����ID</param>
SceneManager::SceneManager(SceneId startSceneId)
	: m_activeScene(nullptr)
	, m_requestedScene(nullptr)
	, m_game(nullptr)
{
	// �V�[�����X�g�̏�����
	for (int i = 0; i < NUM_SCENES; i++)
	{
		m_scenes[i] = nullptr;
	}

	// �V�[���I�u�W�F�N�g�����X�g�ɓo�^
	//m_scenes[SCENE_LOGO] = new LogoScene(this);
	m_scenes[SCENE_TITLE] = new TitleScene(this);
	m_scenes[SCENE_STAGE] = new SerectScene(this);
	m_scenes[SCENE_PLAY] = new GameScene(this);
	// �J�n�V�[���̐ݒ�
	RequestToChangeScene(startSceneId);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager()
{
	m_activeScene = nullptr;
	m_requestedScene = nullptr;

	for (int i = 0; i < NUM_SCENES; i++)
	{
		delete m_scenes[i];
		m_scenes[i] = nullptr;
	}
}


/// <summary>
/// �������̃V�[���̍X�V����
/// </summary>
/// <param name="timer">���ԏ��</param>
void SceneManager::UpdateActiveScene(DX::StepTimer const& timer)
{
	if (m_requestedScene != nullptr)
	{
		ChangeScene();
	}

	if (m_activeScene != nullptr)
	{
		m_activeScene->Update(timer);
	}
}


/// <summary>
/// �������̃V�[���̕`�揈��
/// </summary>
void SceneManager::RenderActiveScene()
{
	if (m_activeScene != nullptr)
	{
		m_activeScene->Render();
	}
}


/// <summary>
/// �V�[���̕ύX��v��
/// </summary>
/// <param name="sceneId">�ύX��v������V�[����ID</param>
/// <returns>�v�����ʂ����ꍇ true, �ʂ�Ȃ��ꍇ false</returns>
bool SceneManager::RequestToChangeScene(SceneId sceneId)
{
	if (sceneId >= 0 && sceneId < NUM_SCENES)
	{
		m_requestedScene = m_scenes[sceneId];
		return true;
	}
	else
	{
		m_requestedScene = nullptr;
		return false;
	}
}


/// <summary>
/// �����V�[���̕ύX
/// </summary>
void SceneManager::ChangeScene()
{
	// �������̃V�[�����I��������
	if (m_activeScene != nullptr)
	{
		m_activeScene->Finalize();
	}


	// �v�����ꂽ�V�[�����������ɂ���
	m_activeScene = m_requestedScene;
	m_requestedScene = nullptr;


	// �V���Ɋ������ɂȂ����V�[��������������
	if (m_activeScene != nullptr)
	{
		m_activeScene->Initialize();
	}
}
