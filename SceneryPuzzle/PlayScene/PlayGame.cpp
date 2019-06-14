
#include "../pch.h"
#include "PlayGame.h"
#include "../Game.h"
#include "Stage.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

// ラウンド数
const int PlayGame::ROUND_MAX = 5;

// 方向に応じた角度
const float PlayGame::DIR_ANGLE[] =
{
	XMConvertToRadians(45.0f * 0),	// 北
	XMConvertToRadians(45.0f * 2),	// 西
	XMConvertToRadians(45.0f * 4),	// 南
	XMConvertToRadians(45.0f * 6),	// 東
};
// 重力（地球上は9.8m/s^2)
const float PlayGame::GRAVITY = 9.8f;

// 落下速度（１秒間に移動するドット数）
const float PlayGame::FALL_SPEED = 8.0f;


PlayGame::PlayGame()
	: m_game(nullptr), m_round(0), m_bgm(0)
{

}

void PlayGame::Initialize(Game * game)
{
	m_game = game;

	// 背景タスクを生成
	m_bg = GetTaskManager()->AddTask<PlayBg>(this);
	m_bg->Initialize(this);

	// ステージタスクを生成
	m_stage = GetTaskManager()->AddTask<Stage>(this);
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

bool PlayGame::Update(float elapsedTime)
{
	auto kb = Keyboard::Get().GetState();
	m_tracker.Update(kb);

	return true;
}

void PlayGame::Render()
{

}

void PlayGame::AddCollision(Object * object)
{
	m_collisionManager->AddObject(object);
}

wchar_t * PlayGame::GetStageFilename(int round)
{
	static wchar_t fname[32];

	wsprintfW(fname, L"StageData\\Stage%02d.csv", round);

	return fname;
}

void PlayGame::InitializeEffectResources(Game* game)
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


