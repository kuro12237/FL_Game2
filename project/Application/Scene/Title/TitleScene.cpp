#include "TitleScene.h"

TitleScene::TitleScene()
{
	gameObjectManager_ = GameObjectManager::GetInstance();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize([[maybe_unused]] GameManager* state)
{
	gameObjectManager_->ClearAllData();
	gameObjectManager_->CameraReset();
	gameObjectManager_->Update();

}

void TitleScene::Update([[maybe_unused]] GameManager* Scene)
{
}

void TitleScene::PostProcessDraw()
{
}

void TitleScene::Flont2dSpriteDraw()
{
}

void TitleScene::ImGuiUpdate()
{
}
