#include "../pch.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "../InputManager.h"
#include "../Game.h"
#include "GameLi/GameManeger.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

extern void ExitGame();
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager">登録されているシーンマネージャー</param>
TitleScene::TitleScene(SceneManager* sceneManager)
	: SceneBase(sceneManager)
{
}


/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{

}


/// <summary>
/// タイトルシーンの初期化
/// </summary>
void TitleScene::Initialize()
{
	// ゲームタイトルの初期化----------------------------
	m_title = GetTaskManager()->AddTask<Title>(this);
	m_title->Initialize(m_sceneManager->GetGame());
	//---------------------------------------------------
	// タイトル背景の初期化------------------------------
	m_titleBg = GetTaskManager()->AddTask<TitleBg>(this);
	m_titleBg->Initialize(m_sceneManager->GetGame());
	//---------------------------------------------------
	// タイトルUIの初期化--------------------------------
	m_titleUi = GetTaskManager()->AddTask<TitleUi>(this);
	m_titleUi->Initialize(m_sceneManager->GetGame());
	//---------------------------------------------------
}


/// <summary>
/// タイトルシーンの後始末処理
/// </summary>
void TitleScene::Finalize()
{
	// ポインターを破棄------------------
	m_sceneManager->PtrDel(m_title);
	m_sceneManager->PtrDel(m_titleBg);
	m_sceneManager->PtrDel(m_titleUi);
	//-----------------------------------
}


/// <summary>
/// タイトルシーンの更新処理
/// </summary>
/// <param name="timer">時間情報</param>
void TitleScene::Update(DX::StepTimer const& timer)
{
	auto kb = System::InputManager::GetInstance().GetKeyState();
	float elapsedTime = float(timer.GetElapsedSeconds());

	// 更新処理--------------------------------------------------
	m_title->Update(elapsedTime);		// ゲームタイトルの更新
	m_titleBg->Update(elapsedTime);		// タイトル背景の更新
	m_titleUi->Update(elapsedTime);		// タイトルUIの更新
	// ----------------------------------------------------------

	if (kb.Space)
	{
		m_sceneManager->RequestToChangeScene(SCENE_PLAY);
	}
}


/// <summary>
/// タイトルシーンの描画処理
/// </summary>
void TitleScene::Render()
{
	// 描画処理-----------------------------------------
	m_titleBg->Render();		// タイトル背景の描画
	m_title->Render();			// ゲームタイトルの描画
	m_titleUi->Render();		// タイトルUIの描画
	//--------------------------------------------------
}

