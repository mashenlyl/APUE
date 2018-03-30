#include <pwd.h>
#include <stddef.h>
#include <string.h>

struct passwd *
mygetpwnam(const char *name)
{
	struct passwd * ptr;

	setpwent();
	while ((ptr = getpwent()) != NULL)
		if (strcmp(name, ptr->pw_name) == 0)
			break;		/* found a match */
	endpwent();
	return(ptr);	/* ptr is NULL if no mathch found */
}

int
main(void)
{
	if (mygetpwnam("lyl") != NULL)
		printf("found a match\n");
	
	return(0);
}
