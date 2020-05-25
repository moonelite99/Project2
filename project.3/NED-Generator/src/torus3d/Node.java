import java.util.ArrayList;
import java.util.List;

public abstract class Node {
    protected String name;
    protected int x, y, z;
    protected double posX, posY;

    private List<Node> adjNodes = new ArrayList<>();

    public Node(int x, int y, int z) {
        setX(x);
        setY(y);
        setZ(z);
        setName();
    }

    public String getName() {
        return name;
    }

    protected abstract void setName();

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getZ() {
        return z;
    }

    public void setZ(int z) {
        this.z = z;
    }

    public double getPosX() {
        return posX;
    }

    public void setPosX(double posX) {
        this.posX = posX;
    }

    public double getPosY() {
        return posY;
    }

    public void setPosY(double posY) {
        this.posY = posY;
    }

    public List<Node> getAdjNodes() {
        return adjNodes;
    }


    public abstract String toNED();

    public void connectTo(Node node) {
        adjNodes.add(node);
    }
}
