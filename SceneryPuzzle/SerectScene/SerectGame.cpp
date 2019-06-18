
#include "../pch.h"
#include "SerectGame.h"
#include "../Game.h"
#include "SerectStage.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

// ラウンド数
const int SerectGame::ROUND_MAX = 5;

// 方向に応じた角度
const float SerectGame::DIR_ANGLE[] =
{
	XMConvertToRadians(45.0f * 0),	// 北
	XMConvertToRadians(45.0f * 2),	// 西
	XMConvertToRadians(45.0f * 4),	// 南
	XMConvertToRadians(45.0f * 6),	// 東
};
// 重力（地球上は9.8m/s^2)
const float SerectGame::GRAVITY = 9.8f;

// 落下速度（１秒間に移動するドット数）
const float SerectGame::FALL_SPEED = 8.0f;


SerectGame::SerectGame()
	: m_game(nullptr), m_round(0), m_bgm(0), m_gameState(STATE_NONE)
{

}

void SerectGame::Initialize(Game * game)
{
	m_game = game;

	// 背景タスクを生成
	m_bg = GetTaskManager()->AddTask<SerectBg>(this);
	m_bg->Initialize(this);

	// ステージタスクを生成
	m_stage = GetTaskManager()->AddTask<SerectStage>(this);
	m_stage->Initialize(this);

	// 衝突判定マネージャータスクの登録
	// ※全てのタスクのUpdate処理が終わった後に衝突判定を行いためここで登録
	m_collisionManager = GetTaskManager()->AddTask<CollisionManager>(this);

	// カメラの位置を固定する
	m_view = Matrix::CreateLookAt(Vector3(5.0f, 20.5f, 6.5f), Vector3(5.0f, 0, 5.5f), Vector3::Up);

	// 射影行列を作成する
	m_projection = Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		SCREEN_W / (float)SCREEN_H,
		0.1f,
		200.0f
	);

	// エフェクト用リソースの初期化
	InitializeEffectResources(m_game);


}

bool SerectGame::Update(float elapsedTime)
{
	auto kb = Keyboard::Get().GetState();
	m_tracker.Update(kb);

	switch (m_gameState)
	{
	case STATE_NONE:	// 開始
						// ラウンド数を設定
		m_gameState = InitializeGame(elapsedTime);
		break;
	case STATE_START:	// 開始
						// ゲームスタート
		m_gameState = StartGame(elapsedTime);
		break;
	case STATE_GAME:	// ゲーム中
		m_gameState = GamePlay(elapsedTime);
		if (kb.Z)
		{
			// ステージをリセットする
			m_gameState = STATE_AGAIN;
		}

		break;
	case STATE_AGAIN:
		// 画面が真っ黒になるまで待つ
			// ステージをリセットする
			m_stage->ResetStageData();
			// ステージデータの読み込み
			m_stage->LoadStageData(GetStageFilename(m_round));
			// ステージデータの設定
			m_stage->SetStageData();
			// 続けてプレイ
			m_gameState = STATE_START;
		break;
	case STATE_NEXT:	// 次のステージへ
						// 画面が真っ黒になるまで待つ
			// 次のステージへ
			m_gameState = NextGame(elapsedTime);

		break;
	}

	


	//if (m_stage->GetPlayer()->GetStateEnd() == Player::STATE_CLEAR)
	//{
	//	if (m_stage->GameEndCheck())
	//		state = STATE_NEXT;
	//	else
	//		state = STATE_AGAIN;// 次のステージへ
	//}

	//// プレイヤーが死んだら
	//if (m_stage->GetPlayer()->GetState() == Player::STATE_DEAD)
	//{
	//	state = STATE_AGAIN;
	//}


	return true;
}

void SerectGame::Render()
{
}

SerectGame::GAME_STATE SerectGame::StartGame(float elapsedTime)
{
	// 敵を全てアクティブにする
	auto goalList = m_stage->GetGoalList();
	for (Object* p : goalList)
	{
		p->SetActive(true);
	}

	// ゲーム中へ
	return STATE_GAME;
}

SerectGame::GAME_STATE SerectGame::InitializeGame(float elapsedTime)
{


	// ラウンド数を設定
	m_round = 1;


	// ステージデータの読み込み
	m_stage->LoadStageData(GetStageFilename(m_round));

	// ステージデータの設定
	m_stage->SetStageData();


	// パーツ選択画面へ
	return 	STATE_START;
}

SerectGame::GAME_STATE SerectGame::GamePlay(float elapsedTime)
{
	GAME_STATE state = STATE_GAME;

	// プレイヤーの移動処理
	m_stage->GetPlayer()->Move(elapsedTime, m_tracker);


	if (m_stage->GetPlayer()->GetStateEnd() == SerectPlayer::STATE_CLEAR)
	{
		if (m_stage->GameEndCheck())
			state = STATE_NEXT;
		else
			state = STATE_AGAIN;// 次のステージへ
	}

	// プレイヤーが死んだら
	if (m_stage->GetPlayer()->GetState() == SerectPlayer::STATE_DEAD)
	{
		state = STATE_AGAIN;
	}

	return state;
}


SerectGame::GAME_STATE SerectGame::NextGame(float elapsedTime)
{

	// ラウンド数を加算
	m_round++;
	if (m_round > ROUND_MAX) m_round = 1;

	// ステージをリセットする
	m_stage->ResetStageData();

	// ステージデータの読み込み
	m_stage->LoadStageData(GetStageFilename(m_round));

	// ステージデータの設定
	m_stage->SetStageData();

	// パーツ選択へ
	return STATE_START;
}

void SerectGame::AddCollision(Object * object)
{
	m_collisionManager->AddObject(object);
}

wchar_t * SerectGame::GetStageFilename(int round)
{
	static wchar_t fname[32];

	wsprintfW(fname, L"Resources\\StageData\\Stage%02d.csv", round);

	return fname;
}

void SerectGame::InitializeEffectResources(Game* game)
{
	// エフェクトの作成
	m_batchEffect = std::make_unique<BasicEffect>(game->GetDevice());
	m_batchEffect->SetTextureEnabled(true);
	m_batchEffect->SetVertexColorEnabled(true);

	// 入力レイアウト生成
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	game->GetDevice()->CreateInputLayout(VertexPositionColorTexture::InputElements, VertexPositionColorTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf());

	// プリミティブバッチの作成
	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(game->GetContext());

	// ヒットエフェクト用テクスチャの読み込み
	CreateWICTextureFromFile(m_game->GetDevice(), L"Resources\\Textures\\hit_effect.png", nullptr, m_hitEffectTexture.GetAddressOf());

	// ジャンプエフェクト用テクスチャの読み込み
	CreateWICTextureFromFile(m_game->GetDevice(), L"Resources\\Textures\\jump_effect.png", nullptr, m_jumpEffectTexture.GetAddressOf());

	// 煙エフェクト用テクスチャの読み込み
	CreateWICTextureFromFile(m_game->GetDevice(), L"Resources\\Textures\\smoke_effect.png", nullptr, m_smokeEffectTexture.GetAddressOf());
}


