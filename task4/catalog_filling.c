#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <time.h>

#define SHM_SIZE 8

sem_t *sem_producer;
sem_t *sem_bookhandler;

int shm_fd;
void *shm_ptr;

void destroy(int num) {
    sem_close(sem_producer);
    sem_close(sem_bookhandler);
    sem_unlink("/producer");
    sem_unlink("/bookhandler");
    shm_unlink("/shared");
    munmap(shm_ptr, SHM_SIZE);
    close(shm_fd);

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    srand(time(0));

    //signals
    struct sigaction act;
    act.sa_handler = destroy;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTERM, &act, NULL);

    //input
    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
    int K = atoi(argv[3]);

    int *book_numbers = malloc(M * N * K * sizeof(int));
    for (int i = 0; i < M * N * K; i++) {
        book_numbers[i] = i + 1;
    }

    //random_shuffle
    for (int i = 0; i < M * N * K; i++) {
        int swapInd = rand() % (M * N * K);
        int tmp = book_numbers[i];
        book_numbers[i] = book_numbers[swapInd];
        book_numbers[swapInd] = tmp;
    }

    printf("Book numbers: ");
    for (int i = 0; i < M * N * K; i++) {
        printf("%d ", book_numbers[i]);
    }
    printf("\n");

    // create shared memory
    shm_fd = shm_open("/shared", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHM_SIZE);
    shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // create semaphore
    sem_producer = sem_open("/producer", O_CREAT, 0666, 0); // 0 default
    sem_bookhandler = sem_open("/bookhandler", O_CREAT, 0666, 1);  // 1 default

    if (sem_producer == SEM_FAILED || sem_bookhandler == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    sleep(1);

    // handler
    if (!fork()) {
        int count_books = 0;
        while (1) {
            if (count_books >= M * N * K) {
                break;
            }
            sem_wait(sem_producer);
            int *shm_array = (int *) shm_ptr;
            int current_book_number = shm_array[0];
            printf("Handler took book: %d\n", current_book_number);
            usleep(500000);
            //bN = a(nk) + bk + c
            int row = (current_book_number + N * K - 1) / (N * K);
            int bookshelf = (current_book_number - (row - 1) * N * K + K - 1) / K;
            int book = current_book_number - (row - 1) * N * K - (bookshelf - 1) * K;
            printf("Handler set book in %d row/ %d bookshelf/ %d place\n", row, bookshelf, book);
            count_books++;
            sem_post(sem_bookhandler);
        }
        printf("Handler finished\n");
        exit(EXIT_SUCCESS);
    }

    // producer
    for (int i = 0; i < N * M * K; ++i) {
        sem_wait(sem_bookhandler);
        int *shm_array = (int *) shm_ptr;
        int current_book_number = book_numbers[i];
        printf("Producer give book: %d\n", current_book_number);
        usleep(500000);
        shm_array[0] = current_book_number;
        sem_post(sem_producer);
    }
    sem_wait(sem_bookhandler);

    //clean data
    destroy(0);
    free(book_numbers);
    return 0;
}