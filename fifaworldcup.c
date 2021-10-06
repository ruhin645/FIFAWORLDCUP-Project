#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t sem1,sem2,car;
int cnt=0, rem=14;

void * German(void *id)
{
    sem_wait(&sem1);

    printf("\t\tGerman player%d arrived\n",id);
    cnt++;
    if(cnt%4==0)
    {
        sem_post(&car);
        cnt=0;
    }
}

void *Italian(void *id)
{
    sem_wait(&sem2);

    printf("\t\tItalian player%d arrived \n",id);
    cnt++;
    if(cnt%4==0)
    {
        sem_post(&car);
        cnt=0;
    }
}
void *tramCar(void *arg)
{
    while(1)
    {
        sem_wait(&car);
        printf("\t\t%d German Player Waiting to Board\n",rem-=2);
        printf("\t\t%d Italian Player Waiting to Board\n\n",rem);

        if(rem==0) printf("\t\tAll players arrived!!!");
        printf("\n\t\t Tram leaves \n\n\n");

        sem_post(&sem1);
        sem_post(&sem1);
        sem_post(&sem2);
        sem_post(&sem2);
    }
}

int main()

{
    printf("\n\t\t\t\t***** FIFA WORLD CUP: GERMENY VS ITALY *****\t\t\t\t\n\n");
    pthread_t ger[14],ita[14],tcar;
    sem_init(&sem1,0,2);
    sem_init(&sem2,0,2);
    sem_init(&car,0,0);

    pthread_create(&tcar,NULL,tramCar,NULL);
    for(int i=1; i<=14; ++i)
    {
        pthread_create(&ger[i],NULL,German,(void*)i);
    }
    for(int j=1; j<=14; ++j)
    {
        pthread_create(&ita[j],NULL,Italian,(void*)j);
    }
    for(int i=1; i<=14; ++i)
    {
        pthread_join(ita[i],NULL);
    }
    for(int j=1; j<=14; ++j)
    {
        pthread_join(ger[j],NULL);
    }

    printf("\n\t\t***Total player: 28 ***\n\n");


}

