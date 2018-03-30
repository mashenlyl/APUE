#include "apue.h"
#include "apue_db.h"
#include <fcntl.h>

int
main(void)
{
	DBHANDLE	db;

	if ((db = db_open("mydb", O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) == NULL)
		err_sys("db_open error");

	if (db_store(db, "Alpha", "data1", DB_INSERT) != 0)
		err_quit("db_store eror for alpha");
	if (db_store(db, "beta", "Data for beta", DB_INSERT) != 0)
		err_quit("db_store eror for beta");
	if (db_store(db, "gamma", "record3", DB_INSERT) != 0)
		err_quit("db_store eror for gamma"); 
	if (db_store(db, "gamma", "replace", DB_REPLACE) != 0)
		err_quit("db_store eror for gamma"); 
	//if (db_delete(db, "gamma") != 0)
	//	err_quit("db_delete eror for gamma"); 
	db_close(db);
	exit(0);
}
