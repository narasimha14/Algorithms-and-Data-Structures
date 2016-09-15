/**
        table.h
        Purpose: Contains the structure implementations of the Huffman Table with all other necessary helper APIs
        
        @author Narasimha Murthy
        @version 1.0 2/19/2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "strfunc.h"

/*A structure that defines the table entries */
typedef struct table_entry{
	char *symbol;
	int length;
	int frequency;
	char *variable_bit_pattern;
	int size;
} table_entry;

/*A structure that defines the table */
typedef struct table{
	int len;
	int highest_freq;
	int cap;
	table_entry *entry;
} table_s, *table_t;

/*A function to create a new table with 10 table entries */
table_t table_new(void)
{
	table_s s = {0, 0, 10, malloc(10*sizeof(table_entry))};
	table_t t =  malloc(sizeof(table_s));
	*t = s;
	return t;
}

/* A function that initializes the table with entries for all 255 characters*/
table_t init_table(table_t table)
{
	int i = -1;
	while(++i <= 255)
	{
		table->entry[table->len].symbol = (char *)&i;
		table->entry[table->len].frequency = 0;
		table->entry[table->len].size = 0;
		++table->len;
	}
}

/* A function to add entries to the table with frequency for each entry already defined */
void table_add_with_frequency(table_t table, char *symbol, int length, int frequency)
{
	if (table->len == table->cap) {
                table->cap *= 2;
                table->entry = realloc(table->entry, table->cap * sizeof(table_entry));
        }
        table->entry[table->len].symbol = copystr(symbol, length);
        table->entry[table->len].length = length;
        table->entry[table->len].frequency = frequency;
        table->entry[table->len].size = 0;
        ++table->len;
        if(table->highest_freq < frequency)
                table->highest_freq = frequency;

}

/*A function to sum up all the frequencies of the table to obtain the total number of characters in the uncompressed file*/
double sum_frequency(table_t table)
{
	int i = -1;
	double sum = 0;
	while( ++i < table->len)
	{
		sum += table->entry[i].frequency;
	}
	return sum;
}

/* A function to add the table entries with symbol and the length of the symbol already known */
void table_add(table_t table, char *symbol, int length)
{
	if (table->len == table->cap) {
		table->cap *= 2;
		table->entry = realloc(table->entry, table->cap * sizeof(table_entry));
	}	
	table->entry[table->len].symbol = copystr(symbol, length);
	table->entry[table->len].length = length;
	table->entry[table->len].frequency = 1;
	table->entry[table->len].size = 0;
	++table->len;
	if(table->highest_freq < 1)
		table->highest_freq = 1;
}

/* A function to find if a symbol exists and then increment it's frequency */
int find_if_present_and_increment(table_t table, char *symbol, int length)
{
	int i = -1;
        while(++i < table->len)
        {
                if(compareString(table->entry[i].symbol, table->entry[i].length, symbol, length) == 0)
                {
                        ++table->entry[i].frequency;
                        if(table->entry[i].frequency > table->highest_freq)
                                table->highest_freq = table->entry[i].frequency;
			return i;
                }
        }
	return -1;

}

/* A function to find if a variable bit pattern already exists which starts with the given pattern 
	Need this for decoding */
int find_if_pattern_starts_with(table_t table, char *pattern, int length)
{
	int i = -1;
	while(++i < table->len)
	{	
		if( (compareString(table->entry[i].variable_bit_pattern, table->entry[i].size, pattern, length) != 0 ) && startsWith(table->entry[i].variable_bit_pattern, table->entry[i].size, pattern, length) == 0)
		{
			return 1;
		}
	}
	return 0;
}

/* A function that return the symbol associated with the given pattern */
int find_symbol_from_pattern(table_t table, char *pattern, int length)
{
	int i = -1;
	while(++i < table->len)
	{
		if( compareString(table->entry[i].variable_bit_pattern, table->entry[i].size, pattern, length) == 0 )
		{
			return i;
		}
	}
	return -1;
}	

/* A function used to find a given symbol among the table entries */
int find_symbol(table_t table, char *symbol, int length)
{
        int i = -1;
        while(++i < table->len)
        {
                if(compareString(table->entry[i].symbol, table->entry[i].length, symbol, length) == 0)
                {
                        return i;
                }
        }
        return -1;

}

/* A function that finds if a symbol exits and then increments it's frequency if it does 
	If it does not, it adds the symbol to the table entries*/
void find_and_increment(table_t table, char *symbol, int length)
{
	int id = find_if_present_and_increment(table, symbol, length);
	if(id == -1)
	{
		table_add(table, symbol, length);		
	}
}

/* A function to sort the table w.r.t to frequencies in ascending order and then print the sorted table */
void sort_table_and_print(table_t table)
{
	int j  = 0;
	while(++j <= table->highest_freq)
	{
		int i = -1;
		while(++i < table->len)
		{
			if(table->entry[i].frequency == j)
				printf("symbol %c frequency %d\n", table->entry[i].symbol[0], table->entry[i].frequency);
		}
	}
}

/* A function to sort the table w.r.t to frequencies in ascending order */
table_t sort_table(table_t table)
{
	table_t new_table = table_new();
	int j  = 0;
        while(++j <= table->highest_freq)
        {
                int i = -1;
                while(++i < table->len)
                {
                        if(table->entry[i].frequency == j)
			{
				if (new_table->len == new_table->cap) {
			                new_table->cap *= 2;
			                new_table->entry = realloc(new_table->entry, new_table->cap * sizeof(table_entry));
        			}
				new_table->entry[new_table->len].symbol =  copystr(table->entry[i].symbol, table->entry[i].length);
				new_table->entry[new_table->len].length =  table->entry[i].length;
				new_table->entry[new_table->len].frequency =  table->entry[i].frequency;
				new_table->entry[new_table->len].size = 0;
				++new_table->len;		
			}
                }
        }
	new_table->highest_freq = table->highest_freq;
	return new_table;
}

/* A function called by split_and_code that updates the variable bit pattern of the given symbol corresponding to it's position in the binary tree*/
void find_and_code(table_t table, char *symbol, char code)
{
	int i = -1;
        while(++i < table->len)
        {
		
                if(compareString(table->entry[i].symbol, table->entry[i].length, symbol, 1) == 0)
                {
			table->entry[i].variable_bit_pattern = realloc(table->entry[i].variable_bit_pattern, (table->entry[i].size + 1 )*sizeof(char));
			table->entry[i].variable_bit_pattern = prefix(table->entry[i].variable_bit_pattern, table->entry[i].size, code );
			++table->entry[i].size;
                }
        }
}

/* A function called by build_code that splits the left and right parts of an element in the binary tree and assigns the Huffman code*/
void split_and_code(table_t table, char * symbol, int length, char code)
{
	int i = -1;
	while(++i < length)
	{
		find_and_code(table, (char *)&symbol[i], code);
	}
}

/* A function that is helped by split_and_code and in turn by find_and_code that creates a Binary Tree and also 
	updates the variable bit patterns of all the symbols in the table */
void build_code(table_t table)
{
	char zero = '0';
	char one = '1';
	table_t new_table = sort_table(table);
	while(new_table->len > 1)
	{
		split_and_code(table, new_table->entry[0].symbol, new_table->entry[0].length, zero);
                split_and_code(table, new_table->entry[1].symbol, new_table->entry[1].length, one);
		new_table->entry[0].symbol = concatenation(new_table->entry[0].symbol, new_table->entry[0].length, new_table->entry[1].symbol, new_table->entry[1].length);
		new_table->entry[0].length = new_table->entry[0].length + new_table->entry[1].length;
		new_table->entry[0].frequency = new_table->entry[0].frequency + new_table->entry[1].frequency;
		if(new_table->entry[0].frequency > new_table->highest_freq)
			new_table->highest_freq = new_table->entry[0].frequency;
		int i = 0;
		while(++i < new_table->len-1)
		{
			new_table->entry[i].symbol = copystr(new_table->entry[i+1].symbol, new_table->entry[i+1].length);
			new_table->entry[i].length =  new_table->entry[i+1].length;
                        new_table->entry[i].frequency =  new_table->entry[i+1].frequency;
		}
		if(--new_table->len > 1)
			new_table = sort_table(new_table);
		
	}
}

/* A function to print all the symbols and it's corresponding frequency, in table entries*/
void print_table(table_t table)
{
	int i = -1;
	while(++i < table->len)
		printf("symbol: %c frequency: %d \n", table->entry[i].symbol[0], table->entry[i].frequency);	
}

/* A function to print the Huffman Codes of all the symbols in the table */
void print_codes(table_t table)
{
	int i = -1;
	while(++i < table->len)
	{
		printf("symbol: %c size %d frequency %d code : ", table->entry[i].symbol[0], table->entry[i].size, table->entry[i].frequency);
		int j = -1;
		while(++j < table->entry[i].size)
		{
			printf("%c", table->entry[i].variable_bit_pattern[j]);
		}
		printf("\n");
		
	}
}

/* A function that frees the allocated memories of the table and its entries */
void table_free(table_t table) {
	int i = -1;
	while(++i > table->len)
	{
		free(table->entry[i].symbol);
		free(table->entry[i].variable_bit_pattern);
	}
	free(table->entry);
	free(table);
}

