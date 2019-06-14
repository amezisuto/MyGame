//---------------------------------------
// �M�~�b�N�N���X
//---------------------------------------
#pragma once

#include "../Livr/Object.h"
class Game;
class GameScene;

class Gimmick : public Object
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

private:
	// �p�[�c�̎��
	Kind m_kind;

public:
	Gimmick();
	~Gimmick();
	void Initialize(GameScene* gameScene, Kind kind, int x, int y, DirectX::Model * model);

	bool Update(float elapsedTime)override;
	void Render()override;

	void Reset();

	// �I�u�W�F�N�g�h�c���擾����֐�
	Object::OBJECT_ID GetID();

private:
	Game* m_game;
	GameScene* m_gameScene;
};
