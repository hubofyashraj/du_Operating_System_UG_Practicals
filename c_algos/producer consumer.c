#include <stdio.h>      // main.c
#include <stdlib.h>
#include <unistd.h>

#include <time.h>


#define SIZE 10

typedef struct cyclicalBuf
{
    int size;
    char bufor[SIZE];
}   cyclicalBuf;

int main(int argc, char *argv[])
{
    if(argc != 1)
    {
        perror("Need no arguments!");
        exit(1);
    }

    int semid;
    int memoryID;

    int key;

    key = semGetKey('A');
    semid = semCreate(key, 2); // 2 sem made

    setVal(semid, 0, SIZE);
    setVal(semid, 1, 0);

    memoryID = memoryCreate('A', sizeof(cyclicalBuf));

    pid_t pid;
    pid = fork();

    switch(pid)
    {
        case -1:
            perror("fork() error in producer section");
            exit(2);
            break;
        case 0:
            execl("./producer", "./producer", NULL);
            perror("execl() error in producer section");
            exit(3);
            break;
        default:
            break;
    }

    sleep(1);

    switch(pid)
    {
        case -1:
            perror("fork() error in consumer section");
            exit(4);
            break;
        case 0:
            execl("./consumer", "./consumer", NULL);
            perror("execl() error in consumer section");
            exit(5);
            break;
        default:
            break;
    }

    int i;
    for(i = 0; i < 2; i++)
    {
        if(wait(0) < 0 )
        {
            perror("wait() error [main.c]");
        }
    }

    semDelete(semid, 2);

    memoryDelete(memoryID);

    return 0;
}


#include <stdio.h>        // producer.c
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


#define SIZE 10

typedef struct cyclicalBuf
{
    int size;
    char bufor[SIZE];
} cyclicalBuf;

void producer()
{
    FILE *fp;
    int i;
    int semid;
    int memoryID;
    cyclicalBuf * buf;
    char c;

    if((fp = fopen("./input.txt", "r")) == NULL)
    {
        perror("fopen() error [producer]");
        exit(1);
    }

    int key;

    key = semGetKey('A');
    semid = semCreate(key, 2); y

    memoryID = memoryAccess('A');

    buf = (cyclicalBuf *)memoryLink(memoryID);

    printf("Producer: ");

    for(i = 0; (c = fgetc(fp)) != EOF; i++)
    {

        semRelease(semid, 0);

        usleep(rand()%5555);

        buf->bufor[i%SIZE] = c;

        buf->size++;

        semAcquire(semid, 1);

        printf(" %c", c);
    }

    if(fclose(fp) == EOF)
    {
        perror("fclose() error [producer]");
        exit(2);
    }

    memoryUnlink(buf);
}

int main(int argc, char *argv[])
{

    if(argc != 1)
    {
        perror("Need no arguments!");
        exit(3);
    }

    srand(time(NULL));

    producer();

    return 0;
}


#include <stdio.h>   // consumer.c
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/sem.h>
#include "memory.h"
#include "semaphore.h"

#define SIZE 10

typedef struct cyclicalBuf
{
    int size;
    char bufor[SIZE];
} cyclicalBuf;

void consumer()
{
    FILE *fp;
    int c_cnt = 0;
    int i = 0;
    int semid;
    int memoryID;
    cyclicalBuf * buf;
    char c;

    if((fp = fopen("./output.txt", "w")) == NULL)
    {
        perror("fopen() error [consumer]");
        exit(1);
    }

    int key;

    key = semGetKey('A');
    semid = semCreate(key, 2);

    memoryID = memoryAccess('A');

    buf = (cyclicalBuf *)memoryLink(memoryID);

    printf("Consumer: ");

    while(!((semctl(semid, 0, GETVAL) == SIZE) && (c_cnt == buf->size)))
    {

        semRelease(semid, 1);

        usleep(rand()%5555);

        c = buf->bufor[i%SIZE];

        semAcquire(semid, 0);

        fputc(c, fp);

        printf(" %c", c);

        i++;
        c_cnt++;
    }

    if(fclose(fp) == EOF) //
    {
        perror("fclose() error [consumer]");
        exit(2);
    }

    memoryUnlink(buf); //
}

int main(int argc, char *argv[])
{

    if(argc != 1)
    {
        perror("Need no arguments!");
        exit(3);
    }

    srand(time(NULL));

    consumer();

    return 0;
}
