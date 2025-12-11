#include "StageSelectUI.h"
using namespace Engine::Manager;

StageSelectUI::StageSelectUI() 
{
   
}

void StageSelectUI::Init()
{
   const int stageCount = 10;
   stageSprites_.resize(stageCount);
   stageTransforms_.resize(stageCount);

   // --- テクスチャロード（キャッシュされるので1回でOK） ---
   textureHandles_.resize(stageCount);
   for (int i = 0; i < stageCount; ++i) {
      std::string path = "SelectNumber/selectNum_" + std::to_string(i + 1) + ".png";
      textureHandles_[i] = TextureManager::LoadPngTexture(path);
   }

   // --- スプライト生成 ---
   for (int i = 0; i < stageCount; ++i) {
      stageSprites_[i] = std::make_unique<Engine::Objects::Sprite>();
      stageSprites_[i]->Initialize();
      stageSprites_[i]->SetTexHandle(textureHandles_[i]);
      stageSprites_[i]->SetSize({140.0f, 140.0f});

      // WorldTransform
      stageTransforms_[i].Initialize();
   }


   float startX = 10.0f;  // 左端の開始位置
   float startY = 150.0f;  // 上からの高さ（固定）
   float offsetX = 115.0f; // X移動量：これが階段の幅
   float offsetY = 250.0f;  // Y移動量：段を下げる量

   for (int i = 0; i < stageCount; ++i) {
      bool upperStep = (i % 2 == 0); // 偶数: 上段, 奇数: 下段

      stageTransforms_[i].transform.translate.x = startX + i * offsetX;
      stageTransforms_[i].transform.translate.y = upperStep ? startY : startY + offsetY;
   }
}

void StageSelectUI::Update()
{
   for (auto &wt : stageTransforms_) {
      wt.UpdateMatrix();
   }

   for (int i = 0; i < stageTransforms_.size(); ++i) {
      if (i == currentIndex_) {
         // 選択中は少し大きく
         stageTransforms_[i].transform.scale = {1.5f, 1.5f, 1.0f};
      }
      else {
         // 他は通常サイズ
         stageTransforms_[i].transform.scale = {1.0f, 1.0f, 1.0f};
      }

      stageTransforms_[i].UpdateMatrix();
   }

   ImGui::Begin("Select");
   ImGui::InputInt("Current", &currentIndex_, 1, 1);
   ImGui::End();

   // 強制的に範囲内に戻す
   int minStage = 0, maxStage = 9;
   currentIndex_ = std::clamp(currentIndex_, minStage, maxStage);
}

void StageSelectUI::Draw()
{
   for (int i = 0; i < stageSprites_.size(); ++i) {
      stageSprites_[i]->Draw(stageTransforms_[i]);
   }
}