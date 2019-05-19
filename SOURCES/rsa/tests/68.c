#include "rsa.h"

int main(void)
{
	unsigned video_seg;
	unsigned video_offset;
	int cursor_pos = 20 * 100 + 20;
	put_cpos(cursor_pos);
	video_offset  = ((int)(cursor_pos / 100)) * 0xa0 - 0xa0;			
	video_offset += ((int)(cursor_pos % 100)) *    2 -    2; 

	video_seg = (is_color_video() == VIDEO_MONO) ? 0xB000 : 0xB800;
	change_video_attribute(video_seg, video_offset, _$hcolor, 10);

	return 0;
}
