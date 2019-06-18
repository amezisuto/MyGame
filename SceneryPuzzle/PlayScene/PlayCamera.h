//--------------------------------------------------------------------------------------
// �f�o�b�O�p�J�����N���X
//--------------------------------------------------------------------------------------
#pragma once

// �J�����N���X
class PlayCamera
{
	// �J�����̋���
	static const float DEFAULT_CAMERA_DISTANCE;

	// ����]
	float m_yAngle, m_yTmp;

	// �c��]
	float m_xAngle, m_xTmp;

	// �h���b�O���ꂽ���W
	int m_x, m_y;

	float m_sx, m_sy;

	// �������ꂽ�r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �X�N���[���t�H�C�[���l
	int m_scrollWheelValue;

	// ���_
	DirectX::SimpleMath::Vector3 m_eye;

	// �����_
	DirectX::SimpleMath::Vector3 m_target;

	// �}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker m_tracker;

	// �J�����̓����̃t���O
	bool m_chengeFlag;
	// �J�����̉�]�t���O
	bool m_chengeAngleFlag;
	// �J�����̈ړ��������������̃t���O
	bool m_chengeFnishFlag;

	// ��Ԉړ��p�̕ϐ�
	float m_lipeFloat;
	// ���̕�Ԉړ���
	DirectX::SimpleMath::Vector3 m_nexteye;
	// ���݂̈ʒu
	DirectX::SimpleMath::Vector3 m_chengeEye;



private:

	void Motion(int x, int y);

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="windowWidth">�E�C���h�E�T�C�Y�i���j</param>
	/// <param name="windowHeight">�E�C���h�E�T�C�Y�i�����j</param>
	PlayCamera(int windowWidth, int windowHeight);

	/// <summary>
	/// �J�����̍X�V
	/// </summary>
	/// <param name="mouse">�}�E�X�I�u�W�F�N�g�ւ̃|�C���^</param>
	void Update();

	/// <summary>
	/// �J�����̃r���[�s��̎擾�֐�
	/// </summary>
	/// <returns>�r���[�s��</returns>
	DirectX::SimpleMath::Matrix GetCameraMatrix();

	/// <summary>
	/// �J�����̈ʒu�̎擾�֐�
	/// </summary>
	/// <returns>���_�̈ʒu</returns>
	DirectX::SimpleMath::Vector3 GetEyePosition();

	/// <summary>
	/// �J�����̒����_�̎擾�֐�
	/// </summary>
	/// <returns>�����_�̈ʒu</returns>
	DirectX::SimpleMath::Vector3 GetTargetPosition();

	/// <summary>
	/// ��ʃT�C�Y�̐ݒ�֐�
	/// </summary>
	/// <param name="windowWidth">�E�C���h�E�T�C�Y�i���j</param>
	/// <param name="windowHeight">�E�C���h�E�T�C�Y�i�����j</param>
	void SetWindowSize(int windowWidth, int windowHeight);

	// �J�����̉�]�t���OOnOff�֐�
	void ChengeFlag();
	void CameraReset();
	void ChengeFlagOn() { m_chengeFlag = true; }
	void ChengeFlagOff() { m_chengeFlag = false; }
	///////////////////////////////////////////////

	// �J�����̓����̃t���OOnOff�֐�
	void ChengeAngleFlag();
	void ChengeAngleOn() { m_chengeAngleFlag = true; }
	void ChengeAngleOff() { m_chengeAngleFlag = false; }
	///////////////////////////////////////////////

	// �J�����̈ړ��������t���O�擾�֐�
	bool GetChengeFinishFlag() { return m_chengeFnishFlag; }
	


};
