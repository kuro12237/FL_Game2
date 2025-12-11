#include "GameSceneEndState.h"

void GameSceneEndState::Initialize([[maybe_unused]] GameScene *scene)
{
   changeSceneAnimation_ = ChangeSceneAnimation::GetInstance();

   playerManager_ = scene->GetPlayerManager();

   scene->SetIsGameStartFlag(false);
   endAnimation_ = make_unique<EndAnimation>();
   endAnimation_->Initialize();
}

void GameSceneEndState::Update([[maybe_unused]] GameScene *scene)
{
   endAnimation_->Update();

   changeSceneAnimation_->ChangeStart();
}

void GameSceneEndState::Draw2d() {}