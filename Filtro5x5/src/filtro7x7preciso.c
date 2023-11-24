#include <stdio_ext.h>
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <stdlib.h>
#include "xscutimer.h"
#include <math.h>
#include "xil_io.h"
#include "xil_cache_l.h"
#include "Lena512_sr180.h"
#include "xtime_l.h"

#define DDRBaseAddr 0x00100000
#define DDRDestAddr 0x1FFFFFFF
#define DDRBaseAddr2 0x10000000
#define DDRBaseAddr3 0x100F0000


int main(){
    XTime tStart, tEnd;
    init_platform();
    int c=0;
    int r=0;
    int M=7;
    int N=7;
    clock_t inizio,fine;
    int cicli=0;
    int centro=ceil(N/2); //prendo il limite superiore della divisione
    float tempo=0;//tempo finale in secondi
    int valori[7][7];


//SCRITTURA DEELLA FOTO IN MEMORIA
    for(u32 i=0;i<512*512;i++){
    	Xil_Out8(DDRBaseAddr2+i,lenna[i]);
    	c++;
    	if(c==512){
    		c=0;
    		r++;
     }  }

tStart=0;
printf("il timer ha valore %llu\n",tStart);
XTime_GetTime(&tStart);//prendo il valore del timer all inizio
int finestra[N][M];
c=0;
r=0;
for(u32 i=0;i<512*512;i++){
        finestra[3][3]=Xil_In8(DDRBaseAddr2+512*r+c);

        //riga 0
        if(r>2 && c>2){
           finestra[0][0]=Xil_In8(DDRBaseAddr2+512*(r-3)+c-3);
        }
        else finestra[0][0]=0;

        if(r>2 && c>1){
            finestra[0][1]=Xil_In8(DDRBaseAddr2+512*(r-3)+c-2);
        }
        else finestra[0][1]=0;

        if(r>2 && c>0){
            finestra[0][2]=Xil_In8(DDRBaseAddr2+512*(r-3)+c-1);
        }
        else finestra[0][2]=0;

        if(r>2){
            finestra[0][3]=Xil_In8(DDRBaseAddr2+512*(r-3)+c);
        }
        else finestra[0][3]=0;

        if(r>2 && c<511){
            finestra[0][4]=Xil_In8(DDRBaseAddr2+512*(r-3)+c+1);
        }
        else finestra[0][4]=0;

        if(r>2 && c<510){
            finestra[0][5]=Xil_In8(DDRBaseAddr2+512*(r-3)+c+2);
        }
        else finestra[0][5]=0;

        if(r>2 && c<509){
            finestra[0][6]=Xil_In8(DDRBaseAddr2+512*(r-3)+c+3);
        }
        else finestra[0][6]=0;

        //riga1
        if(r>1 && c>2){
           finestra[1][0]=Xil_In8(DDRBaseAddr2+512*(r-2)+c-3);
        }
        else finestra[1][0]=0;

        if(r>1 && c>1){
            finestra[1][1]=Xil_In8(DDRBaseAddr2+512*(r-2)+c-2);
        }
        else finestra[1][1]=0;

        if(r>1 && c>0){
            finestra[1][2]=Xil_In8(DDRBaseAddr2+512*(r-2)+c-1);
        }
        else finestra[1][2]=0;

        if(r>1){
            finestra[1][3]=Xil_In8(DDRBaseAddr2+512*(r-2)+c);
        }
        else finestra[1][3]=0;

        if(r>1 && c<511){
            finestra[1][4]=Xil_In8(DDRBaseAddr2+512*(r-2)+c+1);
        }
        else finestra[1][4]=0;

        if(r>1 && c<510){
            finestra[1][5]=Xil_In8(DDRBaseAddr2+512*(r-2)+c+2);
        }
        else finestra[1][5]=0;

        if(r>1 && c<509){
            finestra[1][6]=Xil_In8(DDRBaseAddr2+512*(r-2)+c+3);
        }
        else finestra[1][6]=0;


        //riga 2
        if(r>0 && c>2){
           finestra[2][0]=Xil_In8(DDRBaseAddr2+512*(r-1)+c-3);
        }
        else finestra[2][0]=0;

        if(r>0 && c>1){
            finestra[2][1]=Xil_In8(DDRBaseAddr2+512*(r-1)+c-2);
        }
        else finestra[2][1]=0;

        if(r>0 && c>0){
            finestra[2][2]=Xil_In8(DDRBaseAddr2+512*(r-1)+c-1);
        }
        else finestra[2][2]=0;

        if(r>0){
            finestra[2][3]=Xil_In8(DDRBaseAddr2+512*(r-1)+c);
        }
        else finestra[2][3]=0;

        if(r>0 && c<511){
            finestra[2][4]=Xil_In8(DDRBaseAddr2+512*(r-1)+c+1);
        }
        else finestra[2][4]=0;

        if(r>0 && c<510){
            finestra[2][5]=Xil_In8(DDRBaseAddr2+512*(r-1)+c+2);
        }
        else finestra[2][5]=0;

        if(r>0 && c<509){
            finestra[2][6]=Xil_In8(DDRBaseAddr2+512*(r-1)+c+3);
        }
        else finestra[2][6]=0;

        //riga 3
        if( c>2){
           finestra[3][0]=Xil_In8(DDRBaseAddr2+512*(r)+c-3);
        }
        else finestra[3][0]=0;

        if(c>1){
            finestra[3][1]=Xil_In8(DDRBaseAddr2+512*(r)+c-2);
        }
        else finestra[3][1]=0;

        if(c>0){
            finestra[3][2]=Xil_In8(DDRBaseAddr2+512*(r)+c-1);
        }
        else finestra[3][2]=0;

        if( c<511){
            finestra[3][4]=Xil_In8(DDRBaseAddr2+512*(r)+c+1);
        }
        else finestra[3][4]=0;

        if(c<510){
            finestra[3][5]=Xil_In8(DDRBaseAddr2+512*(r)+c+2);
        }
        else finestra[3][5]=0;

        if(c<509){
            finestra[3][6]=Xil_In8(DDRBaseAddr2+512*(r)+c+3);
        }
        else finestra[3][6]=0;

        //riga 4
        if(r<511 && c>2){
           finestra[4][0]=Xil_In8(DDRBaseAddr2+512*(r+1)+c-3);
        }
        else finestra[4][0]=0;

        if(r<511 && c>1){
           finestra[4][1]=Xil_In8(DDRBaseAddr2+512*(r+1)+c-2);
        }
        else finestra[4][1]=0;

        if(r<511 && c>0){
            finestra[4][2]=Xil_In8(DDRBaseAddr2+512*(r+1)+c-1);
        }
        else finestra[4][2]=0;

        if(r<511){
            finestra[4][3]=Xil_In8(DDRBaseAddr2+512*(r+1)+c);
        }
        else finestra[4][3]=0;

        if(r<511 && c<511){
            finestra[4][4]=Xil_In8(DDRBaseAddr2+512*(r+1)+c+1);
        }
        else finestra[4][4]=0;

        if(r<511 && c<510){
            finestra[4][5]=Xil_In8(DDRBaseAddr2+512*(r+1)+c+2);
        }
        else finestra[4][5]=0;

        if(r<511 && c<509){
            finestra[4][6]=Xil_In8(DDRBaseAddr2+512*(r+1)+c+3);
        }
        else finestra[4][6]=0;

        //riga 5
        if(r<510 && c>2){
           finestra[5][0]=Xil_In8(DDRBaseAddr2+512*(r+2)+c-3);
        }
        else finestra[5][0]=0;

        if(r<510 && c>1){
           finestra[5][1]=Xil_In8(DDRBaseAddr2+512*(r+2)+c-2);
        }
        else finestra[5][1]=0;

        if(r<510 && c>0){
            finestra[5][2]=Xil_In8(DDRBaseAddr2+512*(r+2)+c-1);
        }
        else finestra[5][2]=0;

        if(r<510){
            finestra[5][3]=Xil_In8(DDRBaseAddr2+512*(r+2)+c);
        }
        else finestra[5][3]=0;

        if(r<510 && c<511){
            finestra[5][4]=Xil_In8(DDRBaseAddr2+512*(r+2)+c+1);
        }
        else finestra[5][4]=0;

        if(r<510 && c<510){
            finestra[5][5]=Xil_In8(DDRBaseAddr2+512*(r+2)+c+2);
        }
        else finestra[5][5]=0;

        if(r<510 && c<509){
            finestra[5][6]=Xil_In8(DDRBaseAddr2+512*(r+2)+c+3);
        }
        else finestra[5][6]=0;


        //riga 6
        if(r<509 && c>2){
           finestra[5][0]=Xil_In8(DDRBaseAddr2+512*(r+3)+c-3);
        }
        else finestra[6][0]=0;

        if(r<509 && c>1){
           finestra[6][1]=Xil_In8(DDRBaseAddr2+512*(r+3)+c-2);
        }
        else finestra[6][1]=0;

        if(r<509 && c>0){
            finestra[6][2]=Xil_In8(DDRBaseAddr2+512*(r+3)+c-1);
        }
        else finestra[6][2]=0;

        if(r<509){
            finestra[6][3]=Xil_In8(DDRBaseAddr2+512*(r+3)+c);
        }
        else finestra[6][3]=0;

        if(r<509 && c<511){
            finestra[6][4]=Xil_In8(DDRBaseAddr2+512*(r+3)+c+1);
        }
        else finestra[6][4]=0;

        if(r<509 && c<510){
            finestra[6][5]=Xil_In8(DDRBaseAddr2+512*(r+3)+c+2);
        }
        else finestra[6][5]=0;

        if(r<510 && c<509){
            finestra[6][6]=Xil_In8(DDRBaseAddr2+512*(r+3)+c+3);
        }
        else finestra[6][6]=0;


              //FILTRO BILATERALE APPROSSIMATO
                int ass=0;
                int sottrazione=0;
                for(int i=0;i<N;i++){
                       for(int j=0;j<M;j++){
                    	   sottrazione=(finestra[i][j]-finestra[centro][centro]);
                    	   ass=fabs(sottrazione);
                    	   valori[i][j]=ass;
                    	   ass=0;}}



                //FILTRO RANGE
                float sigmar=15;
                float appr[N][M];
                float approssimazione=0;
                float calcolo=0;
                for(int i=0;i<N;i++){
                    		 for(int j=0;j<M;j++){
                    			 calcolo=((valori[i][j]*valori[i][j])/(2*(sigmar*sigmar)));
                    			 appr[i][j]=powl(2.7182,-calcolo);
                    			 }}


                 //FILTRO SPAZIALE
                 float matspaz[N][M];
                 float distanza=0;
                 float sigmas=1;
                 float spazio=0;
                 for(int i=0;i<N;i++){
                      for(int j=0;j<M;j++){
                         	 distanza=sqrt(pow(i-centro,2)+ pow(j-centro,2));
                         	 spazio=(distanza*distanza)/(2*(sigmas*sigmas));
                           	 matspaz[i][j]=powl(2.71828,-spazio);
                   	    	 }}



                  //FILTRO BILATERALE
                  float filtrob[N][M];
                  float risul;
                  int *indriga=&N;
                  int *indcol=&M;
                  for(u32 i=0;i<*indriga;i++){
                         for(u32 j=0;j<*indcol;j++){
                            risul=appr[i][j]*matspaz[i][j];
                          	filtrob[i][j]=risul*1,06;
                          	risul=0;

                         }}



                  //APPLICAZIONE FILTRO MATRICE 5X5
                          	   float tot=0;
                          	   float molt=0;
                          	   int risultatof=0;
                          	   for(int i=0;i<N;i++){
                          	   		for(int j=0;j<M;j++){
                          	   			    molt=finestra[i][j]*filtrob[i][j];
                          	   			    tot=tot+molt;
                          	   				molt=0;
                          	   		}}

                          	  // print("scrittura in memoria\n");
                          	   Xil_Out32(DDRBaseAddr,tot);
                          	   //print("lettura in memoria\n");
                          	   risultatof=Xil_In32(DDRBaseAddr);
                          	   //xil_printf("valore %d\n",risultatof);

                          	 //CALCOLO PIXEL CENTRALE
                          	  float denominatore=0;
                          	  float pixel=0;
                          	  int pi=0;
                          	  for(int i=0;i<N;i++){
                          	      for(int j=0;j<M;j++){
                          	            denominatore=denominatore+filtrob[i][j];
                          	       }
                          	   }
                          	   pixel=risultatof/denominatore;
                          	   pi=pixel;
                          	   Xil_Out8(DDRBaseAddr3+i,pi);
                          	   //risultato=Xil_In8(DDRBaseAddr3+i);
                          	   //printf("ris %d\n",pi);





  c++;
  if(c%512==0){
     r++;
     c=0;
  }
}
XTime_GetTime(&tEnd);
printf("cicli necessari %llu\n", (tEnd - tStart));
printf("tempo in secondi per il calcolo del FILTRO BILATERALE APPROSSIMATO %.2f\n", 1.0 * (tEnd - tStart) / (COUNTS_PER_SECOND*2));
printf("il timer ha valore %llu\n",tEnd);




    cleanup_platform();
    return 0;

}
