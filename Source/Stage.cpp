#include"Stage.h"
#include<imgui.h>
#include <algorithm>

//コンストラクタ
Stage::Stage()
{
	//ステージ読み込み
	model = new Model("Data/Model/classroom/class_set/classroom_demoscene.mdl");
	wall_mdl = new Model("Data/Model/cube/wall.mdl");
	wall[FRONT_R].angle.y = DirectX::XM_PI * 0.25f;
	wall[FRONT_L].angle.y = -DirectX::XM_PI * 0.25f;
	wall[BACK_R].angle.y = -DirectX::XM_PI * 0.25f;
	wall[BACK_L].angle.y = DirectX::XM_PI * 0.25f;

	wall[FRONT_R].position = { -300,0,0 };
	wall[FRONT_L].position = { 0,0,0 };
	wall[BACK_R].position= {-300,0,-300};
	wall[BACK_L].position = { 0,0,-300 };
}
Stage::~Stage()
{
	//ステージモデルを破棄
	delete model;
	delete wall_mdl;
}
//更新処理
void Stage::Update(float elapsedTime)
{
	for (int i = 0; i < 4; i++)
	{
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(wall[i].scale.x, wall[i].scale.y, wall[i].scale.z);
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(wall[i].angle.x, wall[i].angle.y, wall[i].angle.z);
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(wall[i].position.x, wall[i].position.y, wall[i].position.z);
		DirectX::XMMATRIX W = S * R * T;
		DirectX::XMStoreFloat4x4(&wall[i].transform, W);
	}
	FrontWall();

}

void Stage::FrontWall()
{
	//壁を二枚透明化（一枚だけを追加実装）
	struct WallDistance
	{
		int index;
		float distance;
	};

	std::vector<WallDistance> distances;

	for (int i = 0; i < 4; i++)
	{
		//カメラとの距離
		wall[i].distance.z = wall[i].position.z - camera.GetCameraTarget().z;
		distances.push_back({ i, wall[i].distance.z });
	}

	//距離を比較
	std::sort(distances.begin(), distances.end(),
		[](const WallDistance& a, const WallDistance& b)
		{
			return a.distance < b.distance;
		});

	for (int rank = 0; rank < 4; rank++)
	{
		wall[distances[rank].index].frontNum = rank + 1;
	}

	for (int i = 0; i < 4; i++)
	{
		if (wall[i].frontNum == 1 || wall[i].frontNum == 2)
		{
			wall[i].isFrontWall = true;
		}
	}
}

void Stage::Render(const RenderContext& rc, ModelRenderer* renderer)
{
	//ステージ描画
	//renderer->Render(rc, transform, model, ShaderId::Lambert);

	//壁の描画
	for (int i = 0; i < 4; i++)
	{
		if (!wall[i].isFrontWall) 
		{
			renderer->Render(rc, wall[i].transform, wall_mdl, ShaderId::Lambert);
		}
	}
}

void Stage::DrawDebugGUI()
{
	//ウィンドウの位置
	ImVec2 pos = ImGui::GetMainViewport()->GetWorkPos();
	ImGui::SetNextWindowPos(ImVec2(pos.x + 10, pos.y + 200), ImGuiCond_Once);
	//ウィンドウサイズ
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	//ウィンドウ開始
	if (ImGui::Begin("stage", nullptr, ImGuiWindowFlags_None)) {
		//折り畳みメニュー
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
			for (int i = 0; i < 4; i++)
			{
				//位置
				ImGui::InputFloat3("Position", &wall[i].position.x);
				//回転
				DirectX::XMFLOAT3 a;
				a.x = DirectX::XMConvertToDegrees(wall[i].angle.x);
				a.y = DirectX::XMConvertToDegrees(wall[i].angle.y);
				a.z = DirectX::XMConvertToDegrees(wall[i].angle.z);
				ImGui::InputFloat3("Angle", &a.x);
				wall[i].angle.x = DirectX::XMConvertToRadians(a.x);
				wall[i].angle.y = DirectX::XMConvertToRadians(a.y);
				wall[i].angle.z = DirectX::XMConvertToRadians(a.z);
				//スケール
				ImGui::InputFloat3("Scale", &wall[i].scale.x);
			}
		}
	}
	ImGui::End();

}
