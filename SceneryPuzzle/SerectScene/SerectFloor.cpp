//--------------------------------------------------------------------------------------
// File: Floor.cpp
//
// 床クラス
//
// Date: 2018.11.4
// Author: Takeshi Yamaguthi
//--------------------------------------------------------------------------------------
#include "../pch.h"
#include "SerectFloor.h"
#include "../Game.h"
#include "SerectGame.h"
#include "SerectStage.h"

// ダメージの移行時間
const float SerectFloor::LODE_DELAY_TIME = 0.2f;

using namespace DirectX;
using namespace DirectX::SimpleMath;

SerectFloor::SerectFloor()
	: m_stage(nullptr), m_models{ nullptr }, m_state(NONE), m_lodeFlag(false), m_lodeTimer(0.0f), m_killFlag(false)
{	
	// 描画順の設定
	SetOt(SerectGame::OT_STAGE);
}

void SerectFloor::Initialize(SerectStage * stage, int x, int y)
{
	m_stage = stage;
	m_pos = Vector3((float)x, 0.0f, (float)y);
}

bool SerectFloor::Update(float elapsedTime)
{
	if (m_killFlag == true) return false;
	// 床フラグを落とす
	m_lodeFlag = false;

	// 移行
	if (m_lodeTimer > 0.0f)
	{
		m_lodeTimer -= elapsedTime;
		if (m_lodeTimer <= 0.0f)
		{
			m_lodeTimer = 0.0f;
			switch (m_state)
			{
			case NORMAL:	// 通常
				m_state = SerectFloor::LODE;	// 通過済み
				break;
			case LODE:	// 通路
				m_state = SerectFloor::NORMAL;		// 戻る
				break;
			default:
				break;
			}
		}
	}

	//// 落下状態の場合は床を下に落とす
	//if (m_state == SerectFloor::FALL)
	//{
	//	m_pos.y -= 0.1f;

	//	// ある程度落下したら消す
	//	if (m_pos.y < -3.0f)
	//	{
	//		m_state = SerectFloor::DEAD;
	//	}
	//}

	return true;
}

void SerectFloor::Render()
{
	if (!m_stage || !m_models[m_state]) return;

	// ワールド行列の作成
	Matrix world = Matrix::CreateTranslation(m_pos);

	Game* game = m_stage->GetGame();

	// 通った瞬間からモデル切り替えする
	State state = m_state;
	if (m_lodeTimer > 0) state = LODE;

	// モデルの描画
	m_models[state]->Draw(game->GetContext(), *game->GetStates()
		, world
		, m_stage->GetPlayGame()->GetViewMatrix()
		, m_stage->GetPlayGame()->GetProjectionMatrix(), false, [&]()
	{
		// 床は半透明の加算合成（半透明で暗くなってしまうので）
		game->GetContext()->OMSetBlendState(game->GetStates()->Additive(), nullptr, 0xffffffff);
	});

}

void SerectFloor::SetModel(State state, DirectX::Model * model)
{
	m_models[state] = model;
}

void SerectFloor::Lode()
{
	// １フレームに移動は１度だけ
	if (m_lodeFlag) return;
	m_lodeFlag = true;

	// 移行タイマーセット
	m_lodeTimer = LODE_DELAY_TIME;
}

void SerectFloor::Reset()
{
	m_pos.y = 0.0f;
	if (m_state != SerectFloor::NONE)
	{
		m_state = SerectFloor::NORMAL;
		m_lodeFlag = false;
		m_lodeTimer = 0.0f;
	}
}

