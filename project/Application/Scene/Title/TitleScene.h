#pragma once 

#include "IScene.h"

class TitleScene : public IScene {

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(GameManager* state) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update([[maybe_unused]] GameManager* Scene) override;

	/// <summary>
	/// ポストエフェクトをかける
	/// </summary>
	void PostProcessDraw() override;

	/// <summary>
	/// 前景2d
	/// </summary>
	void Flont2dSpriteDraw() override;

	/// <summary>
	/// Imguiの更新
	/// </summary>
	void ImGuiUpdate() override;



private:


private:



};