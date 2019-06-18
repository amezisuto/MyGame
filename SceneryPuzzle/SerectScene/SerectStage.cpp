#include "../Game.h"
#include "SerectStage.h"
#include "SerectGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �R���X�g���N�^
SerectStage::SerectStage()
 : m_floors{ nullptr }, m_player(nullptr), m_stageData{ 0 }
{
}

// ������
void SerectStage::Initialize(SerectGame* serectGame)
{
	m_serectGame = serectGame;
	m_game = m_serectGame->GetGame();// Game.cpp�̏��̎擾

	// ���f���f�[�^�̓ǂݍ���
	EffectFactory fx(m_game->GetDevice());
	fx.SetDirectory(L"Resources\\Models");
	m_floorModels[SerectFloor::NORMAL] = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\floorPanel_00.cmo", fx);
	m_floorModels[SerectFloor::PILLER] = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\hasira.cmo", fx);
	m_floorModels[SerectFloor::LODE] = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\keiro.cmo", fx);
	m_playerModels = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\start.cmo", fx);
	m_ballModel = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\Key.cmo", fx);
	m_tryModel = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\try.cmo", fx);
	m_notModel = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\notB.cmo", fx);
	m_goalModel = Model::CreateFromCMO(m_game->GetDevice(), L"Resources\\Models\\Enemy_02.cmo", fx);

	
}
Game * SerectStage::GetGame()
{
	return m_game;
}

SerectFloor * SerectStage::GetFloor(int x, int y)
{
	if (x >= 0 && x < STAGE_W && y >= 0 && y < STAGE_H)
	{
		return m_floors[y][x];
	}
	return nullptr;
}

bool SerectStage::LoadStageData(wchar_t * fname)
{
	std::wstring str;

	// �t�@�C���̃I�[�v��
	std::wifstream ifs(fname);

	//----- �X�e�[�W�f�[�^ -----//

	// �w�b�_������
	std::wstring stageHeadName = L"STAGE";

	// �w�b�_�����܂ŃV�[�N
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str.compare(0, stageHeadName.size(), stageHeadName) == 0)
		{
			break;
		}
	}

	// �X�e�[�W�f�[�^�̓ǂݍ���
	for (int i = 0; i < STAGE_H; i++)
	{
		getline(ifs, str);
		std::wstring tmp;
		std::wistringstream stream(str);
		for (int j = 0; j < STAGE_W; j++)
		{
			std::getline(stream, tmp, L',');
			m_stageData.stage[i][j] = std::stoi(tmp) + 1;
		}
	}

	//----- �X�e�[�W��̃I�u�W�F�N�g�f�[�^ -----//

	// �w�b�_������
	std::wstring objectHeadName = L"OBJECT";

	// �t�@�C���|�C���^��擪�փV�[�N
	ifs.clear();
	ifs.seekg(0);

	// �w�b�_�����܂ŃV�[�N
	while (!ifs.eof())
	{
		getline(ifs, str);
		if (str.compare(0, objectHeadName.size(), objectHeadName) == 0)
		{
			break;
		}
	}

	// �I�u�W�F�N�g�f�[�^�̓ǂݍ���
	for (int i = 0; i < STAGE_H; i++)
	{
		getline(ifs, str);
		std::wstring tmp;
		std::wistringstream stream(str);
		for (int j = 0; j < STAGE_W; j++)
		{
			std::getline(stream, tmp, L',');
			m_stageData.object[i][j] = std::stoi(tmp);
		}
	}

	// �t�@�C���̃N���[�Y
	ifs.close();

	return true;
}

void SerectStage::SetStageData()
{
	// ���̃^�X�N����
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			m_floors[j][i] = GetTaskManager()->AddTask<SerectFloor>(this);
			m_floors[j][i]->Initialize(this, i, j);
			// �e��Ԃ̃��f����ݒ�
			m_floors[j][i]->SetModel(SerectFloor::NORMAL, m_floorModels[SerectFloor::NORMAL].get());
			m_floors[j][i]->SetModel(SerectFloor::PILLER, m_floorModels[SerectFloor::PILLER].get());
			m_floors[j][i]->SetModel(SerectFloor::LODE, m_floorModels[SerectFloor::LODE].get());
		}
	}

	// �������̏�Ԃɖ߂�
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			if (m_stageData.stage[i][j] == 1)
			{
				//m_floors[j][i]->Alive();
				m_floors[j][i]->SetState(static_cast<SerectFloor::State>(m_stageData.stage[j][i]));
			}
		}
	}

	// �S�ẴI�u�W�F�N�g�^�X�N�̍폜
	DeleteAllObject();


	//----- �e�^�X�N�̐��� -----//

	SerectGimmick* ball;
	SerectGimmick* tryB;
	SerectGimmick* notB;
	SerectPillar* pillar;
	SerectGimmick* goal;

	// �X�e�[�W��̃I�u�W�F�N�g��z�u����
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			if (m_stageData.stage[i][j] == 2)
			{
				pillar = GetTaskManager()->AddTask<SerectPillar>(this);
				pillar->Initialize(m_serectGame, SerectPillar::PILLAR, i, j, m_floorModels[SerectFloor::PILLER].get());
				m_pillar.push_back(pillar);
			}
			// �I�u�W�F�N�g�̎�ނɂ��^�X�N��������
			switch (m_stageData.object[j][i])
			{
			case OBJECT_ID::PLAYER:	// �v���C���[
				m_player = GetTaskManager()->AddTask<SerectPlayer>(this);
				m_player->Initialize(m_serectGame, i, j);
				m_player->SetModel(SerectPlayer::NORMAL, m_playerModels.get());
				m_floors[j][i]->SetState(SerectFloor::LODE);
				m_floorStack.push(m_floors[j][i]);
				m_floorX = i; m_floorY = j;

				// ���Ƃ̔���֐���o�^
				m_player->SetCheckFloorFunction([&](Object* object)
				{
					return CheckFloor(object->GetPosition(), object->GetWidth(), object->GetHeight());
				});
				// �ʉߎ��̊֐���o�^
				m_player->SetFloorMove([&](Object* object)
				{
					if (m_floors[m_floorY + m_player->GetNextPosY()][m_floorX + m_player->GetNextPosX()]->GetState() ==SerectFloor::NORMAL)
					{
						m_floors[m_floorY + m_player->GetNextPosY()][m_floorX + m_player->GetNextPosX()]->SetState(SerectFloor::LODE);
						m_player->SetNextFloorPos(m_floors[m_floorY + m_player->GetNextPosY()][m_floorX + m_player->GetNextPosX()]->GetPosion());
						m_floorStack.push(m_floors[m_floorY][m_floorX]);
						m_floorX = m_floorX + m_player->GetNextPosX();
						m_floorY = m_floorY + m_player->GetNextPosY();
						m_player->SetFloorCheck(true);

					}
					else if (m_floors[m_floorY + m_player->GetNextPosY()][m_floorX + m_player->GetNextPosX()] == m_floorStack.top())
					{
						m_floors[m_floorY][m_floorX]->SetState(SerectFloor::NORMAL);
						m_player->SetNextFloorPos(m_floorStack.top()->GetPosion());
						m_floorStack.pop();
						m_floorX = m_floorX + m_player->GetNextPosX();
						m_floorY = m_floorY + m_player->GetNextPosY();
					}
					m_player->SetNextPosX(0);
					m_player->SetNextPosY(0);
				});
				// �߂鎞�̊֐���o�^
				m_player->SetFloorBackMove([&](Object* object)
				{
					if (m_floors[m_floorY + m_player->GetNextPosY()][m_floorX + m_player->GetNextPosX()]->GetState() == SerectFloor::PILLER)
					{
						m_player->SetFloorCheck(false);
					}
				});
				//m_player->SetFloorCheckBack([&](Object* object)
				//{
				//	//LodeFloor(object->GetPosition(), object->GetWidth(), object->GetHeight());
				//	if (CheckFloorAnd(object->GetPosition(), object->GetWidth(), object->GetHeight()))
				//	{
				//		m_player->SetFloorCheck(false);
				//	}
				//		
				//});
				break;
			case OBJECT_ID::BALL:	// �{�[��
				ball = GetTaskManager()->AddTask<SerectGimmick>(this);
				ball->Initialize(m_serectGame, SerectGimmick::BALL, i, j, m_ballModel.get());
				// ���Ƃ̔���֐���o�^
				ball->SetCheckFloorFunction([&](Object* object)
				{
					return CheckFloor(object->GetPosition(), object->GetWidth(), object->GetHeight());
				});
				m_ball.push_back(ball);
				break;
			case OBJECT_ID::TRY:		// ����
				tryB = GetTaskManager()->AddTask<SerectGimmick>(this);
				tryB->Initialize(m_serectGame, SerectGimmick::TRY, i, j, m_tryModel.get());
				m_try.push_back(tryB);
				break;
			case OBJECT_ID::NOTB:	// �i���֎~��
				notB = GetTaskManager()->AddTask<SerectGimmick>(this);
				notB->Initialize(m_serectGame, SerectGimmick::NOT, i, j, m_notModel.get());
				m_not.push_back(notB);
				break;
			case OBJECT_ID::GALE:	// �S�[��
				goal = GetTaskManager()->AddTask<SerectGimmick>(this);
				goal->Initialize(m_serectGame, SerectGimmick::GOAL, i, j, m_goalModel.get());
				// ���Ƃ̔���֐���o�^
				goal->SetCheckFloorFunction([&](Object* object)
				{
					return CheckFloor(object->GetPosition(), object->GetWidth(), object->GetHeight());
				});
				m_goal.push_back(goal);
				break;
			}
		}
	}
}

void SerectStage::ResetStageData()
{
	// �������Z�b�g
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			if (m_floors[j][i])
			{
				m_floors[j][i]->Reset();
				m_floors[j][i]->Kill();
			}
			
		}
	}
	// �p�Y�������Z�b�g	
	for (SerectGimmick* p : m_ball)
	{
		p->Reset();
	}
	for (SerectGimmick* p : m_try)
	{
		p->Reset();
	}
	for (SerectGimmick* p : m_not)
	{
		p->Reset();
	}
	// �v���C���[�����Z�b�g
	if (m_player) m_player->Reset();

	// �S�[�������Z�b�g
	for (Object* p : m_goal)
	{
		p->Reset();
	}

	// �������Z�b�g
	for (Object* p : m_pillar)
	{
		p->Reset();
	}
}

bool SerectStage::CheckFloor(DirectX::SimpleMath::Vector3 pos, float w, float h)
{
	int x, y;
	const Vector2 corner[4] = { Vector2(-1.0f, -1.0f), Vector2(1.0f, -1.0f), Vector2(1.0f,  1.0f), Vector2(-1.0f,  1.0f) };

	// ���S����̋����ɂ��邽�ߕ��ƍ������Q�Ŋ���
	w /= 2.0f;
	h /= 2.0f;

	// �S�_�𒲂ׂ�
	int i = 0;
	for (; i < 4; i++)
	{
		// 3D��Ԃ̍��W���}�b�v�`�b�v�̈ʒu�ɕϊ�����
		ConvertPosToMapChip(pos.x + w * corner[i].x, pos.z + h * corner[i].y, &x, &y);
		SerectFloor* floor = this->GetFloor(x, y);
		if ((floor != nullptr)
			&& (floor->GetState() == SerectFloor::State::NORMAL || floor->GetState() ==SerectFloor::State::LODE))
		{
			break;
		}
	}
	if (i == 4) return false;
	return true;
}
bool SerectStage::CheckBackFloor(DirectX::SimpleMath::Vector3 pos, float w, float h)
{
	int x, y;
	const Vector2 corner[4] = { Vector2(-1.0f, -1.0f), Vector2(1.0f, -1.0f), Vector2(1.0f,  1.0f), Vector2(-1.0f,  1.0f) };

	// ���S����̋����ɂ��邽�ߕ��ƍ������Q�Ŋ���
	w /= 2.0f;
	h /= 2.0f;

	// �S�_�𒲂ׂ�
	int i = 0;
	for (; i < 4; i++)
	{
		// 3D��Ԃ̍��W���}�b�v�`�b�v�̈ʒu�ɕϊ�����
		ConvertPosToMapChip(pos.x + w * corner[i].x, pos.z + h * corner[i].y, &x, &y);
		SerectFloor* floor = this->GetFloor(x, y);
		if ((floor != nullptr)
			&& (floor->GetState() == SerectFloor::State::LODE))
		{
			break;
		}
	}
	if (i == 4) return false;
	return true;
}



void SerectStage::SetFloorPos(DirectX::SimpleMath::Vector3 pos, float w, float h)
{
	m_floorPos.position = pos;
	m_floorPos.wid = w;
	m_floorPos.hei = h;
}

void SerectStage::DeleteAllObject()
{
	// ����S�č폜����
	for (SerectGimmick* p : m_ball)
	{
		p->Kill();
	}
	m_ball.clear();

	// �v���C���[���폜����
	if (m_player)
	{
		m_player->Kill();
		m_player = nullptr;
	}

	// �S�[����S�č폜����
	for (Object* p : m_goal)
	{
		p->Kill();
	}
	m_goal.clear();

	// ����S�č폜����
	for (Object* p : m_pillar)
	{
		p->Kill();
	}
	m_pillar.clear();

	// ���̃M�~�b�N��S�č폜����
	for (SerectGimmick* p : m_try)
	{
		p->Kill();
	}
	m_try.clear();
	for (SerectGimmick* p : m_not)
	{
		p->Kill();
	}
	m_not.clear();

	for (int i = 0; i < m_floorStack.size(); i++)
	{
		if (m_floorStack.empty() == 1)
			m_floorStack.pop();
	}
}

void SerectStage::ConvertPosToMapChip(float x, float z, int* floor_x, int* floor_y)
{
	*floor_x = (int)floorf(x + 0.5f);
	*floor_y = (int)floorf(z + 0.5f);
}

// �S�[�������֐�
bool SerectStage::GameEndCheck()
{
	for (int j = 0; j < STAGE_H; j++)
	{
		for (int i = 0; i < STAGE_W; i++)
		{
			if (m_stageData.object[j][i] == 1)
			{
				if (m_floors[j][i]->GetState() == SerectFloor::NORMAL)
				{
					return false;
				}
			}
			if (m_stageData.object[j][i] == 2)
			{
				int a = 0;
				if (m_floors[j - 1][i]->GetState() != SerectFloor::NORMAL)a++;
				if (m_floors[j + 1][i]->GetState() != SerectFloor::NORMAL)a++;
				if (m_floors[j][i - 1]->GetState() != SerectFloor::NORMAL)a++;
				if (m_floors[j][i + 1]->GetState() != SerectFloor::NORMAL)a++;
				if (a > 1 || a == 0)
				{
					return false;
				}
			}
			if (m_stageData.object[j][i] == 3)
			{
				if (m_floors[j - 1][i]->GetState() != SerectFloor::NORMAL)
				{
					return false;
				}
				if (m_floors[j + 1][i]->GetState() != SerectFloor::NORMAL) {
					return false;
				}
				if (m_floors[j][i - 1]->GetState() != SerectFloor::NORMAL) {
					return false;
				}
				if (m_floors[j][i + 1]->GetState() != SerectFloor::NORMAL) {
					return false;
				}
			}
		}
	}

	return true;
}

