//---------------------------------------
// ステージクラス
//---------------------------------------
#pragma once

#include <vector>
#include <stack>
#include "../TaskManager.h"
#include "Floor.h"
#include "Player.h"
#include "Pillar.h"
#include "Gimmick.h"
class Game;
class GameScene;

class Stage : public Task
{
public:
	// オブジェクトＩＤ
	enum OBJECT_ID
	{
		NONE,		// なし
		BALL,		// ボール
		TRY,		// △
		NOTB,		// 進入禁止
		PLAYER,		// プレイヤー
		GALE,		// ゴール
	};
	struct FloorPosion
	{
		DirectX::SimpleMath::Vector3 position;
		float wid;
		float hei;
	};

	// ステージの大きさ
	static const int STAGE_W = 11;
	static const int STAGE_H = 11;

	// ステージデータの構造体
	struct StageData
	{
		int stage[STAGE_H][STAGE_W];
		int object[STAGE_H][STAGE_W];
	};

private:
	//	ゲームのポインター
	Game* m_game;
	//  ゲームシーンのポインター
	GameScene* m_gameScene;

	// 床タスクへのポインタ
	Floor* m_floors[STAGE_H][STAGE_W];
	Floor* m_floorsRecode[STAGE_H][STAGE_W];;

	// プレイヤータスクへのポインタ
	Player* m_player;

	// ゴールタスクへのポインタ
	std::vector<Object*> m_goal;

	// タスクへのポインタ
	std::vector<Gimmick*> m_ball;

	std::vector<Gimmick*> m_try;

	std::vector<Gimmick*> m_not;

	std::vector<Object*> m_pillar;

	//----- モデルへのポインタ -----//

	// 床のモデル
	std::unique_ptr<DirectX::Model> m_floorModels[Floor::STATE_NUM];

	// オブジェクトの影のモデル
	std::unique_ptr<DirectX::Model> m_shadowModel;

	// プレイヤーのモデル
	std::unique_ptr<DirectX::Model> m_playerModels;

	// ボールのモデル
	std::unique_ptr<DirectX::Model> m_ballModel;

	// △柱のモデル
	std::unique_ptr<DirectX::Model> m_tryModel;

	// 進入禁止のモデル
	std::unique_ptr<DirectX::Model> m_notModel;

	// ゴールのモデル
	std::unique_ptr<DirectX::Model> m_goalModel;

	// ステージデータ
	StageData m_stageData;

	// フロアの保存用データ
	FloorPosion m_floorPos;

	std::stack<Floor*> m_floorStack;
	int m_floorX, m_floorY;

public:
	// コンストラクタ
	Stage();

	// 初期化関数
	void Initialize(GameScene* gameScene);

	// ゲームオブジェクトのポインタを取得する関数
	Game* GetGame();

	// 床タスク取得関数
	Floor* GetFloor(int x, int y);

	// ステージデータの読み込み関数
	bool LoadStageData(wchar_t* fname);

	// ステージデータ初期化関数
	void SetStageData();

	// ステージデータのリセット関数
	void ResetStageData();

	// プレイヤーの取得関数
	Player* GetPlayer() { return m_player; }

	// ゴールの取得関数
	//const std::vector<Object*>& GetEnemyList() { return m_goal; }

	bool GameEndCheck();

	bool CheckFloorAnd(DirectX::SimpleMath::Vector3 pos, float w, float h);

private:
	// 通過チェック関数
	bool CheckFloor(DirectX::SimpleMath::Vector3 pos, float w, float h);
	bool CheckBackFloor(DirectX::SimpleMath::Vector3 pos, float w, float h);

	// 床を通過した関数
	void LodeFloor(DirectX::SimpleMath::Vector3 pos, float w, float h);
	bool CheckLodeFloor(DirectX::SimpleMath::Vector3 pos, float w, float h);

	// 通過した床を戻る関数
	void LodeBackFloor(DirectX::SimpleMath::Vector3 pos, float w, float h);
	bool CheckLodeBackFloor(DirectX::SimpleMath::Vector3 pos, float w, float h);

	// 登録されているタスク（プレイヤー、敵、パーツ）を全て削除する関数
	void DeleteAllObject();

	// 位置からステージのマップチップの位置に変換する関数
	void ConvertPosToMapChip(float x, float z, int* floor_x, int* floor_y);

	void SetFloorPos(DirectX::SimpleMath::Vector3 pos, float w, float h);

	void PlayerLodeFllor(DirectX::SimpleMath::Vector3 pos, float w, float h);
};
