package cn.edu.whut.sept.zuul;

public class Item {

    private int itemID;
    private int itemRoomID;
    private String itemName;
    private int itemWeight;

    /**
     * 设置物品ID
     *
     * @param itemId 被设置的ID
     */
    public void setItemID(int itemId) {
        this.itemID = itemId;
    }

    /**
     * 获取物品ID
     *
     * @return 物品的ID
     */
    public int getItemID() {
        return itemID;
    }

    /**
     * 设置物品所属的房间ID
     *
     * @param itemRoomId 房间ID
     */
    public void setItemRoomID(int itemRoomId) {
        this.itemRoomID = itemRoomId;
    }

    /**
     * 获取物品所属的房间ID
     *
     * @return 房间ID
     */
    public int getItemRoomID() {
        return itemRoomID;
    }

    /**
     * 设置物品名称
     *
     * @param itemName 物品的名称
     */
    public void setItemName(String itemName) {
        this.itemName = itemName;
    }

    /**
     * 获取物品名称
     *
     * @return 物品的名称
     */
    public String getItemName() {
        return itemName;
    }

    /**
     * 设置物品的重量
     *
     * @param itemWeight 物品的重量
     */
    public void setItemWeight(int itemWeight) {
        this.itemWeight = itemWeight;
    }

    /**
     * 获取物品的重量
     *
     * @return 物品的重量
     */
    public int getItemWeight() {
        return itemWeight;
    }
}
