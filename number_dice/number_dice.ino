#include "Arduino.h"

const int a2 = 2, b2 = 3, c2 = 4, d2 = 5, e2 = 6, f2 = 7, g2 = 8;
const int a1 = 9, b1 = 10, c1 = 11, d1 = 12, e1 = 13, f1 = 14, g1 = 15;
const int button = A2, seed = A3;

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

int state1, state2;
/*
 * % Increments the state of the first die
 */
void die1()
{
	if (state1 == 6)
		state1 = 1;
	else
		state1++;
}

/*
 * % Increments the state of the second die
 */
void die2()
{
	if (state2 == 6)
		state2 = 1;
	else
		state2++;
}

void setup()
{
	Serial.begin(9600);
	for (int i = a2; i <= g1; i++)
		pinMode(i, OUTPUT);
	pinMode(button, INPUT_PULLUP);
	pinMode(seed, INPUT);
	clear1();
	clear2();

	digitalWrite(g1, HIGH);
	digitalWrite(g2, HIGH);

	randomSeed(analogRead(seed));
	state1 = random(1, 7);
	state2 = random(1, 7);

	Serial.println("Setup complete");
}

void loop()
{
	unsigned long ts = millis();
	if (ts % 2 == 0)
	{
		die1();
		Serial.print(ts);
		Serial.println(": Die 1 rolled");
	}
	if (ts % 3 == 0)
	{
		die2();
		Serial.print(ts);
		Serial.println(": Die 2 rolled");
	}
	if (digitalRead(button) == LOW)
	{
		Serial.print("State: ");
		Serial.print(state1);
		Serial.print(", ");
		Serial.println(state2);
		digitalWrite(g1, LOW);
		digitalWrite(g2, LOW);
		writeNumber1(state1);
		writeNumber2(state2);
		while (digitalRead(button) == LOW)
		{
		}
		clear1();
		clear2();
		digitalWrite(g1, HIGH);
		digitalWrite(g2, HIGH);
	}
	delay(random(5, 10));
}