//---------------------------------------
// è∞ÉNÉâÉX
//---------------------------------------
#pragma once

#include "../TaskManager.h"
class Game;

class Floor :public Task
{
public:
	Floor();
	~Floor();
	void Initialize();

	bool Update(float elapsedTime)override;
	void Render()override;

private:
	Game* m_game;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
};
