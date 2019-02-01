/*
 * Teater_Steuerung_14_12_18.c
 *
 * Created: 14.12.2018 11:12:08
 * Author : kschuppe
 */ 

#include <string.h>
#include <stdio.h>

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

#define Number_R 0xff
#define Number_G 0
#define Number_B 0

void SetPixel(int x, int y, short r, short g, short b){
	
	if(x < 0 || x >= WIDTH)
		return;
	
	if(y < 0 || y >= HEIGHT)
		return;
	
	Screen[x][y].r = r;
	Screen[x][y].g = g;
	Screen[x][y].b = b;
}

void ShowNummber(short nummber){
	
	switch(nummber){
		case 10:{
			SetPixel(2, 4, Number_R, Number_G, Number_B);
			
			SetPixel(1, 3, Number_R, Number_G, Number_B);
			SetPixel(2, 3, Number_R, Number_G, Number_B);
			SetPixel(3, 3, Number_R, Number_G, Number_B);
			SetPixel(4, 3, Number_R, Number_G, Number_B);
			SetPixel(5, 3, Number_R, Number_G, Number_B);
			SetPixel(6, 3, Number_R, Number_G, Number_B);
			
			SetPixel(2, 2, Number_R, Number_G, Number_B);
			SetPixel(3, 2, Number_R, Number_G, Number_B);
			SetPixel(4, 2, Number_R, Number_G, Number_B);
			SetPixel(5, 2, Number_R, Number_G, Number_B);
			
			SetPixel(1, 1, Number_R, Number_G, Number_B);
			SetPixel(6, 1, Number_R, Number_G, Number_B);
			
			SetPixel(2, 0, Number_R, Number_G, Number_B);
			SetPixel(3, 0, Number_R, Number_G, Number_B);
			SetPixel(4, 0, Number_R, Number_G, Number_B);
			SetPixel(5, 0, Number_R, Number_G, Number_B);
		}			
		break;
		
		case 9:{
			SetPixel(1, 1, Number_R, Number_G, Number_B);
			SetPixel(2, 1, Number_R, Number_G, Number_B);
			SetPixel(3, 1, Number_R, Number_G, Number_B);
			SetPixel(4, 1, Number_R, Number_G, Number_B);
			SetPixel(5, 1, Number_R, Number_G, Number_B);
			SetPixel(6, 1, Number_R, Number_G, Number_B);
					
			SetPixel(1, 2, Number_R, Number_G, Number_B);
			SetPixel(3, 2, Number_R, Number_G, Number_B);
					
			SetPixel(1, 3, Number_R, Number_G, Number_B);
			SetPixel(2, 3, Number_R, Number_G, Number_B);
			SetPixel(3, 3, Number_R, Number_G, Number_B);
		}			
		break;
		
		case 8:{
			SetPixel(1, 1, Number_R, Number_G, Number_B);
			SetPixel(2, 1, Number_R, Number_G, Number_B);
			SetPixel(3, 1, Number_R, Number_G, Number_B);
			SetPixel(4, 1, Number_R, Number_G, Number_B);
			SetPixel(5, 1, Number_R, Number_G, Number_B);
			SetPixel(6, 1, Number_R, Number_G, Number_B);
					
			SetPixel(1, 2, Number_R, Number_G, Number_B);
			SetPixel(3, 2, Number_R, Number_G, Number_B);
			SetPixel(6, 2, Number_R, Number_G, Number_B);
					
			SetPixel(1, 3, Number_R, Number_G, Number_B);
			SetPixel(2, 3, Number_R, Number_G, Number_B);
			SetPixel(3, 3, Number_R, Number_G, Number_B);
			SetPixel(4, 3, Number_R, Number_G, Number_B);
			SetPixel(5, 3, Number_R, Number_G, Number_B);
			SetPixel(6, 3, Number_R, Number_G, Number_B);
		}			
		break;
		
		case 7:{
			SetPixel(1, 1, Number_R, Number_G, Number_B);
			SetPixel(2, 1, Number_R, Number_G, Number_B);
			SetPixel(3, 1, Number_R, Number_G, Number_B);
			SetPixel(4, 1, Number_R, Number_G, Number_B);
			SetPixel(5, 1, Number_R, Number_G, Number_B);
			SetPixel(6, 1, Number_R, Number_G, Number_B);
			
			SetPixel(1, 2, Number_R, Number_G, Number_B);
			SetPixel(1, 3, Number_R, Number_G, Number_B);
		}
		break;
		
		case 6:{
			SetPixel(1, 3, Number_R, Number_G, Number_B);
			SetPixel(2, 3, Number_R, Number_G, Number_B);
			SetPixel(3, 3, Number_R, Number_G, Number_B);
			SetPixel(4, 3, Number_R, Number_G, Number_B);
			SetPixel(5, 3, Number_R, Number_G, Number_B);
			SetPixel(6, 3, Number_R, Number_G, Number_B);
			
			SetPixel(1, 2, Number_R, Number_G, Number_B);
			SetPixel(1, 1, Number_R, Number_G, Number_B);
			
			SetPixel(3, 2, Number_R, Number_G, Number_B);
			SetPixel(3, 1, Number_R, Number_G, Number_B);
			
			SetPixel(6, 2, Number_R, Number_G, Number_B);
			SetPixel(6, 1, Number_R, Number_G, Number_B);
			
			SetPixel(4, 1, Number_R, Number_G, Number_B);
			SetPixel(5, 1, Number_R, Number_G, Number_B);
			
		}		
		break;
		
		case 5:{
			SetPixel(1, 3, Number_R, Number_G, Number_B);
			SetPixel(1, 2, Number_R, Number_G, Number_B);
			SetPixel(1, 1, Number_R, Number_G, Number_B);
			
			SetPixel(2, 3, Number_R, Number_G, Number_B);
			
			SetPixel(3, 3, Number_R, Number_G, Number_B);
			SetPixel(3, 2, Number_R, Number_G, Number_B);
			SetPixel(3, 1, Number_R, Number_G, Number_B);
			
			SetPixel(4, 1, Number_R, Number_G, Number_B);
			SetPixel(5, 1, Number_R, Number_G, Number_B);
			
			SetPixel(6, 3, Number_R, Number_G, Number_B);
			SetPixel(6, 2, Number_R, Number_G, Number_B);
			SetPixel(6, 1, Number_R, Number_G, Number_B);
			
		}
		break;
		
		case 4:{
			SetPixel(1, 1, Number_R, Number_G, Number_B);
			SetPixel(2, 1, Number_R, Number_G, Number_B);
			SetPixel(3, 1, Number_R, Number_G, Number_B);
			SetPixel(4, 1, Number_R, Number_G, Number_B);
			SetPixel(5, 1, Number_R, Number_G, Number_B);
			SetPixel(6, 1, Number_R, Number_G, Number_B);
			
			SetPixel(3, 2, Number_R, Number_G, Number_B);
			SetPixel(3, 3, Number_R, Number_G, Number_B);
			
			SetPixel(2, 3, Number_R, Number_G, Number_B);
			SetPixel(1, 3, Number_R, Number_G, Number_B);
			
		}
		break;
		
		case 3:{
			SetPixel(1, 1, Number_R, Number_G, Number_B);
			SetPixel(2, 1, Number_R, Number_G, Number_B);
			SetPixel(3, 1, Number_R, Number_G, Number_B);
			SetPixel(4, 1, Number_R, Number_G, Number_B);
			SetPixel(5, 1, Number_R, Number_G, Number_B);
			SetPixel(6, 1, Number_R, Number_G, Number_B);
			
			SetPixel(3, 2, Number_R, Number_G, Number_B);
			SetPixel(3, 3, Number_R, Number_G, Number_B);
			
			SetPixel(1, 2, Number_R, Number_G, Number_B);
			SetPixel(1, 3, Number_R, Number_G, Number_B);
			
			SetPixel(6, 2, Number_R, Number_G, Number_B);
			SetPixel(6, 3, Number_R, Number_G, Number_B);
			
		}
		break;
		
		case 2:{
			SetPixel(1, 3, Number_R, Number_G, Number_B);
			SetPixel(1, 2, Number_R, Number_G, Number_B);
			SetPixel(1, 1, Number_R, Number_G, Number_B);
			
			SetPixel(2, 3, Number_R, Number_G, Number_B);
			
			SetPixel(2, 1, Number_R, Number_G, Number_B);
			SetPixel(3, 1, Number_R, Number_G, Number_B);
			
			SetPixel(4, 3, Number_R, Number_G, Number_B);
			SetPixel(4, 2, Number_R, Number_G, Number_B);
			SetPixel(4, 1, Number_R, Number_G, Number_B);
			
			SetPixel(4, 1, Number_R, Number_G, Number_B);
			SetPixel(5, 3, Number_R, Number_G, Number_B);
			
			SetPixel(6, 3, Number_R, Number_G, Number_B);
			SetPixel(6, 2, Number_R, Number_G, Number_B);
			SetPixel(6, 1, Number_R, Number_G, Number_B);
		}
		break;
		
		case 1:{
			SetPixel(2, 3, Number_R, Number_G, Number_B);
			
			SetPixel(1, 2, Number_R, Number_G, Number_B);
			SetPixel(2, 2, Number_R, Number_G, Number_B);
			SetPixel(3, 2, Number_R, Number_G, Number_B);
			SetPixel(4, 2, Number_R, Number_G, Number_B);
			SetPixel(5, 2, Number_R, Number_G, Number_B);
			SetPixel(6, 2, Number_R, Number_G, Number_B);
		}
		break;
		
		case 0:{
			SetPixel(2, 3, Number_R, Number_G, Number_B);
			SetPixel(3, 3, Number_R, Number_G, Number_B);
			SetPixel(4, 3, Number_R, Number_G, Number_B);
			SetPixel(5, 3, Number_R, Number_G, Number_B);
			
			SetPixel(1, 2, Number_R, Number_G, Number_B);
			SetPixel(6, 2, Number_R, Number_G, Number_B);
			
			SetPixel(2, 1, Number_R, Number_G, Number_B);
			SetPixel(3, 1, Number_R, Number_G, Number_B);
			SetPixel(4, 1, Number_R, Number_G, Number_B);
			SetPixel(5, 1, Number_R, Number_G, Number_B);
		}
		break;
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



void Rocket(){

	Reset2(0x66, 0x66, 0);
	int newH;
	
	if(c > 11){
		c = 11;
	}
	
	c--;
	if(c < 0){
		
		switch(c){
			case -1:
				SetPixel(6, 2, Number_R, Number_G, Number_B);
				SetPixel(7, 2, Number_R, Number_G, Number_B);
			break;
			case -2:

				SetPixel(5, 2, Number_R, Number_G, Number_B);
				SetPixel(6, 2, Number_R, Number_G, Number_B);
				SetPixel(7, 2, Number_R, Number_G, Number_B);
				
				SetPixel(7, 1, Number_R, Number_G, Number_B);
				SetPixel(7, 3, Number_R, Number_G, Number_B);
			break;
			case -3:
				SetPixel(4, 2, Number_R, Number_G, Number_B);
				SetPixel(5, 2, Number_R, Number_G, Number_B);
				SetPixel(6, 2, Number_R, Number_G, Number_B);
				SetPixel(7, 2, Number_R, Number_G, Number_B);
				
				SetPixel(6, 1, Number_R, Number_G, Number_B);
				SetPixel(6, 3, Number_R, Number_G, Number_B);
				
				SetPixel(7, 0, Number_R, Number_G, Number_B);
				SetPixel(7, 4, Number_R, Number_G, Number_B);
				
			break;
			case -4:
				SetPixel(3, 2, Number_R, Number_G, Number_B);
				SetPixel(4, 2, Number_R, Number_G, Number_B);
				SetPixel(5, 2, Number_R, Number_G, Number_B);
				SetPixel(6, 2, Number_R, Number_G, Number_B);
			
				SetPixel(5, 1, Number_R, Number_G, Number_B);
				SetPixel(5, 3, Number_R, Number_G, Number_B);
			
				SetPixel(6, 0, Number_R, Number_G, Number_B);
				SetPixel(6, 4, Number_R, Number_G, Number_B);
			
				SetPixel(7, 1, Number_R, Number_G, Number_B);
				SetPixel(7, 2, Number_R, Number_G, Number_B);
				SetPixel(7, 3, Number_R, Number_G, Number_B);
			
			break;
			case -5:
				SetPixel(2, 2, Number_R, Number_G, Number_B);
				SetPixel(3, 2, Number_R, Number_G, Number_B);
				SetPixel(4, 2, Number_R, Number_G, Number_B);
				SetPixel(5, 2, Number_R, Number_G, Number_B);
				
				SetPixel(4, 1, Number_R, Number_G, Number_B);
				SetPixel(4, 3, Number_R, Number_G, Number_B);
				
				SetPixel(5, 0, Number_R, Number_G, Number_B);
				SetPixel(5, 4, Number_R, Number_G, Number_B);
				
				SetPixel(6, 1, Number_R, Number_G, Number_B);
				SetPixel(6, 2, Number_R, Number_G, Number_B);
				SetPixel(6, 3, Number_R, Number_G, Number_B);
			
				SetPixel(7, 2, Number_R, Number_G, Number_B);
			break;
			
			case -6:
			case -7:
			case -8:
			case -9:
			case -10:
			case -11:
			case -12:
			case -13:
				newH = (c) + 5;
				SetPixel(2 + newH, 2, Number_R, Number_G, Number_B);
				SetPixel(3 + newH, 2, Number_R, Number_G, Number_B);
				SetPixel(4 + newH, 2, Number_R, Number_G, Number_B);
				SetPixel(5 + newH, 2, Number_R, Number_G, Number_B);
			
				SetPixel(4 + newH, 1, Number_R, Number_G, Number_B);
				SetPixel(4 + newH, 3, Number_R, Number_G, Number_B);
			
				SetPixel(5 + newH, 0, Number_R, Number_G, Number_B);
				SetPixel(5 + newH, 4, Number_R, Number_G, Number_B);
			
				SetPixel(6 + newH, 1, Number_R, Number_G, Number_B);
				SetPixel(6 + newH, 2, Number_R, Number_G, Number_B);
				SetPixel(6 + newH, 3, Number_R, Number_G, Number_B);
			
				SetPixel(7 + newH, 2, Number_R, Number_G, Number_B);
			break;
			default:
				c = 11;
			break;
		}
	
		
	}else{
		ShowNummber(c);
	}
	
	_delay_ms(600);

}

void Waterfall(){

	//Simon
	static char rainzaehler = 0;

	for(char x = 0;x < WIDTH - rainzaehler;x++){
		for(char y = 0;y < HEIGHT; y++){
			if(x >= 1){
				Screen[x - 1][y].b = 0;
			}
			Screen[x][y].b = 255;
			Present();
			_delay_ms(20);
		}
	}	
	rainzaehler++;

}

void DJ_Effect(){
	Reset2(0, 255, 0);

	for(char x = 0;x < WIDTH;x++){
		char r1= rand() % HEIGHT;

		for(char y = 0;y < r1;y++){
			SetPixel(x, y, 0, 0, 255);
		}
	}


	_delay_ms(100);
}

void Welle(){
	for(char x = 0; x < WIDTH; x++)
	{
		for(char y = 0; y < HEIGHT; y++)
		{
			Screen[x][y].r += 10;
			if(Screen[x][y].b+50 <= 255)
			{
				Screen[x][y].b += 20;
			}else
			{
				Reset2(0, 0, 0);
			}
		}
		_delay_ms(20);
		Present();
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
	
	Reset2(0, 25, 0);
	
    while (1) 
    {
		//Taster
		if(!(PIND & (1 << 3))){
			ButtonOn = 1;

		}else{
			if(ButtonOn){
				currAni++;
				if(currAni >= 10){
					currAni = 0;
				}
				eeprom_write_float( ADDRESS_MODE, currAni );
				ButtonOn = 0;
				Reset2(0, 25, 0);
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
			case 6:
				Rocket();
			break;
			case 7:
				Waterfall();
			break;
			case 8:
				DJ_Effect();
			break;
			case 9:
				Welle();
			break;
		}
		
		Present();

    }
}

