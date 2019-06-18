//--------------------------------------------------------------------------------------
// カメラクラス
//--------------------------------------------------------------------------------------
#include "../pch.h"
#include "PlayCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float PlayCamera::DEFAULT_CAMERA_DISTANCE = 5.0f;

//--------------------------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------------------------
PlayCamera::PlayCamera(int windowWidth, int windowHeight)
	: m_yAngle(0.0f), m_yTmp(0.0f), m_xAngle(0.0f), m_xTmp(0.0f), m_x(0), m_y(0), m_scrollWheelValue(0),m_chengeFlag(false)
	,m_lipeFloat(1.0f), m_chengeEye(0.0f, 15.5f, 15.0f), m_chengeAngleFlag(false), m_chengeFnishFlag(false)
{
	SetWindowSize(windowWidth, windowHeight);
}

//--------------------------------------------------------------------------------------
// 更新
//--------------------------------------------------------------------------------------
void PlayCamera::Update()
{

	// ビュー行列を算出する
	Matrix rotX = Matrix::CreateRotationX(m_xTmp);
	Matrix rt;
	Vector3 eye;
	Vector3 starteye;

	Vector3 target(5.0f, 0.0f, 5.5f);
	m_target = target;
	if (!m_chengeFlag)
	{
		starteye = Vector3(5.0f, 20.5f, 15.0f);
		eye = Vector3::Lerp(m_chengeEye, starteye, m_lipeFloat);	// 補間移動
		if (m_chengeFnishFlag)m_chengeFnishFlag = false;
		if (m_lipeFloat < 1.0f)
		{
			m_lipeFloat = m_lipeFloat + 0.05f;
		}
		else
		{
			// 回転
			if (!m_chengeAngleFlag)
			{
				m_yAngle = (m_yAngle + 0.01f);
				if (m_yAngle >= 360.0f)
					m_yAngle = 0.0f;

				Matrix rotY = Matrix::CreateRotationY(m_yAngle);
				rt = rotY;
				eye = starteye;
				eye = Vector3::Transform(eye, rt.Invert());
			}
		}
		m_eye = eye;

		m_view = Matrix::CreateLookAt(eye, target, Vector3::Up);
	}
	else
	{
		m_nexteye = Vector3(5.0f, 20.5f, 6.5f);
	
		m_chengeEye = Vector3::Lerp(m_eye, m_nexteye, m_lipeFloat);		// 補間移動
		if (m_lipeFloat < 1.0f)
		{
			m_lipeFloat = m_lipeFloat + 0.02f;
		}
		else
		{
			m_lipeFloat = 1.0f;
			if (!m_chengeFnishFlag)m_chengeFnishFlag = true;
		}
		m_eye = m_chengeEye;

		m_view = Matrix::CreateLookAt(m_chengeEye, target, Vector3::Up);
	}
}

//--------------------------------------------------------------------------------------
// 行列の生成
//--------------------------------------------------------------------------------------
void PlayCamera::Motion(int x, int y)
{
	// マウスポインタの位置のドラッグ開始位置からの変位 (相対値)
	float dx = (x - m_x) * m_sx;
	float dy = (y - m_y) * m_sy;

	if (dx != 0.0f || dy != 0.0f)
	{
		// Ｙ軸の回転
		float yAngle = dx * XM_PI;
		// Ｘ軸の回転
		float xAngle = dy * XM_PI;

		m_xTmp = m_xAngle + xAngle;
		m_yTmp = m_yAngle + yAngle;
	}
}

DirectX::SimpleMath::Matrix PlayCamera::GetCameraMatrix()
{
	return m_view;
}

DirectX::SimpleMath::Vector3 PlayCamera::GetEyePosition()
{
	return m_eye;
}

DirectX::SimpleMath::Vector3 PlayCamera::GetTargetPosition()
{
	return m_target;
}

void PlayCamera::SetWindowSize(int windowWidth, int windowHeight)
{
	// 画面サイズに対する相対的なスケールに調整
	m_sx = 1.0f / float(windowWidth);
	m_sy = 1.0f / float(windowHeight);
}

void  PlayCamera::ChengeFlag()
{
	m_chengeFlag = !m_chengeFlag;
	m_lipeFloat = 0.0f;
	m_yAngle = 0.0f;
}
void PlayCamera::ChengeAngleFlag()
{
	m_chengeAngleFlag = !m_chengeAngleFlag;
}

void PlayCamera::CameraReset()
{
	m_lipeFloat = 0.0f;
	m_yAngle = 0.0f;
}
