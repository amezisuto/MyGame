//--------------------------------------------------------------------------------------
// File: TaskManager.h
//
// タスクを管理するクラス
//
// Date: 2015.3.8
// 
//--------------------------------------------------------------------------------------
#pragma once

#include <Windows.h>
#include <memory>
#include <list>
#include <set>

class TaskManager;
class Task;

typedef std::unique_ptr<Task> TASK;

//////////////////////////////////////////////////////////////////////////
//																		//
//	タスク連結情報管理クラス											//
//																		//
//////////////////////////////////////////////////////////////////////////
class TaskConnectInfo
{
	friend class TaskManager;

private:
	// タスク管理オブジェクトへのポインタ
	TaskManager* m_taskManager;

	// 親タスクへのポインタ
	Task* m_parent;

	// 子供タスクのリスト
	std::list<TASK> m_child;

	void SetTaskManager(TaskManager* p) { m_taskManager = p; }
	void SetParent(Task* p) { m_parent = p; }
	void AddChild(Task* p) { m_child.push_back(TASK(p)); }
	std::list<TASK>& GetChildList(){ return m_child; }

public:
	TaskManager* GetTaskManager() const { return m_taskManager; }
	Task* GetParent() const { return m_parent; }
};

//////////////////////////////////////////////////////////////////////////
//																		//
//	タスクの基底クラス													//
//																		//
//////////////////////////////////////////////////////////////////////////
class Task
{
	friend class TaskManager;

private:
	// 描画順序管理用(小さいほど手前に描画される）
	int m_ot;

	// タスク連結情報
	TaskConnectInfo m_connect;

public:
	Task() : m_ot(0) {}
	virtual ~Task() {}

	//////////////////////////////////////////
	//										//
	//	オーバーライドして使う関数			//
	//										//
	//////////////////////////////////////////
	virtual bool Update(float elapsedTime) { return true; }
	virtual void Render() {}

protected:
	// タスクマネージャーの取得関数
	TaskManager* GetTaskManager() const { return m_connect.GetTaskManager(); }

	// 親タスクの取得関数
	Task* GetParent() const { return m_connect.GetParent(); }

	// 描画順設定関数（otの値が0が一番手前）
	void SetOt(int ot) { this->m_ot = ot; }

	// 描画順の取得関数
	int GetOt() { return m_ot; }
};

//////////////////////////////////////////////////////////////////////////
//																		//
//	タスク管理クラス													//
//																		//
//////////////////////////////////////////////////////////////////////////
class TaskManager
{

private:
#pragma region
	// 描画順序管理テーブルへの登録用比較関数（otの値が大きい物が先頭へ）
	struct greater_ot : std::binary_function<Task*, Task*, bool>
	{
		bool operator()(Task* a, Task* b) const
		{
			return a->GetOt() > b->GetOt();
		}
	};
	// 描画順序管理テーブルの型
	typedef std::multiset<Task*, greater_ot> OT;

	// 描画順序管理テーブル
	OT m_ot;

	// ルートタスク
	Task m_rootTask;

	// タスクの削除関数
	void DeleteTask(Task* task);

	// 子供タスクの更新関数を実行する関数
	void ChildTaskUpdate(Task* task, float elapsedTime);
#pragma endregion

public:
	// コンストラクタ
	TaskManager() {}
	virtual ~TaskManager() {}

	// 更新関数
	virtual void Update(float elapsedTime);

	// 描画関数
	virtual void Render();

	// タスクの生成関数
	template <class T> T* AddTask(Task* parent = nullptr);
};

#pragma region
// タスクの生成関数
template <class T>
T* TaskManager::AddTask(Task* parent)
{
	// 親の指定がなければ親はルートタスク
	if (parent == nullptr) parent = &m_rootTask;

	// タスクを生成する
	T* task = new T();

	// タスク管理オブジェクトを設定
	task->m_connect.SetTaskManager(this);

	// 親を設定
	task->m_connect.SetParent(parent);

	// 親の子供リストに追加
	parent->m_connect.AddChild(task);

	return task;
}
#pragma endregion

