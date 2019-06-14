#include "../Game.h"
#include "PlayBg.h"
#include"PlayGame.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

PlayBg::PlayBg()
	: m_angle(0.0f)
{
	// �`�揇�̐ݒ�
	SetOt(PlayGame::OT_BG);
}

void PlayBg::Initialize(PlayGame* playGame)
{
	m_playGame = playGame;
	Game* game = m_playGame->GetGame();

	// ���f���f�[�^�̓ǂݍ���
	EffectFactory fx(game->GetDevice());
	fx.SetDirectory(L"Resources\\Models");
	m_model = Model::CreateFromCMO(game->GetDevice(), L"Resources\\Models\\bg.cmo", fx);

	m_model->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ���C�g�̉e�����Ȃ���
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false);
			lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// �G�~�b�V�����F�𔒂ɐݒ肷��
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});


}

bool PlayBg::Update(float elapsedTime)
{
	m_angle += 0.02f;

	return true;
}

void PlayBg::Render()
{
	Game* game = m_playGame->GetGame();

	Matrix world = Matrix::CreateRotationY(m_angle);
	Matrix view = Matrix::CreateLookAt(Vector3(0, 0, 0), Vector3(0, 0, -1), Vector3::Up);
	// �ˉe�s����쐬����
	Matrix projection = Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		960 / (float)720,
		0.1f,
		200.0f
	);

	// ���f���̕`��
	m_model->Draw(game->GetContext(), *game->GetStates(), world, view, projection);
}