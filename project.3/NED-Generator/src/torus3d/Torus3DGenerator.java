import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Torus3DGenerator {
    private final int K;
    private final double SCALE = 200;
    private final double OFFSET = 200;
    private final double SKEW_X = 80;
    final double HOST_OFFSET_X = -30;
    final double HOST_OFFSET_Y = -30;
    private Switch[][][] switches;
    private Host[][][] hosts;
    private ArrayList<Connection> connections = new ArrayList<>();

    public Torus3DGenerator(int k) {
        K = k;
        createSwitches();
        createHosts();
        createConnections();
    }

    private void createSwitches() {
        switches = new Switch[K][K][K];
        for (int x = 0; x < K; x++) {
            for (int y = 0; y < K; y++) {
                for (int z = 0; z < K; z++) {
                    Switch s = new Switch(x, y, z);
                    s.setPosX(OFFSET + z * SKEW_X + x * SCALE);
                    double SKEW_Y = -50;
                    s.setPosY(OFFSET + z * SKEW_Y + y * SCALE);
                    switches[x][y][z] = s;
                }
            }
        }
    }

    private void createHosts() {
        hosts = new Host[K][K][K];
        for (int x = 0; x < K; x++) {
            for (int y = 0; y < K; y++) {
                for (int z = 0; z < K; z++) {
                    var host = new Host(x, y, z);
                    host.setPosX(switches[x][y][z].getPosX() + HOST_OFFSET_X);
                    host.setPosY(switches[x][y][z].getPosY() + HOST_OFFSET_Y);
                    hosts[x][y][z] = host;
                }
            }
        }
    }

    private void createConnections() {
        var channel = new Channel("Channel", 15);

        // Switch to Switch (Lines)
        for (int z = 0; z < K; z++) {
            for (int x = 0; x < K; x++) {
                for (int y = 0; y < K - 1; y++) {
                    connections.add(new Connection(switches[x][y][z], switches[x][y + 1][z], channel));
                }
            }
            for (int y = 0; y < K; y++) {
                for (int x = 0; x < K - 1; x++) {
                    connections.add(new Connection(switches[x][y][z], switches[x + 1][y][z], channel));
                }
            }
        }
        for (int z = 0; z < K - 1; z++) {
            for (int x = 0; x < K; x++) {
                for (int y = 0; y < K; y++) {
                    connections.add(new Connection(switches[x][y][z], switches[x][y][z + 1], channel));
                }
            }
        }

        //Switch to Switch (Curves)
        for (int z = 0; z < K; z++) {
            for (int x = 0; x < K; x++) {
                connections.add(new Connection(switches[x][0][z], switches[x][K - 1][z], channel));
            }
            for (int y = 0; y < K; y++) {
                connections.add(new Connection(switches[0][y][z], switches[K - 1][y][z], channel));
            }
        }
        for (int x = 0; x < K; x++) {
            for (int y = 0; y < K; y++) {
                connections.add(new Connection(switches[x][y][0], switches[x][y][K - 1], channel));
            }
        }

       // Switch to Host
        for (int x = 0; x < K; x++) {
            for (int y = 0; y < K; y++) {
                for (int z = 0; z < K; z++) {
                    connections.add(new Connection(switches[x][y][z], hosts[x][y][z], channel));
                }
            }
        }
    }

    public String generateNED() {
        StringBuilder str = new StringBuilder();
        str.append("" +
                "simple Host\n" +
                "{\n" +
                "\tgates:\n" +
                "\t    inout port[];\n" +
                "}\n" +
                "\n" +
                "simple Switch\n" +
                "{\n" +
                "    gates:\n" +
                "        inout port[];\n" +
                "}\n" +
                "\n" +
                "network Torus3D\n" +
                "{\n" +
                "    @display(\"bgb=1000,700\");\n" +
                "    types:\n" +
                "        channel Channel extends ned.DelayChannel\n" +
                "        {\n" +
                "            delay = 15ms;\n" +
                "        }\n" +
                "    submodules:\n");
        for (int x = 0; x < K; x++) {
            for (int y = 0; y < K; y++) {
                for (int z = 0; z < K; z++) {
                    str.append(switches[x][y][z].toNED());
                }
            }
        }
        for (int x = 0; x < K; x++) {
            for (int y = 0; y < K; y++) {
                for (int z = 0; z < K; z++) {
                    str.append(hosts[x][y][z].toNED());
                }
            }
        }
        str.append("\tconnections:\n");
        for (var c : connections) {
            str.append(c.toNED());
        }
        str.append("}");
        return str.toString();
    }

    public String getConnectionsList() {
        StringBuilder stringBuilder = new StringBuilder();
        for (int x = 0; x < K; x++) {
            for (int y = 0; y < K; y++) {
                for (int z = 0; z < K; z++) {
                    stringBuilder.append(switches[x][y][z].name);
                    stringBuilder.append(" ");
                    for (var adjNode : switches[x][y][z].getAdjNodes()) {
                        stringBuilder.append(adjNode.getName());
                        stringBuilder.append(" ");
                    }
                    stringBuilder.deleteCharAt(stringBuilder.lastIndexOf(" "));
                    stringBuilder.append("\n");
                }
            }
        }
        stringBuilder.deleteCharAt(stringBuilder.lastIndexOf("\n"));
        return stringBuilder.toString();
    }

    public Map<Integer, Node> getMap() {
        Map<Integer, Node> map = new HashMap<>();
        int i = 0;
        for (int x = 0; x < K; x++) {
            for (int y = 0; y < K; y++) {
                for (int z = 0; z < K; z++) {
                    Node s = switches[x][y][z];
                    map.put(i++, s);
                }
            }
        }
        return map;
    }

}
