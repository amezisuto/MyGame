//--------------------------------------------------------------------------------------
// File: Object.h
//
// �I�u�W�F�N�g�N���X
//
// Date: 2018.12.5
// Author: Takeshi Yamaguthi
//--------------------------------------------------------------------------------------
#pragma once

#include "../TaskManager.h"

class GameScene;

// �I�u�W�F�N�g�N���X
class Object : public Task
{
public:

	// �I�u�W�F�N�g�h�c
	enum OBJECT_ID
	{
		NONE,		// �Ȃ�
		BALL,		// �{�[��
		TRY,		// ��
		NOTB,		// �i���֎~
		GOAL,		// �S�[��
		PLAYER,		// �v���C���[
		PILLAR      //	��
	};

protected:

	// �Q�[���E�C���h�E�ւ̃|�C���^
	GameScene* m_gameScene;

	// ���f���f�[�^�ւ̃|�C���^
	DirectX::Model* m_model;

	// �����Ă�������i�W�����ŕ\���B�e�r�b�g�ŉ����ꂽ������\���B�j
	int m_dir;

	// ����
	float m_weight;

	// ���Ƃ̖��C�W���i�ʁj
	float m_coefficientOfFriction;

	// �����x
	DirectX::SimpleMath::Vector3 m_a;

	// ���x
	DirectX::SimpleMath::Vector3 m_v;

	// �ʒu
	DirectX::SimpleMath::Vector3 m_pos;

	// �^�X�N�����t���O
	bool m_killFlag;

	// ���a
	float m_radius;

	// ���ƍ���
	float m_w, m_h;

	// �Փ˃t���O
	bool m_hitFlag;

	// ���̃`�F�b�N�֐�
	std::function<bool(Object*)> m_floorCheckFunction;

	// ���_�����Z����֐�
	std::function<void(int score)> m_addScoreFunction;

	// �\���t���O
	bool m_displayFlag;

	// �X�V�֐������s���邩�ǂ������f����t���O
	bool m_activeFlag;

	// �X�e�[�W��̈ʒu
	int m_x, m_y;

public:
	// �R���X�g���N�^
	Object();

	// �X�V
	bool Update(float elapsedTime) override;

	// �`��
	void Render() override;

	// �^�X�N�����֐�
	virtual void Kill() { m_killFlag = true; }

	// �I�u�W�F�N�g�h�c���擾����֐�
	virtual Object::OBJECT_ID GetID() = 0;

	// �Փ˂�����Ă΂��֐�
	virtual void OnHit(Object* obj) {};

	// �ʒu���擾����֐�
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_pos; }

	// ���a���擾����֐�
	float GetRadius() { return m_radius; }

	// �Փ˃t���O�̐ݒ�֐�
	void SetHitFlag(bool flag) { m_hitFlag = flag; }

	// �Փ˃t���O�̎擾�֐�
	bool GetHitFlag() { return m_hitFlag; }

	// �����擾����֐�
	float GetWidth() { return m_w; }

	// �������擾����֐�
	float GetHeight() { return m_h; }

	// ���ʂ��擾����֐�
	float GetWeight() { return m_weight; }

	// ���̃`�F�b�N�֐��̓o�^�֐�
	void SetCheckFloorFunction(std::function<bool(Object* object)> func);

	// ���_�����Z����֐��̓o�^�֐�
	void SetAddScoreFunction(std::function<void(int score)> func);

	// �\����ON/OFF����֐�
	void SetDisplayFlag(bool flag) { m_displayFlag = flag; }

	// �\����ON/OFF���擾����֐�
	bool GetDisplayFlag() { return m_displayFlag; }

	// �X�V�֐������s���邩�ǂ����ݒ肷��֐�
	void SetActive(bool flag) { m_activeFlag = flag; }

	// �Փ˂������ɑ���ɗ^����͂��擾����֐�
	virtual float GetHitForce();

	// ���Z�b�g�֐�
	virtual void Reset() {}

protected:
	// �͂�������֐�
	void AddForce(float angle, float force);

	// ���C�ɂ�葬�x����������֐�
	void Friction(float elapsedTime);

	// ���̃`�F�b�N�֐��ifalse�F�ʘH�j
	bool CheckFloor();

	// �^�[�Q�b�g�̕�����Ԃ��֐��i�^����O�Ƃ��āA�t���v��]�łW�����j
	int GetDir(Object* object);

	// ���_�����Z����֐�
	void AddScore(int score);
};
