#include "mm.h"


void print_array(int **array_memory, int r, int c)
{
	printf("array dimension : %d * %d\n", r, c);
	
	for(int i = 0 ; i < r ; i++)
	{
		for(int j = 0 ; j < c ; j++)
		{
			printf("%3d ", array_memory[i][j] % 1000);
		}

		printf("\n");
	}
}

void test_malloc(int row, int col)
{
	printf("test fumction for malloc\n");
	printf("----------\n");

	/* first test */
	int **array_memory = (int **)mymalloc(sizeof(int *) * row);
	for(int i = 0 ; i < row ; i++)
		array_memory[i] = (int *)mymalloc(sizeof(int) * col);

	for(int i = 0 ; i < row ; i++)
		for(int j = 0 ; j < col ; j++)
			array_memory[i][j] = i * 10 + j;

	print_array(array_memory, row, col);
	
	printf("---After print_array()---\n");
	trace_free_memory();

	/* free */
	for(int i = 0 ; i < row ; i++)
		myfree(array_memory[i]);
	myfree(array_memory);
	
	printf("After myfree()\n");
	trace_free_memory();
}


void test_calloc(int row,int col)
{
	printf("test fumction for calloc\n");
	printf("----------\n");
	
	/* first test */
	int **array_memory = (int **)mycalloc(row, sizeof(int *));
	for(int i = 0 ; i < row ; i++)
		array_memory[i] = (int *)mymalloc(sizeof(int) * col);

	for(int i = 0 ; i < row ; i++)
		for(int j = 0 ; j < col ; j++)
			array_memory[i][j] = i * 10 + j;

	print_array(array_memory,row,col);
	
	printf("---After print_array()---\n");
	trace_free_memory();

	/* first free */
	for(int i = 0 ; i < row ; i++)
		myfree(array_memory[i]);

	printf("After myfree()\n");
	trace_free_memory();

	/* second test */
	col++;
	for(int i = 0 ; i < row ; i++)
		array_memory[i]=(int *)mycalloc(col, sizeof(int *));
	for(int i = 0 ; i < row ; i++)
		for(int j = 0 ; j < col ; j++)
			array_memory[i][j] = i * 10 + j;

	print_array(array_memory,row,col);
	
	printf("---After print_array()---\n");
	trace_free_memory();

	/* second free */
	for(int i = 0 ; i < row ; i++)
		myfree(array_memory[i]);
	myfree(array_memory);
	
	printf("After myfree()\n");
	trace_free_memory();
}


void test_realloc(int row,int col)
{
	printf("test fumction for realloc\n");

	/* first test */
	int **array_memory = (int **)mymalloc(sizeof(int *) * row);
	for(int i = 0 ; i < row ; i++)
		array_memory[i] = (int *)mymalloc(sizeof(int) * col);

	for(int i = 0 ; i < row ; i++)
		for(int j = 0 ; j < col ; j++)
			array_memory[i][j] = i * 10 + j;

	print_array(array_memory, row, col);
	
	printf("---After print_array()---\n");
	trace_free_memory();

	/* second test */
	array_memory = (int **)myrealloc(array_memory, sizeof(int *) * (row + 5));
	for(int i = 0 ; i < row ; i++)
		array_memory[i] = (int *)myrealloc(array_memory[i], sizeof(int) * (col + 5));
	for(int i = row ; i < row + 5 ; i++)
		array_memory[i] = (int *)mymalloc(sizeof(int) * (col + 5));

	print_array(array_memory, row + 5, col + 5);
	
	printf("---After print_array()---\n");
	trace_free_memory();

	/* third test */
	for (int i = 0; i < row + 5 ; i++)
		array_memory[i] = (int *)myrealloc(array_memory[i], sizeof(int) * col);
	print_array(array_memory, row + 5, col);
	
	printf("---After print_array()---\n");
	trace_free_memory();

	/* free */
	for(int i = 0 ; i < row + 5 ; i++)
		myfree(array_memory[i]);
	myfree(array_memory);
	
	printf("---After myfree()---\n");
	trace_free_memory();
}

int main()
{
	int r,c;
	scanf("%d %d",&r,&c);
	
	test_malloc(r,c);

	test_calloc(r,c);

	test_realloc(r,c);

	return 0;
}