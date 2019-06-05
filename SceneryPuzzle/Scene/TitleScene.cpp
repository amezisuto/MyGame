#include "../pch.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "../Game.h"


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

}


/// <summary>
/// タイトルシーンの後始末処理
/// </summary>
void TitleScene::Finalize()
{


}


/// <summary>
/// タイトルシーンの更新処理
/// </summary>
/// <param name="timer">時間情報</param>
void TitleScene::Update(DX::StepTimer const& timer)
{

}


/// <summary>
/// タイトルシーンの描画処理
/// </summary>
void TitleScene::Render()
{

}

