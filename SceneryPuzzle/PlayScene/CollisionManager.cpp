//--------------------------------------------------------------------------------------
// File: CollisionManager.cpp
//
// �Փ˔���N���X
//
// Date: 2018.11.4
// Author: Takeshi Yamaguthi
//--------------------------------------------------------------------------------------
#include "../pch.h"
#include "CollisionManager.h"
#include "../Livr/Object.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

CollisionManager::CollisionManager()
{
}

bool CollisionManager::Update(float elapsedTime)
{
	// ��������ŏՓ˔��肷��
	for (size_t j = 0; j < m_objects.size(); j++)
	{
		Object* a = m_objects[j];
		for (size_t i = j + 1; i < m_objects.size(); i++)
		{
			Object* b = m_objects[i];
			// ���Ƌ��̏Փ˔���
			Vector3 distance = a->GetPosition() - b->GetPosition();
			float r = a->GetRadius() + b->GetRadius();
			if (distance.LengthSquared() <= r * r)
			{
				// �Փ˂���
				a->OnHit(b);
				b->OnHit(a);
			}
		}
	}
	// �o�^���X�g���N���A
	m_objects.clear();

	return true;
}

void CollisionManager::AddObject(Object * object)
{
	// �Փ˔��胊�X�g�ɓo�^
	m_objects.push_back(object);
}
