//---------------------------------------
// ���N���X
//---------------------------------------
#pragma once

#include "../Livr/Object.h"
class SerectGame;

class SerectPillar :public Object
{
public:
	// �p�[�c�̎��
	enum Kind
	{
		NONE,		// ���w��
		BALL,	
		TRY,		
		NONE1,
		NONE2,
		NONE3,
		PILLAR,

		KIND_NUM
	};

	// ���Ƃ̔���p�̕��ƍ���
	static const float WIDTH;
	static const float HEIGHT;

private:

	// �p�[�c�̎��
	Kind m_kind;

public:
	SerectPillar();
	void Initialize(SerectGame* serectGame, Kind kind, int x, int y, DirectX::Model * model);

	bool Update(float elapsedTime)override;

	// �I�u�W�F�N�g�h�c���擾����֐�
	Object::OBJECT_ID GetID() override;

	// ���Z�b�g�֐�
	void Reset();


private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
};
