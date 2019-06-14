#include "../Game.h"
#include "PlayBg.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// コンストラクタ
PlayBg::PlayBg()
{
}

// デストラクタ
PlayBg::~PlayBg()
{
}

// 初期化
void PlayBg::Initialize(Game* game)
{
	m_game = game;// Game.cppの情報の取得
}

// 更新
bool PlayBg::Update(float elapsedTime)
{
	return false;
}

// 描画
void PlayBg::Render()
{
}
