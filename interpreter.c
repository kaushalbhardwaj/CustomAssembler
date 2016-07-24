#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<math.h>

long long int binaryToDecimal(char *index);		//function to convert binary number to decimal number given binary number as a string
char * extractBinary(char *inp,int start,int end);	//function to extract binary bits from a given instruction and using it for further use
long long int putRegisterMapValue(char *index,long long int val2,long long int registerMap[35]); //function to store values in specified register in the registerMap
long long int getRegisterMapValue(char *index,long long int registerMap[35]);	//function to get values stored in the specified register in registerMap 

void main(void) 
{
	char inp[36], op[36], a[10], ch, lbl[17];
	char temp[10];
	char temp2[17];
	long long int registerMap[35];
	
	long long int zeroFlag=binaryToDecimal("11011");	//variable to store index of zero flag in registerMap
	long long int signFlag=binaryToDecimal("11100");	//variable to store index of sign flag in registerMap
	registerMap[zeroFlag]=0;
	registerMap[signFlag]=0;
	
	FILE *file_inp, *file_out, *fh;
	file_inp = fopen("output.txt", "r");		//reference to output file created by assembler in first step
	file_out = fopen("result.txt", "w");		//reference to result file for storing result of interpreter process

	if((!file_inp) || (!file_out)) 
		return; //test whether each file opens successfully

	printf("Program for executing binary file\n");
	printf("-----------------------------Processing Request--------------------------\n");


    int *p;
    
    while(!feof(file_inp))	//This while loop reads binary instruction created by the assembler code of first part
    {
		fscanf(file_inp, "%s", inp);
		//printf("%s\n",inp);

		int len=strlen(inp);
		//printf("%d\n",len);
		if(strncmp(inp, "001",3)==0)				//opcode length=11
		{
		    //puts(inp);
		  //printf("001\n");
		  char *index=extractBinary(inp,11,15);
		  char *immValue=extractBinary(inp,16,31);
		  long long int value=binaryToDecimal(immValue);
		  if(strncmp(inp,"00100000000",11)==0)			//code for MVI
		    {
			//printf("mvi\n");
			long long int regValDec=putRegisterMapValue(index,value,registerMap); 
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
		    }
		    else if(strncmp(inp,"00100000001",11)==0)		//code for SUBI
		    {
			//printf("subi\n");
			long long int x=getRegisterMapValue(index,registerMap);
			long long int regValDec=putRegisterMapValue(index,x-value,registerMap);
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
		      
		    }
		    else if(strncmp(inp,"00100000010",11)==0)		//code for ADDI
		    {
			//printf("addi\n");
			long long int x=getRegisterMapValue(index,registerMap);
			long long int regValDec=putRegisterMapValue(index,x+value,registerMap);
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
		    }
		    else if(strncmp(inp,"00100000011",11)==0)		//code for MULI
		    {
			//printf("muli\n");
			long long int x=getRegisterMapValue(index,registerMap);
			long long int regValDec=putRegisterMapValue(index,x*value,registerMap);
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
		    }
		    else if(strncmp(inp,"00100000100",11)==0)		//code for DIVI
		    {
			//printf("divi\n");
			long long int x=getRegisterMapValue(index,registerMap);
			long long int regValDec=putRegisterMapValue(index,x/value,registerMap);
		      
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
		    }
		    else if(strncmp(inp,"00100000101",11)==0)		//code for MODI
		    {
			//printf("modi\n");
			long long int x=getRegisterMapValue(index,registerMap);
			long long int regValDec=putRegisterMapValue(index,x%value,registerMap);
		      
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
		    }
		    else if(strncmp(inp,"00100000110",11)==0)		//code for CMPI
		    {
			//printf("cmpi\n");
			long long int x=getRegisterMapValue(index,registerMap);
			if(x==value)
			{
			 registerMap[zeroFlag]=1;
			 registerMap[signFlag]=0;
			}
			else if(x<value)
			{
			  registerMap[signFlag]=1;
			  registerMap[zeroFlag]=0;
			  
			}
			else
			{
			  registerMap[signFlag]=0;
			  registerMap[zeroFlag]=0;
			  
			}
		    }
		    
		    //printf("001\n");
		    
		}
		else if(strncmp(inp, "010",3)==0)			//opcode length=16
		{
		//printf("010\n");
		  
		  char *label=extractBinary(inp,16,31);
		   if(strncmp(inp,"0100000011100000",16)==0)		//code for JZR
		    {
			//printf("jzr\n");
			if(registerMap[zeroFlag]==1)
			{
			
			  rewind(file_inp);
			while(!feof(file_inp))
			{
			  
			  fscanf(file_inp, "%s", op);
			 //printf("in while=%s\n",op);
			  if(strncmp(op, "000",3)==0)
			 {
			   //printf("in if\n");
			   char *label2=extractBinary(op,16,31);
			   if(strcmp(label,label2)==0)
			   {
			     //printf("%s\t%s\n",label,label2);
			    //printf("label reached\n");
			     break;
			   }
			 }
			  
			}
			  
			}
			else 
			{ 
			  
			}
			registerMap[zeroFlag]=0;
			registerMap[signFlag]=0;
		      
			
		      
		    }
		    else if(strncmp(inp,"0100000011100001",16)==0)		//code for JEQ
		    {
			//printf("jeq\n");
			if(registerMap[zeroFlag]==1)
			{
			
			  rewind(file_inp);
			while(!feof(file_inp))
			{
			  
			  fscanf(file_inp, "%s", op);
			 //printf("in while=%s\n",op);
			  if(strncmp(op, "000",3)==0)
			 {
			   //printf("in if\n");
			   char *label2=extractBinary(op,16,31);
			   if(strcmp(label,label2)==0)
			   {
			     //printf("%s\t%s\n",label,label2);
			    //printf("label reached\n");
			     break;
			   }
			 }
			  
			}
			  
			}
			else 
			{ 
			  
			}
			registerMap[zeroFlag]=0;
			registerMap[signFlag]=0;
		      
		    }
		    else if(strncmp(inp,"0100000011100010",16)==0)		//code for JMP
		    {
			//printf("jmp\n");
			rewind(file_inp);
			while(!feof(file_inp))
			{
			  
			  fscanf(file_inp, "%s", op);
			 //printf("in while=%s\n",op);
			  if(strncmp(op, "000",3)==0)
			 {
			   //printf("in if\n");
			   char *label2=extractBinary(op,16,31);
			   if(strcmp(label,label2)==0)
			   {
			     //printf("%s\t%s\n",label,label2);
			   // printf("label reached\n");
			     break;
			   }
			 }
			  
			}
		      
		    }
		    else if(strncmp(inp,"0100000011100011",16)==0)		//code for JLE
		    {
			//printf("jle\n");
			if(registerMap[signFlag]==1)
			{
			
			  rewind(file_inp);
			while(!feof(file_inp))
			{
			  
			  fscanf(file_inp, "%s", op);
			 //printf("in while=%s\n",op);
			  if(strncmp(op, "000",3)==0)
			 {
			   //printf("in if\n");
			   char *label2=extractBinary(op,16,31);
			   if(strcmp(label,label2)==0)
			   {
			     //printf("%s\t%s\n",label,label2);
			    //printf("label reached\n");
			     break;
			   }
			 }
			  
			}
			  
			}
			else 
			{ 
			  
			}
			registerMap[zeroFlag]=0;
			registerMap[signFlag]=0;
		      
		      
		    }
		      
		  
		    
		}
		else if(strncmp(inp, "011",3)==0)		//opcode length=22
		{
		//  printf("011\n");
		
		  char* registerDes=extractBinary(inp,22,26);
		  char* registerSrc=extractBinary(inp,27,31);
		  if(strncmp(inp,"0110000011100100000000",22)==0)		//code for MVR
		   {
			//printf("mvr\n");
			long long int value=getRegisterMapValue(registerSrc,registerMap);
			long long int regValDec=putRegisterMapValue(registerDes,value,registerMap);
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
			
			
		   }  
		   else if(strncmp(inp,"0110000011100100000001",22)==0)		//code for SUBR
		   {
			//printf("subr\n");
			long long int value=getRegisterMapValue(registerSrc,registerMap);
			long long int value2=getRegisterMapValue(registerDes,registerMap);
			long long int regValDec=putRegisterMapValue(registerDes,value2-value,registerMap);
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
			
			
		   }  
		   else if(strncmp(inp,"0110000011100100000010",22)==0)		//code for ADDR
		   {
			//printf("addr\n");
			long long int value=getRegisterMapValue(registerSrc,registerMap);
			long long int value2=getRegisterMapValue(registerDes,registerMap);
			long long int regValDec=putRegisterMapValue(registerDes,value2+value,registerMap);
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
			
			
		   } 
		   else if(strncmp(inp,"0110000011100100000011",22)==0)		//code for MULR
		   {
			//printf("mulr\n");
			long long int value=getRegisterMapValue(registerSrc,registerMap);
			long long int value2=getRegisterMapValue(registerDes,registerMap);
			long long int regValDec=putRegisterMapValue(registerDes,value2*value,registerMap);
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
			
			
		   } 
		   else if(strncmp(inp,"0110000011100100000100",22)==0)		//code for DIVR
		   {
			//printf("divr\n");
			long long int value=getRegisterMapValue(registerSrc,registerMap);
			long long int value2=getRegisterMapValue(registerDes,registerMap);
			long long int regValDec=putRegisterMapValue(registerDes,value2/value,registerMap);
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
			
			
		   } 
		   else if(strncmp(inp,"0110000011100100000101",22)==0)		//code for MODR
		   {
			//printf("MODr\n");
			long long int value=getRegisterMapValue(registerSrc,registerMap);
			long long int value2=getRegisterMapValue(registerDes,registerMap);
			long long int regValDec=putRegisterMapValue(registerDes,value2%value,registerMap);
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
			
			
		   } 
		    else if(strncmp(inp,"0110000011100100000110",22)==0)	//code for CMPR
		   {
			//printf("cmpr\n");
			long long int value=getRegisterMapValue(registerSrc,registerMap);
			long long int value2=getRegisterMapValue(registerDes,registerMap);
			if(value==value2)
			{
			 registerMap[zeroFlag]=1;
			 registerMap[signFlag]=0;
			}
			else if(value2<value)
			{
			  registerMap[signFlag]=1;
			  registerMap[zeroFlag]=0;
			  
			}
			else
			{
			  registerMap[signFlag]=0;
			  registerMap[zeroFlag]=0;
			  
			}
		   }
		  else if(strncmp(inp,"0110000011100100000111",22)==0)		//code for AND
		   {
			//printf("andr\n");
			long long int value=getRegisterMapValue(registerSrc,registerMap);
			long long int value2=getRegisterMapValue(registerDes,registerMap);
			long long int regValDec=putRegisterMapValue(registerDes,value2 & value,registerMap);
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
			
			
		   }
		   else if(strncmp(inp,"0110000011100100001000",22)==0)		//code for OR
		   {
			//printf("orr\n");
			long long int value=getRegisterMapValue(registerSrc,registerMap);
			long long int value2=getRegisterMapValue(registerDes,registerMap);
			long long int regValDec=putRegisterMapValue(registerDes,value2 | value,registerMap);
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
			
			
		   }
		
		   
		    
		}
		else if(strncmp(inp, "100",3)==0)				//opcode length=27
		{
		   char* registerDes=extractBinary(inp,27,31);
		  if(strncmp(inp,"100000001110010000100100001",27)==0)		//code for INC
		   {
			//printf("inc\n");
			long long int value=getRegisterMapValue(registerDes,registerMap);
			long long int regValDec=putRegisterMapValue(registerDes,(value+1),registerMap);
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
			
			
		   }
		   else if(strncmp(inp,"100000001110010000100100010",27)==0)	//code for DEC
		   {
			//printf("dec\n");
			long long int value=getRegisterMapValue(registerDes,registerMap);
			long long int regValDec=putRegisterMapValue(registerDes,(value-1),registerMap);
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
			
			
		   }
		   else if(strncmp(inp,"100000001110010000100100011",27)==0)	//code for INP
		   {
		     int ii;
			//printf("inp\n");
			scanf("%d",&ii);
			//long long int value=getRegisterMapValue(registerDes,registerMap);
			long long int regValDec=putRegisterMapValue(registerDes,ii,registerMap);
			//printf("%lld\t%lld\n",registerMap[regValDec],regValDec);
			
			
		   }
		   else if(strncmp(inp,"100000001110010000100100100",27)==0)		//code for OUT
		   {
		     int ii;
			//printf("out\n");
			//scanf("%d",&ii);
			long long int value=getRegisterMapValue(registerDes,registerMap);
			//long long int regValDec=putRegisterMapValue(registerDes,ii,registerMap);
			printf("%lld\n",value);
			fprintf(file_out,"%lld\n",value);
			
			
		   }
		    
		}
		else if(strncmp(inp, "101",3)==0)			//opcode length=32
		{
		   //printf("101\n");
		   //printf("%s\n",inp);
		  
		  //printf("mvi2\n");
		    if(strncmp(inp,"10100000111001000010010010000000",32)==0)		//code for HLT
		    {
			//printf("hlt\n");
		     
			break;
		    }
		    else if(strncmp(inp,"10111111111111111111111111111111",32)==0)	//code for START
		    {
			//printf("start\n");
			 
		    }
	
		  
		}
		else if(strncmp(inp, "000",3)==0)					//code for label
		{
		  //printf("label\n");
		     
		}
		

		
	}
	fclose(file_inp);
	fclose(file_out);

	return;
}


long long int binaryToDecimal(char *value) /* Function to convert binary to decimal.*/
{
    long long int decimal=0, i=0, remainder;
    long long int n = atoi(value);
    
    while (n!=0)
    {
        remainder = n%10;
        n/=10;
        decimal += remainder * pow(2,i);
        ++i;
    }
    //printf("%lld\n",decimal);
    return decimal;
}

char * extractBinary(char *inp,int start,int end)	//function to extract binary from large binary string
{
	int i,j;
	char *arr=malloc(32*sizeof(char));
	char *temp2=malloc(32*sizeof(char));
	char *temp=malloc(17*sizeof(char));
		
	//printf("inp=%s\n",inp);
	for(i=0;i<32;i++)
	{
	 arr[i]='0'; 
	  
	}
	for(i=start;i<=end;i++)
	{
	 arr[i]='1';
	  
	}
	//printf("arr=%s\n",arr);
	for(i=0;i<32;i++)
	{
	 int a1=arr[i]-0x30;
	 int a2=inp[i]-0x30;
	 int a3=a1 & a2;
	 temp2[i]=(a3+0x30);
	}
	temp2[i]='\0';
	for(i=start,j=0;i<=end;i++,j++)
	{
	
	  temp[j]= inp[i];
	  //printf("%c",inp[i]);
	
	  
	}
	//printf("%s\n",temp);
	return temp;
}

long long int putRegisterMapValue(char *index,long long int value,long long int registerMap[35])		//function to add values in registerMap
{
	int i;
	
	//printf("%s\n",index);
	
	long long int regValDec= binaryToDecimal(index);
	int j=0;
	//printf("%lld\n",value);
	//printf("reg=%lld\n",regValDec);
	registerMap[regValDec]=value;
	//strcpy(registerMap[regValDec],value);
	//printf("%lld\n",registerMap[regValDec]);
	return regValDec;
}

long long int getRegisterMapValue(char *registerSrc,long long int registerMap[35])		//function to get values from registerMap
{
	int i;	
	long long int regValDec=binaryToDecimal(registerSrc);
	int j=0;
	return registerMap[regValDec];
}