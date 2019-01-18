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

#define M_PI 3.14159265358979323846264338327950288
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI

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
			_delay_us(0.5f);
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

void Reset(){
		for(short x = 0;x < WIDTH;x++){
			for(short y = 0;y < HEIGHT;y++){
				
				Screen[x][y].r = 0;
				Screen[x][y].g = 0;
				Screen[x][y].b = 0;
				
			}
		}
}

void Reset2(char R, char G, char B){
	for(short x = 0;x < WIDTH;x++){
		for(short y = 0;y < HEIGHT;y++){
			
			Screen[x][y].r = R;
			Screen[x][y].g = G;
			Screen[x][y].b = B;
			
		}
	}
}

void Animnation1(){
	//aids aka stroboskop
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
	//schachbrett matrix
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
	//linien die collidieren + explosion ESKALATION!!! | Minecraft let's play 
	if(Collide){
		if(c){
			c = 0;
		}else{
			c = 1;
		}
		
		for(short x = 0;x < WIDTH;x++){
			for(short y = 0;y < HEIGHT;y++){
						
				Screen[x][y].r = 0;
				Screen[x][y].g = 0;
				Screen[x][y].b = 0;
						
			}
		}
		
		//mitte
		Screen[3][2].r = c * 0xff;
		Screen[3][2].g = c * 0x66;
		Screen[3][2].b = c * 0;
		
		Screen[4][2].r = c * 0xff;
		Screen[4][2].g = c * 0x66;
		Screen[4][2].b = c * 0;
		
		//oben
		Screen[3][3].r = c * 0xff;
		Screen[3][3].g = c * 0x66;
		Screen[3][3].b = c * 0;
		
		Screen[4][3].r = c * 0xff;
		Screen[4][3].g = c * 0x66;
		Screen[4][3].b = c * 0;
		
		//unten
		Screen[3][1].r = c * 0xff;
		Screen[3][1].g = c * 0x66;
		Screen[3][1].b = c * 0;
		
		Screen[4][1].r = c * 0xff;
		Screen[4][1].g = c * 0x66;
		Screen[4][1].b = c * 0;
		
		//seite
		Screen[2][2].r = c * 0xff;
		Screen[2][2].g = c * 0x66;
		Screen[2][2].b = c * 0;
				
		Screen[5][2].r = c * 0xff;
		Screen[5][2].g = c * 0x66;
		Screen[5][2].b = c * 0;
		
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
	//farb verlauf
	
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

void Animnation5(){
	//linien
	Reset2(0x66, 0x66, 0);
	
	R++;
	if(R >= 255)
		R = 0;
		
	char y = R / (255 / HEIGHT);

	for(char x = 0; x < WIDTH; x++)
	{
		Screen[x][y].r = 0x0;
		Screen[x][y].g = 0xff;
		Screen[x][y].b = 0xff;
	}
	
	char x = R / (255 / WIDTH);
	
	for(char y = 0; y < HEIGHT; y++)
	{

		if(Screen[x][y].g == 0xff){
			Screen[x][y].r = 0xff;
			Screen[x][y].g = 0x00;
			Screen[x][y].b = 0x00;
		}else{
			Screen[x][y].r = 0x0;
			Screen[x][y].g = 0xff;
			Screen[x][y].b = 0xff;
		}

	}

	c -= HEIGHT;

	_delay_ms(60.666f);
	
}

void Animnation6(){
	//sinus
	Reset2(0x66, 0x66, 0);
	
	float start = c % 360;
	c++;
	
	float x_step = 360.0f / WIDTH;
	
	for(char x = 0; x < WIDTH; x++){
		float r = (c) + x * x_step;
		r = degToRad(r);
		//y = 4 * sin(off + x * (1 / 360)) + off
		int y = (int)((sin(r) * (HEIGHT) * 0.5f) + (HEIGHT) * 0.5f);
		
		Screen[x][y].r = 0x0;
		Screen[x][y].g = 0xff;
		Screen[x][y].b = 0xff;
	}

	for(char x = 0; x < WIDTH; x++){
		
		for(char y = 0; Screen[x][y].g != 0xff;y++){
			Screen[x][y].r = 0x0;
			Screen[x][y].g = 0xff;
			Screen[x][y].b = 0xff;
		}

	}

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
				if(currAni >= 6){
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
			case 4:
				Animnation5();
			break;
			case 5:
				Animnation6();
			break;
		}
		
		Present();

    }
}

