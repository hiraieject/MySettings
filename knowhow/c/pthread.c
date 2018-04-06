
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include <pthread.h>

static void *noname_thread(void *pParam);
static pthread_t noname_thread_id = -1;
volatile bool thread_exit = false;

pthread_mutex_t		noname_mutex = PTHREAD_MUTEX_INITIALIZER;

static void *
noname_thread(void *pParam)
{
	int r;

	while(thread_exit) {

		// mutex sync
		pthread_mutex_lock(&noname_mutex);
		pthread_mutex_unlock(&noname_mutex);

		// mutex async
		if ((r=pthread_mutex_trylock(&noname_mutex)) != 0) {
			if (r == EBUSY) {
				// mutex is busy
			} else {
				// lock fail
			}
		} else {
			// lock success
		}
		pthread_mutex_unlock(&noname_mutex);

		sleep(1);
	}
	
#ifndef PTHREAD_USE_JOIN
	// ����åɤΥ꥽�������������
	pthread_detach(pthread_self());
	//  �� detache �򤹤�ʤ顢�ƤǤ� join ������
#endif

	// ����åɽ�λ
	pthread_exit(NULL);
	return NULL;
}

static void
noname_parent_func(void)
{
	// create thread
	{
		thread_exit = false;
		pthread_create(&noname_thread_id, NULL, noname_thread, (void *)0);
	}

	// mutex
	{
		pthread_mutex_lock(&noname_mutex);
		pthread_mutex_unlock(&noname_mutex);
	}

	// destroy thread
	{
		thread_exit = true;

#ifdef PTHREAD_USE_JOIN
		// thread��λ���Թ礻
		pthread_join(noname_thread_id, NULL);
		//  �� join �򤹤�ʤ顢detache ������
#endif
	}
	
}
	
