//---------------------------------------
// �v���C���[�N���X
//---------------------------------------
#pragma once

#include "../Livr/Object.h"
#include "../TaskManager.h"
class SerectPlayer : public Object
{
public:
	// �v���C���[�̃^�C�v�ʃ��f��
	enum ModelType
	{
		NORMAL,	// �ʏ�
		MODEL_TYPE_NUM
	};

	// �v���C���[�̏��
	enum STATE
	{
		STATE_NORMAL,	// �ʏ�
		STATE_JUMP,		// �W�����v��
		STATE_HIT,		// ������΂�����
		STATE_FALL,		// ������
		STATE_DEAD,		// ���S
	};

	// 
	enum STATE_END
	{
		NONE,	// �ʏ�
		STATE_CLEAR,		// �W�����v��
		STATE_NOTCLAER,		// ������΂�����
	};

	struct Pos
	{
		int x;
		int y;
	};


	// ���Ƃ̔���p�̕��ƍ���
	static const float WIDTH;
	static const float HEIGHT;

	// �I�u�W�F�N�g���m�̔���p�̔��a
	static const float RADIUS;

	// �v���C���[�̍ő�ړ����x
	static const float MAX_SPEED;

	// �v���C���[�̏d��
	static const float WEIGHT;

	// ���ɑ΂��門�C�W��
	static const float FRICTION;

private:
	// �W�����v���Ă���t���[����
	static const int JUMP_FRAME;

	// �W�����v�̍���
	static const float JUMP_HEIGHT;

	// ���f���f�[�^�ւ̃|�C���^
	DirectX::Model* m_models[MODEL_TYPE_NUM];

	// �v���C���[�̏��
	STATE m_state;

	// �p���[�A�b�v
	int m_powerupParts;

	// �W�����v�p�[�c�𑕒����Ă��邩�H
	bool m_jumpParts;

	// �W�����v�J�E���^�[
	int m_jumpCounter;

	// �������̉�]
	float m_fallRotateAngle;

	// �ړ����ɌĂ΂��֐�
	std::function<void(Object*)> m_floorMove;

	// �߂鎞�ɌĂ΂��֐�
	std::function<void(Object*)> m_floorBackMove;

	// �߂鎞�ɌĂ΂��֐�
	std::function<void(Object*)> m_floorCheckBack;

	// �߂鎞�ɌĂ΂��֐�
	std::function<void(Object*)> m_playerKey;

	STATE_END m_clear;

	bool m_floorCheck;

	Pos m_nextPos;

	bool m_notMoveFlag;


	DirectX::SimpleMath::Vector3 m_target; // �ړ���
	float   m_speed = 5;
	float   m_attenuation = 0.5f;

	DirectX::SimpleMath::Vector3 m_velocity;

	bool m_moveFlag;


public:
	// �R���X�g���N�^
	SerectPlayer();

	// �������֐�
	void Initialize(SerectGame* serectGame, int x, int y);

	// ���f���ݒ�֐�
	void SetModel(ModelType modelType, DirectX::Model* model);

	// �I�u�W�F�N�g�h�c���擾����֐�
	Object::OBJECT_ID GetID() { return Object::PLAYER; }

	// �X�V�֐�
	bool Update(float elapsedTime) override;

	// �`��֐�
	void Render() override;

	// �X�V�����i�Փ˂��Đ���s�\���j
	void State_Hit(float elapsedTime);

	// �Փ˂�����Ă΂��֐�
	void OnHit(Object* object) override;

	// �v���C���[�̏�Ԃ��擾����֐�
	SerectPlayer::STATE GetState();
	SerectPlayer::STATE_END GetStateEnd();

	// �v���C���[�̈ړ��֐�
	void Move(float elapsedTime, const DirectX::Keyboard::KeyboardStateTracker& tracker);

	// �ړ����ɌĂ΂��֐���ݒ肷��֐�
	void SetFloorMove(std::function<void(Object*)> func);

	// �W�����v�I�����ɌĂ΂��֐���ݒ肷��֐�
	void SetFloorBackMove(std::function<void(Object*)> func);

	// �W�����v�I�����ɌĂ΂��֐���ݒ肷��֐�
	void SetFloorCheckBack(std::function<void(Object*)> func);

	// ���Z�b�g�֐�
	void Reset();
	void SetFloorCheck(bool flag);

	void SetNotMoveFlag(bool flag);

	void SetNextPosX(int x);
	void SetNextPosY(int y);

	int GetNextPosX();
	int GetNextPosY();



	void SetNextFloorPos(DirectX::SimpleMath::Vector3 pos);

	void State_Jump(float elapsedTime);


private:
	// �L�[���͂�����������߂�֐�
	int GetKeyToDir(int key);

	// ENEMY_1�ƏՓ˂������̏����֐�
	void OnHit_Piller(Object* object);
};
