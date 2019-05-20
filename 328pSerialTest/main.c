//------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.					//
//------------------------------------------------------------------------- //
//========================================================================	//
//			COMUNICAÇÃO SERIAL ENTRE O ARDUINO E UM COMPUTADOR				//
//=========================================================================	//
#include "def_principais.h"
#include "USART.h"
#include "LCD.h"

const char primeira_msg[] PROGMEM = "Transmitindo primeira mensagem para o computador! Digite agora - Para sair <*>\n\0";
const char segunda_msg[]  PROGMEM = "\nTransmissao Encerrada: Bye, Bye!\0";

//-------------------------------------------------------------------------
int main()
{
	unsigned char status;
	unsigned char dado_srt[3];
	int x = 0;
	DDRD = 0xFF;
	USART_Inic(MYUBRR);
	inic_LCD_4bits();
	escreve_USART_Flash(primeira_msg);

	while(1)
	{
		status = USART_Recebe();
		if (status == 'L')
		{
			dado_srt[0]= 'L';
			dado_srt[1]= USART_Recebe();
			dado_srt[2]= USART_Recebe();
		}
		if (status == 'D')
		{
			dado_srt[0]= 'D';
			dado_srt[1]= USART_Recebe();
			dado_srt[2]= USART_Recebe();
		}
		
		cmd_LCD(0x80, 0);
		cmd_LCD(dado_srt[0], 1);
		cmd_LCD(dado_srt[1], 1);
		cmd_LCD(dado_srt[2], 1);
		
	}
}
//---------------------------------------------------------------------------

