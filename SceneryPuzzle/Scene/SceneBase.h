/// <summary>
/// SceneBase.h
/// </summary>



// 多重インクルードの防止 =====================================================
#pragma once



// ヘッダファイルのインクルード ===============================================
#include "..\StepTimer.h"



// クラスの宣言 ===============================================================
class SceneManager;



// クラスの定義 ===============================================================
/// <summary>
/// シーンの基底クラス
/// </summary>
class SceneBase
{
	// データメンバの宣言 -------------------------------------------------
protected:
	SceneManager* m_sceneManager;


	// メンバ関数の宣言 ---------------------------------------------------
	// <コンストラクタ>
public:
	SceneBase();
	SceneBase(SceneManager* sceneManager);


	// <デストラクタ>
public:
	virtual ~SceneBase();


	// <操作>
public:
	virtual void Initialize() = 0;
	virtual void Update(DX::StepTimer const& timer) = 0;
	virtual void Render() = 0;
	virtual void Finalize() = 0;
};
