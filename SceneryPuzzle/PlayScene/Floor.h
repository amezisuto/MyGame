//---------------------------------------
// ���N���X
//---------------------------------------
#pragma once

#include "../Livr/Object.h"
class Stage;

class Floor : public Object
{
public:
	// ���̏��
	enum State
	{
		NONE,		// ���Ȃ�
		NORMAL,		// �ʏ�
		PILLER,	// ��
		LODE,		// �ړ�����

		STATE_NUM
	};

	// �_���[�W�̈ڍs����
	static const float LODE_DELAY_TIME;

private:
	// �X�e�[�W�ւ̃|�C���^
	Stage* m_stage;

	// ���f���f�[�^�ւ̃|�C���^
	DirectX::Model* m_models[STATE_NUM];

	// ���̏��
	State m_state;

	// �ʒu
	DirectX::SimpleMath::Vector3 m_pos;

	// �_���[�W�t���O�i�P�t���[���ɂP�񂵂��_���[�W������Ȃ��悤�ɂ��邽�߂̃t���O�j
	bool m_lodeFlag;

	// �_���[�W�������Ď��̏�ԂɈڍs����܂ł̃^�C�}�[
	float m_lodeTimer;

public:
	// �R���X�g���N�^
	Floor();

	// �������֐�
	void Initialize(Stage* stage, int x, int y);

	// �X�V�֐�
	bool Update(float elapsedTime) override;

	// �`��֐�
	void Render() override;

	// ���f���ݒ�֐�
	void SetModel(State state, DirectX::Model* model);

	// ���̏�Ԃ�ݒ肷��֐�
	void SetState(Floor::State state) { m_state = state; }

	// ���̏�Ԃ��擾����֐�
	Floor::State GetState() { return m_state; }

	DirectX::SimpleMath::Vector3 GetPosion() { return m_pos; }

	// �_���[�W��^����֐�
	void Lode();

	// ���Z�b�g�֐�
	void Reset();
};
