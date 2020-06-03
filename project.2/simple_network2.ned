simple SendHost
{
    parameters:
        int EXB_SIZE = 2;
    gates:
        input in @directIn;
        output out;
}
simple RecHost
{
    gates:
        input in;
}

simple Switch
{
    parameters:
        int EXB_SIZE = 2;
        int ENB_SIZE = 2;
        double OPERATION_TIME_PERIOD = 0.005;
    gates:
		input in[] ;
		input notifIn @directIn;
		output out;
}

network SimpleNetwork
{
    parameters:
        double TIMEOUT = 1;
        double MSG_GEN_TIME_PERIOD = 0.005;
        double CHANNEL_DELAY = 0.015;
        double INTERVAL = 0.005;
		double CREDIT_DELAY = 0.001
        @display("bgb=294.32,121.68");
    types:
    channel Channel extends ned.DelayChannel
    {
        delay = 15ms;
    }
    submodules:
        A: SendHost {
            @display("i=device/pc;p=45,25");
        }
        B: SendHost {
            @display("i=device/pc;p=45,60");
        }
        C: SendHost {
            @display("i=device/pc;p=45,95");
        }
        E: RecHost {
            @display("i=device/pc;p=215,60");
        }
        D: Switch {
            @display("p=130,60;i=device/switch");
        }
    connections:
        A.out --> Channel --> D.in++;
        B.out --> Channel --> D.in++;
        C.out --> Channel --> D.in++;
        D.out --> Channel --> E.in;
}
