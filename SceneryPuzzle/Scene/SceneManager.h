/// <summary>
/// SceneManager.h
/// </summary>



// ���d�C���N���[�h�̖h�~ =====================================================
#pragma once



// �w�b�_�t�@�C���̃C���N���[�h ===============================================
#include "..\StepTimer.h"



// �N���X�̐錾 ===============================================================
class SceneBase;
class Game;



/// �萔�̒�` ================================================================
/// <summary>
/// �V�[��ID
/// </summary>
enum SceneId
{
	SCENE_LOGO,
	SCENE_TITLE,
	SCENE_STAGE,
	SCENE_PLAY,

	NUM_SCENES
};



/// �N���X�̒�` ==============================================================
/// <summary>
/// �V�[���}�l�[�W���[�N���X
/// </summary>
class SceneManager
{
	// �f�[�^�����o�̐錾 -------------------------------------------------
private:
	SceneBase* m_scenes[NUM_SCENES];    // �o�^����Ă���V�[���̃��X�g

	SceneBase* m_activeScene;           // �������̃V�[��
	SceneBase* m_requestedScene;        // �v�����ꂽ�V�[��

protected:
	static Game* m_game;


										// �����o�֐��̐錾 ---------------------------------------------------
										// <�R���X�g���N�^>
public:
	SceneManager(SceneId startSceneId);


	// <�f�X�g���N�^>
public:
	~SceneManager();


	// <����>
public:
	void UpdateActiveScene(DX::StepTimer const& timer);
	void RenderActiveScene();
	bool RequestToChangeScene(SceneId sceneId);

private:
	void ChangeScene();

public:
	static Game* GetGame() { return m_game; };

	// �Q�[���I�u�W�F�N�g��ݒ肷��֐�
	void SetGame(Game* game) { m_game = game; };
};
