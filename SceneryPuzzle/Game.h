//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "pch.h"
#include "Scene\SceneManager.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

public:
	// �Q�b�^�[
	// �R���e�L�X�g���擾����֐�
	ID3D11DeviceContext* GetContext() { return m_deviceResources->GetD3DDeviceContext(); };

	// �f�o�C�X���擾����
	ID3D11Device* GetDevice() { return m_deviceResources->GetD3DDevice(); };

	DX::DeviceResources* GetResources() { return m_deviceResources.get(); }

	// �R�����X�e�[�g���擾����
	DirectX::CommonStates* GetStates() { return m_states.get(); };

	// �r���[�s����擾����
	DirectX::SimpleMath::Matrix& GetView() { return m_view; };

	void SetView(DirectX::SimpleMath::Matrix view) { m_view = view; };

	// �ˉe�s����擾����
	DirectX::SimpleMath::Matrix& GetProjection() { return m_projection; };

	DirectX::SpriteBatch* GetSpriteBatch();


private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;

	// �}�E�X
	std::unique_ptr<DirectX::Mouse> m_mouse;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;

	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_sprites;


	// �X�v���C�g�t�H���g
	std::unique_ptr<DirectX::SpriteFont> m_font;


	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

	// �G�t�F�N�g
	std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �V�[���}�l�[�W���[�i�[�p
	SceneManager* m_sceneManager;
};