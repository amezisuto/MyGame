//---------------------------------------
// ギミッククラス
//---------------------------------------
#pragma once

#include "../Livr/Object.h"
class Game;
class PlayGame;

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
	// 床との判定用の幅と高さ
	static const float WIDTH;
	static const float HEIGHT;
private:
	// パーツの種類
	Kind m_kind;

public:
	Gimmick();
	~Gimmick();
	void Initialize(PlayGame* playGame, Kind kind, int x, int y, DirectX::Model * model);

	bool Update(float elapsedTime)override;
	void Render()override;

	void Reset();

	// オブジェクトＩＤを取得する関数
	Object::OBJECT_ID GetID();

private:
	Game* m_game;
};
