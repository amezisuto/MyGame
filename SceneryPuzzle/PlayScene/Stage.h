//---------------------------------------
// �X�e�[�W�N���X
//---------------------------------------
#pragma once

#include <vector>
#include <stack>
#include "../TaskManager.h"
#include "Floor.h"
#include "Player.h"
#include "Pillar.h"
#include "Gimmick.h"
class Game;
class GameScene;

class Stage : public Task
{
public:
	// �I�u�W�F�N�g�h�c
	enum OBJECT_ID
	{
		NONE,		// �Ȃ�
		BALL,		// �{�[��
		TRY,		// ��
		NOTB,		// �i���֎~
		PLAYER,		// �v���C���[
		GALE,		// �S�[��
	};
	struct FloorPosion
	{
		DirectX::SimpleMath::Vector3 position;
		float wid;
		float hei;
	};

	// �X�e�[�W�̑傫��
	static const int STAGE_W = 11;
	static const int STAGE_H = 11;

	// �X�e�[�W�f�[�^�̍\����
	struct StageData
	{
		int stage[STAGE_H][STAGE_W];
		int object[STAGE_H][STAGE_W];
	};

private:
	//	�Q�[���̃|�C���^�[
	Game* m_game;
	//  �Q�[���V�[���̃|�C���^�[
	GameScene* m_gameScene;

	// ���^�X�N�ւ̃|�C���^
	Floor* m_floors[STAGE_H][STAGE_W];
	Floor* m_floorsRecode[STAGE_H][STAGE_W];;

	// �v���C���[�^�X�N�ւ̃|�C���^
	Player* m_player;

	// �S�[���^�X�N�ւ̃|�C���^
	std::vector<Object*> m_goal;

	// �^�X�N�ւ̃|�C���^
	std::vector<Gimmick*> m_ball;

	std::vector<Gimmick*> m_try;

	std::vector<Gimmick*> m_not;

	std::vector<Object*> m_pillar;

	//----- ���f���ւ̃|�C���^ -----//

	// ���̃��f��
	std::unique_ptr<DirectX::Model> m_floorModels[Floor::STATE_NUM];

	// �I�u�W�F�N�g�̉e�̃��f��
	std::unique_ptr<DirectX::Model> m_shadowModel;

	// �v���C���[�̃��f��
	std::unique_ptr<DirectX::Model> m_playerModels;

	// �{�[���̃��f��
	std::unique_ptr<DirectX::Model> m_ballModel;

	// �����̃��f��
	std::unique_ptr<DirectX::Model> m_tryModel;

	// �i���֎~�̃��f��
	std::unique_ptr<DirectX::Model> m_notModel;

	// �S�[���̃��f��
	std::unique_ptr<DirectX::Model> m_goalModel;

	// �X�e�[�W�f�[�^
	StageData m_stageData;

	// �t���A�̕ۑ��p�f�[�^
	FloorPosion m_floorPos;

	std::stack<Floor*> m_floorStack;
	int m_floorX, m_floorY;

public:
	// �R���X�g���N�^
	Stage();

	// �������֐�
	void Initialize(GameScene* gameScene);

	// �Q�[���I�u�W�F�N�g�̃|�C���^���擾����֐�
	Game* GetGame();

	// ���^�X�N�擾�֐�
	Floor* GetFloor(int x, int y);

	// �X�e�[�W�f�[�^�̓ǂݍ��݊֐�
	bool LoadStageData(wchar_t* fname);

	// �X�e�[�W�f�[�^�������֐�
	void SetStageData();

	// �X�e�[�W�f�[�^�̃��Z�b�g�֐�
	void ResetStageData();

	// �v���C���[�̎擾�֐�
	Player* GetPlayer() { return m_player; }

	// �S�[���̎擾�֐�
	//const std::vector<Object*>& GetEnemyList() { return m_goal; }

	bool GameEndCheck();

	bool CheckFloorAnd(DirectX::SimpleMath::Vector3 pos, float w, float h);

private:
	// �ʉ߃`�F�b�N�֐�
	bool CheckFloor(DirectX::SimpleMath::Vector3 pos, float w, float h);
	bool CheckBackFloor(DirectX::SimpleMath::Vector3 pos, float w, float h);

	// ����ʉ߂����֐�
	void LodeFloor(DirectX::SimpleMath::Vector3 pos, float w, float h);
	bool CheckLodeFloor(DirectX::SimpleMath::Vector3 pos, float w, float h);

	// �ʉ߂�������߂�֐�
	void LodeBackFloor(DirectX::SimpleMath::Vector3 pos, float w, float h);
	bool CheckLodeBackFloor(DirectX::SimpleMath::Vector3 pos, float w, float h);

	// �o�^����Ă���^�X�N�i�v���C���[�A�G�A�p�[�c�j��S�č폜����֐�
	void DeleteAllObject();

	// �ʒu����X�e�[�W�̃}�b�v�`�b�v�̈ʒu�ɕϊ�����֐�
	void ConvertPosToMapChip(float x, float z, int* floor_x, int* floor_y);

	void SetFloorPos(DirectX::SimpleMath::Vector3 pos, float w, float h);

	void PlayerLodeFllor(DirectX::SimpleMath::Vector3 pos, float w, float h);
};
