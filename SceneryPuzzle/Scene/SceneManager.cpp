/// <summary>
/// SceneManager.cpp
/// </summary>



// ヘッダファイルのインクルード ===============================================
#include "SceneManager.h"
#include "SceneBase.h"
#include "../Game.h"
//#include "LogoScene.h"
#include "SerectScene.h"
#include "GameScene.h"
#include "TitleScene.h"

// usingディレクティブ ========================================================
//using namespace MyLibrary;

// メンバ関数の定義 ===========================================================
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="startSceneId">開始シーンのID</param>
SceneManager::SceneManager(SceneId startSceneId)
	: m_activeScene(nullptr)
	, m_requestedScene(nullptr)
	, m_game(nullptr)
{
	// シーンリストの初期化
	for (int i = 0; i < NUM_SCENES; i++)
	{
		m_scenes[i] = nullptr;
	}

	// シーンオブジェクトをリストに登録
	//m_scenes[SCENE_LOGO] = new LogoScene(this);
	m_scenes[SCENE_TITLE] = new TitleScene(this);
	m_scenes[SCENE_STAGE] = new SerectScene(this);
	m_scenes[SCENE_PLAY] = new GameScene(this);
	// 開始シーンの設定
	RequestToChangeScene(startSceneId);
}


/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
	m_activeScene = nullptr;
	m_requestedScene = nullptr;

	for (int i = 0; i < NUM_SCENES; i++)
	{
		delete m_scenes[i];
		m_scenes[i] = nullptr;
	}
}


/// <summary>
/// 活動中のシーンの更新処理
/// </summary>
/// <param name="timer">時間情報</param>
void SceneManager::UpdateActiveScene(DX::StepTimer const& timer)
{
	if (m_requestedScene != nullptr)
	{
		ChangeScene();
	}

	if (m_activeScene != nullptr)
	{
		m_activeScene->Update(timer);
	}
}


/// <summary>
/// 活動中のシーンの描画処理
/// </summary>
void SceneManager::RenderActiveScene()
{
	if (m_activeScene != nullptr)
	{
		m_activeScene->Render();
	}
}


/// <summary>
/// シーンの変更を要求
/// </summary>
/// <param name="sceneId">変更を要求するシーンのID</param>
/// <returns>要求が通った場合 true, 通らない場合 false</returns>
bool SceneManager::RequestToChangeScene(SceneId sceneId)
{
	if (sceneId >= 0 && sceneId < NUM_SCENES)
	{
		m_requestedScene = m_scenes[sceneId];
		return true;
	}
	else
	{
		m_requestedScene = nullptr;
		return false;
	}
}


/// <summary>
/// 活動シーンの変更
/// </summary>
void SceneManager::ChangeScene()
{
	// 活動中のシーンを終了させる
	if (m_activeScene != nullptr)
	{
		m_activeScene->Finalize();
	}


	// 要求されたシーンを活動中にする
	m_activeScene = m_requestedScene;
	m_requestedScene = nullptr;


	// 新たに活動中になったシーンを初期化する
	if (m_activeScene != nullptr)
	{
		m_activeScene->Initialize();
	}
}
