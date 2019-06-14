#pragma once

#include "SceneBase.h"

#include "../PlayScene/Floor.h"
#include "../PlayScene/Gimmick.h"
#include "../PlayScene/PlayBg.h"
#include "../PlayScene/Player.h"
#include "../PlayScene/Stage.h"
#include "../TaskManager.h"


class GameScene : public SceneBase, public Task
{
	// 画面サイズ
	static const int SCREEN_W = 960;
	static const int SCREEN_H = 720;

	// ラウンド数
	static const int ROUND_MAX;

	// ゲームステート
	enum GAME_STATE
	{
		STATE_TITLE,		// タイトル画面
		STATE_PARTS_SELECT,	// パーツ選択画面
		STATE_START,		// 開始
		STATE_GAME,			// ゲーム中
		STATE_AGAIN,		// 死んだので再チャレンジ
		STATE_NEXT,			// 次のステージへ
		STATE_GAMEOVER,		// ゲームオーバー
	};

	// 描画順
	enum OT_PRIORITY
	{
		OT_TOP,			// 一番手前（２Ⅾ表示やエフェクトで使用） 
		OT_OBJECT,		// 床の上のオブジェクト
		OT_SHADOW,		// オブジェクトの影
		OT_STAGE,		// ステージ
		OT_FALL,		// 落下オブジェクト
		OT_BG,			// 背景
	};

	// 方向
	enum DIR
	{
		UP, LEFT, DOWN, RIGHT
	};

	// パーツ選択画面用
	enum SELECT_PARTS_KIND
	{
		POWERUP,	// パワーアップパーツ
		JUMP,		// ジャンプパーツ
	};

	// 方向に対応した角度
	static const float DIR_ANGLE[];

	// 重力
	static const float GRAVITY;

	// <コンストラクタ>
public:
	GameScene(SceneManager* sceneManager);	


	// <デストラクタ>
public:
	virtual ~GameScene();


	// <操作>
public:
	virtual void Initialize() override;
	virtual void Update(DX::StepTimer const& timer) override;
	virtual void Render() override;
	virtual void Finalize() override;

	Game* GetGame();

private:

	Floor* m_floor;		// FloorClassのポインター
	Gimmick* m_gimmick; // GimmickClassのポインター
	PlayBg* m_playBg;	// PlayBgClassのポインター
	Player* m_player;	// PlayerClassのポインター
	Stage* m_stage;		// StageClassのポインター



};