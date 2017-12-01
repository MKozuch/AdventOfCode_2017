// Author: MKozuch 
// Date: 2018-12-01

#include <stdio.h>
#include <string.h>

int solveCaptcha(const char*);

int main(int argc, char *argv[])
{
	 if(argc == 1){
		printf("Test\n");
		
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
	else if(argc == 2){
		printf("%d\n", solveCaptcha(argv[1]));
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