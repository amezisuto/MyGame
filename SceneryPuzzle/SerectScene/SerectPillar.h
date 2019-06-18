//---------------------------------------
// 柱クラス
//---------------------------------------
#pragma once

#include "../Livr/Object.h"
class SerectGame;

class SerectPillar :public Object
{
public:
	// パーツの種類
	enum Kind
	{
		NONE,		// 未指定
		BALL,	
		TRY,		
		NONE1,
		NONE2,
		NONE3,
		PILLAR,

		KIND_NUM
	};

	// 床との判定用の幅と高さ
	static const float WIDTH;
	static const float HEIGHT;

private:

	// パーツの種類
	Kind m_kind;

public:
	SerectPillar();
	void Initialize(SerectGame* serectGame, Kind kind, int x, int y, DirectX::Model * model);

	bool Update(float elapsedTime)override;

	// オブジェクトＩＤを取得する関数
	Object::OBJECT_ID GetID() override;

	// リセット関数
	void Reset();


private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
};
