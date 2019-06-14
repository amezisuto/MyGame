#include "../Game.h"
#include "TitleBg.h"
#include "../Scene/GameLi/GameManeger.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

// コンストラクタ
TitleBg::TitleBg():m_scroll(0.0f)
{
}

// デストラクタ
TitleBg::~TitleBg()
{
}

// 初期化
void TitleBg::Initialize(Game* game)
{
	m_game = game;	// Game.cppの情報の取得
	// テクスチャの読み込み
	CreateWICTextureFromFile(m_game->GetDevice(), L"Resources\\Textures\\title_tile2.png", nullptr, m_tileTexture.GetAddressOf());
}

// 更新
bool TitleBg::Update(float elapsedTime)
{
	// スクロール
	//m_scroll += 0.5f;
	if (m_scroll >= 100.0f) m_scroll -= 100.0f;
	return true;
}

// 描画
void TitleBg::Render()
{
	m_game->GetSpriteBatch()->Begin(SpriteSortMode_Deferred, m_game->GetStates()->NonPremultiplied());
	// 後ろのタイルの描画
	for (int j = 0; j < 9; j++)
	{
		for (int i = 0; i < 14; i++)
		{
			m_game->GetSpriteBatch()->Draw(m_tileTexture.Get(), Vector2(i * 100.0f - m_scroll, (j - 1) * 100.0f + m_scroll));
		}
	}
	m_game->GetSpriteBatch()->End();
}
