#include "cimgui_msgbox.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/param.h>

CIMGUI_API int MessageBox( HWND hWnd, const char* text, const char* caption, unsigned int type)
{
	if(hWnd == NULL)
		hWnd = igGetCurrentWindow();

	const char** types   = MB_TYPE[(type & MB_TYPEMASK) >> 0];
	int num_buttons      = MB_TYPE_NUM_BUTTONS[(type & MB_TYPEMASK) >> 0];
	struct mb_icon* icon = &MB_ICON[(type & MB_ICONMASK) >> 4];
	static int selected = 0;
	static bool dontaskagain = false;
  	int index = 0;
	bool open = true;
	ImVec2 text_size,half,pos,window_size;
	const ImGuiID id = igGetID_Str(caption);
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	
	if(igBegin(caption, &open, ImGuiWindowFlags_AlwaysAutoResize))
	{
		if(dontaskagain && selected != 0)
		{
			igCloseCurrentPopup();
			index = selected;
		}
		else
		{
			igSpacing();
			igAlignTextToFramePadding();
			igSetCursorPosX(120.0f);
			if(icon != NULL)
			{
			}
			igTextWrapped("%s", text);
			igSpacing();
			igCheckbox("Don't ask me again", &dontaskagain);
			igSeparator();
			igSpacing();

			ImVec2 size = { .x = 100.0f, .y = 0.0f };
			int count;
			for(count = 0; types[count] != NULL; count++)
			{
				if(igButton( types[count], size))
				{
					index = count + 1;
					igCloseCurrentPopup();
					break;
				}
				igSameLine( 0.0f, 20.0f);
			}

			for(int i = (MAX(3,num_buttons) - 1) - count; i >= 0; i--)
			{
				ImVec2 pos = hWnd->DC.CursorPos;
				pos.y += hWnd->DC.CurrLineTextBaseOffset - style.FramePadding.y;

				ImVec2 size_dummy;
				igCalcItemSize(&size_dummy,size, style.FramePadding.x * 2.0f,  style.FramePadding.y * 2.0f);
				const ImRect* bb = ImRect_ImRect_Float(pos.x, pos.y, pos.x + size_dummy.x, pos.y + size_dummy.y);
				igItemSize_Vec2(size_dummy, style.FramePadding.y);
				igItemAdd(*bb, id, bb, 0);
				igSameLine( 0.0f, 20.0f);
			}
			if(dontaskagain)
				selected = index;
		}
		igEnd();
	}
	return index;
}

