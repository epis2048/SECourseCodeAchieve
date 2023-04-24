package cn.edu.whut.sept.zuul;

import cn.edu.whut.sept.zuul.DB;
import cn.edu.whut.sept.zuul.Item;
import cn.edu.whut.sept.zuul.Player;
import cn.edu.whut.sept.zuul.Room;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.HashMap;

import static org.junit.Assert.*;

public class DBTest {

    DB db;
    HashMap<Integer, Room> rooms;
    Room room1;
    Room room2;
    Player player;
    Item itemInRoom1;
    Item itemInRoom2;
    Item itemInPlayer;

    HashMap<Integer, Room> loadRooms;
    Player loadPlayer;

    @Before
    public void setUp() {
        db = new DB();

        // 设置room
        rooms = new HashMap<Integer, Room>();
        room1 = new Room();
        room1.setRoomID(1);
        room1.setRoomName("testRoom1");
        room2 = new Room();
        room2.setRoomID(2);
        room2.setRoomName("testRoom2");
        room1.setExit("north", room2);
        room2.setExit("south", room1);
        rooms.put(room1.getRoomID(), room1);
        rooms.put(room2.getRoomID(), room2);

        // 设置玩家
        for (String plName : db.getPlayerList()) {
            db.delPlayer(plName);
        }
        db.addPlayer("testPlayer");
        player = db.switchPlayer("testPlayer", rooms);
        assertNotNull(player);

        // 设置物品
        itemInRoom1 = new Item();
        itemInRoom1.setItemID(1);
        itemInRoom1.setItemName("i1");
        room1.addItem(itemInRoom1);
        itemInRoom2 = new Item();
        itemInRoom2.setItemID(2);
        itemInRoom2.setItemName("i2");
        room2.addItem(itemInRoom2);
        itemInPlayer = new Item();
        itemInPlayer.setItemID(3);
        itemInPlayer.setItemName("i3");
        player.addItem(itemInPlayer);
        db.save(rooms, player);
        loadRooms = db.loadRooms();
        loadPlayer = db.loadPlayer(loadRooms);
        db.loadItems(loadRooms, loadPlayer);
    }

    @After
    public void tearDown() {
        db.realiseDB();
    }

    /**
     * 测试保存后能否读取房间信息
     */
    @Test
    public void testRoom() {
        assertEquals(loadRooms.size(), 2);
        assertEquals(loadRooms.get(1).getRoomID(), 1);
        assertEquals(loadRooms.get(1).getRoomName(), "testRoom1");
        assertEquals(loadRooms.get(2).getRoomID(), 2);
        assertEquals(loadRooms.get(2).getRoomName(), "testRoom2");
    }

    /**
     * 测试保存后能否读取玩家信息
     */
    @Test
    public void testPlayerInfo() {
        assertEquals(loadPlayer.getPlayerName(), "testPlayer");
    }

    /**
     * 测试保存后能否读取房间内和玩家持有的物品
     */
    @Test
    public void testItem() {
        assertEquals(loadRooms.size(), 2);
        assertEquals(loadRooms.get(1).getItems().size(), 1);
        assertEquals(loadRooms.get(1).getItems().get(0).getItemID(), 1);
        assertEquals(loadRooms.get(1).getItems().get(0).getItemName(), "i1");
        assertEquals(loadRooms.get(2).getItems().size(), 1);
        assertEquals(loadRooms.get(2).getItems().get(0).getItemID(), 2);
        assertEquals(loadRooms.get(2).getItems().get(0).getItemName(), "i2");
        assertEquals(loadPlayer.getItems().size(), 1);
        assertEquals(loadPlayer.getItems().get(0).getItemID(), 3);
        assertEquals(loadPlayer.getItems().get(0).getItemName(), "i3");
    }

    /**
     * 测试玩家的增查删改
     */
    @Test
    public void testPlayer() {
        db.addPlayer("testPlayer2");
        ArrayList<String> playerList = db.getPlayerList();
        assertEquals(playerList.size(), 2);
        assertEquals(playerList.get(0), "testPlayer");
        assertEquals(playerList.get(1), "testPlayer2");
        Player newPlayer = db.switchPlayer(playerList.get(1), rooms);
        assertEquals(newPlayer.getPlayerName(), "testPlayer2");
        assertEquals(newPlayer.getTotalWeight(), 10);
        assertEquals(newPlayer.getCurrWeight(), 0);
        assertEquals(newPlayer.getCurrentRoomID(), 1);
        assertEquals(newPlayer.getCurrentRoom().getRoomID(), 1);
        assertEquals(newPlayer.getCurrentRoom().getRoomName(), "testRoom1");
        assertEquals(newPlayer.getItems().size(), 0);
        db.switchPlayer("testPlayer", rooms);
    }
}