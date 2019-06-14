//---------------------------------------
// ギミッククラス
//---------------------------------------
#pragma once

#include "../Livr/Object.h"
class Game;
class GameScene;

class Gimmick : public Object
{
public:
	// ギミックの種類
	enum Kind
	{
		NONE,		// なし
		BALL,		// ボール
		TRY,		// △
		NOT,		// 進入禁止
		GOAL,		// ゴール

		KIND_NUM
	};

private:
	// パーツの種類
	Kind m_kind;

public:
	Gimmick();
	~Gimmick();
	void Initialize(GameScene* gameScene, Kind kind, int x, int y, DirectX::Model * model);

	bool Update(float elapsedTime)override;
	void Render()override;

	void Reset();

	// オブジェクトＩＤを取得する関数
	Object::OBJECT_ID GetID();

private:
	Game* m_game;
	GameScene* m_gameScene;
};
