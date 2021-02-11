
#include <vector>
#include "mpq.h"

using namespace std;

//MOST CODE IS ADAPTED FROM LECTURE NOTES AND MODIFIED WHERE REQUIRED
MPQ::MPQ(int capacity)
{
	Heap.resize(capacity+1);
	Location.resize(capacity+1);
	currentSize=0; 
}
MPQ:: ~MPQ() 
{
	/*nothing allocated dynamically 
	everything delets automatically out of fucntion scope*/
}

bool MPQ::isEmpty() const
{
	if(currentSize==0)
	{
		return true;
	}
	else
		return false;
}

void MPQ:: insert( const int & value, const int & label )
{
	int hole= ++currentSize;
	for (;hole>1 && value > Heap[hole/2].value; hole/=2)
	{
		Heap[hole] = Heap[hole/2];
		Location[Heap[hole].label]= hole;
	}
	Heap[hole].value = value;
    Heap[hole].label = label;
    Location[Heap[hole].label] = hole ;
}

void MPQ::percolateDown(int hole) 
{
	int child;
	in_view temp = Heap[hole]; 

	for (; hole * 2 <= currentSize; hole = child)
	{
		child = hole * 2;
		if (child != currentSize && Heap[child + 1].value > Heap[child].value) 
			child++;
		if (Heap[child].value > temp.value) 
		{
			Heap[hole].value = Heap[child].value; 
			Location[Heap[hole].label] = hole;
		}
		else
		{
			break;
		}
	}
	Heap[hole] = temp; 
	Location[Heap[hole].label] = hole;
}

int MPQ:: Remove(const int & remove_build)
{
	int height_deleted=0;
	if(isEmpty() == true)
	{
		return -2; 
	}
	if(Location[remove_build] > -1  )
	{
		height_deleted= Heap[Location[remove_build]].value;
		Heap[Location[remove_build]]= Heap[currentSize--];
		percolateDown(Location[remove_build]);
		Location[remove_build]= -1;
	}
	
	return height_deleted;
	
}

const int MPQ:: GetMax() const
{
	if(isEmpty()==true)
	{
		return 0;
	}
	return Heap[ 1 ].value;
}
