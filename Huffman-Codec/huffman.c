/**
	huffman.c
	Purpose: This is an implementation of the Huffman Codec
	Usage: 
		Encoding:
		./huffman encode <input file> <output file>
		Decoding:
		./huffman decode <input file> <output file>
	
	@author Narasimha Murthy
	@version 1.0 2/19/2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "table.h"

int main(int argc, char *argv[])
{
	/* Create a new table */
        table_t table = table_new();
        unsigned char *currentChar = malloc(sizeof(char));
	unsigned char *out_buffer = malloc(sizeof(char));
        FILE *fp_in, *fp_out;

        if(argc != 4)
        {
                printf("Usage wrong\n");
                exit(0);
        }

        fp_in = fopen(argv[2],"rb");
        fp_out = fopen(argv[3], "wb");

	/* Check to see whether to encode or decode */
        if(strcmp(argv[1],"encode") == 0)
        {
		/* First pass. Read all the bytes from the file and update the table */
                while(fread(currentChar, sizeof(char), 1, fp_in) == 1)
                {
                        find_and_increment(table, currentChar, 1);
                }
                fclose(fp_in);
		
		/* Build the Huffman Code */
                build_code(table);

                fp_in = fopen(argv[2],"rb");
		/* Start encoding. Write the number of table entries first to the output file */
                fwrite(&table->len, sizeof(int) , 1, fp_out);
		/* Write the symbols and the corresponding frequencies to the output file */
                int i = -1;
                while(++i < table->len)
                {
                        fwrite(&table->entry[i].symbol[0], 1,1, fp_out);
                        fwrite(&table->entry[i].frequency, sizeof(int),1,fp_out);
                }
		int j = 7;			// A counter to pack the patterns into bytes
		int written_out = 0;		// A flag to check whether or not to write the output
		/* Second Pass. Read the bytes from the input file and encode */
                while(fread(currentChar, sizeof(char) , 1, fp_in) == 1)
                {
			written_out = 0;
                        int index = find_symbol(table, currentChar, 1);
                        if(index != -1)
                        {
				i = -1;
				while( ++i < table->entry[index].size )
				{
					if(table->entry[index].variable_bit_pattern[i] == '1')
					{
						out_buffer[0] |= 1 << j;
					}
					else{
						out_buffer[0] &= ~(1 << j);
					}
					/* Write the output buffer if it contains 8 bits */
					if(--j == -1)
					{
						fwrite(out_buffer, sizeof(char) ,1,fp_out);
						written_out = 1;
						j = 7;
					}
				}
                        }
                }
		/* While encoding the last few bytes, all 8 bits of the output buffer may not be filled. In that case write out whatever is filled. 
			The un-filled bits will be don't care*/
		if(written_out == 0)
		{
			fwrite(out_buffer, sizeof(char) ,1,fp_out);
		}
		/* Free the allocated memories */
                free(out_buffer); free(currentChar);
        }else if(strcmp(argv[1],"decode") == 0){
		int size;
		char *symbol = malloc(sizeof(char));
		char currentChar;
		char *pattern = malloc(sizeof(char));
		int pattern_size = 0;
		int frequency;
		/* Create a new table */
		table_t table = table_new();
		/* Read the first 4 bytes which will give us the size of the table */
		fread(&size, sizeof(int), 1, fp_in);
		/* Read the next 'size'*(1+ sizeof(int)) bytes and recreate the Binary Tree and hence the Huffman coding */
		int i = -1;
		while(++i < size)
		{
			fread(symbol, 1, 1, fp_in);
			fread(&frequency, sizeof(int), 1, fp_in);
			table_add_with_frequency(table, symbol, 1, frequency);
		}
		build_code(table);
		double decoded = 0;		// A counter of the decoded chars
		double total_chars;
		double bytes =0;
		/* Get the total chars and check with the total decoded chars. Stop if they both are equal. This is to ignore the don't care bits */
		total_chars = sum_frequency(table);
		/* Read the file and get the encoded patterns */
		while(fread(&currentChar, sizeof(char), 1, fp_in) == 1)
		{
			++bytes;
			i = -1;
			while( ++i < 8)
			{
				pattern = realloc(pattern, (pattern_size + 1)*sizeof(char));
				/* Split the byte into bits and check for the pattern by taking one bit at a time */
				if( (currentChar & (1 << (7-i) )) >> (7-i) == 1 )
					pattern = suffix(pattern, pattern_size, '1');
				else
					pattern = suffix(pattern, pattern_size, '0');

				++pattern_size;
				
				/* If none of the pattern entries in the table starts with the given pattern then it must be a pattern for some symbol
					Decode it and output to the file */
				if(find_if_pattern_starts_with(table, pattern, pattern_size) == 0)
				{
					int index = find_symbol_from_pattern(table, pattern, pattern_size);
					if(index != -1)
					{
						fwrite(table->entry[index].symbol, 1,1, fp_out);
						++decoded;
						if( decoded == total_chars)
							break;
					}
					pattern_size = 0;
				}
			}
		}
		/* Free the allocated memories*/
		free(pattern); free(symbol);
	}
	/* Free the allocated memories of the table and its entries */
	table_free(table);
	/* Close the input and output files */
        fclose(fp_in); fclose(fp_out);
}

