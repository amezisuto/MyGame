#include "../Game.h"
#include "TitleUi.h"
#include "../Scene/GameLi/GameManeger.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

// コンストラクタ
TitleUi::TitleUi():m_displayFlag(false), m_interval(0.0f), m_counter(0.0f)
{
}

// デストラクタ
TitleUi::~TitleUi()
{
}

// 初期化
void TitleUi::Initialize(Game* game)
{
	m_interval = 0.5f;
	m_game = game;	// Game.cppの情報の取得
	// テクスチャの読み込み
	CreateWICTextureFromFile(m_game->GetDevice(), L"Resources\\Textures\\push_space.png", nullptr, m_pushSpaceTexture.GetAddressOf());
}

// 更新
bool TitleUi::Update(float elapsedTime)
{
	// 点滅
	m_counter += elapsedTime;
	if (m_counter >= m_interval)
	{
		m_counter = 0.0f;
		if (m_displayFlag)
		{
			m_displayFlag = false;
		}
		else
		{
			m_displayFlag = true;
		}
	}
	return true;
}

// 描画
void TitleUi::Render()
{
	m_game->GetSpriteBatch()->Begin(SpriteSortMode_Deferred, m_game->GetStates()->NonPremultiplied());
	// PUSH STARTの描画
	if (m_displayFlag)
	{
		m_game->GetSpriteBatch()->Draw(m_pushSpaceTexture.Get(), Vector2(430, 570));
	}
	m_game->GetSpriteBatch()->End();
}
