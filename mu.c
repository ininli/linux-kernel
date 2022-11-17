#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/types.h>
#include <time.h>
#define arr_size 6

typedef struct {
    char *segment_name;
    void *address;
} data_format;

int for_data_segment = 48763;
int for_bss_segment;
int *for_heap_segment;
void *for_libraries_segment = &printf;
void for_text_segment() {}

unsigned long bss_seg=0;
unsigned long data_seg=48763;


void* child_thread(void) {
    int for_stack_segment = 357;
    data_format items[] = {
        {"text", &for_text_segment}
        , {"data", &for_data_segment}
        , {"bss", &for_bss_segment}
        , {"heap", for_heap_segment}
        , {"libraries", for_libraries_segment}
        , {"stack", &for_stack_segment}
    };

	unsigned long input_arr[arr_size];
	unsigned long output_arr[arr_size];
/*	long heap_seg=malloc(sizeof(long));
	long stack_seg= 357;
*/
	printf("input\n");
	input_arr[0]=&for_text_segment;
	input_arr[1]=&for_data_segment;
	input_arr[2]=&for_bss_segment;
	input_arr[3]=for_heap_segment;
	input_arr[4]=for_libraries_segment;
	input_arr[5]=&for_stack_segment;
	printf("%p\n", input_arr[0]);
	printf("%p\n", input_arr[1]);
	printf("%p\n", input_arr[2]);
	printf("%p\n", input_arr[3]);
	printf("%p\n", input_arr[4]);
	printf("%p\n", input_arr[5]);

/*	int i = 0;	
    for(; i < (sizeof(items)/sizeof(items[0])); i++) {
        
		unsigned long virtual = items[i].address;
		unsigned long physical = syscall(352, virtual);

		printf("Segment Name: %s, Virutal Address: %p, Physicall Address: %p\n"
            , items[i].segment_name
            , items[i].address
			, (void *)physical
        );
    }
*/
	int a = syscall(351, input_arr, arr_size, output_arr);
	printf("output\n");
	printf("%p\n", output_arr[0]);
	printf("%p\n", output_arr[1]);
	printf("%p\n", output_arr[2]);
	printf("%p\n", output_arr[3]);
	printf("%p\n", output_arr[4]);
	printf("%p\n", output_arr[5]);

    pthread_exit(NULL);
}

int main(void) {
    for_heap_segment = malloc(10);
    for_libraries_segment = &printf;

	/*double (*sum)(double, double);
	long *var1 = malloc(sizeof(long));
	unsigned long input_arr[arr_size];
	unsigned long output_arr[arr_size];
	input_arr[0]=var1;
	input_arr[1]=&printf;
	input_arr[2]=sum;
	int a = syscall(352, input_arr, arr_size, output_arr);*/
    pthread_t pt_1=0;
    pthread_t pt_2=0;

    pthread_create(&pt_1, NULL, (void*)child_thread, "pt_1");
    sleep(1);
    pthread_create(&pt_2, NULL, (void*)child_thread, "pt_2");

    pthread_join(pt_1, NULL);
    pthread_join(pt_2, NULL);

    return 0;
}
