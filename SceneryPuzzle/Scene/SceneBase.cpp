/// <summary>
/// SceneBase.cpp
/// </summary>



// �w�b�_�t�@�C���̃C���N���[�h ===============================================
#include "SceneBase.h"

#include "SceneManager.h"



SceneBase::SceneBase()
{
}

// �����o�֐��̒�` ===========================================================
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager">�o�^����Ă���V�[���}�l�[�W���[</param>
SceneBase::SceneBase(SceneManager* sceneManager)
	: m_sceneManager(sceneManager)
{

}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneBase::~SceneBase()
{

}
