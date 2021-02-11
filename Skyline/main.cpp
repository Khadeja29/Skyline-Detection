#include <iostream>
#include "mpq.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include<vector>
using namespace std;

struct edge
{
	bool left;
	int x;
	int label;
	int height;
};



/*void insertSort ( vector<edge> &a)
{
	int j;
	for (int p = 1; p < a.size(); p++)
	{
		edge temp = a[p];
		for (j =p ; j>0 && temp.x < a[j-1].x ; j--)
		{
			a[j]= a[j-1];
		}
		a[j]=temp;
	}
}*/


/*HEAP SORT COPIED FROM THE CLASS NOTES)*/
void percDown(vector<edge> &a, int i, int n)
{
	int child;
	edge temp;

	for (temp = a[i]; (2 * i) + 1 < n; i = child)
	{
		child = (2 * i) + 1;
		if (child != n - 1 && a[child].x < a[child + 1].x)
		{
			child++;
		}
		if (a[child].x > temp.x)
		{
			a[i] = a[child];
		}
		else
		{
			break;
		}
	}
	a[i] = temp;
}
void heapsort(vector<edge> & a)
{
	for (int i = a.size() / 2; i >= 0; i--)
	{
		percDown(a, i, a.size()); 
	}

	for (int j = a.size() - 1; j > 0; j--)
	{
		swap(a[0], a[j]); 
		percDown(a, 0, j); 
	}
}

int main()
{
	//opening file
	ifstream input;
	string filename ="input.txt";
	input.open(filename.c_str());

	//reading first line for total buildings
	string line1,total_b;
	getline(input,line1);
	istringstream s1(line1);
	s1>>total_b;
	int t_building = stoi(total_b);
	
	//reading the file line by line
	//Intializations
	string lines,lft,top,rht;

	vector<edge> build_info;
	int build_no = 0;
	while (getline(input,lines))
	{
		edge temp_left; //new struct to store info of left edge
		edge temp_right; // new struct to store info of right edge

		//conversions
		istringstream ss(lines);
		ss>>lft>>top>>rht;
		int left = stoi(lft);
		int top_height = stoi(top);
		int right = stoi(rht);	

		temp_left.left= true; //adding left of a building
		temp_left.x= left;
		temp_left.label = build_no;
		temp_left.height= top_height;
		build_info.push_back(temp_left);

		temp_right.left= false;// adding right details of a building
		temp_right.x= right;
		temp_right.label = build_no;
		temp_right.height= top_height;
		build_info.push_back(temp_right);

		build_no++;
	}

	//Sorting Array usinf heapSort alogrithm 
	heapsort(build_info);
	
	/*for (int i = 0; i <build_info.size(); i++)
	{
		string cc;
		if (build_info[i].left== true)
		{
			cc = "Lft";
		}
		else
		{cc="Rht";
		}
		cout<< cc<<" "<< build_info[i].x<<" "<< build_info[i].height<<" " <<"B"<<build_info[i].label<<endl;

	}*/

	//Building a heap of size = number of buildings
	MPQ max_heap(t_building);
	int current_Max= -1; //current Max is negative b/c no height can be negative

	if (build_info[0].x  != 0) //if no building at x=0, height is =0
	{
		cout << 0 <<" "<<0<<endl;
	}

	 for(int i = 0; i < build_info.size();i++) //Iterate over the sorted building list
	 {
        if(build_info[i].left == true) //checking if the current x coordinate is left of a building
		{ 
            max_heap.insert(build_info[i].height, build_info[i].label); //inserting building info to heap 
			//Altering the heap as long as building either start at the same or ends the same coordinate
			while( i < build_info.size() - 1 && build_info[i].x == build_info[i + 1].x) 
			
			{
				if (build_info[i + 1].left == true)
				{
					max_heap.insert(build_info[i + 1].height, build_info[i + 1].label);
				}
				else 
				{
					max_heap.Remove(build_info[i + 1].label);
				}

				i++;
			}
			// Then checking the max value/height at that x
			if(max_heap.GetMax() != current_Max)
			{
				current_Max = max_heap.GetMax();
                cout << build_info[i].x << " " <<current_Max << endl;
			}
			
        }
		
		else if (build_info[i].left == false )
		{ 
				max_heap.Remove(build_info[i].label);
				while( i < build_info.size() - 1 && build_info[i].x == build_info[i + 1].x)
				{
					if (build_info[i + 1].left == true)
					{
						max_heap.insert(build_info[i + 1].height, build_info[i + 1].label);
					}
					else 
					{
						max_heap.Remove(build_info[i + 1].label);
					}
					
					i++;
				}
				if(max_heap.GetMax() != current_Max)
				{
					current_Max = max_heap.GetMax();
					cout << build_info[i].x << " " <<current_Max << endl;
				}
		}
	 }
	return 0;
}
