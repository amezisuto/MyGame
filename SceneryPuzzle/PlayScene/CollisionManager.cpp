//--------------------------------------------------------------------------------------
// File: CollisionManager.cpp
//
// 衝突判定クラス
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
	// 総当たりで衝突判定する
	for (size_t j = 0; j < m_objects.size(); j++)
	{
		Object* a = m_objects[j];
		for (size_t i = j + 1; i < m_objects.size(); i++)
		{
			Object* b = m_objects[i];
			// 球と球の衝突判定
			Vector3 distance = a->GetPosition() - b->GetPosition();
			float r = a->GetRadius() + b->GetRadius();
			if (distance.LengthSquared() <= r * r)
			{
				// 衝突した
				a->OnHit(b);
				b->OnHit(a);
			}
		}
	}
	// 登録リストをクリア
	m_objects.clear();

	return true;
}

void CollisionManager::AddObject(Object * object)
{
	// 衝突判定リストに登録
	m_objects.push_back(object);
}
