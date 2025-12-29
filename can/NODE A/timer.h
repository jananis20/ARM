//DEALY AND TIMER

void initTimer0(void);

void delayUS(unsigned long microseconds);

void delayMS(unsigned int milliseconds);

void startTimer0(void);

unsigned int stopTimer0(void); 

void initTimer0(void)

{

	//Assuming PCLK = 60Mhz

	T0TCR = 0x0;

	T0PR = 60-1; //60 clock cycles @60Mhz = 1 us

	T0TCR = 0x02; //Reset Timer

}

void delayUS(unsigned long microseconds) //Using Timer0

{

	T0TCR = 0x02; //Reset Timer

	T0TCR = 0x01; //Enable timer

	while(T0TC < microseconds); //wait until timer counter reaches the desired delay

	T0TCR = 0x00; //Disable timer

}
void delayMS(unsigned int milliseconds)

{

	delayUS(milliseconds * 1000);

}
void startTimer0(void)

{

	T0TCR = 0x02; //Reset Timer

	T0TCR = 0x01; //Enable timer

}
unsigned int stopTimer0(void)

{

	T0TCR = 0x00; //Disable timer

	return T0TC;

}
