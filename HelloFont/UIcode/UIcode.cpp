﻿#define GUILITE_ON  //Do not define this macro once more!!!
#include "GuiLite.h"
#include <stdlib.h>
#include <string.h>

const int UI_WIDTH = 1400;
const int UI_HEIGHT = 580;

//////////////////////// define widgets & map message ////////////////////////
enum WND_ID
{
	ID_DESKTOP = 1,
	ID_BUTTON
};

#define FONT_SIZE	57
#define START_X		300
#define START_Y		20

#ifdef WIN32
//For Visual studio, one chinese character need 3 UTF-8 bytes
static const char* s_text = "\xe6\x9c\x9d\xe8\xbe\x9e\xe7\x99\xbd\xe5\xb8\x9d\xe5\xbd\xa9\xe4\xba\x91\xe9\x97\xb4\xe5\x8d\x83\xe9\x87\x8c\xe6\xb1\x9f\xe9\x99\xb5\xe4\xb8\x80\xe6\x97\xa5\xe8\xbf\x98\xe4\xb8\xa4\xe5\xb2\xb8\xe7\x8c\xbf\xe5\xa3\xb0\xe5\x95\xbc\xe4\xb8\x8d\xe4\xbd\x8f\xe8\xbd\xbb\xe8\x88\x9f\xe5\xb7\xb2\xe8\xbf\x87\xe4\xb8\x87\xe9\x87\x8d\xe5\xb1\xb1";
#else
//For Unix, all chinese charaters would be encoded in UTF-8 perfectly.
static const char* s_text = "朝辞白帝彩云间千里江陵一日还两岸猿声啼不住轻舟已过万重山";
#endif

class c_myUI : public c_wnd
{
	virtual void on_init_children()
	{
		c_button* button = (c_button*)get_wnd_ptr(ID_BUTTON);
		button->set_on_click((WND_CALLBACK)&c_myUI::on_clicked);
	}
	virtual void on_paint(void)
	{
		c_rect rect;
		get_screen_rect(rect);
		c_image::draw_image(m_surface, m_z_order, c_theme::get_image(IMAGE_CUSTOM1), rect.m_left, rect.m_top);
	}
	void on_clicked(int ctrl_id, int param)
	{
		c_rect rect;
		get_screen_rect(rect);
		c_image::draw_image(m_surface, m_z_order, c_theme::get_image(IMAGE_CUSTOM1), rect.m_left, rect.m_top);

		char one_word[4];
		const char* tmp = s_text;
		for (int x = 0; x < 4; x++)
			for (int y = 0; y < 7; y++)
			{
				memset(one_word, 0, sizeof(one_word));
				memcpy(one_word, tmp, 3);
				c_word::draw_string(m_surface, m_z_order, one_word, (START_X - x * FONT_SIZE), (START_Y + y * FONT_SIZE), c_theme::get_font(FONT_DEFAULT), GL_RGB(0, 0, 0), GL_ARGB(0, 0, 0, 0));
				thread_sleep(500);
				tmp += 3;
			}
	}
};

//////////////////////// layout UI ////////////////////////
static c_myUI s_myUI;
static c_button	s_button;

static WND_TREE s_myUI_children[] =
{
	{(c_wnd*)&s_button, ID_BUTTON, "PLAY", 0, 540, 150, 40, NULL},
	{ NULL,0,0,0,0,0,0 }
};

//////////////////////// start UI ////////////////////////
extern const BITMAP_INFO background_bmp;
extern const LATTICE_FONT_INFO KaiTi_33B;
static c_display* s_display;
void load_resource()
{
	c_theme::add_image(IMAGE_CUSTOM1, &background_bmp);
	//for button
	c_theme::add_font(FONT_DEFAULT, &KaiTi_33B);
	c_theme::add_color(COLOR_WND_FONT, GL_RGB(255, 255, 255));
	c_theme::add_color(COLOR_WND_NORMAL, GL_RGB(59, 75, 94));
	c_theme::add_color(COLOR_WND_PUSHED, GL_RGB(33, 42, 53));
	c_theme::add_color(COLOR_WND_FOCUS, GL_RGB(43, 118, 219));
	c_theme::add_color(COLOR_WND_BORDER, GL_RGB(46, 59, 73));
}

void create_ui(void* phy_fb, int screen_width, int screen_height, int color_bytes)
{
	load_resource();
	c_surface surface = c_surface(UI_WIDTH, UI_HEIGHT, color_bytes, Z_ORDER_LEVEL_0);
	s_display = new c_display(phy_fb, screen_width, screen_height, &surface);

	s_myUI.set_surface(&surface);
	s_myUI.connect(NULL, ID_DESKTOP, 0, 0, 0, UI_WIDTH, UI_HEIGHT, s_myUI_children);
	s_myUI.show_window();

	while(1)
	{
		thread_sleep(1000000);
	}
}

//////////////////////// interface for all platform ////////////////////////
void startHelloFont(void* phy_fb, int width, int height, int color_bytes)
{
	create_ui(phy_fb, width, height, color_bytes);
}

void sendTouch2HelloFont(int x, int y, bool is_down)
{
	is_down ? s_myUI.on_touch(x, y, TOUCH_DOWN) : s_myUI.on_touch(x, y, TOUCH_UP);
}

void* getUiOfHelloFont(int* width, int* height, bool force_update)
{
	return s_display->get_updated_fb(width, height, force_update);
}

int captureUiOfHelloFont()
{
	return s_display->snap_shot("snap_short.bmp");
}