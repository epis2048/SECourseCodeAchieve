package cn.edu.whut.sept.zuul;

import cn.edu.whut.sept.zuul.Command;
import cn.edu.whut.sept.zuul.DB;
import cn.edu.whut.sept.zuul.Game;
import cn.edu.whut.sept.zuul.Item;
import cn.edu.whut.sept.zuul.Player;
import cn.edu.whut.sept.zuul.Room;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.util.HashMap;

import static org.junit.Assert.*;

public class GameTest {

    DB db;
    HashMap<Integer, Room> rooms;
    Room room1;
    Room room2;
    Player player;
    Item itemInRoom1;
    Item itemInRoom2;
    Item itemInPlayer;

    Game game;

    @Before
    public void setUp() {
        db = new DB();

        // 设置room
        rooms = new HashMap<Integer, Room>();
        room1 = new Room();
        room1.setRoomID(1);
        room1.setRoomName("testRoom1");
        room1.setHasMagicCookie(true);
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
        db.realiseDB();

        game = new Game();
    }

    @After
    public void tearDown() {
        game.releaseDB();
    }

    /**
     * 测试移动功能，go和back
     */
    @Test
    public void testGoBack() {
        assertEquals(game.getPlayer().getCurrentRoomID(), 1);
        game.getCommands().get("go").runCommand(new Command("go", "north"));
        assertEquals(game.getPlayer().getCurrentRoomID(), 2);
        game.getCommands().get("back").runCommand(new Command("back", null));
        assertEquals(game.getPlayer().getCurrentRoomID(), 1);
        game.getCommands().get("go").runCommand(new Command("go", "north"));
        game.getCommands().get("go").runCommand(new Command("go", "south"));
        assertEquals(game.getPlayer().getCurrentRoomID(), 1);
        game.getCommands().get("back").runCommand(new Command("back", "2"));
        assertEquals(game.getPlayer().getCurrentRoomID(), 1);
        game.getCommands().get("go").runCommand(new Command("go", "north"));
        game.getCommands().get("go").runCommand(new Command("go", "south"));
        game.getCommands().get("back").runCommand(new Command("back", null));
        assertEquals(game.getPlayer().getCurrentRoomID(), 2);
    }

    /**
     * 测试Take和Drop命令，用于拾起和房价物品
     */
    @Test
    public void testTakeDrop() {
        assertEquals(game.getPlayer().getItems().size(), 1);
        assertEquals(game.getPlayer().getItems().get(0).getItemID(), 3);
        game.getCommands().get("take").runCommand(new Command("take", "1"));
        assertEquals(game.getPlayer().getItems().size(), 2);
        assertEquals(game.getPlayer().getItems().get(1).getItemID(), 1);
    }

    /**
     * 测试Eat命令，增加背包上限
     */
    @Test
    public void testEat() {
        game.getCommands().get("eat").runCommand(new Command("eat", null));
        assertEquals(game.getPlayer().getTotalWeight(), 15);
    }
}