/*
 * In real Xeon processor multi lcore test, using mutex causes kernel
 * to run much more time than sync method.
 * So my suggestions according to thread sync is to use sync method as long as
 * possible.
 * And in terms of specifying 'volatile' before int a, it does no good in
 * thread synchronization. Do not use it.
 *
 * And I have used this to test on my i7 core. Result seem to overwhelm the
 * Xeon's result by an order of magnitude. (i7 6700 vs. Xeon5 2630 v4)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <inttypes.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>

#define MAX_TRY 50000000

struct pdata {
	int i;
	pid_t pid;      //print by %d
	pid_t tid;      //print by %d
	pthread_t ptid; //print by %lu
};

int a = 0;
pthread_mutex_t mutex;

//Current best version of thread synchronization method.
void *foo~(void *args)
{
	struct pdata *data = (struct pdata *)args;
	int i = 0;
	data->pid = getpid();
	data->tid = syscall(SYS_gettid);
	data->ptid = pthread_self();

	while (a < MAX_TRY) {
		__sync_fetch_and_add (&a, 1);
		if (unlikely(a > MAX_TRY)) {
			__sync_fetch_and_sub (&a, 1);
			break;
		}
		if (unlikely(a == MAX_TRY)) {
			//Do something while finished.
		}
		i ++;
	}

	printf("from p%lu : a = %d\n", data->ptid, a);
	printf("from p%lu : local i = %d\n", data->ptid, 1);
	return (void *)data;
}

//Past version.
void *foo(void *args)
{
	struct pdata *data = (struct pdata *)args;
	int i = 0;
	data->pid = getpid();
	data->tid = syscall(SYS_gettid);
	data->ptid = pthread_self();

	for (; i < 10000000; i ++) {
		pthread_mutex_lock (&mutex);
		a ++;
		pthread_mutex_unlock (&mutex);
		//__sync_fetch_and_add (&a, 1);
	}
	printf("from p%lu : a = %d\n", data->ptid, a);
	return (void *)data;
}

int ss(int num)
{
	int i = 0;
	int ret = 0;
	pthread_t *tids = malloc(sizeof(pthread_t) * num);
	for (; i < num; i ++) {
		struct pdata *data = (struct pdata *) malloc(sizeof(struct pdata));
		data->i = i;
		ret = pthread_create(&tids[i], NULL, foo, (void*)data);
		if (ret)
			perror("create pthread error.\n");
	}
	for (i = 0; i < num; i ++) {
		struct pdata *status;
		ret = pthread_join(tids[i], (void *)&status);
		if (ret)
			perror ("pthread join error.\n");
		else
			free (status);
	}
	free (tids);
}

int main()
{
	mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	ss(5);
	pthread_mutex_destroy(&mutex);
	printf("atlast: %d\n", a);
	return 0;
}
