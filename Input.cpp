#include "Input.h"
#include <cassert>

using namespace Microsoft::WRL;

void Input::Initialize(WinApp* winApp)
{
    winApp_ = winApp;

    HRESULT result;

    result = DirectInput8Create(
      winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
    assert(SUCCEEDED(result));

    // キーボードデバイスの生成
    result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
    // 入力データ形式のセット
    result = keyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式
    assert(SUCCEEDED(result));
    // 排他制御レベルのセット
    result = keyboard->SetCooperativeLevel(
        winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
}

void Input::Update()
{
    // keyPreの中にkeyの情報をコピーする
    memcpy(keyPre, key, sizeof(key));

    // キーボード情報の取得開始
    keyboard->Acquire();
    // 全キーの入力状態を取得する
    keyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber)
{
    // 任意ボタンが押されているか
    if (key[keyNumber])
    {
        return true;
    }

    // 任意ボタンが押されていないとき
    return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
    if (keyPre[keyNumber] == false && key[keyNumber] == true)
    {
        return true;
    }

    return false;
}
