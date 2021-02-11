#ifndef mpq_h
#define mpq_h
#include <string>
#include <vector> 
using namespace std;
struct in_view{	int value;	int label;};
class MPQ
{
public:
	explicit MPQ( int capacity); //	constructor
	~MPQ();//destructor
	bool isEmpty( ) const;//return true if 
	void insert( const int & val, const int & lab );
	int Remove(const int & x);
	const int GetMax() const;
private:
	int currentSize; 

	vector<in_view> Heap;
	vector<int> Location;
	//void buildarray( );
	void percolateDown( int hole );
};
#endif