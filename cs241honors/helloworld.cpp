#include <bits/stdc++.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {
	//cout << "Hello world\n";
	/*
	int k = 4;
	k++;
	k*=k;
	cout << k << "\n";
	k++;
	cout << k << "\n";
	*/
	/*
	write(1, "Hello world\n", 13);
	write(1, "Hello\n", 7);
	write(1, "world.\n", 8);
	write(1, "Hello worldz\n", 14);
	write(1, "Hi world\n", 10);
	
	char* str = (char*)malloc(5);
	
	strcpy(str, "hello");			// should be error here
	
	int a = 50;
		
	int b = 100;
	int retq = 100;
	
	cerr << "Will this appear????\n";
	*/
	
	// objdump -l -d helloworld > helloworld_perm.asm

	char* hello = "hello world";
	
	double g = 1.05;
	double G = 11.0567;
	
	char c = 'a';
	
	unsigned int ui = -1;
	
	unsigned long long ull = -1;
	
	unsigned long ul = -1;
	
	long long int ll = -1;
	
	long l = 1L << 32;
	
	short s = 1 << 14; 

	int sum = 0;
	for (int i = 0; i < 10; ++i)
		sum += i;
		
	cout << "Sum is: " << sum << "\n";			// must have this in order for stack frame to move
	
	g *= G;
	
	return 0;
}
