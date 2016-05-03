#include <bits/stdc++.h>
#include <unistd.h>
#include <string.h>

using namespace std;

// objdump -l -d helloworld > helloworld_perm.asm

void mess_up() {
	char* mess_this_up = "here to break the stack";
	int a = 5;
	int b = 0;
	int c = 1;
	
	a *= ~b;
}


void call_me() {
	int j = 0;
	++j;
	
	mess_up();
	
	j <<= ++j;
	j += 2;
}


void random_funct() {
	int i = 0;
	++i;
	
	call_me();
	
	int b = 5;
	i <<= b;
	b *= i;
}



int main() {
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
	
	random_funct();
	
	g *= G;
	
	g += sum;
	
	s /= g;
	
	mess_up();
	
	random_funct();
	
	g *= sum;
	
	return 0;
}
