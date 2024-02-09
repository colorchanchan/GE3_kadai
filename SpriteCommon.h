#pragma once
#include <Windows.h>
#include <dxcapi.h>
#include <wrl.h>
#include <string>
#include "DirectXCommon.h"
#include <d3d12.h>
#include<DirectXTex.h>

// ‹¤’Ê
class SpriteCommon
{
public:
	void Initialize(DirectXCommon* dxCommon);

	// Getter
	ID3D12RootSignature* GetRootSignature() { return rootSignature.Get(); }
	ID3D12PipelineState* GetPipelineState() { return pipelineState.Get(); }

private:
	static IDxcBlob* CompileShader(
		const std::wstring& filePath,
		const wchar_t* profile,
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler
		);
private:
	DirectXCommon* dxCommon_ = nullptr;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
};

