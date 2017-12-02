// Author: MKozuch 
// Date: 2018-12-01

#include <stdio.h>
#include <string.h>

int solveCaptcha(const char*);
void testOf_solveCaptcha();

int solveCaptcha2(const char*);
void testOf_solveCaptcha2();

int main(int argc, char *argv[])
{
	 if(argc == 1){
		testOf_solveCaptcha(); 
		printf("\n");
		testOf_solveCaptcha2();
	}
	else if(argc == 2){
		printf("Captcha: %d\n", solveCaptcha(argv[1]));
		printf("Captcha2: %d\n", solveCaptcha2(argv[1]));
	}
	return 0;
}

int solveCaptcha(const char *captcha){
	int len = strlen(captcha);
	int sum = 0;
	
	for(int i=0; i<=len; ++i){
		if(captcha[i] == captcha[(i+1) % len])
			sum += captcha[i] - 48;
	}
	return sum;
}

void testOf_solveCaptcha(){
	printf("Test solveCaptcha\n");
	
	char *testData[] = {
		"1122",
		"1111",
		"1234",
		"91212129"
	};
	int testResult[] = {3, 4, 0, 9};
	
	for(int i=0; i<4; ++i){
		printf("Input: %s\n ", testData[i]);
		printf("\t Actual result:   %d\n", solveCaptcha(testData[i]));
		printf("\t Expected result: %d\n", testResult[i]);
	}
}

int solveCaptcha2(const char *captcha){
	int len = strlen(captcha);
	if(len % 2)
		return 0;
	
	int sum = 0;
	
	for(int i=0; i<=len; ++i){
		if(captcha[i] == captcha[(i+len/2) % len])
			sum += captcha[i] - 48;
	}
	return sum;
}

void testOf_solveCaptcha2(){
	printf("Test solveCaptcha2\n");
	
	char *testData[] = {
		"1212",
		"1221",
		"123425",
		"123123",
		"12131415"
	};
	int testResult[] = {6, 0, 4, 12, 4};
	
	for(int i=0; i<5; ++i){
		printf("Input: %s\n ", testData[i]);
		printf("\t Actual result:   %d\n", solveCaptcha2(testData[i]));
		printf("\t Expected result: %d\n", testResult[i]);
	}
}
