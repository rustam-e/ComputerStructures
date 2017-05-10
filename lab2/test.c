/*Filename: test.c *
 *Part of: C335 Lab Assignment 2 *
 *Created by: name *
 *Created on: mm/dd/yyy *
 *Last Modified by:  *
 *Last Modified on:  *
 */

/*
 * I changed some numerical values and added more print statements for testing purposes.
 */


extern void myprintf(const char *, ...);

int main(){

	myprintf("Nothing much\n");
	myprintf("The letter %c\n", 'A');
	myprintf("A string: %s\n", "Splash!");
	myprintf("The number %d\n", 12345); /* changed from 11 */
	myprintf("number 1 in decimal         : %d\n", 1);
	myprintf("number 19 in decimal        : %d\n", 19);
	myprintf("number 123 in decimal       : %d\n", 123);
	myprintf("number 1234 in decimal      : %d\n", 1234);
	myprintf("number 12345 in decimal     : %d\n", 12345);
	myprintf("number 1 in hex        (0x1): %x\n", 1); /* should be 1 */
	myprintf("number 12 in hex       (0xc): %x\n", 12); /* should be C */
	myprintf("number 123 in hex     (0x7b): %x\n", 123); /* should be 7B */
	myprintf("number 1234 in hex   (0x4d2): %x\n", 1234); /* should be 4D2 */
	myprintf("number 12345 in hex (0x3039): %x\n\n", 12345); /* should be 3039 */

	myprintf("The number %x in hexadecimal\n", 11);	//b
	myprintf("%d is a negative number\n", -10); /* changed from -5 */
	myprintf("The number %d\n", 'A');
	myprintf("The number %x in hexadecimal\n", 'A');	

}
