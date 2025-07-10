#pragma once
#include "MyWin.h"
#include <d3d11.h>
#include <wrl.h>
#include "MyException.h"
#include "Colors.h"
#include "Vec2.h"
#include "Surface.h"
#include "Rect.h"

class Graphics
{
public:
	class Exception : public MyException
	{
	public:
		Exception(HRESULT hr, const std::wstring& note, const wchar_t* file, unsigned int line);
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x, y, z;		// position
		float u, v;			// texcoords
	};
public:
	Graphics(class HWNDKey& key);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	void EndFrame(int delay);
	void BeginFrame(Color bg);
	Color GetPixel(int x, int y) const;
	void PutPixel(int x, int y, int r, int g, int b)
	{
		PutPixel(x, y, { unsigned char(r),unsigned char(g),unsigned char(b) });
	}
	void PutPixel(int x, int y, Color c);
	void DrawRect(RectI srcRect, Color c);
	void DrawRect(RectI srcRect, const RectI& clip, Color c);
	template<typename E>
	void DrawImage(int x, int y, const Surface& s, E effect, bool reversed = false)
	{
		DrawImage(x, y, s.GetRect(), s, effect, reversed);
	}
	template<typename E>
	void DrawImage(const Vec2& pos, const Surface& s, E effect, bool reversed = false)
	{
		DrawImage(int(pos.x), int(pos.y), s, effect, reversed);
	}
	template<typename E>
	void DrawImage(int x, int y, const RectI& srcRect, const Surface& s, E effect, bool reversed = false)
	{
		DrawImage(x, y, srcRect, GetScreenRect(), s, effect, reversed);
	}
	template<typename E>
	void DrawImage(const Vec2& pos, const RectI& srcRect, const Surface& s, E effect, bool reversed = false)
	{
		DrawImage(int(pos.x), int(pos.y), srcRect, s, effect, reversed);
	}
	template<typename E>
	void DrawImage(int x, int y, RectI srcRect, const RectI& clip, const Surface& s, E effect, bool reversed = false)
	{
		if (x < clip.left)
		{
			if (!reversed)
			{
				srcRect.left += clip.left - x;
				x = clip.left;
			}
			else
			{
				srcRect.right -= clip.left - x;
				x = clip.left;
			}
		}
		if (y < clip.top)
		{
			srcRect.top += clip.top - y;
			y = clip.top;
		}
		if (x + srcRect.GetWidth() > clip.right)
		{
			if (!reversed)
			{
				srcRect.right -= x + srcRect.GetWidth() - clip.right;
			}
			else
			{
				srcRect.left += x + srcRect.GetWidth() - clip.right;
			}
		}
		if (y + srcRect.GetHeight() > clip.bottom)
		{
			srcRect.bottom -= y + srcRect.GetHeight() - clip.bottom;
		}
		for (int sx = srcRect.left; sx < srcRect.right; sx++)
		{
			for (int sy = srcRect.top; sy < srcRect.bottom; sy++)
			{

				if (!reversed)
				{
					effect(s.GetPixel(sx, sy), sx + x - srcRect.left, sy + y - srcRect.top, *this);
				}
				else
				{
					const int xOffset = srcRect.left + srcRect.right - 1;
					effect(s.GetPixel(xOffset - sx, sy), x + sx - srcRect.left, y + sy - srcRect.top, *this);
				}
			}
		}
	}
	template<typename E>
	void DrawImage(const Vec2& pos, RectI srcRect, const RectI& clip, const Surface& s, E effect, bool reversed = false)
	{
		DrawImage(int(pos.x), int(pos.y), srcRect, clip, s, effect, reversed);
	}


	~Graphics();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Surface												sysBuffer;
public:
	static constexpr int ScreenWidth = 1000;
	static constexpr int ScreenHeight = 700;
	static RectI GetScreenRect();
};