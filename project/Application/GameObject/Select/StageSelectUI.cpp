#include "StageSelectUI.h"
using namespace Engine::Manager;

StageSelectUI::StageSelectUI() 
{
   sprite_ = std::make_unique<Engine::Objects::Sprite>();
   
}

void StageSelectUI::Init()
{
   uint32_t selectnum1 = TextureManager::LoadPngTexture("SelectNumber/selectNum_1.png");
   uint32_t selectnum2 = TextureManager::LoadPngTexture("SelectNumber/selectNum_2.png");
   uint32_t selectnum3 = TextureManager::LoadPngTexture("SelectNumber/selectNum_3.png");
   uint32_t selectnum4 = TextureManager::LoadPngTexture("SelectNumber/selectNum_4.png");
   uint32_t selectnum5 = TextureManager::LoadPngTexture("SelectNumber/selectNum_5.png");
   uint32_t selectnum6 = TextureManager::LoadPngTexture("SelectNumber/selectNum_6.png");
   uint32_t selectnum7 = TextureManager::LoadPngTexture("SelectNumber/selectNum_7.png");
   uint32_t selectnum8 = TextureManager::LoadPngTexture("SelectNumber/selectNum_8.png");
   uint32_t selectnum9 = TextureManager::LoadPngTexture("SelectNumber/selectNum_9.png");
   uint32_t selectnum10 = TextureManager::LoadPngTexture("SelectNumber/selectNum_10.png");

   selectnum1;
   selectnum2;
   selectnum3;
   selectnum4;
   selectnum5;
   selectnum6;
   selectnum7;
   selectnum8;
   selectnum9;
   selectnum10;

   sprite_->Initialize();
   sprite_->SetTexHandle(selectnum1);

   worldTransform_.Initialize();
}

void StageSelectUI::Update()
{
   worldTransform_.UpdateMatrix();
}

void StageSelectUI::Draw()
{
   sprite_->Draw(worldTransform_);
}