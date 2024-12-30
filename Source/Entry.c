#include <stdlib.h>

#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>

#define CLAY_IMPLEMENTATION
#include <clay.h>

#include "Renderer.h"
#include "Theme.h"

#define DISPLAY_TRANSFER_FLAGS GX_TRANSFER_FLIP_VERT(0) \
	| GX_TRANSFER_OUT_TILED(0) \
	| GX_TRANSFER_RAW_COPY(0) \
	| GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) \
	| GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) \
	| GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO)

extern Clay_RenderCommandArray bottomLayout();
extern Clay_RenderCommandArray topLayout();

s32 main(void)
{
  // Lower the maximum number of elements the layout engine can handle, as we only have 16MB of RAM.
  Clay_SetMaxElementCount(1024);
  u64 clayMemSize = Clay_MinMemorySize();
  Clay_Arena clayArena = Clay_CreateArenaWithCapacityAndMemory(clayMemSize, malloc(clayMemSize));
	Clay_SetMeasureTextFunction(Renderer_clayMeasureText);
  Clay_Initialize(clayArena, (Clay_Dimensions){ 0, 0 }, (Clay_ErrorHandler) { Renderer_clayError });

	gfxInitDefault();

	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bottom = C3D_RenderTargetCreate(240, 320, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetOutput(top, GFX_TOP, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);
	C3D_RenderTargetSetOutput(bottom, GFX_BOTTOM, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);

	u32 clearColor = C2D_Color32(0, 0, 0, 255);
	u64 previousTime = osGetTime();

	while (aptMainLoop())
	{
    u64 currentTime = osGetTime();
		float deltaTime = (currentTime - previousTime) / 1000.f;
		previousTime = currentTime;

		Theme_updateTransition(deltaTime);

		// ===========================
		// Input Handling
		// ===========================

		// Do the scroll containers update here because it works well with our interaction mode.
		Clay_UpdateScrollContainers(true, (Clay_Vector2){ 0.f, 0.f }, deltaTime);

  	hidScanInput();
		bool isTouching = hidKeysHeld() & KEY_TOUCH;
		touchPosition touch;
    hidTouchRead(&touch);

		if (isTouching)
    {
			Clay_SetPointerState((Clay_Vector2) { touch.px, touch.py }, true);
    }
    else
    {
			Clay_SetPointerState((Clay_Vector2) { -1, -1 }, false);
    }

		// ===========================
		// Rendering
		// ===========================

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		// ===================
		// Top Screen
		// ===================

		C2D_TargetClear(top, clearColor);
		C2D_SceneBegin(top);

		Clay_Dimensions dimensions = (Clay_Dimensions){ 400, 240 };
		Clay_SetLayoutDimensions(dimensions);
		Clay_RenderCommandArray topCommands = topLayout();
		Renderer_clayRender(top, dimensions, topCommands);

		// ===================
		// Bottom Screen
		// ===================

		C2D_TargetClear(bottom, clearColor);
		C2D_SceneBegin(bottom);

		dimensions = (Clay_Dimensions){ 320, 240 };
		Clay_SetLayoutDimensions(dimensions);
		Clay_RenderCommandArray bottomCommands = bottomLayout();
		Renderer_clayRender(bottom, dimensions, bottomCommands);

		if (isTouching)
		{
			// When the user is touching the display, show an indicator that follows the
			// coordinates of the input.
			C2D_DrawCircleSolid(touch.px, touch.py, 0.f, 3.f, C2D_Color32(180, 180, 180, 100));
		}

    C3D_FrameEnd(0);
  }

  C2D_Fini();
	C3D_Fini();

	gfxExit();
  return 0;
}
