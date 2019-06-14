//---------------------------------------
// �^�C�g���w�i�N���X
//---------------------------------------
#pragma once

#include "../TaskManager.h"
class Game;

class TitleBg :public Task
{
public:
	TitleBg();
	~TitleBg();
	void Initialize(Game* game);

	bool Update(float elapsedTime)override;
	void Render()override;

private:
	Game* m_game;
	// �e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tileTexture;
	// �X�N���[���l
	float m_scroll;
};