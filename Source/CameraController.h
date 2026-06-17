#pragma once
#include<DirectXMath.h>
#include"System/Mouse.h"//移動・回転操作

//カメラコントローラー
class CameraController
{
public:
	//更新処理
	void Update(float elaosedTime);
	//ターゲット位置設定
	void SetTerget(const DirectX::XMFLOAT3& target) { this->target = target; }
	//デバッグ用GUI描画
	void DrawDebugGUI();

private:

	//回転角度制限
	float maxAngleX = DirectX::XMConvertToRadians(45);
	float minAngleX = DirectX::XMConvertToRadians(-45);

	//距離制限
	float minRange = 630.0f;
	float maxRange = 1500.0f;


	DirectX::XMFLOAT3 target = { 0,0,0 };//注視点
	DirectX::XMFLOAT3 angle = { 0,0,0 };//回転角度
	float rollSpeed = DirectX::XMConvertToRadians(90);//回転速度
	float range = maxRange;//距離

public:
	DirectX::XMFLOAT3 GetCameraTarget() { return target; }

};