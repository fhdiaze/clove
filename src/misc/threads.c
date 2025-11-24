#include "log.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#define THRD_COUNT 3
#define THRD_NAME_BUFFER_SIZE 50

static tss_t thrd_name_key;
static tss_t thrd_counter_key;

static void cleanup(void *data)
{
	logi("cleaning up '%p'", data);
	if (data)
		free(data);
}

static int thrd_counter_run(void *arg_thrd_id)
{
	unsigned thrd_id = *(unsigned *)arg_thrd_id;
	logi("starting thrd_id='%u'", thrd_id);

	char *thrd_name = malloc(THRD_NAME_BUFFER_SIZE);
	if (!thrd_name)
		return EXIT_FAILURE;
	sprintf(thrd_name, "thrd_%u", thrd_id);
	if (tss_set(thrd_name_key, thrd_name) != thrd_success)
		return EXIT_FAILURE;

	unsigned *thrd_counter = malloc(sizeof(unsigned));
	if (!thrd_counter)
		return EXIT_FAILURE;
	*thrd_counter = 0;
	if (tss_set(thrd_counter_key, thrd_counter) != thrd_success)
		return EXIT_FAILURE;

	for (unsigned i = 0; i < 5; ++i) {
		char *name = (char *)tss_get(thrd_name_key);
		if (!name)
			return EXIT_FAILURE;

		logi("incrementing the counter for thrd_name='%s'", name);
		unsigned *counter = (unsigned *)tss_get(thrd_counter_key);
		if (!counter)
			return EXIT_FAILURE;
		logi("thrd_name='%s' counter current value '%u'", name, *counter);
		++(*counter);
		logi("thrd_name='%s' counter new value '%u'", name, *counter);

		thrd_sleep(&(struct timespec){ .tv_sec = 10 }, nullptr);
	}

	logi("finishing thread_id='%u'", thrd_id);
	return EXIT_SUCCESS;
}

/*
 * Testing thread specific storage type
 */
int main(void)
{
	if (tss_create(&thrd_name_key, cleanup) != thrd_success)
		return EXIT_FAILURE;

	if (tss_create(&thrd_counter_key, cleanup) != thrd_success) {
		tss_delete(thrd_name_key);
		return EXIT_FAILURE;
	}

	thrd_t threads[THRD_COUNT];
	unsigned threads_ids[THRD_COUNT] = { 1, 2, 3 };

	for (unsigned i = 0; i < THRD_COUNT; ++i) {
		thrd_create(&threads[i], thrd_counter_run, &threads_ids[i]);
	}

	for (unsigned i = 0; i < 3; ++i) {
		thrd_join(threads[i], nullptr);
	}

	tss_delete(thrd_name_key);
	tss_delete(thrd_counter_key);

	return EXIT_SUCCESS;
}
