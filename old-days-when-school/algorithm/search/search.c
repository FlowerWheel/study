#include "search.h"

int BinSearch(const ElemType *Arr, const int l, const int r, const int key)
{
	int		mid;

	if ( l > r )
		return -1;

	mid = ( l + r ) / 2;
	if ( key == Arr[mid] )
		return mid;
	else if ( key < Arr[mid] )
		return BinSearch(Arr, l, mid - 1, key);
	else 
		return BinSearch(Arr, mid + 1, r, key);
}
