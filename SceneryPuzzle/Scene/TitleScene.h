#pragma once

#include "SceneBase.h"
#include "GameScene.h"
#include "../TitleScene/Title.h"
#include "../TitleScene/TitleBg.h"
#include "../TitleScene/TitleUi.h"
#include "../TaskManager.h"

class TitleScene : public SceneBase,public Task
{
	// <�R���X�g���N�^>
public:
	TitleScene(SceneManager* sceneManager);


	// <�f�X�g���N�^>
public:
	virtual ~TitleScene();


	// <����>
public:
	virtual void Initialize() override;
	virtual void Update(DX::StepTimer const& timer) override;
	virtual void Render() override;
	virtual void Finalize() override;

private:

	Title* m_title;		// TitleClass�̃|�C���^�[
	TitleBg* m_titleBg; // TitleBgClass�̃|�C���^�[
	TitleUi* m_titleUi; // TitleUiClass�̃|�C���^�[

	TaskManager m_titleTM;

};