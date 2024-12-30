#ifndef __CLAYON3DS_RENDERER_H
#define __CLAYON3DS_RENDERER_H

#include <citro3d.h>

#include <clay.h>

void Renderer_clayError(Clay_ErrorData errorData);
Clay_Dimensions Renderer_clayMeasureText(Clay_String* string, Clay_TextElementConfig* config);
void Renderer_clayRender(C3D_RenderTarget* renderTarget, Clay_Dimensions dimensions, Clay_RenderCommandArray renderCommands);

#endif // __CLAYON3DS_RENDERER_H
