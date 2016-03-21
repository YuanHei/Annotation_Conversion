#include "conversion.h"

extern int CommentConvert(FILE *inputfile, FILE *outputfile);

//VC -->

/***************************************
 *Function name: main
 *Function Dis:  
 *input argu  : void
 *output argu : 0 OK
                -1 Error
 what   why   when   who

 ***************************************/

int main()
{
	FILE *fpIn = NULL;  //inputfile
	FILE *fpOut = NULL; //outputfile

	fpIn = fopen("input.c","r");             
	if(NULL == fpIn)
	{
		cout<<"Open input file fail!"<<endl;
		return -1;
	}
	fpOut = fopen("output.c","w");            
	if(NULL == fpOut)
	{
		cout<<"Open output file fail!"<<endl;
		return -1;
	}

	CommentConvert(fpIn,fpOut);            

	fclose(fpIn);                            
	fclose(fpOut);
	return 0;
}
