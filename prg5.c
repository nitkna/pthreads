#include<stdio.h>
#include<pthread.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

pthread_t philosopher[5];
pthread_mutex_t chopstick[5];

void *fun(void*);
int main(){

  int i;
  for(i=0;i<5;i++)
    pthread_mutex_init(&chopstick[i],NULL);
  for(i=0;i<5;i++)
    pthread_create(&philosopher[i],NULL, fun, (void*)&i);
  for(i=0; i<5; i++)
    pthread_join(philosopher[i],NULL);
   
}

void *fun(void *n){

  int num = *(int*)n;
  printf(RED "philosopher %d is thinking\n" RESET, num);
  pthread_mutex_lock(&chopstick[num]);
  pthread_mutex_lock(&chopstick[(num+1)%5]);
  printf(GREEN "philosopher %d is eating \n\n" RESET,num);
  sleep(5);
  pthread_mutex_unlock(&chopstick[num]);
  pthread_mutex_unlock(&chopstick[(num+1)%5]);
  printf(CYAN "Philosopher %d finished eating\n" RESET,num);

  
}
