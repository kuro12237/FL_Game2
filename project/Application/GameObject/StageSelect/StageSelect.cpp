#include "StageSelect.h"
#include "Input/Input.h"

using namespace Engine;
using namespace Engine::Manager;
using namespace Engine::Objects;
using namespace Engine::Transform;

namespace
{
constexpr int StageCount = 10;
constexpr int Cols = 5;
constexpr int Rows = 2;

// ===== アトラス =====
constexpr float AtlasSize = 2560.0f;
constexpr float CellSize = 512.0f;

// ===== 表示サイズ / 選択拡大 =====
constexpr float DrawSize = 140.0f;
constexpr float SelectedScale = 1.35f; // ← もっとデカく（1.15 → 1.35）

// ===== 画面 =====
constexpr float ScreenW = 1280.0f;
constexpr float ScreenH = 720.0f;

// ===== レイアウト（余白調整）=====
// “詰め/広げ”はここだけ触ればOK
constexpr float SpacingX = 100.0f; // ← 少し広げて拡大分の余白確保
constexpr float SpacingY = 150.0f;

// 画面センターを基準に少しだけ上/下にずらしたい時
constexpr float OffsetX = 0.0f;
constexpr float OffsetY = 0.0f;

// 選択拡大時に「右下方向に伸びる」のがイヤなら true
// true なら中心がズレないように translate を補正する
constexpr bool KeepCenterWhenScaled = true;
} // namespace

void StageSelect::Init()
{
   atlasTex_ = TextureManager::LoadPngTexture("StageSelectAtlas.png");

   cursor_ = 0;
   selectedStage_ = 1;
   inputWait_ = 0;

   CreateButtons();
}

void StageSelect::CreateButtons()
{
   buttons_.clear();

   // ----------------------------
   // グリッド全体のサイズを計算して、画面中央に配置
   // ここが「左寄り」を直す本体
   // ----------------------------
   const float gridW = DrawSize * Cols + SpacingX * (Cols - 1);
   const float gridH = DrawSize * Rows + SpacingY * (Rows - 1);

   const float startX = (ScreenW - gridW) * 0.5f + OffsetX;
   const float startY = (ScreenH - gridH) * 0.5f + OffsetY;

   for (int i = 0; i < StageCount; ++i) {
      StageButton btn;
      btn.stage = i + 1;

      btn.sprite = std::make_unique<Sprite>();
      btn.sprite->Initialize();
      btn.sprite->SetTexHandle(atlasTex_);
      btn.sprite->SetSize({DrawSize, DrawSize});

      ApplyUV(btn);

      btn.transform.Initialize();

      const int col = i % Cols;
      const int row = i / Cols; // 0 or 1

      btn.transform.transform.translate = {startX + col * (DrawSize + SpacingX), startY + row * (DrawSize + SpacingY), 0.0f};

      buttons_.push_back(std::move(btn));
   }
}

void StageSelect::ApplyUV(StageButton &btn)
{
   const int idx = btn.stage - 1;

   const int col = idx % Cols; // 0〜4
   const int row = idx / Cols; // 0〜1

   const float u0 = (col * CellSize) / AtlasSize;
   const float v0 = (row * CellSize) / AtlasSize;
   const float u1 = ((col + 1) * CellSize) / AtlasSize;
   const float v1 = ((row + 1) * CellSize) / AtlasSize;

   btn.sprite->SetSrc({u0, v0}, // TL
                      {u0, v1}, // BL
                      {u1, v0}, // TR
                      {u1, v1}  // BR
   );
}

void StageSelect::Update()
{
   if (inputWait_ > 0) {
      --inputWait_;
      return;
   }

   UpdateCursor();
}

void StageSelect::UpdateCursor()
{
   const int prev = cursor_;

   if (Input::PushKeyPressed(DIK_LEFT))
      cursor_--;
   if (Input::PushKeyPressed(DIK_RIGHT))
      cursor_++;
   if (Input::PushKeyPressed(DIK_UP))
      cursor_ -= Cols;
   if (Input::PushKeyPressed(DIK_DOWN))
      cursor_ += Cols;

   cursor_ = std::clamp(cursor_, 0, StageCount - 1);

   if (cursor_ != prev) {
      selectedStage_ = cursor_ + 1;
      inputWait_ = 6;
   }
}

void StageSelect::Draw()
{
   for (int i = 0; i < static_cast<int>(buttons_.size()); ++i) {
      auto &btn = buttons_[i];

      const bool selected = (i == cursor_);
      const float scale = selected ? SelectedScale : 1.0f;

      // サイズ変更
      btn.sprite->SetSize({DrawSize * scale, DrawSize * scale});

      // 拡大しても「中心がズレない」ように補正（必要なら）
      if (KeepCenterWhenScaled) {
         // CreateButtons() で置いた座標は「通常サイズの左上」なので
         // 拡大分(増えた分)の半分だけ左上に戻す
         const float extra = DrawSize * (scale - 1.0f);
         btn.transform.transform.translate.x -= extra * 0.5f;
         btn.transform.transform.translate.y -= extra * 0.5f;
      }

      btn.transform.UpdateMatrix();
      btn.sprite->Draw(btn.transform);

      // 補正した分を戻す（次フレームでズレが累積しないように）
      if (KeepCenterWhenScaled) {
         const float extra = DrawSize * (scale - 1.0f);
         btn.transform.transform.translate.x += extra * 0.5f;
         btn.transform.transform.translate.y += extra * 0.5f;
      }
   }
}

void StageSelect::ImGuiUpdate()
{
   ImGui::Text("StageSelect");
   ImGui::Text("Selected Stage : %d", selectedStage_);
   ImGui::Text("Cursor Index   : %d", cursor_);
}
