#define CPP_TEST

#include <stdio.h>

#ifdef CPP_TEST
#include "threadpool.hpp"
#else
#include "threadpool.h"
#endif

void testFun(void* arg){
    printf("i = %d\n", *(int *)arg);
}

int main(){
#ifdef CPP_TEST
    ThreadPool *pool = new ThreadPool(1000, 2000);
#else
    nThreadPool *pool = (nThreadPool*)malloc(sizeof(nThreadPool));
    int ret = nThreadPoolCreate(pool, 1000);
    if (ret != 1){
        perror("线程池初始化失败");
        printf("ret = %d\n", ret);
        return -1;
    }
#endif

    printf("线程池初始化成功\n");
    int i = 0;
    for (i = 0; i < 1000; ++i) {
#ifdef CPP_TEST
        pool->pushJob(testFun, &i, sizeof(int));
#else
        nThreadPush(pool, testFun, &i, sizeof(int));
#endif
    }

#ifdef CPP_TEST
    delete pool;
#else
    nThreadPoolDestroy(pool);
    free(pool);
#endif

    return 0;
}
