/******************************************************************************
 *
 * Project:Calculator with multiple operations
 *
 * File Name: calculator.c
 *
 * Author: Mazen Raafat
 *
 *******************************************************************************/

#include "keypad.h"
#include "lcd.h"
#include <util/delay.h>

#define NUMBER_SIZE 16   /*The size of the array to store the numbers in it */


int main()
{

	uint8 key;
	uint8 i=0;
	uint8 j=0;
	uint8 counter=0;
	uint8 flag_negative=0;
	uint8 flag_error =0;
	sint32 number=0;
	sint32 temp=0;
	sint32 result=0;
	sint32 array_numbers[NUMBER_SIZE];


	LCD_init(); /*Initialize the LCD*/

	while(1)
	{


		key =KEYPAD_getPressedKey();
/*
 This Loop for getting the number and store it in number variable
 it will be broken only if you entered any operation
 */

		while((key>=0 && key<=9))

		{

			_delay_ms(250); /*delay for debounce*/
			number=(number*10)+key;
			LCD_longToString(key);
			key= KEYPAD_getPressedKey();

		}

		_delay_ms(250);
		/*
		 The 'c' button is used to clear the calculator and reset it
		 so this condition to show the operation which last entered to
		 quit the previous loop
		 */
		if(key!='c')
		{
			LCD_displayCharacter(key);
		}
		/*
		 The negative flag is used as if it was set before, it will be
		 activated on the current number and consider it as negative number
		 */
		if(flag_negative==1)
		{
			number*=-1;
			flag_negative=0;
		}

          /*
           This Loop checking if the is 'x' or '%'
           then it will evaluate the multiplication or the division
           and store it in the number,then it will stay as if you want to
           multiply or divide multiple times each time it will use temp variable
           then it will store the result of the operation in number

           * */
		while((key=='x') || (key=='%'))
		{

			switch(key)
			{
			case 'x':

				key =KEYPAD_getPressedKey();

				while((key>=0 && key<=9))
				{
					key =KEYPAD_getPressedKey();
					_delay_ms(250);
					temp=(temp*10)+key;
					LCD_longToString(key);
					key= KEYPAD_getPressedKey();
				}
				_delay_ms(250);
				if(key!='c')
				{
					LCD_displayCharacter(key);
				}

				if(flag_negative==1)
				{
					flag_negative=0;
					temp*=-1;
				}

				if(key=='-' && temp==0)
				{
					flag_negative=1;
					key='x';

				}
				else
				{
					number*=temp;
					temp=0;
				}
				break;

			case '%':
				key =KEYPAD_getPressedKey();

				while((key>=0 && key<=9))
				{
					key =KEYPAD_getPressedKey();
					_delay_ms(250);
					temp=(temp*10)+key;
					LCD_longToString(key);
					key= KEYPAD_getPressedKey();
				}
				_delay_ms(250);
				if(key!='c')
				{
					LCD_displayCharacter(key);
				}

				if(flag_negative==1)
				{
					flag_negative=0;
					temp*=-1;
				}

				if(key=='-' && temp==0)
				{
					flag_negative=1;
					key='%';

				}
				/*
				 If you divide by 0, this is not allowed so it will set the
				 error flag
				 */

			else if(temp==0)
				{
					flag_error=1;
				}

				else
				{
					number=number/temp;
					temp=0;
				}
				break;


			}

		}

		/*
		 Each number is store in a location in the array, then the  number
		 variable is cleared for next operations, i variable is incremented
		 to the next location of the array and counter is incremented as number
		 of elements in the array incremented
		 */
		array_numbers[i]=number;
		number=0;
		counter++;
		i++;


		/*
		 This condition to set the negative flag for the next entry
		 */
		if(key=='-')
		{

			flag_negative=1;
		}


		/*
		 If the key is 'c' button in the keypad, then the calculator will be
		 reset and cleared
		  */
		if(key=='c')
		{
			LCD_init();
			i=0;
			j=0;
			while(j!=counter)
			{
				array_numbers[j]=0;
				j++;
			}
			j=0;
			counter=0;
			flag_negative=0;
			number=0;
			temp=0;
			result=0;

		}

		/*
		 This loop to do a summation of all the elements in the array
		 and put it into the result variable
		 */

		while(j!=counter)
		{

			result+=array_numbers[j];
			j++;

		}

		/*
		 If you pressed the '=' button in the keypad, it will check on
		 the flag error first as if it's set, it will print a message
		 error on the screen, otherwise it will print the result on the screen.
		 I stored the value of result in the number variable for any operations
		 I want to do after the '=' is pressed
		 */
		if(key=='=')
		{
			if(flag_error==1)
			{
				flag_error=0;
				LCD_displayString("Error!");
			}
			else
			{
			number = result;

			LCD_longToString(result);

			result = 0;

		    }
		}


	}
}














