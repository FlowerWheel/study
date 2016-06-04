#include <iostream>

using namespace std;

typedef int	index;
index height = -1;

class Screen{
	public:
		typedef int	index;
		Screen( index cur = 2, index ht = 2, index wd = 2 )
			:cursor(cur), height(ht), width(wd){
				
			}
		void dummy_fcn(index height)
		{
	//		cursor = width * height;
			cursor = width * this->height;
			::height = height;
		}
		void print(void) const
		{
			cout << cursor << " " << height << " " << width << endl;
		}
	private:
		index cursor;
		index height;
		index width;
};
int main(void)
{
	int i;

	Screen	scr;
	
	scr.print();
	cout << height << endl;

	scr.dummy_fcn(3);
	scr.print();
	cout << height << endl;

	return 0;
}
