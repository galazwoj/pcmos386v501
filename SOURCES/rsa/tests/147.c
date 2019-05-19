#include "rsa.h"

//
//	if either row or column is reported to be 0 then mouse is reported as not present
//

char *status[] = { "not present", "present" };

int main(void)
{
	int button_status;
	int rows, columns;
	printf("mouse status: %s\n", status[read_mouse(0, &button_status, &rows, &columns)]);
	printf("button: %d, row: %d, column: %d\n", button_status, rows, columns);	
	return 0;
}
