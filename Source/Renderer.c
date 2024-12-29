#include "Renderer.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>

#define GET_TEXT_SCALE(fs) ((float)fs / 30.f)
#define CLAY_COLOR_TO_C2D(cc) C2D_Color32((u8)cc.r, (u8)cc.g, (u8)cc.b, (u8)cc.a)

void clayError(Clay_ErrorData errorData)
{
  printf("clay_error: %s\n", errorData.errorText.chars);
	// __builtin_trap();
}

Clay_Dimensions clayMeasureText(Clay_String* string, Clay_TextElementConfig* config)
{
	float scale = GET_TEXT_SCALE(config->fontSize);

	// TODO: re-use the same buffer for performance.
  char* cloned = (char*)malloc(string->length + 1);
  memcpy(cloned, string->chars, string->length);
	cloned[string->length] = '\0';

	C2D_Text text;
	C2D_TextBuf buffer = C2D_TextBufNew(string->length);
	C2D_TextParse(&text, buffer, cloned);
	C2D_TextOptimize(&text);

	float width = 0.f;
	float height = 0.f;
	C2D_TextGetDimensions(&text, scale, scale, &width, &height);

	C2D_TextBufDelete(buffer);
	free(cloned);
	return (Clay_Dimensions){ width, height };
}

void clayRender(C3D_RenderTarget* renderTarget, Clay_Dimensions dimensions, Clay_RenderCommandArray renderCommands)
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
				C2D_DrawRectSolid(bbox.x, bbox.y, 0.f, bbox.width, bbox.height, CLAY_COLOR_TO_C2D(config->color));
        break;
      }
			case CLAY_RENDER_COMMAND_TYPE_BORDER:
			{
        Clay_BorderElementConfig* config = renderCommand->config.borderElementConfig;
				
				if (config->left.width > 0)
				{
					C2D_DrawRectSolid(bbox.x, bbox.y, 0.f, config->left.width, bbox.height, CLAY_COLOR_TO_C2D(config->left.color));
				}
				if (config->right.width > 0)
				{
					C2D_DrawRectSolid(bbox.x + bbox.width - config->right.width, bbox.y, 0.f, config->right.width, bbox.height, CLAY_COLOR_TO_C2D(config->right.color));
				}
				if (config->top.width > 0)
				{
					C2D_DrawRectSolid(bbox.x, bbox.y, 0.f, bbox.width, config->top.width, CLAY_COLOR_TO_C2D(config->top.color));
				}
				if (config->bottom.width > 0)
				{
					C2D_DrawRectSolid(bbox.x, bbox.y + bbox.height - config->bottom.width, 0.f, bbox.width, config->bottom.width, CLAY_COLOR_TO_C2D(config->bottom.color));
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
 				C2D_TextBuf buffer = C2D_TextBufNew(string.length);
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
