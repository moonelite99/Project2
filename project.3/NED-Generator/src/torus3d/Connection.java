public class Connection {
    private Node a;
    private Node b;
    private Channel channel;

    public Connection(Node a, Node b, Channel c){
        this.a = a;
        this.b = b;
        this.channel = c;
        a.connectTo(b);
        b.connectTo(a);
    }

    String toNED(){
        return "\t\t" + a.getName() + ".port++ <--> " + channel.getName() + " <--> " + b.getName() + ".port++;\n";
    }
}
