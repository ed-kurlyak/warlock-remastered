#include "backbuffer.h"


/*
int Screen_Width = 640;
int Screen_Height = 480;
*/



int Screen_Width = 800;
int Screen_Height = 600;


/*
int Screen_Width = 1280;
int Screen_Height = 720;
*/

/*
int Screen_Width = 320;
int Screen_Height = 200;
*/




MGLDC *windc = NULL;
MGLDC *dibdc = NULL;

Palette GamePalette[256];


void Create_Palette()
{
	
	palette_t pal[256];

	for (int i = 0; i < 256; i++)
	{
		pal[i].red = GamePalette[i].r;
		pal[i].green = GamePalette[i].g;
		pal[i].blue = GamePalette[i].b;
	}

	MGL_setPalette(dibdc, pal, 256, 0);
	MGL_realizePalette(dibdc, 256, 0, false);
	

	/*
	palette_t	pal[256];

	for (int i = 0; i < 256; i++)
	{
		if (i == 0)
		{
			pal[i].red = 0;
			pal[i].green = 0;
			pal[i].blue = 0;
		}
		else
		{
			pal[i].red = 255;
			pal[i].green = 255;
			pal[i].blue = 127;
		}
	}

	MGL_setPalette(dibdc, pal, 256, 0);
	MGL_realizePalette(dibdc, 256, 0, false);
	*/

}

void Create_BackBuffer()
{

//	Screen_Width = 320;
//	Screen_Height = 200;

	pixel_format_t pf;

	MGL_setAppInstance(g_hInst);

	MGL_registerDriver(MGL_PACKED8NAME, PACKED8_driver);

	//��� �������� ������
	MGL_initWindowed("");

	if (!MGL_changeDisplayMode(grWINDOWED))
		MGL_fatalError("Unable to use window mode!");

	if ((windc = MGL_createWindowedDC(g_hWnd)) == NULL)
		MGL_fatalError("Unable to create Windowed DC!");

	MGL_getPixelFormat(windc, &pf);

	if ((dibdc = MGL_createMemoryDC(Screen_Width, Screen_Height, 8, &pf)) ==
		NULL)
		MGL_fatalError("Unable to create Memory DC!");

	// Create_Palette();
}

/*

void Clear_BackBuffer()
{
		MGL_beginDirectAccess();

		char * phd_winptr_my = NULL;

		phd_winptr_my = (char*)dibdc->surface;

		//������� m_BackBuffer (�����)
		for (int x = 0; x < Screen_GetResWidth(); x++)
		{
				for (int y = 0; y < Screen_GetResHeight(); y++)
				{
						int Index = y * Screen_GetResWidth() + x;

						phd_winptr_my[Index + 0] = 0;
				}
		}

}

void Present_BackBuffer()
{
		MGL_endDirectAccess();

		//MGL present back buffer
		HDC hdcScreen = GetDC(g_hWnd);
		MGL_setWinDC(windc, hdcScreen);

		MGL_bitBltCoord(windc, dibdc, 0, 0, Screen_GetResWidth(),
Screen_GetResHeight(), 0, 0, MGL_REPLACE_MODE);

		ReleaseDC(g_hWnd, hdcScreen);

}

*/

void Clear_BackBuffer()
{
	MGL_beginDirectAccess();

	char *phd_winptr_my = NULL;

	phd_winptr_my = (char *)dibdc->surface;

	//������� m_BackBuffer (�����)
	for (int x = 0; x < Screen_Width; x++)
	{
		for (int y = 0; y < Screen_Height; y++)
		{
			int Index = y * Screen_Width + x;

			phd_winptr_my[Index + 0] = 0;
		}
	}
}

void Present_BackBuffer()
{
	MGL_endDirectAccess();

	// MGL present back buffer
	HDC hdcScreen = GetDC(g_hWnd);
	MGL_setWinDC(windc, hdcScreen);

	MGL_bitBltCoord(windc, dibdc, 0, 0, Screen_Width, Screen_Height, 0, 0,
					MGL_REPLACE_MODE);

	ReleaseDC(g_hWnd, hdcScreen);
}

void Delete_BackBuffer()
{
	if (windc)
		MGL_destroyDC(windc);
	if (dibdc)
		MGL_destroyDC(dibdc);

	windc = dibdc = NULL;
}
