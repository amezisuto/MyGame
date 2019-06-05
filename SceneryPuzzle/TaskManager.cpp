//--------------------------------------------------------------------------------------
// File: TaskManager.cpp
//
// タスクを管理するクラス
//
// Date: 2015.3.8
// 
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "TaskManager.h"

using namespace std;

// 更新関数
void TaskManager::Update(float elapsedTime)
{
	// ルートタスクから子供タスクに向かって再起的に更新処理を実行する
	ChildTaskUpdate(&m_rootTask, elapsedTime);
}

// 描画関数
void TaskManager::Render()
{
	// 描画順序管理テーブルに従ってタスクの描画関数を呼び出す
	multiset<Task*>::iterator p = m_ot.begin();
	while (p != m_ot.end())
	{
		(*p)->Render();
		p++;
	}
	// 描画順序管理テーブルクリア
	m_ot.clear();
}

// タスクの削除（子供タスクも全て死ぬ）
void TaskManager::DeleteTask(Task* task)
{
	// 子供タスクを再帰で削除していく
	while (task->m_connect.GetChildList().empty() != true)
	{
		DeleteTask(task->m_connect.GetChildList().back().get());
		task->m_connect.GetChildList().pop_back();
	}
}

// 子供タスクの更新関数を再起呼び出しで実行する関数
void TaskManager::ChildTaskUpdate(Task* task, float elapsedTime)
{
	std::list<TASK>::iterator p = task->m_connect.GetChildList().begin();
	while (p != task->m_connect.GetChildList().end())
	{
		// Update関数の戻り値がfalseの場合はタスクを削除する
		if (!(*p)->Update(elapsedTime))
		{
			// タスクの削除
			DeleteTask((*p).get());
			// 子供タスクリストから削除
			p = task->m_connect.GetChildList().erase(p);
			continue;
		}
		// 描画順序管理テーブルに登録
		m_ot.insert((*p).get());
		// 子供のタスクの更新処理を実行する
		ChildTaskUpdate((*p).get(), elapsedTime);
		p++;
	}
}
