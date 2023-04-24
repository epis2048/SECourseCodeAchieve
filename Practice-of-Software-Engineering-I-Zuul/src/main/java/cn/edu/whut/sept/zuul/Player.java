package cn.edu.whut.sept.zuul;

import java.util.ArrayList;

public class Player {

    private String playerName;
    private int currentRoomID;
    private Room currentRoom;

    private final ArrayList<Item> itemHeld;
    private int currWeight;
    private int totalWeight;

    public Player() {
        playerName = "my";
        itemHeld = new ArrayList<Item>();
        totalWeight = 10;
    }

    public String getPlayerName() {
        return playerName;
    }

    public void setPlayerName(String playerName) {
        this.playerName = playerName;
    }

    public int getCurrentRoomID() {
        return currentRoomID;
    }

    public Room getCurrentRoom() {
        return currentRoom;
    }

    public void setCurrentRoomID(int currentRoomID) {
        this.currentRoomID = currentRoomID;
    }

    public void setCurrentRoom(Room currentRoom) {
        this.currentRoom = currentRoom;
        setCurrentRoomID(currentRoom.getRoomID());
    }

    public int getTotalWeight() {
        return totalWeight;
    }

    public void setTotalWeight(int totalWeight) {
        this.totalWeight = totalWeight;
    }

    /**
     * 拾取一个物品，要判断是否超重
     *
     * @param item 物品对象
     * @return 是否成功
     */
    public boolean addItem(Item item) {
        if (this.currWeight + item.getItemWeight() <= this.getTotalWeight()) {
            itemHeld.add(item);
            currWeight += item.getItemWeight();
            return true;
        } else {
            return false;
        }
    }

    public void removeItem(int itemNum) {
        currWeight -= itemHeld.get(itemNum).getItemWeight();
        itemHeld.remove(itemNum);
    }

    public ArrayList<Item> getItems() {
        return itemHeld;
    }

    public int getCurrWeight() {
        return currWeight;
    }

    public void setCurrWeight(int currWeight) {
        this.currWeight = currWeight;
    }
}
