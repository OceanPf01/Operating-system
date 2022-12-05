#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

int count = 0;
sem_t sem;
clock_t start1, end1, start2, end2, s, e, s1, e1, s2, e2;
double time_use1, time_use2, time_th1, time_th2, time_th3;

void *thread_1(void *arg) {
    FILE* fp1 = fopen("data_thread_1.csv", "w+");
   
    fprintf(fp1, "time,Count\n");

    s = clock();
    printf("\nThoi gian 1 : %lf\n", (double)s/CLOCKS_PER_SEC);
    printf("Enter Critical Section 1...\n");
    int i;
    for ( i = 0; i < 10000; i++) {
        count ++;
        time_th1 = (double) clock()/CLOCKS_PER_SEC;
        fprintf(fp1,"%f,%d\n", time_th1,count);

    }

    printf("Exit Critical Section 1...\n");
    e = clock();
    printf("Thoi gian 1 : %lf\n", (double)e/CLOCKS_PER_SEC);
    
   // fclose(fb1);

}

void *thread_2(void *arg) {
    FILE* fp2 = fopen("data_thread_2.csv", "w+");
   
    fprintf(fp2, "time,      Count\n");
    
    s1 = clock();
    printf("\nThoi gian 2 : %lf\n", (double)s1/CLOCKS_PER_SEC);
    printf("Enter Critical Section 2...\n");
    int j;
    for (j = 0; j < 10000; j++) {
    	//sem_wait(&sem);
        count ++;
        time_th2 = (double) clock()/CLOCKS_PER_SEC;
        fprintf(fp2,"%f,%d\n", time_th2,count);
        //sem_post(&sem);
    }

    printf("Exit Critical Section 2...\n");
    e1 = clock();
    printf("Thoi gian 2 : %lf\n", (double)e1/CLOCKS_PER_SEC);

   // fclose(fb2);
}

void *thread_3(void *arg) {
    FILE* fp3 = fopen("data_thread_3.csv", "w+");
   
    fprintf(fp3, "time,      Count\n");

    s2 = clock();
    printf("\nThoi gian 3 : %lf\n", (double)s2/CLOCKS_PER_SEC);
    printf("Enter Critical Section 3...\n");
    int k;
    for (k = 0; k < 10000; k++) {
    	//sem_wait(&sem);
        count ++;
        time_th3 = (double) clock()/CLOCKS_PER_SEC;
        fprintf(fp3,"%f,%d\n", time_th3,count);
       // sem_post(&sem);
    }

    printf("Exit Critical Section 3..	.\n");
    e2 = clock();
    printf("Thoi gian 3 : %lf\n", (double)e2/CLOCKS_PER_SEC);



    //fclose(fb3);

}
int main() {

 

    sem_init(&sem, 0, 1); //1 là giá tr? c?a semaphore

    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;


    pthread_create(&thread1, NULL, thread_1, NULL);
    pthread_create(&thread2, NULL, thread_2, NULL);
    pthread_create(&thread3, NULL, thread_3, NULL);



    pthread_join(thread1, NULL);

    pthread_join(thread2, NULL);

    pthread_join(thread3, NULL);

    sem_destroy(&sem);

    printf("count = %d\n", count);



    return 0;
}


