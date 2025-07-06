# Philosophers

A 42 School project implementing the classic dining philosophers problem using threads and mutexes.

## Overview

The dining philosophers problem is a classic synchronization problem in computer science. It illustrates the challenges of resource allocation and deadlock avoidance in concurrent programming.

## Problem Description

Five philosophers sit around a circular table with a bowl of spaghetti in the center. Between each pair of philosophers is a single fork. To eat, a philosopher must pick up both forks adjacent to them (left and right). The challenge is to design an algorithm that prevents deadlock and starvation.

## Project Requirements

- **Language**: C
- **Allowed functions**: `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`
- **Forbidden**: Global variables
- **Compilation**: Must compile with `-Wall -Wextra -Werror`

## Usage

```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die`: Time in milliseconds - if a philosopher doesn't start eating within this time since their last meal, they die
- `time_to_eat`: Time in milliseconds it takes for a philosopher to eat
- `time_to_sleep`: Time in milliseconds a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat`: (Optional) Simulation stops when all philosophers have eaten at least this many times

### Examples

```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
./philo 4 410 200 200
./philo 4 310 200 100
```

## Implementation Details

### Data Structures

```c
typedef struct s_philo
{
    pthread_t       thread;
    int             num;                // philosopher number (1-indexed)
    int             num_of_philos;      // total number of philosophers
    int             time_to_sleep;      // time to sleep in ms
    int             time_to_eat;        // time to eat in ms
    int             time_to_die;        // time to die in ms
    int             num_to_eat;         // number of meals required (-1 if unlimited)
    int             eating;             // flag: 1 if currently eating, 0 otherwise
    int             meals_eaten;        // number of meals eaten so far
    int             *dead;              // shared death flag
    size_t          last_meal;          // timestamp of last meal
    size_t          start;              // simulation start time
    pthread_mutex_t *rfork;             // right fork mutex
    pthread_mutex_t *lfork;             // left fork mutex
    pthread_mutex_t *dead_lock;         // mutex for death flag
    pthread_mutex_t *meal_lock;         // mutex for meal counting
    pthread_mutex_t *write_lock;        // mutex for printing
    pthread_mutex_t *start_time;        // mutex for start time synchronization
} t_philo;

typedef struct s_monitor
{
    int             dead_flag;          // global death flag
    pthread_mutex_t dead_lock;          // protects death flag
    pthread_mutex_t meal_lock;          // protects meal counting
    pthread_mutex_t write_lock;         // protects console output
    pthread_mutex_t start;              // synchronizes simulation start
    t_philo         *philos;            // array of philosophers
} t_monitor;
```

### Key Concepts

#### Mutexes
- **Fork mutexes** (`rfork`, `lfork`): Protect access to individual forks
- **Write lock** (`write_lock`): Ensures thread-safe printing of status messages
- **Dead lock** (`dead_lock`): Protects the shared death flag
- **Meal lock** (`meal_lock`): Protects meal counting operations
- **Start time** (`start_time`): Synchronizes simulation start across all threads

#### Thread Management
- Each philosopher runs in their own thread
- Main thread monitors for death conditions
- Proper cleanup with `pthread_join`

#### Deadlock Prevention
Several strategies can be implemented:
1. **Odd-Even Strategy**: Odd-numbered philosophers pick up left fork first, even-numbered pick up right fork first
2. **Resource Ordering**: Always acquire forks in numerical order
3. **Timeout Mechanism**: Release forks if unable to acquire both within a time limit

## Status Messages

The program outputs timestamped status messages:
- `timestamp_in_ms X has taken a fork`
- `timestamp_in_ms X is eating`
- `timestamp_in_ms X is sleeping`
- `timestamp_in_ms X is thinking`
- `timestamp_in_ms X died`

## Function Prototypes

### Core Functions
```c
// Parsing and initialization
int     test_parsing(char **av, int ac);
long    ft_atoi(char *str);
void    init_philos(t_philo *philo, char **argv, pthread_mutex_t *forks, t_monitor *monitor);
int     init_forks(pthread_mutex_t *forks, int num);
int     init_monitor(t_monitor *t, t_philo *philos);

// Thread management
void    creat_threads(t_monitor *monitor, pthread_mutex_t *forks);
void    *philo_routine(void *ptr);

// Death monitoring
int     check_died(t_philo *philos);
int     check_died1(t_philo *philo);
void    *check_diedloop(void *ptr);

// Philosopher actions
void    philo_is_think(t_philo *philo);
void    philo_is_sleep(t_philo *philo);
void    philo_is_eating(t_philo *philo);

// Utilities
size_t  get_time(void);
void    ft_usleep(int time, t_philo *philo);
void    print_message(t_philo *philo, char *message, int flag);
void    ccclean(pthread_mutex_t *forks, t_philo *philos);
```

1. **Data Races**: Always protect shared data with mutexes
2. **Deadlock**: Ensure consistent lock ordering
3. **Memory Leaks**: Clean up all allocated memory and destroy mutexes
4. **Race Conditions**: Be careful with death checking and meal counting
5. **Timing Issues**: Use precise timing functions and avoid busy waiting

## Testing

### Test Cases
```bash
# Should not die
./philo 5 800 200 200

# Should die
./philo 1 800 200 200

# Should stop after eating
./philo 5 800 200 200 7

# Edge case - tight timing
./philo 4 310 200 100
```

### Debugging Tips
- Use `valgrind` to check for memory leaks and race conditions
- Add debug prints (remove before submission)
- Test with different timing values
- Use `helgrind` for thread safety analysis
- Use `fsanitize ` for both.
## File Structure

```
philosophers/
├── Makefile
├── philo.h             // Header file with structs and function prototypes
├── main.c              // Main program entry point
├── ft_atoi.c           // String to integer conversion
├── init.c              // init_philos, init_forks, init_monitor
├── philos.c            // Philosopher creation and management functions
├── philoroutine.c      // philo_routine and philosopher actions
├── monitoring.c        // check_died, check_died1, check_diedloop
├── clean.c             // ccclean and cleanup functions
```

## Implementation Tips

### File Organization
- **main.c**: Program entry point and argument parsing
- **ft_atoi.c**: Custom string to integer conversion (handles edge cases)
- **init.c**: Initialization functions for philosophers, forks, and monitor
- **philos.c**: Philosopher creation and thread management functions
- **philoroutine.c**: Core philosopher routine and action functions
- **monitoring.c**: Death monitoring and checking functions
- **clean.c**: Cleanup and memory management functions

### Death Monitoring
```c
// Your dual death checking approach
int check_died(t_philo *philos);      // Check all philosophers
int check_died1(t_philo *philo);      // Check individual philosopher
void *check_diedloop(void *ptr);      // Monitoring thread
```

### Synchronization Strategy
- Use the `eating` flag to prevent death during meals
- The monitor structure centralizes all shared state
- Separate mutexes for different concerns (writing, death, meals)

### Timing Precision
- `get_time()` returns current timestamp in milliseconds
- `ft_usleep()` includes death checking during sleep
- `last_meal` timestamp updated before and after eating

## Learning Objectives

- Understanding of threading and synchronization
- Mutex usage and deadlock prevention
- Race condition identification and resolution
- Resource management in concurrent programs
- Timing and scheduling in multi-threaded applications

## Resources

- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [Mutex vs Semaphore](https://stackoverflow.com/questions/62814/difference-between-binary-semaphore-and-mutex)

---

*This project is part of the 42 School curriculum and focuses on concurrent programming concepts.*
