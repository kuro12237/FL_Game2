#include "TitleSpriteManager.h"
#include "imgui.h"
using namespace Engine;
using namespace Engine::Manager;

namespace {
constexpr float ScreenCenterX = 640.0f;
constexpr float ScreenCenterY = 360.0f;
inline Math::Vector::Vector3 CenteredTranslate(float centerX, float centerY, const Math::Vector::Vector2 &size)
{
   return {centerX - size.x * 0.5f, centerY - size.y * 0.5f, 0.0f};
}
}

void TitleSpriteManager::Init()
{
   Clear();

   {
      TSpriteItem logoback;
      const Math::Vector::Vector2 size = {1223.0f / 1.5f, 285.0f / 1.5f};

      uint32_t handle = TextureManager::LoadPngTexture("TitleSpr/OffSideLogisticsLogoBack.png");

      logoback.sprite = std::make_unique<Engine::Objects::Sprite>();
      logoback.sprite->Initialize();
      logoback.sprite->SetTexHandle(handle);
      logoback.sprite->SetSize(size);

      logoback.transform.Initialize();
      logoback.transform.transform.translate = CenteredTranslate(ScreenCenterX, ScreenCenterY, size);

      logoback.name = "TitleLogoBack";
      sprites_.push_back(std::move(logoback));
   }

   {
      TSpriteItem logo;
      const Math::Vector::Vector2 size = {1223.0f / 1.5f, 285.0f / 1.5f};

      uint32_t handle = TextureManager::LoadPngTexture("TitleSpr/OffSideLogisticsLogo.png");

      logo.sprite = std::make_unique<Engine::Objects::Sprite>();
      logo.sprite->Initialize();
      logo.sprite->SetTexHandle(handle);
      logo.sprite->SetSize(size);

      logo.transform.Initialize();
      logo.transform.transform.translate = CenteredTranslate(ScreenCenterX, ScreenCenterY, size);

      logo.name = "TitleLogo";
      sprites_.push_back(std::move(logo));
   }

   {
      TSpriteItem pushA;
      const Math::Vector::Vector2 size = {1000.0f * 0.4f, 400.0f * 0.4f};

      uint32_t handle = TextureManager::LoadPngTexture("TitleSpr/PushATex.png");

      pushA.sprite = std::make_unique<Engine::Objects::Sprite>();
      pushA.sprite->Initialize();
      pushA.sprite->SetTexHandle(handle);
      pushA.sprite->SetSize(size);

      pushA.transform.Initialize();
      pushA.transform.transform.translate = CenteredTranslate(ScreenCenterX, ScreenCenterY + 300.0f, size);

      pushA.name = "PushA";
      sprites_.push_back(std::move(pushA));
   }
}

void TitleSpriteManager::Update()
{
   for (auto &item : sprites_) {
      item.transform.UpdateMatrix();
   }
}

void TitleSpriteManager::Draw()
{
   for (auto &item : sprites_) {
      item.sprite->Draw(item.transform);
   }
}

void TitleSpriteManager::Clear()
{
   sprites_.clear();
}