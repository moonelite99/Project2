simple Host
{
	gates:
	    inout port[];
}

simple Switch
{
    gates:
        inout port[];
}

network Torus3D
{
    @display("bgb=1000,800");
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 15ms;
		}
	 submodules: 
 		 sw0_0_0: Switch { @display("p=200,200;i=device/switch"); } 
		 sw0_0_1: Switch { @display("p=280,150;i=device/switch"); } 
		 sw0_0_2: Switch { @display("p=360,100;i=device/switch"); } 
		 sw0_1_0: Switch { @display("p=200,400;i=device/switch"); } 
		 sw0_1_1: Switch { @display("p=280,350;i=device/switch"); } 
		 sw0_1_2: Switch { @display("p=360,300;i=device/switch"); } 
		 sw0_2_0: Switch { @display("p=200,600;i=device/switch"); } 
		 sw0_2_1: Switch { @display("p=280,550;i=device/switch"); } 
		 sw0_2_2: Switch { @display("p=360,500;i=device/switch"); } 
		 sw1_0_0: Switch { @display("p=400,200;i=device/switch"); } 
		 sw1_0_1: Switch { @display("p=480,150;i=device/switch"); } 
		 sw1_0_2: Switch { @display("p=560,100;i=device/switch"); } 
		 sw1_1_0: Switch { @display("p=400,400;i=device/switch"); } 
		 sw1_1_1: Switch { @display("p=480,350;i=device/switch"); } 
		 sw1_1_2: Switch { @display("p=560,300;i=device/switch"); } 
		 sw1_2_0: Switch { @display("p=400,600;i=device/switch"); } 
		 sw1_2_1: Switch { @display("p=480,550;i=device/switch"); } 
		 sw1_2_2: Switch { @display("p=560,500;i=device/switch"); } 
		 sw2_0_0: Switch { @display("p=600,200;i=device/switch"); } 
		 sw2_0_1: Switch { @display("p=680,150;i=device/switch"); } 
		 sw2_0_2: Switch { @display("p=760,100;i=device/switch"); } 
		 sw2_1_0: Switch { @display("p=600,400;i=device/switch"); } 
		 sw2_1_1: Switch { @display("p=680,350;i=device/switch"); } 
		 sw2_1_2: Switch { @display("p=760,300;i=device/switch"); } 
		 sw2_2_0: Switch { @display("p=600,600;i=device/switch"); } 
		 sw2_2_1: Switch { @display("p=680,550;i=device/switch"); } 
		 sw2_2_2: Switch { @display("p=760,500;i=device/switch"); } 
		 h0_0_0: Host { @display("p=170,170;i=device/server;is=s"); } 
		 h0_0_1: Host { @display("p=250,120;i=device/server;is=s"); } 
		 h0_0_2: Host { @display("p=330,70;i=device/server;is=s"); } 
		 h0_1_0: Host { @display("p=170,370;i=device/server;is=s"); } 
		 h0_1_1: Host { @display("p=250,320;i=device/server;is=s"); } 
		 h0_1_2: Host { @display("p=330,270;i=device/server;is=s"); } 
		 h0_2_0: Host { @display("p=170,570;i=device/server;is=s"); } 
		 h0_2_1: Host { @display("p=250,520;i=device/server;is=s"); } 
		 h0_2_2: Host { @display("p=330,470;i=device/server;is=s"); } 
		 h1_0_0: Host { @display("p=370,170;i=device/server;is=s"); } 
		 h1_0_1: Host { @display("p=450,120;i=device/server;is=s"); } 
		 h1_0_2: Host { @display("p=530,70;i=device/server;is=s"); } 
		 h1_1_0: Host { @display("p=370,370;i=device/server;is=s"); } 
		 h1_1_1: Host { @display("p=450,320;i=device/server;is=s"); } 
		 h1_1_2: Host { @display("p=530,270;i=device/server;is=s"); } 
		 h1_2_0: Host { @display("p=370,570;i=device/server;is=s"); } 
		 h1_2_1: Host { @display("p=450,520;i=device/server;is=s"); } 
		 h1_2_2: Host { @display("p=530,470;i=device/server;is=s"); } 
		 h2_0_0: Host { @display("p=570,170;i=device/server;is=s"); } 
		 h2_0_1: Host { @display("p=650,120;i=device/server;is=s"); } 
		 h2_0_2: Host { @display("p=730,70;i=device/server;is=s"); } 
		 h2_1_0: Host { @display("p=570,370;i=device/server;is=s"); } 
		 h2_1_1: Host { @display("p=650,320;i=device/server;is=s"); } 
		 h2_1_2: Host { @display("p=730,270;i=device/server;is=s"); } 
		 h2_2_0: Host { @display("p=570,570;i=device/server;is=s"); } 
		 h2_2_1: Host { @display("p=650,520;i=device/server;is=s"); } 
		 h2_2_2: Host { @display("p=730,470;i=device/server;is=s"); } 
	connections:
		sw0_0_0.port++ <--> Channel <--> sw0_1_0.port++;
		sw0_1_0.port++ <--> Channel <--> sw0_2_0.port++;
		sw1_0_0.port++ <--> Channel <--> sw1_1_0.port++;
		sw1_1_0.port++ <--> Channel <--> sw1_2_0.port++;
		sw2_0_0.port++ <--> Channel <--> sw2_1_0.port++;
		sw2_1_0.port++ <--> Channel <--> sw2_2_0.port++;
		sw0_0_0.port++ <--> Channel <--> sw1_0_0.port++;
		sw1_0_0.port++ <--> Channel <--> sw2_0_0.port++;
		sw0_1_0.port++ <--> Channel <--> sw1_1_0.port++;
		sw1_1_0.port++ <--> Channel <--> sw2_1_0.port++;
		sw0_2_0.port++ <--> Channel <--> sw1_2_0.port++;
		sw1_2_0.port++ <--> Channel <--> sw2_2_0.port++;
		sw0_0_1.port++ <--> Channel <--> sw0_1_1.port++;
		sw0_1_1.port++ <--> Channel <--> sw0_2_1.port++;
		sw1_0_1.port++ <--> Channel <--> sw1_1_1.port++;
		sw1_1_1.port++ <--> Channel <--> sw1_2_1.port++;
		sw2_0_1.port++ <--> Channel <--> sw2_1_1.port++;
		sw2_1_1.port++ <--> Channel <--> sw2_2_1.port++;
		sw0_0_1.port++ <--> Channel <--> sw1_0_1.port++;
		sw1_0_1.port++ <--> Channel <--> sw2_0_1.port++;
		sw0_1_1.port++ <--> Channel <--> sw1_1_1.port++;
		sw1_1_1.port++ <--> Channel <--> sw2_1_1.port++;
		sw0_2_1.port++ <--> Channel <--> sw1_2_1.port++;
		sw1_2_1.port++ <--> Channel <--> sw2_2_1.port++;
		sw0_0_2.port++ <--> Channel <--> sw0_1_2.port++;
		sw0_1_2.port++ <--> Channel <--> sw0_2_2.port++;
		sw1_0_2.port++ <--> Channel <--> sw1_1_2.port++;
		sw1_1_2.port++ <--> Channel <--> sw1_2_2.port++;
		sw2_0_2.port++ <--> Channel <--> sw2_1_2.port++;
		sw2_1_2.port++ <--> Channel <--> sw2_2_2.port++;
		sw0_0_2.port++ <--> Channel <--> sw1_0_2.port++;
		sw1_0_2.port++ <--> Channel <--> sw2_0_2.port++;
		sw0_1_2.port++ <--> Channel <--> sw1_1_2.port++;
		sw1_1_2.port++ <--> Channel <--> sw2_1_2.port++;
		sw0_2_2.port++ <--> Channel <--> sw1_2_2.port++;
		sw1_2_2.port++ <--> Channel <--> sw2_2_2.port++;
		sw0_0_0.port++ <--> Channel <--> sw0_0_1.port++;
		sw0_1_0.port++ <--> Channel <--> sw0_1_1.port++;
		sw0_2_0.port++ <--> Channel <--> sw0_2_1.port++;
		sw1_0_0.port++ <--> Channel <--> sw1_0_1.port++;
		sw1_1_0.port++ <--> Channel <--> sw1_1_1.port++;
		sw1_2_0.port++ <--> Channel <--> sw1_2_1.port++;
		sw2_0_0.port++ <--> Channel <--> sw2_0_1.port++;
		sw2_1_0.port++ <--> Channel <--> sw2_1_1.port++;
		sw2_2_0.port++ <--> Channel <--> sw2_2_1.port++;
		sw0_0_1.port++ <--> Channel <--> sw0_0_2.port++;
		sw0_1_1.port++ <--> Channel <--> sw0_1_2.port++;
		sw0_2_1.port++ <--> Channel <--> sw0_2_2.port++;
		sw1_0_1.port++ <--> Channel <--> sw1_0_2.port++;
		sw1_1_1.port++ <--> Channel <--> sw1_1_2.port++;
		sw1_2_1.port++ <--> Channel <--> sw1_2_2.port++;
		sw2_0_1.port++ <--> Channel <--> sw2_0_2.port++;
		sw2_1_1.port++ <--> Channel <--> sw2_1_2.port++;
		sw2_2_1.port++ <--> Channel <--> sw2_2_2.port++;
		sw0_0_0.port++ <--> Channel <--> sw0_2_0.port++;
		sw1_0_0.port++ <--> Channel <--> sw1_2_0.port++;
		sw2_0_0.port++ <--> Channel <--> sw2_2_0.port++;
		sw0_0_0.port++ <--> Channel <--> sw2_0_0.port++;
		sw0_1_0.port++ <--> Channel <--> sw2_1_0.port++;
		sw0_2_0.port++ <--> Channel <--> sw2_2_0.port++;
		sw0_0_1.port++ <--> Channel <--> sw0_2_1.port++;
		sw1_0_1.port++ <--> Channel <--> sw1_2_1.port++;
		sw2_0_1.port++ <--> Channel <--> sw2_2_1.port++;
		sw0_0_1.port++ <--> Channel <--> sw2_0_1.port++;
		sw0_1_1.port++ <--> Channel <--> sw2_1_1.port++;
		sw0_2_1.port++ <--> Channel <--> sw2_2_1.port++;
		sw0_0_2.port++ <--> Channel <--> sw0_2_2.port++;
		sw1_0_2.port++ <--> Channel <--> sw1_2_2.port++;
		sw2_0_2.port++ <--> Channel <--> sw2_2_2.port++;
		sw0_0_2.port++ <--> Channel <--> sw2_0_2.port++;
		sw0_1_2.port++ <--> Channel <--> sw2_1_2.port++;
		sw0_2_2.port++ <--> Channel <--> sw2_2_2.port++;
		sw0_0_0.port++ <--> Channel <--> sw0_0_2.port++;
		sw0_1_0.port++ <--> Channel <--> sw0_1_2.port++;
		sw0_2_0.port++ <--> Channel <--> sw0_2_2.port++;
		sw1_0_0.port++ <--> Channel <--> sw1_0_2.port++;
		sw1_1_0.port++ <--> Channel <--> sw1_1_2.port++;
		sw1_2_0.port++ <--> Channel <--> sw1_2_2.port++;
		sw2_0_0.port++ <--> Channel <--> sw2_0_2.port++;
		sw2_1_0.port++ <--> Channel <--> sw2_1_2.port++;
		sw2_2_0.port++ <--> Channel <--> sw2_2_2.port++;
		sw0_0_0.port++ <--> Channel <--> h0_0_0.port++;
		sw0_0_1.port++ <--> Channel <--> h0_0_1.port++;
		sw0_0_2.port++ <--> Channel <--> h0_0_2.port++;
		sw0_1_0.port++ <--> Channel <--> h0_1_0.port++;
		sw0_1_1.port++ <--> Channel <--> h0_1_1.port++;
		sw0_1_2.port++ <--> Channel <--> h0_1_2.port++;
		sw0_2_0.port++ <--> Channel <--> h0_2_0.port++;
		sw0_2_1.port++ <--> Channel <--> h0_2_1.port++;
		sw0_2_2.port++ <--> Channel <--> h0_2_2.port++;
		sw1_0_0.port++ <--> Channel <--> h1_0_0.port++;
		sw1_0_1.port++ <--> Channel <--> h1_0_1.port++;
		sw1_0_2.port++ <--> Channel <--> h1_0_2.port++;
		sw1_1_0.port++ <--> Channel <--> h1_1_0.port++;
		sw1_1_1.port++ <--> Channel <--> h1_1_1.port++;
		sw1_1_2.port++ <--> Channel <--> h1_1_2.port++;
		sw1_2_0.port++ <--> Channel <--> h1_2_0.port++;
		sw1_2_1.port++ <--> Channel <--> h1_2_1.port++;
		sw1_2_2.port++ <--> Channel <--> h1_2_2.port++;
		sw2_0_0.port++ <--> Channel <--> h2_0_0.port++;
		sw2_0_1.port++ <--> Channel <--> h2_0_1.port++;
		sw2_0_2.port++ <--> Channel <--> h2_0_2.port++;
		sw2_1_0.port++ <--> Channel <--> h2_1_0.port++;
		sw2_1_1.port++ <--> Channel <--> h2_1_1.port++;
		sw2_1_2.port++ <--> Channel <--> h2_1_2.port++;
		sw2_2_0.port++ <--> Channel <--> h2_2_0.port++;
		sw2_2_1.port++ <--> Channel <--> h2_2_1.port++;
		sw2_2_2.port++ <--> Channel <--> h2_2_2.port++;
}