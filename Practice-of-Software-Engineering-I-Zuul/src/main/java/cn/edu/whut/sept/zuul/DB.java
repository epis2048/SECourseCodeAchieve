package cn.edu.whut.sept.zuul;

import java.sql.*;
import java.util.ArrayList;
import java.util.HashMap;

public class DB {

    private Connection conn = null;

    public DB() {
        try {
            Class.forName("org.sqlite.JDBC");
            conn = DriverManager.getConnection("jdbc:sqlite:data.db");
            conn.setAutoCommit(false);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 保存系统中的数据，物品隐含在房间和玩家中
     *
     * @param rooms  房间
     * @param player 玩家
     */
    public void save(HashMap<Integer, Room> rooms, Player player) {
        try {
            System.out.println("Begin to save...");
            Statement stmt;

            // 创建表
            stmt = conn.createStatement();
            stmt.executeUpdate("DROP TABLE IF EXISTS rooms;");
            stmt.executeUpdate("CREATE TABLE rooms(" +
                "id int primary key, " +
                "roomName text, " +
                "roomDes text, " +
                "isRandomRoom int, " +
                "hasMagicCookie int, " +
                "northExit int, " +
                "southExit int, " +
                "eastExit int, " +
                "westExit int" +
                ");");
            stmt.executeUpdate("DROP TABLE IF EXISTS items;");
            stmt.executeUpdate("CREATE TABLE items(" +
                "id int , " +
                "itemName text, " +
                "itemWhere int, " +
                "itemRoomID int, " +
                "itemPlayerName text, " +
                "itemWeight int" +
                ");");
            stmt.executeUpdate("UPDATE player SET lastLogin = 0;");
            conn.commit();

            // 保存数据
            PreparedStatement pstmtRooms = conn
                .prepareStatement("INSERT INTO rooms VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);");
            PreparedStatement pstmtItems = conn
                .prepareStatement("INSERT INTO items VALUES (?, ?, ?, ?, ?, ?);");
            PreparedStatement pstmtPlayer = conn.prepareStatement(
                "UPDATE player SET CurrentRoomID = ?, currWeight = ?, totalWeight = ?, lastLogin = 1 WHERE playerName = ?");
            for (HashMap.Entry<Integer, Room> room : rooms.entrySet()) {
                pstmtRooms.setInt(1, room.getKey());
                pstmtRooms.setString(2, room.getValue().getRoomName());
                pstmtRooms.setString(3, room.getValue().getShortDescription());
                pstmtRooms.setInt(4, (room.getValue().getIsRandomRoom() ? 1 : 0));
                pstmtRooms.setInt(5, (room.getValue().isHasMagicCookie() ? 1 : 0));
                pstmtRooms.setInt(6, (room.getValue().getExit("north") == null ? 0
                    : room.getValue().getExit("north").getRoomID()));
                pstmtRooms.setInt(7, (room.getValue().getExit("south") == null ? 0
                    : room.getValue().getExit("south").getRoomID()));
                pstmtRooms.setInt(8, (room.getValue().getExit("east") == null ? 0
                    : room.getValue().getExit("east").getRoomID()));
                pstmtRooms.setInt(9, (room.getValue().getExit("west") == null ? 0
                    : room.getValue().getExit("west").getRoomID()));
                pstmtRooms.executeUpdate();
                for (Item item : room.getValue().getItems()) {
                    pstmtItems.setInt(1, item.getItemID());
                    pstmtItems.setString(2, item.getItemName());
                    pstmtItems.setInt(3, 0);
                    pstmtItems.setInt(4, room.getKey());
                    pstmtItems.setString(5, null);
                    pstmtItems.setInt(6, item.getItemWeight());
                    pstmtItems.executeUpdate();
                }
            }
            if (player != null) {
                for (Item item : player.getItems()) {
                    pstmtItems.setInt(1, item.getItemID());
                    pstmtItems.setString(2, item.getItemName());
                    pstmtItems.setInt(3, 1);
                    pstmtItems.setInt(4, 0);
                    pstmtItems.setString(5, player.getPlayerName());
                    pstmtItems.setInt(6, item.getItemWeight());
                    pstmtItems.executeUpdate();
                }
                pstmtPlayer.setString(4, player.getPlayerName());
                pstmtPlayer.setInt(1, player.getCurrentRoomID());
                pstmtPlayer.setInt(2, player.getCurrWeight());
                pstmtPlayer.setInt(3, player.getTotalWeight());
                pstmtPlayer.executeUpdate();
            }
            conn.commit();

            stmt.close();
            pstmtItems.close();
            pstmtPlayer.close();
            pstmtRooms.close();
            System.out.println("Save data successfully!");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 在数据库中增加一个用户
     *
     * @param playerName 用户名称
     */
    public void addPlayer(String playerName) {
        try {
            PreparedStatement pstmt = conn
                .prepareStatement("INSERT INTO player VALUES (?, 1, 0, 10, 0);");
            pstmt.setString(1, playerName);
            pstmt.executeUpdate();
            conn.commit();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 切换用户
     *
     * @param playerName 要切换的玩家名
     * @param rooms      房间列表
     * @return 切换后的player类
     */
    public Player switchPlayer(String playerName, HashMap<Integer, Room> rooms) {
        Player player = null;
        try {
            // 寻找用户，填充player
            PreparedStatement pstmt = conn
                .prepareStatement("SELECT * FROM player WHERE playerName = ?;");
            pstmt.setString(1, playerName);
            ResultSet rs = pstmt.executeQuery();
            while (rs.next()) {
                player = new Player();
                player.setPlayerName(playerName);
                player.setCurrentRoomID(rs.getInt("currentRoomID"));
                player.setCurrWeight(rs.getInt("currWeight"));
                player.setTotalWeight(rs.getInt("totalWeight"));
                player.setCurrentRoom(rooms.get(rs.getInt("currentRoomID")));

                // 设置用户状态
                Statement stmt = conn.createStatement();
                stmt.executeUpdate("UPDATE player SET lastLogin = 0;");
                pstmt = conn
                    .prepareStatement("UPDATE player SET lastLogin = 1 WHERE playerName = ?;");
                pstmt.setString(1, playerName);
                pstmt.executeUpdate();
                conn.commit();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return player;
    }

    /**
     * 获取玩家列表
     *
     * @return 返回的玩家列表，只有名称一列
     */
    public ArrayList<String> getPlayerList() {
        ArrayList<String> players = new ArrayList<String>();
        try {
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT playerName FROM player;");
            while (rs.next()) {
                players.add(rs.getString("playerName"));
            }
        } catch (Exception e) {
            System.err.println(e.getClass().getName() + ": " + e.getMessage());
        }
        return players;
    }

    public void delPlayer(String playerName) {
        try {
            PreparedStatement pstmt = conn
                .prepareStatement("DELETE FROM player WHERE playerName = ?");
            pstmt.setString(1, playerName);
            pstmt.executeUpdate();
            conn.commit();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 加载房间信息
     *
     * @return 返回一张哈希表
     */
    public HashMap<Integer, Room> loadRooms() {
        try {
            HashMap<Integer, Room> rooms = new HashMap<Integer, Room>();
            Statement stmt;
            stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM rooms;");
            while (rs.next()) {
                Room room = new Room();
                room.setRoomID(rs.getInt("id"));
                room.setRoomName(rs.getString("roomName"));
                room.setIsRandomRoom(rs.getInt("isRandomRoom") == 1);
                room.setHasMagicCookie(rs.getInt("hasMagicCookie") == 1);
                room.setDescription(rs.getString("roomDes"));
                rooms.put(rs.getInt("id"), room);
            }
            rs.close();
            rs = stmt.executeQuery("SELECT * FROM rooms;");
            while (rs.next()) {
                Room room = rooms.get(rs.getInt("id"));
                if (rs.getInt("northExit") != 0) {
                    room.setExit("north", rooms.get(rs.getInt("northExit")));
                }
                if (rs.getInt("southExit") != 0) {
                    room.setExit("south", rooms.get(rs.getInt("southExit")));
                }
                if (rs.getInt("eastExit") != 0) {
                    room.setExit("east", rooms.get(rs.getInt("eastExit")));
                }
                if (rs.getInt("westExit") != 0) {
                    room.setExit("west", rooms.get(rs.getInt("westExit")));
                }
            }
            rs.close();
            stmt.close();
            return rooms;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    /**
     * 加载玩家信息
     *
     * @param rooms 需要给出已经加载好的房间信息
     * @return 返回Player类
     */
    public Player loadPlayer(HashMap<Integer, Room> rooms) {
        try {
            Player player = new Player();
            Statement stmt;
            stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM player where lastLogin = 1;");
            boolean hasFound = false;
            while (rs.next()) {
                hasFound = true;
                player.setPlayerName(rs.getString("playerName"));
                player.setCurrentRoomID(rs.getInt("currentRoomID"));
                player.setCurrentRoom(rooms.get(player.getCurrentRoomID()));
                player.setCurrWeight(rs.getInt("currWeight"));
                player.setTotalWeight(rs.getInt("totalWeight"));
            }
            if (!hasFound) {
                rs.close();
                stmt.close();
                return null;
            }
            rs.close();
            stmt.close();
            return player;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    /**
     * 加载物品信息
     *
     * @param rooms  已经加载好的房间的指针
     * @param player 已经加载好的玩家的指针
     */
    public void loadItems(HashMap<Integer, Room> rooms, Player player) {
        try {
            HashMap<Integer, Item> items = new HashMap<Integer, Item>();
            PreparedStatement pstmt;
            if (player != null) {
                pstmt = conn.prepareStatement(
                    "SELECT * FROM items WHERE itemWhere = 0 OR (itemWhere = 1 and itemPlayerName = ?);");
                pstmt.setString(1, player.getPlayerName());
            } else {
                pstmt = conn.prepareStatement("SELECT * FROM items WHERE itemWhere = 0;");
            }
            ResultSet rs = pstmt.executeQuery();
            while (rs.next()) {
                Item item = new Item();
                item.setItemID(rs.getInt("id"));
                item.setItemName(rs.getString("itemName"));
                item.setItemRoomID(rs.getInt("itemRoomID"));
                item.setItemWeight(rs.getInt("itemWeight"));
                if (rs.getInt("itemWhere") == 1) {
                    if(player != null) {
                        player.getItems().add(item);
                    }
                } else {
                    rooms.get(rs.getInt("itemRoomID")).addItem(item);
                }
            }
            rs.close();
            pstmt.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void realiseDB() {
        try {
            conn.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void finalize() {
        realiseDB();
    }
}
