#include "System/Graphics.h"
#include "SceneGame.h"
#include"Camera.h"

// 初期化
void SceneGame::Initialize()
{
	//ステージ初期化
	stage = new Stage();
	//プレイヤー初期化
	player = new Player();

	//カメラ初期設定
	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::Instance();
	camera.SetLookAt(
		DirectX::XMFLOAT3(0, 10, -10),
		DirectX::XMFLOAT3(0, 0, 0),
		DirectX::XMFLOAT3(0, 1, 0)
	);
	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(45),
		graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		2000.0f
	);

	cameraController = new CameraController();
}

// 終了化
void SceneGame::Finalize()
{
	if (cameraController != nullptr) {
		delete cameraController;
		cameraController = nullptr;
	}
	
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	if (stage != nullptr)
	{
		delete stage;
		stage = nullptr;
	}
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{
	cameraController->Update(elapsedTime);
	
	stage->Update(elapsedTime);
	player->Update(elapsedTime);
}

// 描画処理
void SceneGame::Render()
{
	Graphics& graphics = Graphics::Instance(); 
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ShapeRenderer* shapeRenderer = graphics.GetShapeRenderer();
	ModelRenderer* modelRenderer = graphics.GetModelRenderer();

	RenderContext rc;
	rc.deviceContext = dc;
	rc.renderState = graphics.GetRenderState();
	rc.lightDirection = { 0.0f, -1.0f, 0.0f };

	Camera& camera = Camera::Instance();
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();


	// 3Dモデル描画
	{
		stage->Render(rc, modelRenderer);
		player->Render(rc, modelRenderer);
	}

	// 3Dデバッグ描画
	{

	}

	// 2Dスプライト描画
	{

	}
}

// GUI描画
void SceneGame::DrawGUI()
{
	// プレイヤーデバッグ描画
	player->DrawDebugGUI();
	cameraController->DrawDebugGUI();
	stage->DrawDebugGUI();
}
