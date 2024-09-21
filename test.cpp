
#include "mpi.h"
#include<iostream>
int main(int argc, char *argv[])
{	
	int n = atoi(argv[1]);
	int myid;

	int numprocs;

	int rc;
	
	int *arr  = new int[n];
	
	MPI_Status status;

	
	for (int i = 0 ; i!=n; i++)
	{
		arr[i]= atoi(argv[i+2]);
		
	}
		
	 
	if (rc=MPI_Init(&argc, &argv))
	{
		std::cout << " переделывай" <<std::endl;

    		MPI_Abort(MPI_COMM_WORLD, rc);
	}
	
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs); 

	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	int child_arr_size = n/numprocs;
	int child_arr[child_arr_size];
	if (myid == 0)
	{
		for (int i = 1 ;i!= numprocs;++i)
		{
			MPI_Send(&arr[i* n/numprocs],n/numprocs,MPI_INT,i,0,MPI_COMM_WORLD);
		}
		if (status.MPI_ERROR)
		{MPI_Finalize
    			MPI_Abort(MPI_COMM_WORLD, rc);
		}

	}
	else
	{

		MPI_Recv(&child_arr,child_arr_size,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
	}
	
	

	std::cout<<myid<<':';
	int i;
	for (i = 0 ; i!=child_arr_size; ++i)
	{
		std::cout<<child_arr[i]<<' ';
	}
	std::cout<<std::endl;
	
	MPI_Finalize();

}	
		

