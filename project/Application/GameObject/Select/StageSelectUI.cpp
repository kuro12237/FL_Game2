#include "StageSelectUI.h"
using namespace Engine;
using namespace Engine::Manager;
#include "Input/Input.h"

StageSelectUI::StageSelectUI() 
{
   
}

void StageSelectUI::Init()
{
    // 配列のresize
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

   // --- スプライト配置 ---
#if 0
   int columns = 5;  // 列数
   float startX = 100.0f;  // 最初の配置X座標
   float startY = 180.0f;  // 最初の配置Y座標
   float offsetX = 240.0f;  // 横方向の間隔
   float offsetY = 240.0f;  // 縦方向の間隔

   for (int i = 0; i < stageCount; ++i) {
      int col = i % columns;
      int row = i / columns;

      stageTransforms_[i].transform.translate.x = startX + col * offsetX;
      stageTransforms_[i].transform.translate.y = startY + row * offsetY;
   }
#endif

#if 1
   float startX = 10.0f;  // 左端の開始位置
   float startY = 150.0f;  // 上からの高さ（固定）
   float offsetX = 115.0f; // X移動量：これが階段の幅
   float offsetY = 250.0f;  // Y移動量：段を下げる量
   for (int i = 0; i < stageCount; ++i) {
      bool upperStep = (i % 2 == 0); // 偶数: 上段, 奇数: 下段
      stageTransforms_[i].transform.translate.x = startX + i * offsetX;
      stageTransforms_[i].transform.translate.y = upperStep ? startY : startY + offsetY;
   }
#endif

   currentIndex_ = 0; // 最初のステージ選択は0(1stage目)
}

void StageSelectUI::Update()
{
    // worldtransformの更新
   for (auto &wt : stageTransforms_) {
      wt.UpdateMatrix();
   }

   // 選択中のスプライトは拡大、白色へ
   for (int i = 0; i < stageTransforms_.size(); ++i) {
      if (i == currentIndex_) {
         // 選択中は少し大きく
         stageTransforms_[i].transform.scale = {1.5f, 1.5f, 1.0f};
         stageSprites_[i]->SetColor({1.0f, 1.0f, 1.0f, 1.0f});
      }
      else {
         // 他は通常サイズ
         stageTransforms_[i].transform.scale = {1.0f, 1.0f, 1.0f};
         stageSprites_[i]->SetColor({0.0f, 0.0f, 0.0f, 1.0f});
      }
      stageTransforms_[i].UpdateMatrix();
   }

   // 右入力
   if (Input::PushKeyPressed(DIK_D) || 
       Input::PushKeyPressed(DIK_RIGHT) || 
       Input::PushBottonPressed(XINPUT_GAMEPAD_DPAD_RIGHT) || 
       IsLJoystickRight()) {
       currentIndex_++;   
   }
   // 左入力
   if (Input::PushKeyPressed(DIK_A) || 
       Input::PushKeyPressed(DIK_LEFT) || 
       Input::PushBottonPressed(XINPUT_GAMEPAD_DPAD_LEFT) || 
       IsLJoystickLeft()) {
       currentIndex_--;
   }

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

bool StageSelectUI::IsLJoystickRight()
{
   Math::Vector::Vector2 Ljoy = Engine::Input::GetInstance()->GetJoyLStickPos();
   bool isRight = (Ljoy.x > joystickThreshold_);

   bool triggered = (!prevRight_ && isRight);

   prevRight_ = isRight;

   return triggered;
}

bool StageSelectUI::IsLJoystickLeft()
{
   Math::Vector::Vector2 Ljoy = Engine::Input::GetInstance()->GetJoyLStickPos();
   bool isLeft = (Ljoy.x < -joystickThreshold_);

   bool triggered = (!prevLeft_ && isLeft);

   prevLeft_ = isLeft;

   return triggered;
}
