public class Switch extends Node {

    public Switch(int x, int y, int z) {
        super(x, y, z);
    }

    @Override
    protected void setName() {
        this.name = "sw" + x + "_" + y + "_" + z;
    }

    @Override
    public String toNED() {
        return "\t\t" + getName() + ": Switch { @display(\"p=" + getPosX() + "," + getPosY() + ";i=abstract/switch\"); }\n";
    }
}
