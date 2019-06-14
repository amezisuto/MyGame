#include "../Game.h"
#include "Stage.h"
#include "PlayGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// コンストラクタ
Stage::Stage()
{
}

// デストラクタ
Stage::~Stage()
{
}

// 初期化
void Stage::Initialize(PlayGame* playGame)
{
	m_playGame = playGame;
	m_game = m_playGame->GetGame();// Game.cppの情報の取得

	// モデルデータの読み込み
	EffectFactory fx(m_game->GetDevice());
	fx.SetDirectory(L"Resources\\Models");
	m_floorModels[Floor::NORMAL] = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\floorPanel_00.cmo", fx);
	m_floorModels[Floor::PILLER] = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\hasira.cmo", fx);
	m_floorModels[Floor::LODE] = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\keiro.cmo", fx);
	m_playerModels = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\start.cmo", fx);
	m_ballModel = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\Key.cmo", fx);
	m_tryModel = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\try.cmo", fx);
	m_notModel = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\notB.cmo", fx);
	m_goalModel = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\Enemy_02.cmo", fx);

	// 床のタスク生成
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			m_floors[j][i] = GetTaskManager()->AddTask<Floor>(this);
			m_floors[j][i]->Initialize(this, i, j);
			// 各状態のモデルを設定
			m_floors[j][i]->SetModel(Floor::NORMAL, m_floorModels[Floor::NORMAL].get());
			m_floors[j][i]->SetModel(Floor::PILLER, m_floorModels[Floor::PILLER].get());
			m_floors[j][i]->SetModel(Floor::LODE, m_floorModels[Floor::LODE].get());
		}
	}
}
Game * Stage::GetGame()
{
	return m_game;
}

Floor * Stage::GetFloor(int x, int y)
{
	if (x >= 0 && x < STAGE_W && y >= 0 && y < STAGE_H)
	{
		return m_floors[y][x];
	}
	return nullptr;
}

bool Stage::LoadStageData(wchar_t * fname)
{
	std::wstring str;

	// ファイルのオープン
	std::wifstream ifs(fname);

	//----- ステージデータ -----//

	// ヘッダ文字列
	std::wstring stageHeadName = L"STAGE";

	// ヘッダ部分までシーク
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str.compare(0, stageHeadName.size(), stageHeadName) == 0)
		{
			break;
		}
	}

	// ステージデータの読み込み
	for (int i = 0; i < STAGE_H; i++)
	{
		getline(ifs, str);
		std::wstring tmp;
		std::wistringstream stream(str);
		for (int j = 0; j < STAGE_W; j++)
		{
			std::getline(stream, tmp, L',');
			m_stageData.stage[i][j] = std::stoi(tmp) + 1;
		}
	}

	//----- ステージ上のオブジェクトデータ -----//

	// ヘッダ文字列
	std::wstring objectHeadName = L"OBJECT";

	// ファイルポインタを先頭へシーク
	ifs.clear();
	ifs.seekg(0);

	// ヘッダ部分までシーク
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str.compare(0, objectHeadName.size(), objectHeadName) == 0)
		{
			break;
		}
	}

	// オブジェクトデータの読み込み
	for (int i = 0; i < STAGE_H; i++)
	{
		getline(ifs, str);
		std::wstring tmp;
		std::wistringstream stream(str);
		for (int j = 0; j < STAGE_W; j++)
		{
			std::getline(stream, tmp, L',');
			m_stageData.object[i][j] = std::stoi(tmp);
		}
	}

	// ファイルのクローズ
	ifs.close();

	return true;
}

void Stage::SetStageData()
{
	// 床を元の状態に戻す
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			if (m_stageData.stage[i][j] == 1)
			{
				m_floors[j][i]->SetState(static_cast<Floor::State>(m_stageData.stage[j][i]));
			}
		}
	}

	// 全てのオブジェクトタスクの削除
	DeleteAllObject();


	//----- 各タスクの生成 -----//

	Gimmick* ball;
	Gimmick* tryB;
	Gimmick* notB;
	Pillar* pillar;
	Gimmick* goal;

	// ステージ上のオブジェクトを配置する
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			if (m_stageData.stage[i][j] == 2)
			{
				pillar = GetTaskManager()->AddTask<Pillar>(this);
				pillar->Initialize(m_playGame, Pillar::PILLAR, i, j, m_floorModels[Floor::PILLER].get());
				m_pillar.push_back(pillar);
			}
			// オブジェクトの種類によりタスク生成する
			switch (m_stageData.object[j][i])
			{
			case OBJECT_ID::PLAYER:	// プレイヤー
				m_player = GetTaskManager()->AddTask<Player>(this);
				m_player->Initialize(m_playGame, i, j);
				m_player->SetModel(Player::NORMAL, m_playerModels.get());
				m_floors[j][i]->SetState(Floor::LODE);
				m_floorStack.push(m_floors[j][i]);
				m_floorX = i; m_floorY = j;

				// 床との判定関数を登録
				m_player->SetCheckFloorFunction([&](Object* object)
				{
					return CheckFloor(object->GetPosition(), object->GetWidth(), object->GetHeight());
				});
				// 通過時の関数を登録
				m_player->SetFloorMove([&](Object* object)
				{
					if (m_floors[m_floorY + m_player->GetNextPosY()][m_floorX + m_player->GetNextPosX()]->GetState() == Floor::NORMAL)
					{
						m_floors[m_floorY + m_player->GetNextPosY()][m_floorX + m_player->GetNextPosX()]->SetState(Floor::LODE);
						m_player->SetNextFloorPos(m_floors[m_floorY + m_player->GetNextPosY()][m_floorX + m_player->GetNextPosX()]->GetPosion());
						m_floorStack.push(m_floors[m_floorY][m_floorX]);
						m_floorX = m_floorX + m_player->GetNextPosX();
						m_floorY = m_floorY + m_player->GetNextPosY();
						m_player->SetFloorCheck(true);

					}
					else if (m_floors[m_floorY + m_player->GetNextPosY()][m_floorX + m_player->GetNextPosX()] == m_floorStack.top())
					{
						m_floors[m_floorY][m_floorX]->SetState(Floor::NORMAL);
						m_player->SetNextFloorPos(m_floorStack.top()->GetPosion());
						m_floorStack.pop();
						m_floorX = m_floorX + m_player->GetNextPosX();
						m_floorY = m_floorY + m_player->GetNextPosY();
					}
					m_player->SetNextPosX(0);
					m_player->SetNextPosY(0);
				});
				// 戻る時の関数を登録
				m_player->SetFloorBackMove([&](Object* object)
				{
					if (m_floors[m_floorY + m_player->GetNextPosY()][m_floorX + m_player->GetNextPosX()]->GetState() == Floor::PILLER)
					{
						m_player->SetFloorCheck(false);
					}
				});
				//m_player->SetFloorCheckBack([&](Object* object)
				//{
				//	//LodeFloor(object->GetPosition(), object->GetWidth(), object->GetHeight());
				//	if (CheckFloorAnd(object->GetPosition(), object->GetWidth(), object->GetHeight()))
				//	{
				//		m_player->SetFloorCheck(false);
				//	}
				//		
				//});
				break;
			case OBJECT_ID::BALL:	// ボール
				ball = GetTaskManager()->AddTask<Gimmick>(this);
				ball->Initialize(m_playGame, Gimmick::BALL, i, j, m_ballModel.get());
				// 床との判定関数を登録
				ball->SetCheckFloorFunction([&](Object* object)
				{
					return CheckFloor(object->GetPosition(), object->GetWidth(), object->GetHeight());
				});
				m_ball.push_back(ball);
				break;
			case OBJECT_ID::TRY:		// △柱
				tryB = GetTaskManager()->AddTask<Gimmick>(this);
				tryB->Initialize(m_playGame, Gimmick::TRY, i, j, m_tryModel.get());
				m_try.push_back(tryB);
				break;
			case OBJECT_ID::NOTB:	// 進入禁止柱
				notB = GetTaskManager()->AddTask<Gimmick>(this);
				notB->Initialize(m_playGame, Gimmick::NOT, i, j, m_notModel.get());
				m_not.push_back(notB);
				break;
			case OBJECT_ID::GALE:	// ゴール
				goal = GetTaskManager()->AddTask<Gimmick>(this);
				goal->Initialize(m_playGame, Gimmick::GOAL, i, j, m_goalModel.get());
				// 床との判定関数を登録
				goal->SetCheckFloorFunction([&](Object* object)
				{
					return CheckFloor(object->GetPosition(), object->GetWidth(), object->GetHeight());
				});
				m_goal.push_back(goal);
				break;
			}
		}
	}
}

void Stage::ResetStageData()
{
	// 床をリセット
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			m_floors[j][i]->Reset();
		}
	}
	// パズルをリセット	
	for (Gimmick* p : m_ball)
	{
		p->Reset();
	}
	for (Gimmick* p : m_try)
	{
		p->Reset();
	}
	for (Gimmick* p : m_not)
	{
		p->Reset();
	}
	// プレイヤーをリセット
	if (m_player) m_player->Reset();

	// ゴールをリセット
	for (Object* p : m_goal)
	{
		p->Reset();
	}

	// 柱をリセット
	for (Object* p : m_pillar)
	{
		p->Reset();
	}
}

bool Stage::CheckFloor(DirectX::SimpleMath::Vector3 pos, float w, float h)
{
	int x, y;
	const Vector2 corner[4] = { Vector2(-1.0f, -1.0f), Vector2(1.0f, -1.0f), Vector2(1.0f,  1.0f), Vector2(-1.0f,  1.0f) };

	// 中心からの距離にするため幅と高さを２で割る
	w /= 2.0f;
	h /= 2.0f;

	// ４点を調べる
	int i = 0;
	for (; i < 4; i++)
	{
		// 3D空間の座標をマップチップの位置に変換する
		ConvertPosToMapChip(pos.x + w * corner[i].x, pos.z + h * corner[i].y, &x, &y);
		Floor* floor = this->GetFloor(x, y);
		if ((floor != nullptr)
			&& (floor->GetState() == Floor::State::NORMAL || floor->GetState() == Floor::State::LODE))
		{
			break;
		}
	}
	if (i == 4) return false;
	return true;
}
bool Stage::CheckBackFloor(DirectX::SimpleMath::Vector3 pos, float w, float h)
{
	int x, y;
	const Vector2 corner[4] = { Vector2(-1.0f, -1.0f), Vector2(1.0f, -1.0f), Vector2(1.0f,  1.0f), Vector2(-1.0f,  1.0f) };

	// 中心からの距離にするため幅と高さを２で割る
	w /= 2.0f;
	h /= 2.0f;

	// ４点を調べる
	int i = 0;
	for (; i < 4; i++)
	{
		// 3D空間の座標をマップチップの位置に変換する
		ConvertPosToMapChip(pos.x + w * corner[i].x, pos.z + h * corner[i].y, &x, &y);
		Floor* floor = this->GetFloor(x, y);
		if ((floor != nullptr)
			&& (floor->GetState() == Floor::State::LODE))
		{
			break;
		}
	}
	if (i == 4) return false;
	return true;
}



void Stage::SetFloorPos(DirectX::SimpleMath::Vector3 pos, float w, float h)
{
	m_floorPos.position = pos;
	m_floorPos.wid = w;
	m_floorPos.hei = h;
}

void Stage::DeleteAllObject()
{
	// 鍵を全て削除する
	for (Gimmick* p : m_ball)
	{
		p->Kill();
	}
	m_ball.clear();

	// プレイヤーを削除する
	if (m_player)
	{
		m_player->Kill();
		m_player = nullptr;
	}

	// ゴールを全て削除する
	for (Object* p : m_goal)
	{
		p->Kill();
	}
	m_goal.clear();

	// 柱を全て削除する
	for (Object* p : m_pillar)
	{
		p->Kill();
	}
	m_pillar.clear();

	// 柱のギミックを全て削除する
	for (Gimmick* p : m_try)
	{
		p->Kill();
	}
	m_try.clear();
	for (Gimmick* p : m_not)
	{
		p->Kill();
	}
	m_not.clear();

	for (int i = 0; i < m_floorStack.size(); i++)
	{
		if (m_floorStack.empty() == 1)
			m_floorStack.pop();
	}
}

void Stage::ConvertPosToMapChip(float x, float z, int* floor_x, int* floor_y)
{
	*floor_x = (int)floorf(x + 0.5f);
	*floor_y = (int)floorf(z + 0.5f);
}

// ゴール条件関数
bool Stage::GameEndCheck()
{
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			if (m_stageData.object[j][i] == 1)
			{
				if (m_floors[j][i]->GetState() == Floor::NORMAL)
				{
					return false;
				}
			}
			if (m_stageData.object[j][i] == 2)
			{
				int a = 0;
				if (m_floors[j - 1][i]->GetState() != Floor::NORMAL)a++;
				if (m_floors[j + 1][i]->GetState() != Floor::NORMAL)a++;
				if (m_floors[j][i - 1]->GetState() != Floor::NORMAL)a++;
				if (m_floors[j][i + 1]->GetState() != Floor::NORMAL)a++;
				if (a > 1 || a == 0)
				{
					return false;
				}
			}
			if (m_stageData.object[j][i] == 3)
			{
				if (m_floors[j - 1][i]->GetState() != Floor::NORMAL)
				{
					return false;
				}
				if (m_floors[j + 1][i]->GetState() != Floor::NORMAL) {
					return false;
				}
				if (m_floors[j][i - 1]->GetState() != Floor::NORMAL) {
					return false;
				}
				if (m_floors[j][i + 1]->GetState() != Floor::NORMAL) {
					return false;
				}
			}
		}
	}

	return true;
}

