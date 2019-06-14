//---------------------------------------
// �v���C��ʔw�i�N���X
//---------------------------------------
#pragma once

#include "../TaskManager.h"
class PlayGame;

class PlayBg : public Task
{
	// �Q�[���E�C���h�E�ւ̃|�C���^
	PlayGame* m_playGame;

	// ���f���f�[�^�ւ̃|�C���^
	std::unique_ptr<DirectX::Model> m_model;

	// ��]�p
	float m_angle;

public:
	// �R���X�g���N�^
	PlayBg();

	// �������֐�
	void Initialize(PlayGame* playGame);

	// �X�V�֐�
	bool Update(float elapsedTime) override;

	// �`��֐�
	void Render() override;
}

