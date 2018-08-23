#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// pre-defined variable!

//use to control how many experiment to repeat
const int num_exp = 10000;

//for converting seconds into nano seconds
const int nanos_cons = 1000000000;

//reserve for minimal function call,
//to mesure the minimal function call
struct timespec func_start;
struct timespec func_stop;

//reserve for minial system call,
//to mesure the minimal system call
struct timespec sys_start;
struct timespec sys_stop;

//reserve for read or write system call,
//to measure the cost of it by transfer one byte
struct timespec rwsys_start;
struct timespec rwsys_stop;

//set up function call for case of minimal function call
void emp_func(){};

//implement the case of measure of minimal function call
unsigned long long func_call()
{
	int i;
	//used for sum the time cost in nanosecond into func_sum
	unsigned long long func_sum=0;
	//used for carry the return average time cost result in nanosecond
	unsigned long long func_res=0;
	for(i=0; i<num_exp;i++)
	{
		//record time begin here
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&func_start);
		//call a empty function call
		emp_func();
		//stop record the time
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &func_stop);
		//sum the time into rwsys_sum
		func_sum+=((func_stop.tv_sec * nanos_cons) + func_stop.tv_nsec)-
		((func_start.tv_sec * nanos_cons) + func_start.tv_nsec);
	}
	return func_res = func_sum / num_exp;
}

//implement the case of measure of minimal system call
unsigned long long sys_call()
{
	int i;
	//used for sum the time cost in nanosecond into func_sum
	unsigned long long sys_sum=0;
	//used for carry the return average time cost result in nanosecond
	unsigned long long sys_res=0;

	for(i=0; i<num_exp;i++)
	{
		//record time begin here
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&sys_start);
		//make a system call
		getpid();
		//stop record the time
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &sys_stop);
		//sum the time into rwsys_sum
		sys_sum+=((sys_stop.tv_sec * nanos_cons) + sys_stop.tv_nsec)-
		((sys_start.tv_sec * nanos_cons) + sys_start.tv_nsec);
	}
	return sys_res = sys_sum / num_exp;
}


//implement the case of measure the cost of read/write
//system call by transfer one byte between parent and child process
unsigned long long rwsys_call()
{
	int i, piperet;
	pid_t pid;
	//use for transfer one byte
	char a = 'b';
	//used for sum the time cost in nanosecond into rwsys_sum
	unsigned long long rwsys_sum=0;
	//used for carry the return average time cost result in nanosecond
	unsigned long long rwsys_res=0;
	//repeat the experiment based on the defined num_exp
	for (i=0;i<num_exp; i++)
	{
		//set up a pipe for parent and child process
		int mypipefd[2];
		//initialize the pipe and deal with pipe error
		piperet = pipe(mypipefd);
		if(piperet < 0)
		{
			perror("pipe error");
			return(1);
		}

		//fork a child process
		pid = fork();

		//fork error
		if(pid < 0)
		{
			perror("fork error");
			exit(1);
		}
		else if(pid>0){
			//parent process
			//prevent parent process from read
			close(mypipefd[0]);
			//record time begin here
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&rwsys_start);
			//parent process would write only
			write(mypipefd[1], &a, sizeof(a));
			//check here whether the child has exit successfully
			wait(NULL);
			//stop record the time
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &rwsys_stop);
			//terminate the pipe after all the process ended
			close(mypipefd[1]);}

		else{
			//child process here
			//prevent child process from write
			close(mypipefd[1]);
			//read the character transfer from parent process
			read(mypipefd[0], &a, sizeof(a));
			exit(0);}

			//sum the time into rwsys_sum
			rwsys_sum+=((rwsys_stop.tv_sec * nanos_cons) + rwsys_stop.tv_nsec)-
			((rwsys_start.tv_sec * nanos_cons) + rwsys_start.tv_nsec);
		}
			return rwsys_res = rwsys_sum / num_exp;
}

int main(void){
	//set up the return variable to carry the output from each function
	unsigned long long rw_ret, sys_ret, func_ret;
	printf("Note the default number of experiment repeated is: %d\n", num_exp);
	printf("Also, the cost of time would be measure as nanosecond.\n\n");
	//calling the minimal function call function
	func_ret = func_call();
	printf("Case1: minimal function call, the average time cost in nanos is: %llu\n\n", func_ret);
	//calling the minimal system call function
	sys_ret = sys_call();
	printf("Case2: minimal system call, the average time cost in nanos is: %llu\n\n", sys_ret);
	//calling the read/write system call function
	rw_ret = rwsys_call();
	printf("Case3: read/write system call, the average time cost in nanos is: %llu\n\n", rw_ret);

	return 0;
}