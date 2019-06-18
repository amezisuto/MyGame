#include "SerectScene.h"
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
SerectScene::SerectScene(SceneManager* sceneManager)
	: SceneBase(sceneManager)
{


}


/// <summary>
/// デストラクタ
/// </summary>
SerectScene::~SerectScene()
{

}


/// <summary>
/// ゲームシーンの初期化
/// </summary>
void SerectScene::Initialize()
{
	// ゲームの初期化----------------------------------------
	m_serectGmae = m_gameTM.AddTask<SerectGame>();
	m_serectGmae->Initialize(m_sceneManager->GetGame());
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
void SerectScene::Finalize()
{
	// ポインターを破棄------------------
	m_sceneManager->PtrDel(m_serectGmae);
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
void SerectScene::Update(DX::StepTimer const& timer)
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
void SerectScene::Render()
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

Game* SerectScene::GetGame()
{
	return m_sceneManager->GetGame();
}

