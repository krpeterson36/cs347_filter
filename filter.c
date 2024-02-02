/*
 * Implementation of functions that filter values in strings.
 *****
 * YOU MAY NOT USE ANY FUNCTIONS FROM <string.h> OTHER THAN
 * strcpy() and strlen()
 *****
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "filter.h"


/*
 * YOU MAY FIND THIS FUNCTION USEFUL.
 * Return true if and only if character <c> is in string <s>.
 */
static bool includes(char c, char *s) {
	while( *s && c != *s ) {
		s++ ;
	}
	return c == *s ;
}

/*
 * YOU MAY ALSO FIND THIS FUNCTION USEFUL.
 * Return true if and only if string <pre> is a prefix of string <s>.
 */
static bool prefix(char *s, char *pre) {
	while( *pre && *s == *pre ) {
		s++ ;
		pre++ ;
	}
	return *pre == '\0' ;
}


/*
 * Return a pointer to a string that is a copy of <string> with
 * all occurrences of <ch> removed. The returned string must occupy
 * the least possible dynamically allocated space.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *filter_ch_ptr(char *string, char ch) {
	//If the character isn't in the string return a copy
	if (includes(ch, string) != true){
		return strcpy(malloc(strlen(string) + 1), string);
	}

	char *temp = string;
	int i = 0;
	int count = 0;
	int len = strlen(string);

	//This loop counts the occurances of the character, in order to properly malloc the return string
	while(i < len){
		if(*temp != ch){
			count++;
		}
		i++;
	}
	
	char *ret = malloc((sizeof(char) * count) + 1);
	char *ret1 = ret;
	i = 0;

	//This loop copies the original string without the occurances of the character
	while(i < len){
		if(*temp != ch){
			*ret = *temp;
			ret++;
		}
		temp++;
		i++;
	}
	*ret = '\0';
	return ret1; 
}



/*
 * Return a pointer to a copy of <string> after removing all
 * occurrrences of any characters in <remove>.
 * The returned string must occupy the least possible dynamically
 * allocated space.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *filter_any_ptr(char *string, char* remove) {
	int rem_len = strlen(remove);
	int str_len = strlen(string);
	int ret_len = strlen(string);
	char *rem = remove;
	char* temp = string;

	//These loops count the amount of bytes that need to be malloced
	for(int i = 0; i < rem_len; i++){
		temp = string;
		for(int j = 0; j < str_len; j++){
			if(*temp == *rem){
				ret_len--;
			}
			temp++;
		}
		rem++;
	}

	//if zero bytes, it just mallocs(1), then returns
	if(ret_len == 0){
		char *ret = malloc(1);
		*ret = '\0';
		return ret;
	}

	char *ret = malloc((sizeof(char) * ret_len) + 1);
	char *ret1 = ret;
	int boole;
	int count = 0;
	temp = string;

	//These loops iterate through the original string and determine which characters need to be copied
	for(int i = 0; i < str_len; i++){
		rem = remove;
		boole = 1;
		for(int j = 0; j < rem_len; j++){
			if(*temp == *rem){
				boole = 0;
				break;
			}
			rem++;
		}
		if(boole){
			*ret = *temp;
			ret++;
			count++;
		}
		temp++;
		if(count == ret_len){
			break;
		}
	}
	*ret = '\0';
	return ret1; 
}

/*
 * Return a pointer to a copy of <string> after removing all
 * occurrrences of the substring <substr>.
 * The returned string must occupy the least possible dynamically
 * allocated space.
 *****
 * YOU MAY *NOT* USE ARRAY INDEXING.
 *****
 */
char *filter_substr(char *string, char* substr) {
	int str_len = strlen(string);
	int ret_len = strlen(string);
	int sub_len = strlen(substr);
	char *temp = string;

	//These loops determine the lenght of the returned string
	for(int i = 0; str_len - i >= sub_len; i++){
		if(prefix(temp, substr)){
			ret_len = ret_len - sub_len;
			temp = temp + sub_len;
		}else{
			temp++;
		}
	}

	char *ret = malloc((sizeof(char) * ret_len) + 1);
	char *ret1 = ret;
	temp = string;

	//These loops remove all occurances of the substring, and then make the copy
	for(int i = 0; i < str_len; i++){
		if(str_len - i >= sub_len){
			if(prefix(temp, substr)){
				temp = temp + sub_len;
			}else{
				*ret = *temp;
				temp++;
				ret++;
			}
		}else{
			*ret = *temp;
			temp++;
			ret++;
		}
	}

	*ret = '\0';
	return ret1; 
}
