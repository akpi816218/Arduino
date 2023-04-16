#include <Thread.h>
#include "Arduino.h"

const int a1 = 2, b1 = 3, c1 = 4, d1 = 5, e1 = 6, f1 = 7, g1 = 8;
const int a2 = 9, b2 = 10, c2 = 11, d2 = 12, e2 = 13, f2 = 14, g2 = 15;
const int button = A3;

#pragma region "Utility function definitions"
void clear1()
{
	// % Skipped g intentionally; it is kept on as a hyphen to indicate that the die is rolling
	for (int i = a1; i <= f1; i++)
	{
		digitalWrite(i, LOW);
	}
}

void clear2()
{
	// % Skipped g intentionally; it is kept on as a hyphen to indicate that the die is rolling
	for (int i = a2; i <= f2; i++)
	{
		digitalWrite(i, LOW);
	}
}

void writeArr(const int array[], int size)
{
	;
	for (int i = 0; i < size; i++)
	{
		digitalWrite(array[i], HIGH);
	}
}

void writeOne1()
{
	const int arr[2] = {b1, c1};
	writeArr(arr, 2);
}

void writeTwo1()
{
	const int arr[5] = {a1, b1, g1, e1, d1};
	writeArr(arr, 5);
}

void writeThree1()
{
	const int arr[5] = {a1, b1, g1, c1, d1};
	writeArr(arr, 5);
}

void writeFour1()
{
	const int arr[4] = {f1, g1, b1, c1};
	writeArr(arr, 4);
}

void writeFive1()
{
	const int arr[5] = {a1, f1, g1, c1, d1};
	writeArr(arr, 5);
}

void writeSix1()
{
	const int arr[6] = {a1, f1, g1, e1, c1, d1};
	writeArr(arr, 6);
}

void writeOne2()
{
	const int arr[2] = {b2, c2};
	writeArr(arr, 2);
}

void writeTwo2()
{
	const int arr[5] = {a2, b2, g2, e2, d2};
	writeArr(arr, 5);
}

void writeThree2()
{
	const int arr[5] = {a2, b2, g2, c2, d2};
	writeArr(arr, 5);
}

void writeFour2()
{
	const int arr[4] = {f2, g2, b2, c2};
	writeArr(arr, 4);
}

void writeFive2()
{
	const int arr[5] = {a2, f2, g2, c2, d2};
	writeArr(arr, 5);
}

void writeSix2()
{
	const int arr[6] = {a2, f2, g2, e2, c2, d2};
	writeArr(arr, 6);
}

void writeNumber1(int number)
{
	switch (number)
	{
	case 1:
		writeOne1();
		break;
	case 2:
		writeTwo1();
		break;
	case 3:
		writeThree1();
		break;
	case 4:
		writeFour1();
		break;
	case 5:
		writeFive1();
		break;
	case 6:
		writeSix1();
		break;
	default:
		break;
	}
}

void writeNumber2(int number)
{
	switch (number)
	{
	case 1:
		writeOne2();
		break;
	case 2:
		writeTwo2();
		break;
	case 3:
		writeThree2();
		break;
	case 4:
		writeFour2();
		break;
	case 5:
		writeFive2();
		break;
	case 6:
		writeSix2();
		break;
	default:
		break;
	}
}
#pragma endregion "Utility function definitions"

void die1()
{
	while (true)
	{
		for (int i = a1; i <= g2; i++)
		{
			if (digitalRead(button) == LOW)
				continue;
			digitalWrite(g1, LOW);
			writeNumber1(i);
			while (digitalRead(button) == HIGH)
			{
			}
			clear1();
			digitalWrite(g1, HIGH);
			// % random is used here so that when multiple dice are used with separate microcontrollers/threads, they don't all roll at the same frequency
			delay(random(1, 5));
		}
	}
}

void die2()
{
	// TODOdone Change pin numbers
	while (true)
	{
		for (int i = a2; i <= g2; i++)
		{
			if (digitalRead(button) == LOW)
				continue;
			writeNumber2(i);
			while (digitalRead(button) == HIGH)
			{
			}
			clear2();
			digitalWrite(g2, HIGH);
			// % random is used here so that when multiple dice are used with separate microcontrollers/threads, they don't all roll at the same frequency
			delay(random(1, 5));
		}
	}
}

void setup()
{
	for (int i = a1; i <= g2; i++)
	{
		pinMode(i, OUTPUT);
	}
	pinMode(button, INPUT_PULLUP);
	clear1();
	clear2();

	Thread t1 = Thread();
	t1.enabled = true;
	t1.onRun(die1);
	if (t1.shouldRun())
		t1.run();
	Thread t2 = Thread();
	t2.enabled = true;
	t2.onRun(die2);
	if (t2.shouldRun())
		t2.run();
}

void loop() {}