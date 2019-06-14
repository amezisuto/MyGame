#include "../Game.h"
#include "Title.h"
#include "../Scene/GameLi/GameManeger.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// コンストラクタ
Title::Title()
{
}

// デストラクタ
Title::~Title()
{
}

// 初期化
void Title::Initialize(Game* game)
{
	m_game = game;		// Game.cppの情報の取得
	// テクスチャの読み込み
	CreateWICTextureFromFile(m_game->GetDevice(), L"Resources\\Textures\\title.png", nullptr, m_titleTexture.GetAddressOf());
}

// 更新
bool Title::Update(float elapsedTime)
{
	return false;
}

// 描画
void Title::Render()
{
	// タイトルの描画
	RECT destRect = { 0, 0, 1280, 720 };
	m_game->GetSpriteBatch()->Begin(SpriteSortMode_Deferred, m_game->GetStates()->NonPremultiplied());
	m_game->GetSpriteBatch()->Draw(m_titleTexture.Get(), destRect);
	m_game->GetSpriteBatch()->End();
}
