#pragma once
#include "SerectBg.h"
#include "../TaskManager.h"
#include "../PlayScene/CollisionManager.h"
class Game;
class SerectStage;
class SerectGame : public Task
{
public:
	// 画面サイズ
	static const int SCREEN_W = 960;
	static const int SCREEN_H = 720;

	// ラウンド数
	static const int ROUND_MAX;

	// ゲームステート
	enum GAME_STATE
	{
		STATE_NONE,			// 最初
		STATE_START,		// 開始
		STATE_GAME,			// ゲーム中
		STATE_AGAIN,		// 死んだので再チャレンジ
		STATE_NEXT,			// 次のステージへ
	};

	// 描画順
	enum OT_PRIORITY
	{
		OT_TOP,			// 一番手前（２Ⅾ表示やエフェクトで使用） 
		OT_OBJECT,		// 床の上のオブジェクト
		OT_SHADOW,		// オブジェクトの影
		OT_STAGE,		// ステージ
		OT_FALL,		// 落下オブジェクト
		OT_BG,			// 背景
	};

	// 方向
	enum DIR
	{
		UP, LEFT, DOWN, RIGHT
	};
	// 方向に対応した角度
	static const float DIR_ANGLE[];

	// 重力
	static const float GRAVITY;

	// 落下速度
	static const float FALL_SPEED;

private:
	// キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker m_tracker;

	// ゲームオブジェクトへのポインタ
	Game* m_game;
	// ゲームの状態
	GAME_STATE m_gameState;


	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;

	// 背景
	SerectBg* m_bg;

	// ステージ
	SerectStage* m_stage;

	// 衝突判定用オブジェクト
	CollisionManager* m_collisionManager;

	// ラウンド数
	int m_round;

	// ヒットエフェクト用テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_hitEffectTexture;

	// ジャンプエフェクト用テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_jumpEffectTexture;

	// 煙エフェクト用テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_smokeEffectTexture;

	//----- エフェクト用 -----//

	// エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_batchEffect;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitiveBatch;

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// BGMハンドル
	int m_bgm;

public:
	// コンストラクタ
	SerectGame();

	// 初期化関数
	void Initialize(Game* game);

	// 更新関数
	bool Update(float elapsedTime) override;

	// 描画関数
	void Render() override;

	// ゲームオブジェクトへのポインタを取得する関数
	Game* GetGame() { return m_game; }

	// ビュー行列を取得する関数
	const DirectX::SimpleMath::Matrix& GetViewMatrix() { return m_view; }

	// 射影行列を取得する関数
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() { return m_projection; }

	// 衝突判定用オブジェクトに登録する関数
	void AddCollision(Object* object);

	// ステージタスク取得関数
	SerectStage* GetStage() { return m_stage; }

	// エフェクト用ベーシックエフェクトを取得する関数
	DirectX::BasicEffect* GetBatchEffect() { return m_batchEffect.get(); }

	// エフェクト用プリミティブバッチを取得する関数
	DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>* GetPrimitiveBatch() { return m_primitiveBatch.get(); }

	// エフェクト用入力レイアウトを取得する関数
	ID3D11InputLayout* GetInputLayout() { return m_inputLayout.Get(); }

	// ヒットエフェクト用テクスチャの取得関数
	ID3D11ShaderResourceView* GetHitEffectTexture() { return m_hitEffectTexture.Get(); }

	// ジャンプエフェクト用テクスチャの取得関数
	ID3D11ShaderResourceView* GetJumpEffectTexture() { return m_jumpEffectTexture.Get(); }

	// 煙エフェクト用テクスチャの取得関数
	ID3D11ShaderResourceView* GetSmokeEffectTexture() { return m_smokeEffectTexture.Get(); }


	// ゲームの初期化関数
	GAME_STATE InitializeGame(float elapsedTime);

	// ゲームをスタートさせる関数
	GAME_STATE StartGame(float elapsedTime);

	// ゲーム中の関数
	GAME_STATE GamePlay(float elapsedTime);

	// 次のステージへ
	GAME_STATE NextGame(float elapsedTime);

	private:
		// ステージデータのファイル名を取得する関数
		wchar_t* GetStageFilename(int round);

		// エフェクト用リソースの初期化
		void InitializeEffectResources(Game* game);
};