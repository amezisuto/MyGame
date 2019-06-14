#include "GameScene.h"
#include "SceneManager.h"
#include "../Game.h"
#include "../InputManager.h"

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

// ラウンド数
const int GameScene::ROUND_MAX = 5;

// 方向に応じた角度
const float GameScene::DIR_ANGLE[] =
{
	XMConvertToRadians(45.0f * 0),	// 北
	XMConvertToRadians(45.0f * 2),	// 西
	XMConvertToRadians(45.0f * 4),	// 南
	XMConvertToRadians(45.0f * 6),	// 東
};

// 重力（地球上は9.8m/s^2)
const float GameScene::GRAVITY = 9.8f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager">登録されているシーンマネージャー</param>
GameScene::GameScene(SceneManager* sceneManager)
	: SceneBase(sceneManager)
{

	
}


/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene()
{
	
}


/// <summary>
/// ゲームシーンの初期化
/// </summary>
void GameScene::Initialize()
{
	// 床の初期化----------------------------------------
	m_floor = GetTaskManager()->AddTask<Floor>(this);
	//m_floor->Initialize();
	//---------------------------------------------------
	//// ギミックの初期化----------------------------------
	//m_gimmick = GetTaskManager()->AddTask<Gimmick>(this);
	//m_gimmick->Initialize(m_sceneManager->GetGame());
	////---------------------------------------------------
	//// 背景の初期化--------------------------------------
	//m_playBg = GetTaskManager()->AddTask<PlayBg>(this);
	//m_playBg->Initialize(m_sceneManager->GetGame());
	////---------------------------------------------------
	//// プレイヤーの初期化--------------------------------
	//m_player = GetTaskManager()->AddTask<Player>(this);
	//m_player->Initialize(m_sceneManager->GetGame());
	////---------------------------------------------------
	//// ステージの初期化----------------------------------
	//m_stage = GetTaskManager()->AddTask<Stage>(this);
	//m_stage->Initialize(this);
	////---------------------------------------------------
}


/// <summary>
/// ゲームシーンの後始末処理
/// </summary>
void GameScene::Finalize()
{
	// ポインターを破棄------------------
	m_sceneManager->PtrDel(m_floor);
	m_sceneManager->PtrDel(m_gimmick);
	m_sceneManager->PtrDel(m_playBg);
	m_sceneManager->PtrDel(m_player);
	m_sceneManager->PtrDel(m_stage);
	//-----------------------------------
}






/// <summary>
/// ゲームシーンの更新処理
/// </summary>
/// <param name="timer">時間情報</param>
void GameScene::Update(DX::StepTimer const& timer)
{
	auto kb = System::InputManager::GetInstance().GetKeyState();
	float elapsedTime = float(timer.GetElapsedSeconds());
	// 更新処理--------------------------------------------------
	m_floor->Update(elapsedTime);		// 床の更新
	m_gimmick->Update(elapsedTime);		// ギミックの更新
	m_playBg->Update(elapsedTime);		// 背景の更新
	m_player->Update(elapsedTime);		// プレイヤーの更新
	m_stage->Update(elapsedTime);		// ステージの更新
	// ----------------------------------------------------------
}




/// <summary>
/// ゲームシーンの描画処理
/// </summary>
void GameScene::Render()
{

	// 描画処理-----------------------------------------
	m_floor->Render();		// 床の描画
	m_gimmick->Render();	// ギミックの描画
	m_playBg->Render();		// 背景の描画
	m_player->Render();		// プレイヤーの描画
	m_stage->Render();		// ステージの描画
	//--------------------------------------------------
	
}

Game* GameScene::GetGame()
{
	return m_sceneManager->GetGame(); 
}

