//--------------------------------------------------------------------------------------
// File: CollisionManager.h
//
// �Փ˔���N���X
//
// Date: 2018.11.4
// Author: Takeshi Yamaguthi
//--------------------------------------------------------------------------------------
#pragma once

#include "../TaskManager.h"

class Object;

class CollisionManager : public Task
{
private:
	// �o�^���X�g
	std::vector<Object*> m_objects;

public:
	// �R���X�g���N�^
	CollisionManager();

	// �X�V�֐�
	bool Update(float elapsedTime) override;

	// �o�^�֐�
	void AddObject(Object* object);
};
