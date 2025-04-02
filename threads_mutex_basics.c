#include <pthread.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

// exercice 0
// Goal: Create and execute multiple threads.

// 🔹 Task:

// Create a program that spawns 3 threads.
// Each thread should print "Hello from thread X" (where X is the thread number).
// Make sure the main function waits for all threads to finish before exiting.
// ------------------------------------------------------------------------------------------>
// typedef struct lol
// {
// 	pthread_t id[3];
// 	int num;
// 	pthread_mutex_t write;
// } s_lol;

// void *print(void *args)
// {
// 	s_lol *h;
// 	h = (s_lol *)args;
// 	pthread_mutex_lock(&h->write); //avoid data race;
// 	h->num += 1;
// 	printf("Hello from thread %d\n", h->num);
// 	pthread_mutex_unlock(&h->write);
// 	return(NULL);
// }

// int main()
// {
// 	s_lol h;
// 	h.num = 0;
// 	pthread_mutex_init(&h.write, NULL);
// 	pthread_create(&h.id[0], NULL, print, &h);
// 	pthread_create(&h.id[1], NULL, print, &h);
// 	pthread_create(&h.id[2], NULL, print, &h);
// 	pthread_join(h.id[0], NULL);
// 	pthread_join(h.id[1], NULL);
// 	pthread_join(h.id[2], NULL);
// 	pthread_mutex_destroy(&h.write); 
// }
// //exercice 01
// // Goal: Understand race conditions when multiple threads access shared data.

// // 🔹 Task:

// // Create a shared variable counter = 0.
// // Spawn 5 threads, where each thread increments the counter 100,000 times.
// // Print the final value of counter.
// // Run the program multiple times and observe if the result is always correct.
// // 🔹 Expected Issue:
// // Due to race conditions, the final value of counter will likely be incorrect.
// //---------------------------------------------------------------------------------------------->
// typedef struct lol
// {
//     pthread_t id[5];
//     int counter;
//     pthread_mutex_t write;
// } s_lol;

// void *print(void *args)
// {
//     int i = 0;
//     s_lol *thread;
//     thread = (s_lol *)args;
//     pthread_mutex_lock(&thread->write);
//     while(i < 10000000)
//     {
//         thread->counter++;
//         i++;
//     }
//     pthread_mutex_unlock(&thread->write);
// }
// int main()
// {
//     s_lol thread;
//     thread.counter = 0;
//     int i = 1;
//     pthread_mutex_init(&thread.write, NULL);
//     pthread_create(&thread.id[0], NULL, print, &thread);
//     while (i < 5)
//     {
//         pthread_create(&thread.id[i], NULL, print, &thread);
//         pthread_join(thread.id[i], NULL);
//         i++;
//     }
//     pthread_mutex_destroy(&thread.write);
//     printf("num = %d\n", thread.counter);
// }
// exercice 2
// 📝 Exercise 4: Deadlock Simulation
// Goal: Understand how deadlocks occur.

// 🔹 Task:

// Create two mutexes (mutexA and mutexB).
// Create two threads:
// Thread 1: Locks mutexA first, then mutexB after 1 second.
// Thread 2: Locks mutexB first, then mutexA after 1 second.
// Observe that both threads get stuck (deadlock).
// 🔹 Fix Challenge:

// !!!!!!!!!!!!!!Implement a strategy to prevent deadlocks (e.g., always locking mutexes in the same order).
//------------------------------------------------------------------------------------------------->
// typedef struct lol
// {
//     pthread_t id[2];
//     pthread_mutex_t A;
//     pthread_mutex_t B;
// } s_lol;

// void *print(void *args)
// {
//     s_lol *thread;
//     thread = (s_lol *)args;
//     pthread_mutex_lock(&thread->A);
//     sleep(1);
//     pthread_mutex_lock(&thread->B);
//     printf("IM here 1");
//     pthread_mutex_unlock(&thread->A);
//     pthread_mutex_unlock(&thread->B);
// }
// void *printt(void *args)
// {
//     s_lol *thread;
//     thread = (s_lol *)args;
//     pthread_mutex_lock(&thread->B);
//     sleep(1);
//     pthread_mutex_lock(&thread->A);
//     pthread_mutex_unlock(&thread->A);
//     pthread_mutex_unlock(&thread->B);
//     printf("IM here 2");
// }

// int main()
// {
//     s_lol thread;
//     pthread_mutex_init(&thread.A, NULL);
//     pthread_mutex_init(&thread.B, NULL);
//     pthread_create(&thread.id[0], NULL, print, &thread);
//     pthread_create(&thread.id[1], NULL, printt, &thread);
//     pthread_join(thread.id[1], NULL);

// }
//-------------------------------> finish -------------------------------------------------------------------------->