#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_CORES 4
#define CPU_FREQ 2000

// per thread variable
__thread int per_lcore__lcore_id;

struct lcore_conf {
    pthread_t tid;
    // can only write in fd[1] and read from fd[0]
    int master2slave[2];
    int slave2master[2];
};
struct lcore_conf lcore_conf[MAX_CORES];

void *thread_task(void *arg) {
    pthread_t tid = pthread_self();
    cpu_set_t cpuset;
    int i = 0;
    int m2s, s2m;
    // finds current core id i
    for (; i < MAX_CORES && tid != lcore_conf[i].tid; i ++);
    m2s = lcore_conf[i].master2slave[0];
    s2m = lcore_conf[i].slave2master[1];
    per_lcore__lcore_id = i;
    CPU_ZERO(&cpuset);
    CPU_SET(i, &cpuset);
    pthread_setaffinity_np(tid, sizeof(cpu_set_t), &cpuset);

    //XXX: test code 
    //for(;;) {
    //    for(int j =0;j < CPU_FREQ*3; j++ )
    //        i++;
    //    usleep(1);
    //}

    // thread iteration
    while (1) {
        if (i)
            continue;
    }
    // never exits.

    sleep(100);
    return NULL;
}

int main() {
    int i = 0;
    int ret = 0;
    pthread_t master_tid = pthread_self();
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    for (; i < MAX_CORES; i ++) {
        ret = pipe(lcore_conf[i].master2slave);
        if (ret < 0)
            return -1;
        ret = pipe(lcore_conf[i].master2slave);
        if (ret < 0)
            return -1;
        pthread_create(&lcore_conf[i].tid, NULL,
                thread_task, NULL);
    }
    pthread_setaffinity_np(master_tid, sizeof(cpu_set_t), &cpuset);
    sleep(1000);
    return 0;
}
