#pragma once

#include "SceneBase.h"
#include "GameScene.h"


class Game;

class TitleScene : public SceneBase
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



public:
	


};