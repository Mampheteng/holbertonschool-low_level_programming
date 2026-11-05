
#include <stdio.h>
#include <time.h>

#define DATASET_SIZE 50000
#define SEED_VALUE 42u

static int dataset[DATASET_SIZE];

/**
 * next_value - Generates the next pseudo-random value
 * @state: Pointer to the current state
 *
 * Return: The next generated value
 */
static unsigned int next_value(unsigned int *state)
{
	*state = (*state * 1103515245u) + 12345u;
	return (*state);
}

/**
 * build_dataset - Fills the dataset with generated values
 */
static void build_dataset(void)
{
	unsigned int state;
	int i;

	state = SEED_VALUE;

	for (i = 0; i < DATASET_SIZE; i++)
		dataset[i] = (int)(next_value(&state) % 100000);
}

/**
 * process_dataset - Performs calculations on dataset values
 */
static void process_dataset(void)
{
	int i;
	int v;

	for (i = 0; i < DATASET_SIZE; i++)
	{
		v = dataset[i];
		v = (v * 3) + (v / 7) - (v % 11);
		if (v < 0)
			v = -v;
		dataset[i] = v;
	}
}

/**
 * reduce_checksum - Calculates a checksum from the dataset
 *
 * Return: The calculated checksum
 */
static unsigned long reduce_checksum(void)
{
	unsigned long sum;
	int i;

	sum = 0;
	for (i = 0; i < DATASET_SIZE; i++)
		sum = (sum * 131ul) + (unsigned long)dataset[i];

	return (sum);
}

/**
 * struct measurements - Stores benchmark timestamps
 * @total_start: Start of the entire benchmark
 * @total_end: End of the entire benchmark
 * @build_start: Start of dataset creation
 * @build_end: End of dataset creation
 * @process_start: Start of dataset processing
 * @process_end: End of dataset processing
 * @reduce_start: Start of checksum calculation
 * @reduce_end: End of checksum calculation
 */
struct measurements
{
	clock_t total_start;
	clock_t total_end;
	clock_t build_start;
	clock_t build_end;
	clock_t process_start;
	clock_t process_end;
	clock_t reduce_start;
	clock_t reduce_end;
};

/**
 * print_times - Calculates and prints benchmark timings
 * @times: Pointer to the benchmark timestamps
 */
static void print_times(struct measurements *times)
{
	double total_time;
	double build_time;
	double process_time;
	double reduce_time;

	total_time = (double)(times->total_end - times->total_start) /
		(double)CLOCKS_PER_SEC;
	build_time = (double)(times->build_end - times->build_start) /
		(double)CLOCKS_PER_SEC;
	process_time = (double)(times->process_end -
		times->process_start) / (double)CLOCKS_PER_SEC;
	reduce_time = (double)(times->reduce_end - times->reduce_start) /
		(double)CLOCKS_PER_SEC;

	printf("TOTAL seconds: %.6f\n", total_time);
	printf("BUILD_DATA seconds: %.6f\n", build_time);
	printf("PROCESS seconds: %.6f\n", process_time);
	printf("REDUCE seconds: %.6f\n", reduce_time);
}

/**
 * main - Runs the controlled instrumentation experiment
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	unsigned long checksum;
	struct measurements times;

	times.total_start = clock();

	times.build_start = clock();
	build_dataset();
	times.build_end = clock();

	times.process_start = clock();
	process_dataset();
	times.process_end = clock();

	times.reduce_start = clock();
	checksum = reduce_checksum();
	times.reduce_end = clock();

	times.total_end = clock();

	if (checksum == 0ul)
		printf("impossible\n");

	print_times(&times);

	return (0);
}

