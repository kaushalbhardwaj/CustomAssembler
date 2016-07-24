#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* decimalToBinary(int decimalNumber);

void main(void) 
{
	char input[30], opcode[30], in[20], ch, labelFile[20];
	int indicator1, indicator2, indicator3, indicator4, i;
	int lineNumber; //to indicate line number in code
	int countError; //to count the number of errors in the code
	int countLabel; // to count number of labels in the input.txt

	FILE *inputFile, *opcodeFile, *registerFile, *decimalFile, *outputFile, *labelOutput, *labelInput, *fh;
	inputFile = fopen("input.txt", "r");		//reference to input.txt file containing input assembly code 
	labelOutput = fopen("label.txt", "w");		//reference to label.txt file stores information about label present in input.txt

	if((!inputFile) || (!labelOutput)) //checks whether files openup or have some error while opening them 
	{
	  printf("Error in opening files\n");
	  return; 

	}
	printf("Program for a simple Two Pass Assembler\n\n");
	printf("---------------------Processing Input-------------------------\n");


	lineNumber = 0;
	countError = 0;
	countLabel = 0;
	
    int *bin;
	fscanf(inputFile,"%s",in);	//scans input file

	// identifies labels in the assembly input file through presence of ":" by running till end of input file
    while(!feof(inputFile))		
    {
        if(strchr(in,':') != NULL)	//if colon occurs means label in assembly instruction input file
        {
            countLabel++;
            bin = decimalToBinary(countLabel);

	    int i1;
	    char inp[20];
	    int length=strlen(in);
	    for(i1=0;i1<length-1;i1++)
	    {
	      inp[i1]=in[i1];
	      
	    }
	    inp[i1]='\0';
            int c;
	    c=0;
            fprintf(labelOutput, "%s ",inp);
            while(c < 16)
            {
                fprintf(labelOutput, "%d", *(bin+c));
                c++;
            }
            fprintf(labelOutput,"\n");
        }
        fscanf(inputFile, "%s", in);
    }

    fprintf(labelOutput,"----"); // add ---- at the end of label.txt to indicate end of file
    fclose(labelOutput);
    fclose(inputFile);
    inputFile = fopen("input.txt", "r");
    labelInput = fopen("label.txt", "r");
    opcodeFile = fopen("opcode.txt", "r"); 		//reference to opcode.txt file containing opcode for our ISA
    decimalFile = fopen("decimalToBinary.txt", "r");//reference to decimalToBinary.txt file containing binary equivalent of decimal
    outputFile = fopen("output.txt", "w");		//reference to output.txt file which stores binary conversion of assembly instructions
    registerFile = fopen("register.txt", "r");	//reference to register.txt file containing binary equivalent of all registers
	if((!inputFile) || (!outputFile) || (!opcodeFile) || (!registerFile) || (!decimalFile) || (!labelInput)) //checks whether files openup or have some error while opening them 
	{
	  printf("Error in opening files\n");
	  return; 
	}
    
    while(!feof(inputFile)) //This while loop runs till the end of input file
    {
		rewind(opcodeFile); //sets cursor to the begining of file so that we can use it for next scan of input file
		rewind(registerFile);
		rewind(decimalFile);
		rewind(labelInput);
		fscanf(inputFile, "%s", input);

		if(strcasecmp(input, "HLT")==0)
		{
		    fprintf(outputFile,"\n10100000111001000010010010000000"); //if HLT occurs in input file append this to output file   
			break;
		}


        //This while loop scans labelFile and use it to write binary equivalent of labels present in input file
        while(1)
        {

			fscanf(labelInput,"%s",labelFile); //read label from label.txt
			if(strcasecmp(labelFile,"----")==0) // if end of label.txt file reached break from parent while loop
			{
				break;
			}
			if(strchr(input,':') != NULL)
			{
			 
			  int i1;
			  char inp[20];
			  int length=strlen(input);
			  for(i1=0;i1<length-1;i1++)
			  {
			      inp[i1]=input[i1];
	      
			  }
			    inp[i1]='\0';
			 
			    if(strcasecmp(inp, labelFile) == 0) { //if label found
             
				fscanf(labelInput,"%s",labelFile); //read binary equivalent of label from label.txt
				fprintf(outputFile,"\n0000000000000000%s",labelFile); //write in output file
				indicator1 = 1;
				break;
				
			      
			    }
			  
			}
			
			else if(strcasecmp(input, labelFile) == 0) { //if label found
             
				fscanf(labelInput,"%s",labelFile); //read binary equivalent of label from label.txt
				fprintf(outputFile,"%s",labelFile); //write in output file
				indicator1 = 1;
				break;
			} else {
				fscanf(labelInput,"%s",labelFile); //read binary value equivalent to label scanned above
				indicator1 = 0;
			}
		}

		//This while loop scans opcodeFile and use it to write binary equivalent of opcodes present in input file
		while(1) { 
			fscanf(opcodeFile,"%s",opcode); //read first opcode from opcode.txt file
			if(strcasecmp(opcode,"----")==0) //if at the end of opcode.txt break from parent while loop
			{
				break;
			}
			if(strcasecmp(input, opcode) == 0) { //if opcode found
				fscanf(opcodeFile, "%s", opcode); //read binary equivalent of opcode from opcode.txt
				fprintf(outputFile, "\n%s", opcode); //write in output file
				indicator2 = 1;
				break;
			} else {
				fscanf(opcodeFile, "%s", opcode); //read binary value equivalent to opcode scanned above
				indicator2 = 0;
			}
		}
		if(indicator2 == 1) //if value of indicator2 becomes one means an opcode found which must be written in a new line of code
			lineNumber++;

		//This while loop scans registerFile and use it to write binary equivalent of register present in input file
		while(1) {
			fscanf(registerFile, "%s", opcode); //read first register from register.txt file
			if(strcasecmp(opcode, "----") == 0) //if at the end of registerFile.txt break from parent while loop
			{
				break;
			}
			if(strcasecmp(input, opcode) == 0) 
			{ //if register found
				fscanf(registerFile, "%s", opcode); //read binary equivalent of register from registerFile.txt
				fprintf(outputFile, "%s", opcode); //write in output file
				indicator3 = 1;
				break; 
			} else { 
			  
				fscanf(registerFile,"%s",opcode); //read binary value equivalent to register scanned above
				indicator3 = 0;
			}
		}

		//This while loop scans decimalFile and use it to write binary equivalent of decimals present in input file
		while(1)
		{
			fscanf(decimalFile,"%s",opcode); //read first decimal from decimalFile.txt file
			if(strcasecmp(opcode,"----")==0) //if at the end of decimalFile.txt break from parent while loop
			{
				break;
			}
			if(strcasecmp(input,opcode)==0) { //if decimal found
				fscanf(decimalFile,"%s",opcode); //read binary equivalent of decimal from decimalFile.txt
				fprintf(outputFile,"%s",opcode);
				indicator4 = 1; 
				break;
			} else { //read binary value equivalent to decimal scanned above
				fscanf(decimalFile,"%s",opcode);
				indicator4 = 0;
			}
		}

		if(!indicator1 && !indicator2 && !indicator3 && !indicator4)
		{
			printf("\nError occured in Line Number: %d", lineNumber);
			printf("\n\"%s\" is not a valid Mnemonic or Operand\n",input);
			fprintf(outputFile," \"%s\"",input); //write incorrect mnemonic or operand to output.txt
			countError++;
			printf("\n1. Continue execution\t2. Exit Program\n");
			scanf("%d", &i);
			switch(i)
			{
			  case 1:
			    continue;
			    break;
			    
			  case 2:
			    break;
			    
			  default:
			    printf("Wrong Entry\n"); 
			  
			}
		}
	}
	fclose(inputFile);
	fclose(outputFile);
	fclose(opcodeFile);
	fclose(labelInput);
	fclose(registerFile);
	fclose(decimalFile);
	if (countError == 0)
		printf("\nProgram Assembled Successfully.\n"); //count variable to print total number of errors
    else
    	printf("\nTotal %d Errors found in code.\n", countError);
    	return;
}

int* decimalToBinary(int decimalNumber) // convert decimal number to binary number 1 to 0000001
{
    int quotient, i, j;
    int* binaryNumber;
    binaryNumber = (int*)malloc(16*sizeof(int));
    for(i = 0; i < 16; i++)
    {
        binaryNumber[i]=0;
    }
    i=15;
    quotient = decimalNumber;
    while(quotient!=0)
    {
         binaryNumber[i]= quotient % 2;
	 i=i-1;
         quotient = quotient / 2;
    }
    return binaryNumber;
} 
