/*
 * Teater_Steuerung_14_12_18.c
 *
 * Created: 14.12.2018 11:12:08
 * Author : kschuppe
 */ 

#include <string.h>

#define WIDTH 8
#define HEIGHT 5

#include <avr/io.h>
#include <avr/eeprom.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#define ADDRESS_MODE 0x00

/*
	LED Matrix: B5
	Taster: D3 <- Pull up
*/

struct _Pixel{
	short r;
	short g;
	short b;
};
typedef struct _Pixel Pixel;

Pixel Screen[WIDTH][HEIGHT];

//Senden
void SendColor(short color){
	
	for(short c = 0;c < 8;c++){
		char bit = color & (1 << (8 - c));
				
		if(bit){
			//1
			PORTB |= (1<<5);
			_delay_us(0.5f);
			PORTB &= ~(1<<5);
			_delay_us(0.4f);
		}else{
			//0
			PORTB |= (1<<5);
			_delay_us(0.25f);
			PORTB &= ~(1<<5);
			_delay_us(0.6f);
		}
				
	}
	
}

void Present(){
	
	for(short y = 0;y < HEIGHT;y++){
		for(short x = 0;x < WIDTH;x++){
			
			SendColor(Screen[x][y].g);
			SendColor(Screen[x][y].r);
			SendColor(Screen[x][y].b);
			
		}
	}
	
	PINB &= ~(1<<5);
	_delay_us(60);
}

short c = 0;

void Animnation1(){
	
	if(c){
		c = 0;
	}else{
		c = 1;
	}
	
	for(short x = 0;x < WIDTH;x++){
		for(short y = 0;y < HEIGHT;y++){
			
			Screen[x][y].r = c * 0xff;
			Screen[x][y].g = c * 0xff;
			Screen[x][y].b = c * 0xff;
			
		}
	}
	
	_delay_ms(20.0f);
}

void Animnation2(){
	
	if(c){
		c = 0;
		}else{
		c = 1;
	}
	
	for(short x = 0;x < WIDTH;x++){
		for(short y = 0;y < HEIGHT;y++){
			if(((x + y + c) % 2) == 0){
				Screen[x][y].r = 0x90;
				Screen[x][y].g = 0;
			}else{
				Screen[x][y].r = 0;
				Screen[x][y].g = 0x90;
			}

			Screen[x][y].b = 0;
			
		}
	}
	
	
	for(short c = 0;c < 8;c++){
		_delay_ms(50.0f);
	}
}

static short Collide = 0;
static short CollideThrows = 0;

void Animnation3(){

	if(Collide){
		if(c){
			c = 0;
		}else{
			c = 1;
		}
		
		for(short x = 0;x < WIDTH;x++){
			for(short y = 0;y < HEIGHT;y++){
				
				Screen[x][y].r = c * 0xff;
				Screen[x][y].g = c * 0x66;
				Screen[x][y].b = c * 0;
				
			}
		}
		
		
		_delay_ms(20.0f);
		
		CollideThrows++;
		if(CollideThrows > 200){
			CollideThrows = 0;
			Collide = 0;
		}
	}
	else
	{
		if(c > WIDTH / 2){
			Collide = 1;
		}
		c++;
		
		for(short x = 0;x < WIDTH;x++){
			for(short y = 0;y < HEIGHT;y++){
					
				Screen[x][y].r = 0;
				Screen[x][y].g = 0;
				Screen[x][y].b = 0;
					
			}
		}
			
		for(short x = 0;x < c;x++){

				Screen[x][2].r = 0;
				Screen[x][2].g = 0xff;
				Screen[x][2].b = 0;
			
		}
		
		for(short x = WIDTH - c;x < WIDTH ;x++){

				Screen[x][2].r = 0;
				Screen[x][2].g = 0xff;
				Screen[x][2].b = 0;

		}
		
		for(short c = 0;c < 16;c++){
			_delay_ms(50.0f);
		}
	}
}

static char R = 255, G = 0, B = 0;
static char sim_a = 0, sim_k = 0, sim_c = 0;

void Animnation4(){
	if(R == 0 && G == 255){sim_a = 1;}else if(R == 255){sim_a = -1;}else if(R == 0){sim_a = 0;}
	if(G == 0 && B == 255){sim_k = 1;}else if(G == 255){sim_k = -1;}else if(G == 0){sim_k = 0;}
	if(B == 0 && R == 255){sim_c = 1;}else if(B == 255){sim_c = -1;}else if(B == 0){sim_c = 0;}
			
			
			
			
	R += sim_a;
	G += sim_k;
	B += sim_c;
			

	for(char x = 0; x < WIDTH; x++)
	{
		for(char y = 0;y < HEIGHT;y++){
			Screen[x][y].r = R;
			Screen[x][y].g = G;
			Screen[x][y].b = B;
		}
	}

	_delay_ms(16.666f);
}


int main(void)
{
    DDRB|=(1<<5);
	DDRD&=~(1<<3);
	PORTD|=(1<<3);
	_delay_ms(500);
	
	short currAni = 0;
	short ButtonOn = 0;
	
	currAni = eeprom_read_float(ADDRESS_MODE);
	
    while (1) 
    {
		//Taster
		if(!(PIND & (1 << 3))){
			ButtonOn = 1;

		}else{
			if(ButtonOn){
				currAni++;
				if(currAni >= 4){
					currAni = 0;
				}
				eeprom_write_float( ADDRESS_MODE, currAni );
				ButtonOn = 0;
			}

		}
		
		switch(currAni){
			case 0:
				Animnation1();
			break;
			case 1:
				Animnation2();
			break;
			case 2:
				Animnation3();
			break;
			case 3:
				Animnation4();
			break;
		}
		
		Present();

    }
}

