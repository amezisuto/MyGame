/// <summary>
/// SceneBase.cpp
/// </summary>



// ヘッダファイルのインクルード ===============================================
#include "SceneBase.h"

#include "SceneManager.h"



SceneBase::SceneBase()
{
}

// メンバ関数の定義 ===========================================================
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager">登録されているシーンマネージャー</param>
SceneBase::SceneBase(SceneManager* sceneManager)
	: m_sceneManager(sceneManager)
{

}


/// <summary>
/// デストラクタ
/// </summary>
SceneBase::~SceneBase()
{

}
