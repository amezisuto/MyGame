/// <summary>
/// SceneManager.h
/// </summary>



// 多重インクルードの防止 =====================================================
#pragma once



// ヘッダファイルのインクルード ===============================================
#include "..\StepTimer.h"



// クラスの宣言 ===============================================================
class SceneBase;
class Game;



/// 定数の定義 ================================================================
/// <summary>
/// シーンID
/// </summary>
enum SceneId
{
	SCENE_LOGO,
	SCENE_TITLE,
	SCENE_STAGE,
	SCENE_PLAY,

	NUM_SCENES
};



/// クラスの定義 ==============================================================
/// <summary>
/// シーンマネージャークラス
/// </summary>
class SceneManager
{
	// データメンバの宣言 -------------------------------------------------
private:
	SceneBase* m_scenes[NUM_SCENES];    // 登録されているシーンのリスト

	SceneBase* m_activeScene;           // 活動中のシーン
	SceneBase* m_requestedScene;        // 要求されたシーン

protected:
	Game* m_game;

										// メンバ関数の宣言 ---------------------------------------------------
										// <コンストラクタ>
public:
	SceneManager(SceneId startSceneId);


	// <デストラクタ>
public:
	~SceneManager();


	// <操作>
public:
	void UpdateActiveScene(DX::StepTimer const& timer);
	void RenderActiveScene();
	bool RequestToChangeScene(SceneId sceneId);

public:
	// ポインター終了処理関数
	template<typename T> static void PtrDel(T ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
private:
	void ChangeScene();

public:
	Game* GetGame() { return m_game; };

	// ゲームオブジェクトを設定する関数
	void SetGame(Game* game) { m_game = game; };
};
