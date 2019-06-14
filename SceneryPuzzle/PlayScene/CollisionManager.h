//--------------------------------------------------------------------------------------
// File: CollisionManager.h
//
// 衝突判定クラス
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
	// 登録リスト
	std::vector<Object*> m_objects;

public:
	// コンストラクタ
	CollisionManager();

	// 更新関数
	bool Update(float elapsedTime) override;

	// 登録関数
	void AddObject(Object* object);
};
