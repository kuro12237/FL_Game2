#include "GamePlayOperationUIManager.h"

using namespace Engine;
using namespace Engine::Manager;

namespace
{
// =====================================
// Screen（左上基準）
// =====================================
constexpr float ScreenWidth = 1280.0f;
constexpr float ScreenHeight = 720.0f;

// 画面端マージン
constexpr float MarginRight = 24.0f;
constexpr float MarginBottom = 24.0f;

// 元画像サイズ & 表示スケール（固定）
constexpr float SrcW = 1000.0f;
constexpr float SrcH = 400.0f;
constexpr float UIScale = 0.3f;

inline Math::Vector::Vector2 CalcUISize()
{
   return {SrcW * UIScale, SrcH * UIScale};
}

// =====================================
// 画像内余白を「重ね」で吸収する量
// =====================================

// 横方向（Y–X / A–B を詰める）
constexpr float OverlapX = 100.0f;

// 縦方向（行間を詰める）
constexpr float OverlapY = 40.0f;
} // namespace

void GamePlayOperationUIManager::Init()
{
   Clear();

   const Math::Vector::Vector2 size = CalcUISize();

   // -------------------------------------------------
   // X 座標（右端・左列）
   // -------------------------------------------------
   const float rightX = ScreenWidth - MarginRight - size.x;
   const float leftX = rightX - (size.x - OverlapX);

   // -------------------------------------------------
   // Y 座標（下端・上段）
   // -------------------------------------------------
   const float rowAB_Y = ScreenHeight - MarginBottom - size.y; // A / B（最下段）
   const float rowYX_Y = rowAB_Y - (size.y - OverlapY);        // Y / X
   const float rowHome_Y = rowYX_Y - (size.y - OverlapY) - 16.0f; // Home

   // =========================
   // Home（縦棒の上）
   // =========================
   {
      UISpriteItem item;
      item.sprite = std::make_unique<Objects::Sprite>();
      item.sprite->Initialize();
      item.sprite->SetTexHandle(TextureManager::LoadPngTexture("stageButtonUI/stageButtonHome.png"));
      item.sprite->SetSize(size);

      item.transform.Initialize();
      item.transform.transform.translate = {rightX, rowHome_Y, 0.0f};

      item.name = "ButtonHome";
      sprites_.push_back(std::move(item));
   }

   // =========================
   // Y / X（横棒の中段）
   // =========================
   {
      UISpriteItem item;
      item.sprite = std::make_unique<Objects::Sprite>();
      item.sprite->Initialize();
      item.sprite->SetTexHandle(TextureManager::LoadPngTexture("stageButtonUI/stageButtonY.png"));
      item.sprite->SetSize(size);

      item.transform.Initialize();
      item.transform.transform.translate = {leftX, rowYX_Y, 0.0f};

      item.name = "ButtonY";
      sprites_.push_back(std::move(item));
   }

   {
      UISpriteItem item;
      item.sprite = std::make_unique<Objects::Sprite>();
      item.sprite->Initialize();
      item.sprite->SetTexHandle(TextureManager::LoadPngTexture("stageButtonUI/stageButtonX.png"));
      item.sprite->SetSize(size);

      item.transform.Initialize();
      item.transform.transform.translate = {rightX, rowYX_Y, 0.0f};

      item.name = "ButtonX";
      sprites_.push_back(std::move(item));
   }

   // =========================
   // A / B（横棒の下段）
   // =========================
   {
      UISpriteItem item;
      item.sprite = std::make_unique<Objects::Sprite>();
      item.sprite->Initialize();
      item.sprite->SetTexHandle(TextureManager::LoadPngTexture("stageButtonUI/stageButtonA.png"));
      item.sprite->SetSize(size);

      item.transform.Initialize();
      item.transform.transform.translate = {leftX, rowAB_Y, 0.0f};

      item.name = "ButtonA";
      sprites_.push_back(std::move(item));
   }

   {
      UISpriteItem item;
      item.sprite = std::make_unique<Objects::Sprite>();
      item.sprite->Initialize();
      item.sprite->SetTexHandle(TextureManager::LoadPngTexture("stageButtonUI/stageButtonB.png"));
      item.sprite->SetSize(size);

      item.transform.Initialize();
      item.transform.transform.translate = {rightX, rowAB_Y, 0.0f};

      item.name = "ButtonB";
      sprites_.push_back(std::move(item));
   }
}

void GamePlayOperationUIManager::Update()
{
   for (auto &item : sprites_) {
      if (!item.visible) {
         continue;
      }
      item.transform.UpdateMatrix();
   }
}

void GamePlayOperationUIManager::Draw()
{
   if (!isVisible_) {
      return;
   }

   for (auto &item : sprites_) {
      if (!item.visible) {
         continue;
      }
      item.sprite->Draw(item.transform);
   }
}

void GamePlayOperationUIManager::SetVisible(bool visible)
{
   isVisible_ = visible;
}

void GamePlayOperationUIManager::Clear()
{
   sprites_.clear();
}
