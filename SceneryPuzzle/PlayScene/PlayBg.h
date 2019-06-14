//---------------------------------------
// �v���C��ʔw�i�N���X
//---------------------------------------
#pragma once

#include "../Livr/Object.h"
class Game;

class PlayBg : public Object
{
public:
	PlayBg();
	~PlayBg();
	void Initialize(Game* game);

	bool Update(float elapsedTime)override;
	void Render()override;

private:
	Game* m_game;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
};
