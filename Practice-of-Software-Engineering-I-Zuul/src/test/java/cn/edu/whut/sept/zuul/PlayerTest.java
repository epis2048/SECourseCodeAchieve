package cn.edu.whut.sept.zuul;

import cn.edu.whut.sept.zuul.Item;
import cn.edu.whut.sept.zuul.Player;
import cn.edu.whut.sept.zuul.Room;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class PlayerTest {

    Player player;
    Room room;
    Item item1;
    Item item2;

    @Before
    public void setUp() {
        player = new Player();
        player.setPlayerName("test");
        room = new Room();
        room.setRoomID(1);
        room.setRoomName("testRoom");
        item1 = new Item();
        item1.setItemName("testItem1");
        item1.setItemID(1);
        item1.setItemWeight(6);
        item2 = new Item();
        item2.setItemName("testItem2");
        item2.setItemID(2);
        item2.setItemWeight(5);
    }

    /**
     * 基础测试
     */
    @Test
    public void baseTest() {
        assertEquals(player.getPlayerName(), "test");
        assertEquals(player.getTotalWeight(), 10);
        assertEquals(player.getCurrWeight(), 0);
    }

    /**
     * 测试设置房间
     */
    @Test
    public void testRoom() {
        player.setCurrentRoom(room);
        assertEquals(player.getCurrentRoomID(), room.getRoomID());
    }

    /**
     * 测试物品相关
     */
    @Test
    public void testItem() {
        assertTrue(player.addItem(item1));
        assertEquals(player.getCurrWeight(), 6);
        assertEquals(player.getItems().size(), 1);
        assertEquals(player.getItems().get(0).getItemName(), "testItem1");
        assertEquals(player.getItems().get(0).getItemID(), 1);
        assertFalse(player.addItem(item2));
        assertEquals(player.getCurrWeight(), 6);
        assertEquals(player.getItems().size(), 1);
    }
}