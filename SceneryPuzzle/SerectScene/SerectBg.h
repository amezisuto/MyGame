//---------------------------------------
// �v���C��ʔw�i�N���X
//---------------------------------------
#pragma once

#include "../TaskManager.h"
class SerectGame;

class SerectBg : public Task
{
	// �Q�[���E�C���h�E�ւ̃|�C���^
	SerectGame* m_serectGame;

	// ���f���f�[�^�ւ̃|�C���^
	std::unique_ptr<DirectX::Model> m_model;

	// ��]�p
	float m_angle;

public:
	// �R���X�g���N�^
	SerectBg();

	// �������֐�
	void Initialize(SerectGame* serectGame);

	// �X�V�֐�
	bool Update(float elapsedTime) override;

	// �`��֐�
	void Render() override;
};

