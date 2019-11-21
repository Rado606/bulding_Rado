#include <stdio.h>                     // This ert_main.c example uses printf/fflush 
#include "budynek.h"   
#include <string>
#include <stddef.h>
#include <windows.h>
#include <cstdio>
#include <iostream>


static symulacja_budynkuModelClass rtObj;// Instance of model class

void rt_OneStep(void){
  rtObj.step();
}

int main(){
	rtObj.initialize();
  
	int time_sim = 0;
	int samples = 0;
	int time = 10000;
	int Tzco = 70;
	int T_o= 10;
	
	int iteration = 0;
    bool flagLoop = true;
	bool sim_flag = false;

    while(flagLoop == true) {  // additional interrupt for debugging replace with  "   while(true) {  "
			///GET tu musisz napisać sobie sam kod który Ci pobiera aktualne dane z serwera, bo ja chyba tak z głowy sam nie dam rady, zresztą pisze to w notepad++ więc nie za bardzo mam możliwość się sprawdzić
		// "time" jako czas tylko najlepiej w sekundach i w formacie double, jak nie to daj znać to poprawięc kod na te floaty, ale to walnie mocno po obliczeniach
		// "Tzco" jako temperature wychodzącą z wymiennika ciepła
		// "T_o" jako temperaturę otoczenia
		//
		bool test = time_sim != time;
		// std::cout << "test_val: " << test << std::endl;			debug porous
		//std::cout <<  "sim_time: " << time_sim << std::endl;
		//std::cout << "time: " << time << std::endl;
		if (time_sim != time){
			//std::cout << "if" << std::endl;			
			samples = time - time_sim;
			std::cout << samples << std::endl;
			rtObj.rtU.T_zCo = Tzco;
			for (int i = 0; i < samples; i++){
				std::cout << std::endl << "Czas [s]: " << i << std::endl;
				rtObj.rtU.T_otoczenia = 0 ; //just for debuging 
				rtObj.rtU.T_zadana = 20 ;		//just for debuging
				
				rtObj.rtU.T_otoczenia = T_o;
				
				rtObj.step();
				std::cout << "Sterowanie: " << rtObj.rtY.Sterowanie << std::endl;
				std::cout << "T_ref: " << rtObj.rtY.T_ref << std::endl;
				std::cout << "T_r: " << rtObj.rtY.T_r << std::endl;
				std::cout << "T_pco: " << rtObj.rtY.T_pco << std::endl;
				std::cout << "Uchyb: " << (rtObj.rtY.T_ref - rtObj.rtY.T_r) << std::endl;
			}
			time_sim = time;
			sim_flag = true;
		}
		
		
		
		if (sim_flag == true){
			// Put values from simulation
			sim_flag = false;
			//std::cout << "helo";
			
		}
		
		
		
		if(GetAsyncKeyState(VK_SPACE) & 0x8000) {	// interupt for debuging
		flagLoop = false;							// /|\
												// -||-
		}
	}
    std::cout << "loop stoped" << '\n';
	rtObj.terminate();
	return 0;
}

//
// File trailer for generated code.
//
// [EOF]
//
