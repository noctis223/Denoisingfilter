/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 *   //l obiettivo e di calcoare il tempo di calcolo per l applicazione del
 *   filtro di riduzione del rumore che si riduce ad un operazione di prodotto tra
 *   matrici ed in seguito la somma per trovare il valroe che deve avere il
 *   pixel corretto , per trovare questo tempo sono necassarie l uso di aclune
 *   librerie in particolare la xscutimer.h ideata per poter avere il tempo
 *   in cicli di clock tra l inizio e la fine dell operazione da noi desiderata
 *   in seguito tramite i cicli è possibile ottenere il tempo effettivo
 *   in secondo necessari per poter portare a termine l operzione. Nel nostro caso
 *   si è imposto come frequanza di clock una frequenza 100 volte poi piccola
 *   siccome l operazione attuale è semplice finirebbe subito
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <stdlib.h>
#include "xscutimer.h"
#include <math.h>
#define N 3
#define M 3
int main()
{
    init_platform();
    int clock=0;//usata dopo , frequnza di clock con cui lavoro
    int timer;//timer di lavoro ovvero da inizio a fine ciclo di clock
    int status;//stato di configurazione del distpositivi
    int cicli=0;//cicli totali di clock per l operazione
    int centro=ceil(N/2); //prendo il limite superiore della divisione
    long double tempo=0;//tempo finale in secondi
    int valori[N][M];//valori di valore assoluto

    //istanzio il timer e lo configuro
    XScuTimer mytimer;
    XScuTimer_Config *Timer_Config; //formato da id ed indirizzo base

    //cercha la configurazione corretta in base all id del device
    Timer_Config=XScuTimer_LookupConfig(XPAR_PS7_SCUTIMER_0_DEVICE_ID);

   //si inizializza la configurazione conl id univoco ed l indirizzo base del dispoitivo
    status = XScuTimer_CfgInitialize(&mytimer, Timer_Config,Timer_Config->BaseAddr);

   //faccio lavorare la cpu alla sua frequenza/100
    XScuTimer_LoadTimer(&mytimer,XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ/100);
    clock=(XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ/100);
    int ris=0;
    int mol=0;
	unsigned int foto[N][M] = {
	{245,243, 246} ,
	{246 , 244, 245} ,
	{242 , 245 , 250}
	};
	int filt[N][M] = {
	{1, 2, 1} ,
	{2, 3, 2} ,
	{1, 2, 1}
	};
	print("la prima matrice è\n");
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			xil_printf("|%d| ",foto[i][j]);

	}
		print("\n");
	}
	print("\n");
	print("la seconda matrice è\n\r");
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			xil_printf("|%d| ",filt[i][j]);

				}
		print("\n");
	}
	//inizzializzo il timer
	print("\n");
    XScuTimer_Start(&mytimer);
    timer=XScuTimer_GetCounterValue(&mytimer);//valore del timer nel registro
    xil_printf("Il timer è partito ed ha valore %d\n",timer);
    //FILTRO DI SMOOTHING
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			    mol=foto[i][j]*filt[i][j];
			    ris=ris+mol;
				mol=0;//moltipicazione
				//ad ogni operzione verifico il timer
				timer=XScuTimer_GetCounterValue(&mytimer);
				if(timer==0){//viene riavviato
					XScuTimer_RestartTimer(&mytimer);
					xil_printf("il timer ha raggiunto lo zero %d\n ",cicli+1);
					cicli++;
				}
				else{
					xil_printf("il timer procede ed ha valore %d\n",timer);}
	}}
	XScuTimer_Stop(&mytimer);
	print("\n");
	xil_printf("IL RISULTATO DEL FILTRO DI SMOOTHING E %d\n",ris);
	//abbiamo delle operazioni fatte in un altro ciclo di clock sebbene non completo
	//if(timer>1){
	//	cicli=cicli+1;
	//}questo lo metto nel caso voglio i cicli separati e devo fare un altra variabie
	xil_printf("Il timer è finito ci sono %d cicli di clock \n",cicli);
    xil_printf("frequenza di clock %d \n",clock);
    tempo=(long double)cicli/(long double)clock;
    print("Il tempo di operazione del filtro è ");
    printf(":%.15Lf secondi\n",tempo);
    tempo=tempo*pow(10,6);
    printf("convetendo abbiamo %Lf microsecondi\n",tempo);
    print("\n");
    cleanup_platform();
    return 0;

}
