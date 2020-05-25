public class Host extends Node{

    public Host(int x, int y, int z) {
        super(x, y, z);
    }

    @Override
    protected void setName() {
        this.name = "h" + x + "_" + y + "_" + z;
    }

    @Override
    public String toNED() {
        return "\t\t" + getName() + ": Host { @display(\"p=" + getPosX() + "," + getPosY() + ";i=abstract/server;is=s\"); }\n";
    }
}
