#pragma once

#include "SceneBase.h"

#include "../Game.h"




class GameScene : public SceneBase
{
	// <�R���X�g���N�^>
public:
	GameScene(SceneManager* sceneManager);	


	// <�f�X�g���N�^>
public:
	virtual ~GameScene();


	// <����>
public:
	virtual void Initialize() override;
	virtual void Update(DX::StepTimer const& timer) override;
	virtual void Render() override;
	virtual void Finalize() override;

	



};