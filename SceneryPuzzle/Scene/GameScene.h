#pragma once

#include "SceneBase.h"

#include "../Game.h"




class GameScene : public SceneBase
{
	// <コンストラクタ>
public:
	GameScene(SceneManager* sceneManager);	


	// <デストラクタ>
public:
	virtual ~GameScene();


	// <操作>
public:
	virtual void Initialize() override;
	virtual void Update(DX::StepTimer const& timer) override;
	virtual void Render() override;
	virtual void Finalize() override;

	



};