#pragma once

#include <iostream>
#include <stdio.h>
using namespace std;

extern int CommentConvert(FILE *inputfile, FILE *outputfile);   
typedef enum                                                   
{
	NO_COMMENT_STATE,                                          
	C_COMMENT_STATE,                                           
	CPP_COMMENT_STATE,                                         
	STR_STATE,                                                  
	END_STATE                                                 
}STATE_ENUM;

typedef struct                                                 
{
	FILE *inputfile;                                           
	FILE *outputfile;                                           
	STATE_ENUM ulstate;                                         
}STATE_MACHINE; 
//
STATE_MACHINE g_state = {0};                                   
///////////////////////////////////////////////////
void EventPro(char ch);                                        
void EventProAtNo(char ch);                                    
void EventProAtC(char ch);                                     
void EventProAtCpp(char ch);                                   
void EventProAtStr(char ch);                                   
////////////////////////////////////////////////////

int CommentConvert(FILE *inputfile, FILE *outputfile)   
{	
	if(inputfile==NULL || outputfile==NULL)
	{
		cout<<"input argument Invalid!"<<endl;
		return -1;
	}

	g_state.inputfile = inputfile;                             
	g_state.outputfile = outputfile;
	g_state.ulstate = NO_COMMENT_STATE;

	char ch;
	while(g_state.ulstate != END_STATE)                      
	{
		ch = fgetc(g_state.inputfile); 
		EventPro(ch);
	}
	return 0;
}

void EventPro(char ch)                                      
{
	switch(g_state.ulstate)
	{
	case NO_COMMENT_STATE:
		EventProAtNo(ch);
		break;
	case C_COMMENT_STATE:
		EventProAtC(ch);
		break;
	case CPP_COMMENT_STATE:
		EventProAtCpp(ch);
		break;
	case STR_STATE:
		EventProAtStr(ch);
		break;
	case END_STATE:
		break;
	}
}
//C++//  C /**/
void EventProAtNo(char ch)
{
	char nextch;
	switch(ch)
	{
/*	case '"':
		EventProAtStr(ch);
		break;*/
	case '/':   // // /* 
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/') // C++
		{
			fputc('/',g_state.outputfile);
			fputc('*',g_state.outputfile);
			g_state.ulstate = CPP_COMMENT_STATE;
		}
		else if(nextch == '*') //C
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
			g_state.ulstate = C_COMMENT_STATE;
		}
		break;
	case '*':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/') // C++
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
			g_state.ulstate = NO_COMMENT_STATE;
		}
		break;
	case EOF:
		g_state.ulstate = END_STATE;
		break;
	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}
void EventProAtC(char ch)
{
	char nextch;
	switch(ch)
	{
	case '*':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/')
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);
			g_state.ulstate = C_COMMENT_STATE;
		}
		break;
	case '/':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/')
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);
			g_state.ulstate = CPP_COMMENT_STATE;
		}
		else if(nextch == '*')
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);
			g_state.ulstate = NO_COMMENT_STATE;
		}
		break;
	case EOF:
		fputc('*',g_state.outputfile);
		fputc('/',g_state.outputfile);
		g_state.ulstate = END_STATE;
		break;
	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}
void EventProAtCpp(char ch)
{
	//123  /*123
	char nextch;
	switch(ch)
	{
	case '/':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/') // C++
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);
			g_state.ulstate = CPP_COMMENT_STATE;
		}
		else if(nextch == '*')
		{
			fputc(' ',g_state.outputfile);
			fputc(' ',g_state.outputfile);
			g_state.ulstate = C_COMMENT_STATE;
		}
		break;
	case '*':
		nextch = fgetc(g_state.inputfile);
		if(nextch == '/')
		{
			fputc(ch,g_state.outputfile);
			fputc(nextch,g_state.outputfile);
			g_state.ulstate = NO_COMMENT_STATE;
		}
		break;
	case EOF:
		fputc('*',g_state.outputfile);
		fputc('/',g_state.outputfile);
		g_state.ulstate = END_STATE;
		break;
	default:
		fputc(ch,g_state.outputfile);
		break;
	}
}
void EventProAtStr(char ch){           //hou qi shi xian
/*	fputc(ch,g_state.outputfile);*/
}
