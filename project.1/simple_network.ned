simple Host
{
    parameters:
        int EXB_SIZE = 2;
    gates:
        output out;
}

simple Switch
{
    gates:
        input in;
}

network SimpleNetwork
{
    parameters:
        double TIMEOUT = 1;
        double MSG_GEN_INTERVAL = 0.005;
        double CHANNEL_DELAY = 0.015;

        @display("bgb=242,100");
    submodules:
        host: Host {
            @display("i=device/pc;p=72.24,50");
        }
        switch: Switch {
            @display("p=173.04001,50;i=device/switch");
        }
    connections:
        host.out --> {  delay = 15ms; } --> switch.in;
}
