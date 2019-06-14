//---------------------------------------
// ���N���X
//---------------------------------------
#pragma once

#include "../Livr/Object.h"
class Game;
class GameScene;

class Pillar :public Object
{
public:
	// �p�[�c�̎��
	enum Kind
	{
		NONE,		// ���w��
		BALL,	// �p���[�A�b�v
		TRY,		// �W�����v
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
	Pillar();
	~Pillar();
	void Initialize(PlayGame* playGame, Kind kind, int x, int y, DirectX::Model * model);

	bool Update(float elapsedTime)override;
	void Render()override;

private:
	Game* m_game;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
};
