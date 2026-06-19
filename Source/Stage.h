#pragma once
#include"System/ModelRenderer.h"
#include"ModelCommon.h"
#include"CameraController.h"

//ステージ
class Stage:public ModelCommon
{
public:
	Stage();
	~Stage()override;

	//更新処理
	void Update(float elapsedTime);
	//描画処理
	void Render(const RenderContext& rc, ModelRenderer* renderer);

	void FrontWall();

	//デバッグ用GUI描画
	void DrawDebugGUI();

private:
	struct Wall
	{
		DirectX::XMFLOAT3 position = { 0,0,0 };
		DirectX::XMFLOAT3 angle = { 0,0,0 };
		DirectX::XMFLOAT3 scale = { 1,1,1 };
		DirectX::XMFLOAT4X4 transform = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};

		DirectX::XMFLOAT3 distance = {};
		bool isFrontWall = false;
		int frontNum = 0;//1-4の順で近い
	};
	enum wallPos
	{
		FRONT_R,
		FRONT_L,
		BACK_R,
		BACK_L
	};
private:
	Model* model = nullptr;
	Model* wall_mdl = nullptr;
	Wall wall[4];
	CameraController camera;


};