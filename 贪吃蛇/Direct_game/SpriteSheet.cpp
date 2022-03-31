#include"SpriteSheet.h"

SpriteSheet::SpriteSheet(LPCWSTR filename, Graphics * gfx)
{
	graphics = gfx;
	bmp = NULL;
	HRESULT hr;
	IWICImagingFactory * wicFactory = NULL;

	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);


	IWICBitmapDecoder * wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	if (hr != S_OK)
		return;

	IWICBitmapFrameDecode * wicFrame = NULL;
	hr = wicDecoder -> GetFrame(0, &wicFrame);


	IWICFormatConverter * wicCoverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicCoverter);


	hr = wicCoverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom);


	graphics->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicCoverter,
		NULL,
		&bmp);

	if (wicFactory)wicFactory->Release();
	if (wicDecoder)wicDecoder->Release();
	if (wicCoverter)wicCoverter->Release();
	if (wicFrame)wicFrame->Release();

	if (bmp != NULL) 
	{
		spriteWidth = (int)bmp->GetSize().width;
		spriteHeight = (int)bmp->GetSize().height;
	}
	spriteAccross_W = 1;
	spriteAccross_H = 1;

}

SpriteSheet::SpriteSheet(LPCWSTR filename, Graphics * gfx, int width, int height) :
	SpriteSheet(filename, gfx)
{
	spriteWidth = width;
	spriteHeight = height;
	spriteAccross_W = (int)(bmp->GetSize().width / spriteWidth);
	spriteAccross_H = (int)(bmp->GetSize().height / spriteHeight);
}

SpriteSheet::~SpriteSheet()
{
	if (bmp)bmp->Release();
}

void SpriteSheet::Draw()//�����ߴ�
{
	graphics->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height),//Ŀ��
		1.0f,//͸����

		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,//���ٽ���ֵ
		D2D1::RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height));//Դ
}

void SpriteSheet::Draw(int index, int x, int y, float zoom)
{
	D2D_RECT_F src = D2D1::RectF(
		(float)((index % spriteAccross_W) * spriteWidth),
		(float)((index / spriteAccross_H) * spriteHeight),
		(float)((index % spriteAccross_W) * spriteWidth + spriteWidth),
		(float)((index / spriteAccross_H) * spriteHeight) + spriteHeight);

	D2D_RECT_F dest = D2D1::RectF(
		(float)x,
		(float)y,
		(float)(x + spriteWidth * zoom),
		(float)(y + spriteHeight * zoom)
	);

	graphics->GetRenderTarget()->DrawBitmap(
		bmp,
		dest,//Ŀ��
		1.0f,//͸����

		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,//���ٽ���ֵ
		src);//Դ
}

void SpriteSheet::Draw(int index, int x, int y, int width, int height)
{
	D2D_RECT_F src = D2D1::RectF(
		(float)((index % spriteAccross_W) * spriteWidth),
		(float)((index / spriteAccross_H) * spriteHeight),
		(float)((index % spriteAccross_W) * spriteWidth + spriteWidth),
		(float)((index / spriteAccross_H) * spriteHeight) + spriteHeight);

	D2D_RECT_F dest = D2D1::RectF(
		(float)x,
		(float)y,
		(float)(x + width),
		(float)(y + height)
	);

	graphics->GetRenderTarget()->DrawBitmap(
		bmp,
		dest,//Ŀ��
		1.0f,//͸����

		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,//���ٽ���ֵ
		src);//Դ
}
