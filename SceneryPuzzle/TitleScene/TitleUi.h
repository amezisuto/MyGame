//---------------------------------------
// �^�C�g��UI�N���X
//---------------------------------------
#pragma once

#include "../TaskManager.h"
class Game;

class TitleUi :public Task
{
public:
	TitleUi();
	~TitleUi();
	void Initialize(Game* game);

	bool Update(float elapsedTime)override;
	void Render()override;

private:
	Game* m_game;
	// �e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pushSpaceTexture;

	// �\���t���O
	bool m_displayFlag;

	// �_�ŊԊu
	float m_interval;

	// �_�ŃJ�E���^
	float m_counter;
};