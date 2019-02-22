
	#include <C8051F020.h>



	void init_Clock(void); // System clock initialization
	void init_Port(void); // General system (ports) initialization 

	sbit output1=P0^4;
	sbit output2=P0^5;
	sbit output3=P0^6;
	sbit output4=P0^7;

	sbit a=P1^0;
	sbit b=P1^1;
	sbit c=P1^2;
	sbit d=P1^3;
	sbit e=P1^4;
	sbit f=P1^5;
	sbit g=P1^6;
	sbit h=P1^7;






	void init_Port(void)
	{

	// cross bar configurations
		XBR0 = 0x00;
		XBR1 = 0x00;
		XBR2 = 0x40; // Enable the crossbar, diable weak pullups

		P0MDOUT = 0xFF; // configured as open=drain for P0
		P2MDOUT = 0xFF; // configured as open=drain for P1
		P1MDOUT = 0x00; // configured as open=drain for P1

		

		P74OUT = 0x08;	// configure P.5 as puch-pull
		P5=0x0F; //0 to 3 are input pins
			 
	}




	void servo_delay(int times)     // Creating Delay in multilple of 50us using 8051 Timers
	{
	    int m;
	    for(m=0;m<times;m++)
	    {
	        TH0=0xFF;
	        TL0=0xD2;
	        TR0=1;
	        while(TF0==0);
	        TF0=0;
	        TR0=0;
	    }
	}


	void init_Clock(void)
	{	 /*
		// external osc must be config. first before the internal , to be ready when we switch to it.. 
		OSCXCN = 0x67; // External Osc Freq Control Bits (Bits
			// 2-0; XFCN2-0) set to 111 because crystal frequency > 6.7 MHz
			//Crystal Oscillator Mode (Bits 6-4; XOSCMD2-0) set to 110
		
		while (!(OSCXCN & 0x80)); // Wait till XTLVLD ( bit no 7 ) pin is set
		OSCICN = 0x08;
		*/
			
		//OSCICN = 0x04;  //2Mhz
	    OSCICN = 0x07;    //16Mhz
	}


	void clockwise(){

		int n;
	        //for(n=0;n<2;n=n+1)
	        //{
	    		output1=1;
				output2=0;
				output3=0;
				output4=0;
	         
	            servo_delay(150);
		
				output1=0;
				output2=1;
				output3=0;
				output4=0;
	   
	            servo_delay(150);

				output1=0;
				output2=0;
				output3=1;
				output4=0;
	  
	            servo_delay(150);
				output1=0;
				output2=0;
				output3=0;
				output4=1;
	     
	            servo_delay(150);
			
	        //}
	    }

	 
	void anticlock(){
		int n;
	        
			output1=0;
			output2=0;
			output3=0;
			output4=1;

	        servo_delay(150);
		
			output1=0;
			output2=0;
			output3=1;
			output4=0;

	        servo_delay(150);
			
			output1=0;
			output2=1;
			output3=0;
			output4=0;

	        servo_delay(150);
		
			output1=1;
			output2=0;
			output3=0;
			output4=0;
	 
	        servo_delay(150);
		
		

	    }
	void leds()
		{
			
		P1= 0x01;
	    }

	void main()
	{	int j ;
		int y ;
		int s ;
		int f0;
		int f1;
		int f2;
		int f4;
		f4=0;
		s=0;
		WDTCN = 0xDE; // Disable watchdog timer
		WDTCN = 0xAD;
		init_Clock();
		init_Port();

		P2 = 0x3f;
		
		
	    TMOD=0x01;                // Selecting Timer 0, Mode 1
		/*
		a=0;
		b=0;
		c=0;
		d=0;
		e=0;
		f=0;
		g=0;
		h=0;
		*/
		P1 = 0xff;
		
		
		while(1)

	    {	
		
			
		
			
			if(P5==0x0E && (s==1 || s==2 ) && (f4==0)) // floor 0
			{
				if(s==1 )
				{
				
					for(j=0;j<230;j++)
						{	
						
							anticlock(); // down
							if(P5==0x0D  )
							{
								f1= 1;
							}
							if(P5==0x0B )
							{
								f2= 1;
							}
						
						
						}
				}
				if(s==2 )
				{
					for(j=0;j<460;j++)
						{	
						
							anticlock(); // down
							
							if(P5==0x0D  )
							{
								f1= 1;
							}
							if(P5==0x0B )
							{
								f2= 1;
							}
						
						}	
				}
					P2=0x3f;		
					s=0;
					//-------hro7 anfz el interuppt bta3e 
					if (f1 ==1 ) // interpet from 0 floor to 1 floor
					{
						for(j=0;j<230;j++)
						{	
						
							clockwise(); // up
							P2=0x06;		
							s=1;
						
						}
						f1=0;
					}

					if (f2 ==1 ) // // interpet from 0 floor to 2 floor
					{
						for(j=0;j<460;j++)
						{	
				
							clockwise(); // up
							P2=0x5b;		
							s=2;
						}
						f2=0;
					}
			}
	//--------------------------------------------------------------------------------
			if(P5==0x0D && (s==0 || s==2 ) && (f4==0)) // a person in floor 1
			{
				if(s==0 )
				{
				
					for(j=0;j<230;j++)
						{	
							
							clockwise(); // up
							//leds();
							P2 = 0x00;
							if(P5==0x0E )
							{
								f0= 1;
							}
							if(P5==0x0B )
							{
								f2= 1;
							}
						
						}
				}
				if(s==2 )
				{
					for(j=0;j<230;j++)
						{	
						
							anticlock(); // down
							if(P5==0x0E )
							{
								f0= 1;
							}
							if(P5==0x0B )
							{
								f2= 1;
							}
						
						}	
				}
					P2=0x06;		
					s=1;
					
				//-------hro7 anfz el interuppt bta3e 
					if (f0 ==1 ) // interpet from 1 floor to 0 floor
					{
						servo_delay(950000000000);

						for(j=0;j<230;j++)
						{	
						
							anticlock(); // down
							P2=0x3f;		
							s=0;
						}
						f0=0;
					}

					if (f2 ==1 ) // // interpet from 1 floor to 2 floor
					{
						for(j=0;j<230;j++)
						{	
				
							clockwise(); // up
							P2=0x5b;		
							s=2;
						}
						f2=0;
					}

					

			}
	//------------------------------------------------------------------------------------
			if(P5==0x0B && (s==0 || s==1) && (f4==0)) //floor 2
			{
				if(s==0 ) // law kan fl door el zero asln
				{
				
					for(j=0;j<460;j++)
						{	
						
							clockwise(); // up
							if(P5==0x0E )
							{
								f0= 1;
							}
							if(P5==0x0D)
							{
								f1= 1;
							}
							
						}
				}
				if(s==1 )
				{
					for(j=0;j<230;j++)
						{	
						
							clockwise(); // down
							if(P5==0x0E )
							{
								f0= 1;
							}
							if(P5==0x0D)
							{
								f1= 1;
							}
						
						}	
				}
					P2=0x5B;		
					s=2;
					// hroo7 anfz el interuppt
					if (f0 ==1 ) // interpet from 2 floor to 0 floor
					{
						for(j=0;j<460;j++)
						{	
						
							anticlock(); // down
							P2=0x3f;		
							s=0;
						}
						f0=0;
					}

					if (f1 ==1 ) // // interpet from 2 floor to 1 floor
					{
						for(j=0;j<230;j++)
						{	
				
							anticlock(); // down
							P2=0x06;		
							s=1;
						}
						f1=0;
					}
			}
	//-------------------------------------------------------------------------
			if(P5==0x07 )
			{
				
				
					//clockwise();
					//P2=0x4F;
					//leds();
					f4=1;
						
				
				
				}

				if(P5!= 0x07 )
				{
				
				
					//clockwise();
					//P2=0x4F;
					//leds();
					f4=0;
						
				
				
				}
		
	      
	    }

		

	   

	}




