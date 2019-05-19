#include "rsa.h"

char *video_name[] = {"VGA", "EGA", "CGA", "HGC", "NONE" };

int main(void)
{
	int n;
	printf("%s\n", ((n = get_video_type()) <= 4) ? video_name[n] : "unknown");
	return 0;
}
