#ifndef _WAVE_CTRL_EX_H_
#define _WAVE_CTRL_EX_H_

class c_ecg_wave_ctrl : public c_wave_ctrl
{
protected:
	virtual void on_paint(void);
	void draw_grid();
};

///////////////////////////////////////////////////

#include "../include/GuiLite.h"
class c_bitmap_wave_ctrl : public c_wave_ctrl
{
public:
	void set_bitmap(IMAGE_LIST type) { m_bitmap_type = type; }
protected:
	virtual void on_paint(void);
private:
	IMAGE_LIST m_bitmap_type;
};

#endif /* _WAVE_CTRL_EX_H_ */
