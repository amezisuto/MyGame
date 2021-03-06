#include "GameScene.h"
#include "SceneManager.h"
#include "../Game.h"
#include "../InputManager.h"

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;


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
	// ゲームの初期化----------------------------------------
		m_playGmae = m_gameTM.AddTask<PlayGame>();
		m_playGmae->Initialize(m_sceneManager->GetGame());
	//---------------------------------------------------
	// 床の初期化----------------------------------------
	//m_floor = GetTaskManager()->AddTask<Floor>(this);
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
	m_sceneManager->PtrDel(m_playGmae);
	//m_sceneManager->PtrDel(m_gimmick);
	//m_sceneManager->PtrDel(m_playBg);
	//m_sceneManager->PtrDel(m_player);
	//m_sceneManager->PtrDel(m_stage);
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
	m_gameTM.Update(elapsedTime);	// 床の更新
	//m_gimmick->Update(elapsedTime);		// ギミックの更新
	//m_playBg->Update(elapsedTime);		// 背景の更新
	//m_player->Update(elapsedTime);		// プレイヤーの更新
	//m_stage->Update(elapsedTime);		// ステージの更新
	// ----------------------------------------------------------
}




/// <summary>
/// ゲームシーンの描画処理
/// </summary>
void GameScene::Render()
{

	// 描画処理-----------------------------------------
	m_gameTM.Render();
	//m_floor->Render();		// 床の描画
	//m_gimmick->Render();	// ギミックの描画
	//m_playBg->Render();		// 背景の描画
	//m_player->Render();		// プレイヤーの描画
	//m_stage->Render();		// ステージの描画
	//--------------------------------------------------
	
}

Game* GameScene::GetGame()
{
	return m_sceneManager->GetGame(); 
}

