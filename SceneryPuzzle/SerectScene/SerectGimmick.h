//---------------------------------------
// �M�~�b�N�N���X
//---------------------------------------
#pragma once

#include "../Livr/Object.h"
class Serectame;

class SerectGimmick : public Object
{
public:
	// �M�~�b�N�̎��
	enum Kind
	{
		NONE,		// �Ȃ�
		BALL,		// �{�[��
		TRY,		// ��
		NOT,		// �i���֎~
		GOAL,		// �S�[��

		KIND_NUM
	};
	// ���Ƃ̔���p�̕��ƍ���
	static const float WIDTH;
	static const float HEIGHT;
private:
	// �p�[�c�̎��
	Kind m_kind;

public:
	SerectGimmick();
	void Initialize(SerectGame* serectGame, Kind kind, int x, int y, DirectX::Model * model);

	bool Update(float elapsedTime)override;

	void OnHit(Object* object);
	void Reset();

	// �I�u�W�F�N�g�h�c���擾����֐�
	Object::OBJECT_ID GetID();

private:
};
