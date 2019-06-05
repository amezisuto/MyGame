/// <summary>
/// SceneBase.h
/// </summary>



// ���d�C���N���[�h�̖h�~ =====================================================
#pragma once



// �w�b�_�t�@�C���̃C���N���[�h ===============================================
#include "..\StepTimer.h"



// �N���X�̐錾 ===============================================================
class SceneManager;



// �N���X�̒�` ===============================================================
/// <summary>
/// �V�[���̊��N���X
/// </summary>
class SceneBase
{
	// �f�[�^�����o�̐錾 -------------------------------------------------
protected:
	SceneManager* m_sceneManager;


	// �����o�֐��̐錾 ---------------------------------------------------
	// <�R���X�g���N�^>
public:
	SceneBase();
	SceneBase(SceneManager* sceneManager);


	// <�f�X�g���N�^>
public:
	virtual ~SceneBase();


	// <����>
public:
	virtual void Initialize() = 0;
	virtual void Update(DX::StepTimer const& timer) = 0;
	virtual void Render() = 0;
	virtual void Finalize() = 0;
};
