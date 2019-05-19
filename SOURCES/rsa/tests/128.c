#include "rsa.h"

int main(void)
{
	printf("Is color video present? %s\n", (is_color_video() == VIDEO_COLOR) ? "YES" :  "NO");
	printf("Is color video present? %s\n", (is_color_video() ==  VIDEO_MONO) ?  "NO" : "YES");
	return 0;
}
