//--------------------------------------------------------------------------------------
// File: TaskManager.h
//
// �^�X�N���Ǘ�����N���X
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
//	�^�X�N�A�����Ǘ��N���X											//
//																		//
//////////////////////////////////////////////////////////////////////////
class TaskConnectInfo
{
	friend class TaskManager;

private:
	// �^�X�N�Ǘ��I�u�W�F�N�g�ւ̃|�C���^
	TaskManager* m_taskManager;

	// �e�^�X�N�ւ̃|�C���^
	Task* m_parent;

	// �q���^�X�N�̃��X�g
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
//	�^�X�N�̊��N���X													//
//																		//
//////////////////////////////////////////////////////////////////////////
class Task
{
	friend class TaskManager;

private:
	// �`�揇���Ǘ��p(�������قǎ�O�ɕ`�悳���j
	int m_ot;

	// �^�X�N�A�����
	TaskConnectInfo m_connect;

public:
	Task() : m_ot(0) {}
	virtual ~Task() {}

	//////////////////////////////////////////
	//										//
	//	�I�[�o�[���C�h���Ďg���֐�			//
	//										//
	//////////////////////////////////////////
	virtual bool Update(float elapsedTime) { return true; }
	virtual void Render() {}

protected:
	// �^�X�N�}�l�[�W���[�̎擾�֐�
	TaskManager* GetTaskManager() const { return m_connect.GetTaskManager(); }

	// �e�^�X�N�̎擾�֐�
	Task* GetParent() const { return m_connect.GetParent(); }

	// �`�揇�ݒ�֐��iot�̒l��0����Ԏ�O�j
	void SetOt(int ot) { this->m_ot = ot; }

	// �`�揇�̎擾�֐�
	int GetOt() { return m_ot; }
};

//////////////////////////////////////////////////////////////////////////
//																		//
//	�^�X�N�Ǘ��N���X													//
//																		//
//////////////////////////////////////////////////////////////////////////
class TaskManager
{

private:
#pragma region
	// �`�揇���Ǘ��e�[�u���ւ̓o�^�p��r�֐��iot�̒l���傫�������擪�ցj
	struct greater_ot : std::binary_function<Task*, Task*, bool>
	{
		bool operator()(Task* a, Task* b) const
		{
			return a->GetOt() > b->GetOt();
		}
	};
	// �`�揇���Ǘ��e�[�u���̌^
	typedef std::multiset<Task*, greater_ot> OT;

	// �`�揇���Ǘ��e�[�u��
	OT m_ot;

	// ���[�g�^�X�N
	Task m_rootTask;

	// �^�X�N�̍폜�֐�
	void DeleteTask(Task* task);

	// �q���^�X�N�̍X�V�֐������s����֐�
	void ChildTaskUpdate(Task* task, float elapsedTime);
#pragma endregion

public:
	// �R���X�g���N�^
	TaskManager() {}
	virtual ~TaskManager() {}

	// �X�V�֐�
	virtual void Update(float elapsedTime);

	// �`��֐�
	virtual void Render();

	// �^�X�N�̐����֐�
	template <class T> T* AddTask(Task* parent = nullptr);
};

#pragma region
// �^�X�N�̐����֐�
template <class T>
T* TaskManager::AddTask(Task* parent)
{
	// �e�̎w�肪�Ȃ���ΐe�̓��[�g�^�X�N
	if (parent == nullptr) parent = &m_rootTask;

	// �^�X�N�𐶐�����
	T* task = new T();

	// �^�X�N�Ǘ��I�u�W�F�N�g��ݒ�
	task->m_connect.SetTaskManager(this);

	// �e��ݒ�
	task->m_connect.SetParent(parent);

	// �e�̎q�����X�g�ɒǉ�
	parent->m_connect.AddChild(task);

	return task;
}
#pragma endregion

