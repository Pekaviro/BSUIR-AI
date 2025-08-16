#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	double y[17];
	int k = 0;
	for (double i = -1; i <= 0.5; i += 0.25) {
		y[k] = 1;
		k++;
	}
	for (double i = 0.75; i <= 1; i += 0.25) {
		y[k] = sin(i)*sin(i);
		k++;
	}
	for (double i = 1.25; i <= 3; i += 0.25) {
		y[k] = exp(i)-1;
		k++;
	}
	k = 0;
	for (double i = -1; i <= 3; i += 0.25) {
		cout << setw(5) << i << setw(10) << y[k] << endl;
		k++;
	}
}