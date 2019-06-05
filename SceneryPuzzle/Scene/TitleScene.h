#pragma once

#include "SceneBase.h"
#include "GameScene.h"


class Game;

class TitleScene : public SceneBase
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



public:
	


};