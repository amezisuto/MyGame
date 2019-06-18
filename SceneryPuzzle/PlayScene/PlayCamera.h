//--------------------------------------------------------------------------------------
// デバッグ用カメラクラス
//--------------------------------------------------------------------------------------
#pragma once

// カメラクラス
class PlayCamera
{
	// カメラの距離
	static const float DEFAULT_CAMERA_DISTANCE;

	// 横回転
	float m_yAngle, m_yTmp;

	// 縦回転
	float m_xAngle, m_xTmp;

	// ドラッグされた座標
	int m_x, m_y;

	float m_sx, m_sy;

	// 生成されたビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// スクロールフォイール値
	int m_scrollWheelValue;

	// 視点
	DirectX::SimpleMath::Vector3 m_eye;

	// 注視点
	DirectX::SimpleMath::Vector3 m_target;

	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker m_tracker;

	// カメラの動きのフラグ
	bool m_chengeFlag;
	// カメラの回転フラグ
	bool m_chengeAngleFlag;
	// カメラの移動が完了したかのフラグ
	bool m_chengeFnishFlag;

	// 補間移動用の変数
	float m_lipeFloat;
	// 次の補間移動先
	DirectX::SimpleMath::Vector3 m_nexteye;
	// 現在の位置
	DirectX::SimpleMath::Vector3 m_chengeEye;



private:

	void Motion(int x, int y);

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="windowWidth">ウインドウサイズ（幅）</param>
	/// <param name="windowHeight">ウインドウサイズ（高さ）</param>
	PlayCamera(int windowWidth, int windowHeight);

	/// <summary>
	/// カメラの更新
	/// </summary>
	/// <param name="mouse">マウスオブジェクトへのポインタ</param>
	void Update();

	/// <summary>
	/// カメラのビュー行列の取得関数
	/// </summary>
	/// <returns>ビュー行列</returns>
	DirectX::SimpleMath::Matrix GetCameraMatrix();

	/// <summary>
	/// カメラの位置の取得関数
	/// </summary>
	/// <returns>視点の位置</returns>
	DirectX::SimpleMath::Vector3 GetEyePosition();

	/// <summary>
	/// カメラの注視点の取得関数
	/// </summary>
	/// <returns>注視点の位置</returns>
	DirectX::SimpleMath::Vector3 GetTargetPosition();

	/// <summary>
	/// 画面サイズの設定関数
	/// </summary>
	/// <param name="windowWidth">ウインドウサイズ（幅）</param>
	/// <param name="windowHeight">ウインドウサイズ（高さ）</param>
	void SetWindowSize(int windowWidth, int windowHeight);

	// カメラの回転フラグOnOff関数
	void ChengeFlag();
	void CameraReset();
	void ChengeFlagOn() { m_chengeFlag = true; }
	void ChengeFlagOff() { m_chengeFlag = false; }
	///////////////////////////////////////////////

	// カメラの動きのフラグOnOff関数
	void ChengeAngleFlag();
	void ChengeAngleOn() { m_chengeAngleFlag = true; }
	void ChengeAngleOff() { m_chengeAngleFlag = false; }
	///////////////////////////////////////////////

	// カメラの移動が完了フラグ取得関数
	bool GetChengeFinishFlag() { return m_chengeFnishFlag; }
	


};
