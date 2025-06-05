#pragma once

#include <d3d10.h>
#include <d3dx10.h>

//
// Warpper class to simplify texture manipulation. See also CGame::LoadTexture
//
class CTexture
{
protected:
	ID3D10Texture2D* _tex;
	ID3D10ShaderResourceView* _rsview;
	int _width;
	int _height;
public:
	CTexture()
	{
		_tex = NULL;
		_rsview = NULL;
		_width = -1;
		_height = -1;
	}

	CTexture(ID3D10Texture2D* tex, ID3D10ShaderResourceView* rsview)
	{
		this->_tex = tex;
		this->_rsview = rsview;

		D3D10_TEXTURE2D_DESC desc;
		this->_tex->GetDesc(&desc);
		this->_width = desc.Width;
		this->_height = desc.Height;
	}

	ID3D10ShaderResourceView* getShaderResourceView() { return this->_rsview; }

	int getWidth() { return this->_width; }
	int getHeight() { return this->_height; }

    CTexture* Cut(int left, int top, int right, int bottom, ID3D10Device* device)
    {
        D3D10_TEXTURE2D_DESC desc;
        _tex->GetDesc(&desc);

        D3D10_TEXTURE2D_DESC subDesc = desc;
        subDesc.Width = right - left;
        subDesc.Height = bottom - top;
        subDesc.MipLevels = 1;
        subDesc.ArraySize = 1;
        subDesc.Format = desc.Format;
        subDesc.SampleDesc.Count = 1;
        subDesc.SampleDesc.Quality = 0;
        subDesc.Usage = D3D10_USAGE_DEFAULT;
        subDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE;

        ID3D10Texture2D* subTexture = nullptr;
        HRESULT hr = device->CreateTexture2D(&subDesc, nullptr, &subTexture);

        D3D10_BOX sourceRegion;
        sourceRegion.left = left;
        sourceRegion.top = top;
        sourceRegion.front = 0;
        sourceRegion.right = right;
        sourceRegion.bottom = bottom;
        sourceRegion.back = 1;

        device->CopySubresourceRegion(subTexture, 0, 0, 0, 0, _tex, 0, &sourceRegion);

        ID3D10ShaderResourceView* subRsview = nullptr;
        hr = device->CreateShaderResourceView(subTexture, nullptr, &subRsview);

        return new CTexture(subTexture, subRsview);
    }

	~CTexture()
	{
		if (_rsview != NULL) this->_rsview->Release();
		if (_tex != NULL) this->_tex->Release();
	}
};

typedef CTexture* LPTEXTURE;