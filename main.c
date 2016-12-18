/*
 * main.c
 *
 *  Created on: 2016Äê12ÔÂ12ÈÕ
 *      Author: CHN28150056
 */


#include <stdio.h>
#include <stdint.h>

int main(int argc,char *argv[])
{
	FILE *txt;
	FILE *bin;

	int out,in;
	int data[2];
	uint32_t i = 0;
	uint32_t cnt = 0;

	if(argc != 3)
	{
		printf("useage: txt2bin file.txt file.bin\n");
		return -1;
	}

	txt = fopen(argv[1],"r");
	if(!txt)
	{
		printf("%s cannot be open!\n",argv[1]);
		return -1;
	}

	bin = fopen(argv[2],"wb");
	if(!bin)
	{
		printf("could not create the binary file: %s\n",argv[2]);
		return -1;
	}

	while(1)
	{
		out = fgetc(txt);

		if(out == EOF)
		{
			if(i==1)
			{
				fputc(data[0],bin);
				cnt++;
			}
			break;
		}
		else if(out == ' ' || out == '\n' || out == '\r')
		{
			continue;
		}
		else if(out>='0' && out<='9')
		{
			out = out -'0';
		}
		else if(out>='a' && out<='f')
		{
			out = out -'a' + 10;
		}
		else if(out>='A' && out<='F')
		{
			out = out -'A' + 10;
		}
		else
		{
			printf("the txt file contains non-binary character!\n");
			fclose(bin);
			fclose(txt);
			return -1;
		}

		data[i] = out;
		i++;
		if(i == 2)
		{
			i = 0;
			in = (data[0]<<4) + data[1];
			fputc(in,bin);
			cnt++;
		}
	}

	fclose(bin);
	fclose(txt);

	printf("convert success!\n");
	printf("totally %d bytes!\n", cnt);
	return 0;
}
