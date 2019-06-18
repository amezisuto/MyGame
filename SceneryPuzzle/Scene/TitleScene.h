#pragma once

#include "SceneBase.h"
#include "GameScene.h"
#include "../TitleScene/Title.h"
#include "../TitleScene/TitleBg.h"
#include "../TitleScene/TitleUi.h"
#include "../TaskManager.h"

class TitleScene : public SceneBase,public Task
{
	// <コンストラクタ>
public:
	TitleScene(SceneManager* sceneManager);


	// <デストラクタ>
public:
	virtual ~TitleScene();


	// <操作>
public:
	virtual void Initialize() override;
	virtual void Update(DX::StepTimer const& timer) override;
	virtual void Render() override;
	virtual void Finalize() override;

private:

	Title* m_title;		// TitleClassのポインター
	TitleBg* m_titleBg; // TitleBgClassのポインター
	TitleUi* m_titleUi; // TitleUiClassのポインター

	TaskManager m_titleTM;

};