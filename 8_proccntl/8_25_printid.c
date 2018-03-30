#include "apue.h"

int
main(void)
{
	printf("real uid = %d, effictive uid = %d\n", getuid(), geteuid());
	exit(0);
}
