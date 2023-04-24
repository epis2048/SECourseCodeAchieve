package cn.edu.whut.sept.zuul;

import java.util.ArrayList;
import java.util.Set;
import java.util.HashMap;

public class Room {

    private String description;
    private final HashMap<String, Room> exits;

    private int roomID;
    private String roomName;
    private final ArrayList<Item> items;
    private boolean isRandomRoom;
    private boolean hasMagicCookie;

    /**
     * 初始化房间信息
     */
    public Room() {
        exits = new HashMap<>();
        items = new ArrayList<Item>();
        isRandomRoom = false;
        hasMagicCookie = false;
    }

    /**
     * 设置房间出口
     *
     * @param direction 该出口的方向
     * @param neighbor  该出口邻居，即穿过该出口后下一个房间
     */
    public void setExit(String direction, Room neighbor) {
        exits.put(direction, neighbor);
    }

    /**
     * 获取房间的简短的描述
     *
     * @return 房间的描述
     */
    public String getShortDescription() {
        return description;
    }

    /**
     * 获取房间的长描述
     *
     * @return 房间的长描述
     */
    public String getLongDescription() {
        return "You are " + description + ".\n" + getExitString();
    }

    /**
     * 该房间所有的出口拼接为字符串
     *
     * @return 房间所有出口组成的字符串
     */
    private String getExitString() {
        StringBuilder returnString = new StringBuilder("Exits:");
        Set<String> keys = exits.keySet();
        for (String exit : keys) {
            returnString.append(" ").append(exit);
        }
        return returnString.toString();
    }

    /**
     * 获取该房间在某个方向的出口
     *
     * @param direction 方向
     * @return 该方向上出口对应的房间
     */
    public Room getExit(String direction) {
        return exits.get(direction);
    }

    /**
     * 设置房间ID
     *
     * @param roomID 房间的ID
     */
    public void setRoomID(int roomID) {
        this.roomID = roomID;
    }

    public int getRoomID() {
        return roomID;
    }

    /**
     * 设置房间名称
     *
     * @param roomName 房间的名称
     */
    public void setRoomName(String roomName) {
        this.roomName = roomName;
    }

    public String getRoomName() {
        return roomName;
    }

    /**
     * 设置房间描述
     *
     * @param description 房间的描述
     */
    public void setDescription(String description) {
        this.description = description;
    }

    /**
     * 向房间内增加一个物品
     *
     * @param item 增加的物品
     */
    public void addItem(Item item) {
        items.add(item);
    }

    /**
     * 获取房间内的所有物品
     *
     * @return 物品列表
     */
    public ArrayList<Item> getItems() {
        return items;
    }

    /**
     * 设置该房间是否会随机传送
     *
     * @param isRandomRoom 该房间是否会随机传送
     */
    public void setIsRandomRoom(boolean isRandomRoom) {
        this.isRandomRoom = isRandomRoom;
    }

    /**
     * 获取是否是具有随机传送功能的房间
     *
     * @return 该房间是否会随机传送
     */
    public boolean getIsRandomRoom() {
        return isRandomRoom;
    }

    public boolean isHasMagicCookie() {
        return hasMagicCookie;
    }

    public void setHasMagicCookie(boolean hasMagicCookie) {
        this.hasMagicCookie = hasMagicCookie;
    }
}


