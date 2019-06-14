//
// Game.cpp
//

#include "pch.h"
#include "Game.h"
#include "Scene/SceneManager.h"
#include "InputManager.h"

#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;


using Microsoft::WRL::ComPtr;

Game::Game()
{
	m_deviceResources = std::make_unique<DX::DeviceResources>();
	m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{

	//// �f�o�b�O�J�����̍쐬
	//m_debugCamera = std::make_unique<DebugCamera>(width, height);

	m_deviceResources->SetWindow(window, width, height);

	m_deviceResources->CreateDeviceResources();
	CreateDeviceDependentResources();

	m_deviceResources->CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/

	// �V�[���}�l�[�W���[�̏�����-------------------
	m_sceneManager = new SceneManager(SCENE_TITLE);
	m_sceneManager->SetGame(this);
	//----------------------------------------------



}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
	m_timer.Tick([&]()
	{
		Update(m_timer);
	});



	Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	System::InputManager::GetInstance().Update();

	// �V�[���}�l�[�W���[�̍X�V-------------------
	m_sceneManager->UpdateActiveScene(timer);
	//----------------------------------------------
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}


	Clear();

	m_deviceResources->PIXBeginEvent(L"Render");
	auto context = m_deviceResources->GetD3DDeviceContext();

	// �V�[���}�l�[�W���[�̕`��---------------------
	m_sceneManager->RenderActiveScene();
	//----------------------------------------------
	/// <summary>
	/// //////////////////////////////////////////////////////////////////////////////
	/// </summary>

	// �����܂�

	m_deviceResources->PIXEndEvent();

	// Show the new frame.
	m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
	m_deviceResources->PIXBeginEvent(L"Clear");


	// Clear the views.
	auto context = m_deviceResources->GetD3DDeviceContext();
	auto renderTarget = m_deviceResources->GetRenderTargetView();
	auto depthStencil = m_deviceResources->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, Colors::Aquamarine);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// Set the viewport.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
	// TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
	// TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
	// TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
	m_timer.ResetElapsedTime();

	// TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
	if (!m_deviceResources->WindowSizeChanged(width, height))
		return;

	CreateWindowSizeDependentResources();

	// TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
	// TODO: Change to desired default window size (note minimum size is 320x200).
	width = 1280;
	height = 720;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
	ID3D11Device* device = m_deviceResources->GetD3DDevice();
	ID3D11DeviceContext* context = m_deviceResources->GetD3DDeviceContext();

	// TODO: Initialize device dependent objects here (independent of window size).
	device;


	// �R�����X�e�[�g�̍쐬
	m_states = std::make_unique<CommonStates>(device);

	// �X�v���C�g�o�b�`�̍쐬
	m_sprites = std::make_unique<SpriteBatch>(context);

	// �X�v���C�g�t�H���g�̍쐬
	m_font = std::make_unique<SpriteFont>(device, L"SegoeUI_18.spritefont");


	// �G�t�F�N�g�̍쐬
	m_batchEffect = std::make_unique<AlphaTestEffect>(device);
	m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	m_batchEffect->SetReferenceAlpha(255);

	// ���̓��C�A�E�g����
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	device->CreateInputLayout(VertexPositionTexture::InputElements, VertexPositionTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf());

	
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
	// TODO: Initialize windows-size dependent objects here.

	// �E�C���h�E�T�C�Y����A�X�y�N�g����Z�o����
	RECT size = m_deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// ��p��ݒ�
	float fovAngleY = XMConvertToRadians(45.0f);

	// �ˉe�s����쐬����
	m_projection = Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		1000.0f
	);

	// �f�o�b�O�J�����ɃE�C���h�E�̃T�C�Y�ύX��`����
	//m_debugCamera->SetWindowSize(size.right, size.bottom);
}

void Game::OnDeviceLost()
{
	// TODO: Add Direct3D resource cleanup here.

	m_states.reset();			// �R�����X�e�[�g�̉��

	m_sprites.reset();			// �X�v���C�g�o�b�`�̉��

	m_font.reset();				// �X�v���C�g�t�H���g�̉��

	m_keyboard.reset();			// �L�[�{�[�h�̉��

	m_mouse.reset();			// �}�E�X�̉��

	m_deviceResources.reset();	// �f�o�C�X�̉��

	delete m_sceneManager;
	m_sceneManager = nullptr;

	//ADX2Le* adx2le = ADX2Le::GetInstance();
	//adx2le->Finalize();

}



void Game::OnDeviceRestored()
{
	CreateDeviceDependentResources();

	CreateWindowSizeDependentResources();
}

DirectX::SpriteBatch* Game::GetSpriteBatch()
{
	return m_sprites.get();
}


#pragma endregion