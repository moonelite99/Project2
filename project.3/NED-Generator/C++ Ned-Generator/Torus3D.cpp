#include <bits/stdc++.h>
using namespace std;

const int K = 3;
const int delay = 15;
const int offset = 200;
const int scale = 200;
const int sx = 80;
const int sy = -50;
int main()
{
    freopen("Torus3D.ned", "w+", stdout);
    cout << R"(simple Host
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
            )";
    cout << "delay = " << delay << "ms;" << endl;
    cout << "\t\t}";

    cout << "\n\t submodules: \n ";

    // Tao Switch
    for (int x = 0; x < K; x++)
    {
        for (int y = 0; y < K; y++)
        {
            for (int z = 0; z < K; z++)
            {
                cout << "\t\t sw" << x << "_" << y << "_" << z 
                << ": Switch { @display(\"p=" << offset + z * sx + x * scale << "," 
                << offset + z * sy + y * scale << ";i=device/switch\"); } \n";
            }
        }
    }
    // Tao Host
    for (int x = 0; x < K; x++)
    {
        for (int y = 0; y < K; y++)
        {
            for (int z = 0; z < K; z++)
            {
                cout << "\t\t h" << x << "_" << y << "_" << z 
                << ": Host { @display(\"p=" << offset + z * sx + x * scale - 30 << "," 
                << offset + z * sy + y * scale - 30 << ";i=device/server;is=s\"); } \n";
            }
        }
    }
    // Ket noi

    cout << "\tconnections:\n";

    //Lines
    for (int z = 0; z < K; z++)
    {
        for (int x = 0; x < K; x++)
        {
            for (int y = 0; y < K - 1; y++)
            {
                cout << "\t\tsw" << x << "_" << y << "_" << z << ".port++"
                     << " <--> Channel <--> "
                     << "sw" << x << "_" << y + 1 << "_" << z << ".port++;" << endl;
                // switches[x][y][z] <--> switches[x][y + 1][z]
            }
        }
        for (int y = 0; y < K; y++)
        {
            for (int x = 0; x < K - 1; x++)
            {
                cout << "\t\tsw" << x << "_" << y << "_" << z << ".port++"
                     << " <--> Channel <--> "
                     << "sw" << x + 1 << "_" << y << "_" << z << ".port++;" << endl;
                // switches[x][y][z], switches[x + 1][y][z]
            }
        }
    }
    for (int z = 0; z < K - 1; z++)
    {
        for (int x = 0; x < K; x++)
        {
            for (int y = 0; y < K; y++)
            {
                cout << "\t\tsw" << x << "_" << y << "_" << z << ".port++"
                     << " <--> Channel <--> "
                     << "sw" << x << "_" << y << "_" << z + 1 << ".port++;" << endl;
                //switches[x][y][z], switches[x][y][z + 1]
            }
        }
    }
    //Curves
    for (int z = 0; z < K; z++)
    {
        for (int x = 0; x < K; x++)
        {
            cout << "\t\tsw" << x << "_" << 0 << "_" << z << ".port++"
                 << " <--> Channel <--> "
                 << "sw" << x << "_" << K - 1 << "_" << z << ".port++;" << endl;
            //switches[x][0][z], switches[x][K - 1][z]
        }
        for (int y = 0; y < K; y++)
        {
            cout << "\t\tsw" << 0 << "_" << y << "_" << z << ".port++"
                 << " <--> Channel <--> "
                 << "sw" << K - 1 << "_" << y << "_" << z << ".port++;" << endl;
            //switches[0][y][z], switches[K - 1][y][z]
        }
    }
    for (int x = 0; x < K; x++)
    {
        for (int y = 0; y < K; y++)
        {
            cout << "\t\tsw" << x << "_" << y << "_" << 0 << ".port++"
                 << " <--> Channel <--> "
                 << "sw" << x << "_" << y << "_" << K - 1 << ".port++;" << endl;
            //switches[x][y][0], switches[x][y][K - 1]
        }
    }
    //Switch to Host
    for (int x = 0; x < K; x++)
    {
        for (int y = 0; y < K; y++)
        {
            for (int z = 0; z < K; z++)
            {
                cout << "\t\tsw" << x << "_" << y << "_" << z << ".port++"
                     << " <--> Channel <--> "
                     << "h" << x << "_" << y << "_" << z << ".port++;" << endl;
                //switches[x][y][z], hosts[x][y][z]
            }
        }
    }
    cout << "}";
    return 0;
}