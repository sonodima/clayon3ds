#include "Renderer.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>

#define GET_TEXT_SCALE(fs) ((float)fs / 30.f)
#define CLAY_COLOR_TO_C2D(cc) C2D_Color32((u8)cc.r, (u8)cc.g, (u8)cc.b, (u8)cc.a)
#define DEG_TO_RAD(value) ((value) * (M_PI / 180.f))

void drawArc(float cx, float cy, float radius, float angs, float ange, float thickness, u32 color)
{
  u32 segments = 8;
  float step = (ange - angs) / segments;

	float angle = DEG_TO_RAD(angs);
  float x1 = cx + radius * cos(angle);
  float y1 = cy + radius * sin(angle);

  for (u32 i = 0; i <= segments; ++i)
	{
  	angle = DEG_TO_RAD(angs + i * step);
    float x2 = cx + radius * cos(angle);
    float y2 = cy + radius * sin(angle);

    C2D_DrawLine(x1, y1, color, x2, y2, color, thickness, 0.f);
    x1 = x2;
    y1 = y2;
  }
}

void drawArcSolid(float cx, float cy, float radius, float angs, float ange, u32 color)
{
  u32 segments = 8;
  float step = (ange - angs) / segments;

  float angle = DEG_TO_RAD(angs);
  float x1 = cx + radius * cos(angle);
  float y1 = cy + radius * sin(angle);

  for (u32 i = 0; i <= segments; ++i)
  {
    angle = DEG_TO_RAD(angs + i * step);
    float x2 = cx + radius * cos(angle);
    float y2 = cy + radius * sin(angle);

    C2D_DrawTriangle(cx, cy, color, x1, y1, color, x2, y2, color, 0.f);
    x1 = x2;
    y1 = y2;
  }
}

void Renderer_clayError(Clay_ErrorData errorData)
{
  printf("clay_error: %s\n", errorData.errorText.chars);
	// __builtin_trap();
}

Clay_Dimensions Renderer_clayMeasureText(Clay_String* string, Clay_TextElementConfig* config)
{
	float scale = GET_TEXT_SCALE(config->fontSize);

	// TODO: re-use the same buffer for performance.
  char* cloned = (char*)malloc(string->length + 1);
  memcpy(cloned, string->chars, string->length);
	cloned[string->length] = '\0';

	C2D_Text text;
	C2D_TextBuf buffer = C2D_TextBufNew(string->length + 1);
	C2D_TextParse(&text, buffer, cloned);
	C2D_TextOptimize(&text);

	float width = 0.f;
	float height = 0.f;
	C2D_TextGetDimensions(&text, scale, scale, &width, &height);

	C2D_TextBufDelete(buffer);
	free(cloned);
	return (Clay_Dimensions){ width, height };
}

void Renderer_clayRender(C3D_RenderTarget* renderTarget, Clay_Dimensions dimensions, Clay_RenderCommandArray renderCommands)
{
  for (u32 i = 0; i < renderCommands.length; i++)
  {
    Clay_RenderCommand* renderCommand = Clay_RenderCommandArray_Get(&renderCommands, i);
    Clay_BoundingBox bbox = renderCommand->boundingBox;

    switch (renderCommand->commandType)
    {
      case CLAY_RENDER_COMMAND_TYPE_RECTANGLE:
      {
        Clay_RectangleElementConfig* config = renderCommand->config.rectangleElementConfig;
				u32 color = CLAY_COLOR_TO_C2D(config->color);
				float tlr = config->cornerRadius.topLeft;
				float trr = config->cornerRadius.topRight;
				float brr = config->cornerRadius.bottomRight;
				float blr = config->cornerRadius.bottomLeft;

				if (tlr <= 0.f && trr <= 0.f && brr <= 0.f && blr <= 0.f)
				{
					// If no rounding is used, fall back to the faster, simpler, rectangle drawing.
 					C2D_DrawRectSolid(bbox.x, bbox.y, 0.f, bbox.width, bbox.height, color);
				}
				else
				{
					// Make sure that the rounding is not bigger than half of any side.
					float max = fminf(bbox.width, bbox.height) / 2.f;
					tlr = fminf(tlr, max);
					trr = fminf(trr, max);
					brr = fminf(brr, max);
					blr = fminf(blr, max);

					// Holy Moly!
					// This is cryptic as fuck but it works well.
					float lx = bbox.x;
					float ly1 = bbox.y + tlr;
					float ly2 = bbox.y + bbox.height - blr;
					float ty = bbox.y;
					float tx1 = bbox.x + tlr;
					float tx2 = bbox.x + bbox.width - trr;
					float rx = bbox.x + bbox.width;
					float ry1 = bbox.y + trr;
					float ry2 = bbox.y + bbox.height - brr;
					float by = bbox.y + bbox.height;
					float bx1 = bbox.x + blr;
					float bx2 = bbox.x + bbox.width - brr;

					C2D_DrawTriangle(lx, ly1, color, bbox.x + tlr, ly1, color, lx, ly2, color, 0.f);
					C2D_DrawTriangle(bbox.x + blr, ly2, color, bbox.x + tlr, ly1, color, lx, ly2, color, 0.f);
					C2D_DrawTriangle(tx1, ty, color, tx1, bbox.y + tlr, color, tx2, ty, color, 0.f);
					C2D_DrawTriangle(tx2, bbox.y + trr, color, tx1, bbox.y + tlr, color, tx2, ty, color, 0.f);
					C2D_DrawTriangle(rx, ry1, color, bbox.x + bbox.width - trr, ry1, color, rx, ry2, color, 0.f);
					C2D_DrawTriangle(bbox.x + bbox.width - brr, ry2, color, bbox.x + bbox.width - trr, ry1, color, rx, ry2, color, 0.f);
					C2D_DrawTriangle(bx1, by, color, bx1, bbox.y + bbox.height - blr, color, bx2, by, color, 0.f);
					C2D_DrawTriangle(bx2, bbox.y + bbox.height - brr, color, bx1, bbox.y + bbox.height - blr, color, bx2, by, color, 0.f);

					C2D_DrawTriangle(tx2, ry1, color, tx1, ly1, color, bx2, ry2, color, 0.f);
					C2D_DrawTriangle(bx1, ly2, color, tx1, ly1, color, bx2, ry2, color, 0.f);

					drawArcSolid(bbox.x + tlr, bbox.y + tlr, tlr, 180.f, 270.f, color);
					drawArcSolid(bbox.x + bbox.width - trr, bbox.y + trr, trr, 270.f, 360.f, color);
					drawArcSolid(bbox.x + blr, bbox.y + bbox.height - blr, blr, 90.f, 180.f, color);
					drawArcSolid(bbox.x + bbox.width - brr, bbox.y + bbox.height - brr, brr, 0.f, 90.f, color);
				}

				break;
      }
			case CLAY_RENDER_COMMAND_TYPE_BORDER:
			{
        Clay_BorderElementConfig* config = renderCommand->config.borderElementConfig;
				u32 tc = CLAY_COLOR_TO_C2D(config->top.color);
				u32 lc = CLAY_COLOR_TO_C2D(config->left.color);
				u32 rc = CLAY_COLOR_TO_C2D(config->right.color);
				u32 bc = CLAY_COLOR_TO_C2D(config->bottom.color);
				float lw = config->left.width;
				float tw = config->top.width;
				float rw = config->right.width;
				float bw = config->bottom.width;
				// Make sure that the rounding is not bigger than half of any side.
				float max = fminf(bbox.width, bbox.height) / 2.f;
				float tlr = fminf(config->cornerRadius.topLeft, max);
				float trr = fminf(config->cornerRadius.topRight, max);
				float brr = fminf(config->cornerRadius.bottomRight, max);
				float blr = fminf(config->cornerRadius.bottomLeft, max);

				if (config->top.width > 0.f)
				{
					C2D_DrawRectSolid(bbox.x + tlr, bbox.y, 0.f, bbox.width - tlr - trr, tw, tc);
				}
				if (config->left.width > 0.f)
				{
					C2D_DrawRectSolid(bbox.x, bbox.y + tlr, 0.f, lw, bbox.height - tlr - blr, lc);
				}
				if (config->right.width > 0.f)
				{
					C2D_DrawRectSolid(bbox.x + bbox.width - rw, bbox.y + trr, 0.f, rw, bbox.height - trr - brr, rc);
				}
				if (config->bottom.width > 0.f)
				{
					C2D_DrawRectSolid(bbox.x + brr, bbox.y + bbox.height - bw, 0.f, bbox.width - blr - brr, bw, bc);
				}
				if (tlr > 0)
				{
					drawArc(bbox.x + tlr, bbox.y + tlr, tlr - tw / 2.f, 180.f, 270.f, tw, tc);
				}
				if (trr > 0)
				{
					drawArc(bbox.x + bbox.width - trr, bbox.y + trr, trr - tw / 2.f, 270.f, 360.f, tw, tc);
				}
				if (blr > 0)
				{
					drawArc(bbox.x + blr, bbox.y + bbox.height - blr, blr - bw / 2.f, 90.f, 180.f, bw, bc);
				}
				if (brr > 0)
				{
					drawArc(bbox.x + bbox.width - brr, bbox.y + bbox.height - brr, brr - bw / 2.f, 0.f, 90.f, bw, bc);
				}

        break;
			}
			case CLAY_RENDER_COMMAND_TYPE_TEXT:
			{
				Clay_TextElementConfig* config = renderCommand->config.textElementConfig;
				float scale = GET_TEXT_SCALE(config->fontSize);

				Clay_String string = renderCommand->text;
				// TODO: re-use the same buffer for performance.
        char* cloned = (char*)malloc(string.length + 1);
        memcpy(cloned, string.chars, string.length);
				cloned[string.length] = '\0';

				C2D_Text text;
				// TODO: re-use the same buffer for performance.
 				C2D_TextBuf buffer = C2D_TextBufNew(string.length + 1);
				C2D_TextParse(&text, buffer, cloned);
				C2D_TextOptimize(&text);
				C2D_DrawText(&text, C2D_WithColor, bbox.x, bbox.y, 0.f, scale, scale, CLAY_COLOR_TO_C2D(config->textColor));

				C2D_TextBufDelete(buffer);
				free(cloned);
				break;
			}
			case CLAY_RENDER_COMMAND_TYPE_IMAGE:
			{
				// TODO: test this
				C2D_Image image = *(C2D_Image*)renderCommand->config.imageElementConfig->imageData;
				C2D_DrawParams params = (C2D_DrawParams)
				{
					.pos = { .x = bbox.x, .y = bbox.y, .w = bbox.width, .h = bbox.height }
				};

				C2D_DrawImage(image, &params, NULL);
				break;
			}
			case CLAY_RENDER_COMMAND_TYPE_SCISSOR_START:
			{
				C2D_SceneBegin(renderTarget);

				// Stupid ass coordinate system.
				C3D_SetScissor(GPU_SCISSOR_NORMAL,
										   dimensions.height - bbox.height - bbox.y,
											 dimensions.width - bbox.width - bbox.x,
											 bbox.height + bbox.y,
											 dimensions.width - bbox.x);

				break;
			}
			case CLAY_RENDER_COMMAND_TYPE_SCISSOR_END:
			{
				C3D_SetScissor(GPU_SCISSOR_DISABLE, 0, 0, 0, 0);
				break;
			}
      default:
      {
  			printf("clay_command: command [%d] has not been implemented yet\n", (s32)renderCommand->commandType);
				// __builtin_trap();
      }
    }
  }
}
