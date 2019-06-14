//---------------------------------------
// 柱クラス
//---------------------------------------
#pragma once

#include "../Livr/Object.h"
class Game;
class GameScene;

class Pillar :public Object
{
public:
	// パーツの種類
	enum Kind
	{
		NONE,		// 未指定
		BALL,	// パワーアップ
		TRY,		// ジャンプ
		NONE1,
		NONE2,
		NONE3,
		PILLAR,

		KIND_NUM
	};

	// 床との判定用の幅と高さ
	static const float WIDTH;
	static const float HEIGHT;

private:

	// パーツの種類
	Kind m_kind;

public:
	Pillar();
	~Pillar();
	void Initialize(GameScene* gameScene, Kind kind, int x, int y, DirectX::Model * model);

	bool Update(float elapsedTime)override;
	void Render()override;

private:
	Game* m_game;
	GameScene* m_gameScene;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
};
