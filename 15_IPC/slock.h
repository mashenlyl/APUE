struct slock {
	sem_t	*semp;
	char	name[1024];
};
