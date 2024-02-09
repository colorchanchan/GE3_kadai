#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Sprite.h"
#include "SpriteCommon.h"
#include "ImGuiManager.h"
#include <vector>
#include "TextureManager.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ポインタ置き場
    Input* input_ = nullptr;
    WinApp* winApp_ = nullptr;
    DirectXCommon* dxCommon_ = nullptr;

// WindowsAPI初期化処理
    winApp_ = new WinApp();
    winApp_->Initialize();

// DirectX初期化処理
    dxCommon_ = new DirectXCommon();
    dxCommon_->Initialize(winApp_);

    input_ = new Input();
    input_->Initialize(winApp_);

    ImGuiManager* imgui = ImGuiManager::Create();
    ImGuiManager::Initialize(winApp_->GetHwnd(), dxCommon_);

    // スプライトコモン
    SpriteCommon* spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon_);

    // テクスチャマネージャー
    TextureManager::Getinstance()->Initialize(dxCommon_);
    TextureManager::Getinstance()->LoadTexture(L"Resources/mario.jpg");
    TextureManager::Getinstance()->LoadTexture(L"Resources/reimu.png");

    // 画像
   
    Sprite* sprite1 = new Sprite();
    Sprite* sprite2 = new Sprite();
    sprite1->Initialize(dxCommon_, spriteCommon, L"Resources/mario.jpg");
    sprite2->Initialize(dxCommon_, spriteCommon, L"Resources/reimu.png");

    sprite1->SetPosition({ 100,100 });
    sprite2->SetPosition({ 500,100 });
    
    // ゲームループ
    while (true) {
        // 更新
        if (winApp_->Update() == true){
            break;
        }
        ImGuiManager::NewFrame();

        input_->Update();
        
        sprite1->Update();
        sprite2->Update();

        // 描画前処理
        ImGuiManager::CreateCommand();
        dxCommon_->PreDraw();

        sprite1->Draw();
        sprite2->Draw();

        // 描画後処理
        ImGuiManager::CommandsExcute(dxCommon_->GetCommandList());
        dxCommon_->PostDraw();
    }
    delete input_;

    winApp_->Finalize();
    delete winApp_;
    TextureManager::Getinstance()->Finalize();
    delete dxCommon_;

    delete imgui;

    delete spriteCommon;
    
    delete sprite1;
    delete sprite2;

    return 0;
}