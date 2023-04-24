/*
  该类是“World-of-Zuul”应用程序的主类。
  《World of Zuul》是一款简单的文本冒险游戏。用户可以在一些房间组成的迷宫中探险。
  你们可以通过扩展该游戏的功能使它更有趣!.
  <p>
  如果想开始执行这个游戏，用户需要创建Game类的一个实例并调用“play”方法。
  <p>
  Game类的实例将创建并初始化所有其他类:它创建所有房间，并将它们连接成迷宫；它创建解析器
  接收用户输入，并将用户输入转换成命令后开始运行游戏。

  @author Michael Kölling and David J. Barnes
 * @version 1.0
 */
package cn.edu.whut.sept.zuul;

import java.util.*;

public class Game {

    private Parser parser;
    private Player player;
    private Stack<Room> visitRoomHistory;
    private final DB db;
    private HashMap<Integer, Room> rooms;
    private final HashMap<String, CommandBaseImpl> commands;

    /**
     * 创建游戏并初始化内部数据和解析器.
     */
    public Game() {
        // 创建命令列表
        commands = new HashMap<String, CommandBaseImpl>();
        commands.put("go", new CommandGo());
        commands.put("help", new CommandHelp());
        commands.put("look", new CommandLook());
        commands.put("back", new CommandBack());
        commands.put("take", new CommandTake());
        commands.put("drop", new CommandDrop());
        commands.put("item", new CommandItem());
        commands.put("eat", new CommandEat());
        commands.put("load", new CommandLoad());
        commands.put("save", new CommandSave());
        commands.put("init", new CommandInit());
        commands.put("quit", new CommandSave());
        commands.put("listplayer", new CommandListPlayer());
        commands.put("addplayer", new CommandAddPlayer());
        commands.put("delplayer", new CommandDelPlayer());
        commands.put("switch", new CommandSwitchPlayer());

        parser = new Parser(commands);
        db = new DB();

        // 执行加载命令
        commands.get("load").runCommand(new Command("load", null));
    }

    /**
     * 游戏主控循环，直到用户输入退出命令后结束整个程序.
     */
    public void play() {
        printWelcome();

        // Enter the main command loop.  Here we repeatedly read commands and
        // execute them until the game is over.

        boolean finished = false;
        while (!finished) {
            Command command = parser.getCommand();
            finished = processCommand(command);
        }
        System.out.println("Thank you for playing.  Good bye.");
    }

    /**
     * 向用户输出欢迎信息.
     */
    private void printWelcome() {
        System.out.println();
        if (player != null) {
            System.out.println("Hello, " + player.getPlayerName());
        }
        System.out.println("Welcome to the World of Zuul!");
        System.out.println("World of Zuul is a new, incredibly boring adventure game.");
        System.out.println("Type 'help' if you need help.");
        System.out.println();
    }

    /**
     * 执行用户输入的游戏指令.
     *
     * @param command 待处理的游戏指令，由解析器从用户输入内容生成.
     * @return 如果执行的是游戏结束指令，则返回true，否则返回false.
     */
    private boolean processCommand(Command command) {
        if (command.isUnknown()) {
            System.out.println("I don't know what you mean...");
            return false;
        }

        // 单独处理退出命令
        if (command.getCommandWord().equals("quit")) {
            if (command.hasSecondWord()) {
                System.out.println("Quit what?");
                return false;
            } else {
                commands.get("save").runCommand(new Command("save", null));
                return true;  // signal that we want to quit
            }
        }

        // 处理当前player为空的情况
        if (player == null) {
            if (!command.getCommandWord().equals("listplayer") && !command.getCommandWord()
                .equals("addplayer") &&
                !command.getCommandWord().equals("switch") && !command.getCommandWord()
                .equals("help") &&
                !command.getCommandWord().equals("init")) {
                System.out.println("Please choose a player before start!");
                return false;
            }
        }

        CommandBaseImpl commandHandler = commands.get(command.getCommandWord());
        commandHandler.runCommand(command);
        return false;
    }

    // implementations of user commands:

    /**
     * 执行help指令，在终端打印游戏帮助信息. 此处会输出游戏中用户可以输入的命令列表
     */
    public class CommandHelp implements CommandBaseImpl {

        @Override
        public void runCommand(Command command) {
            System.out.println("You are lost. You are alone. You wander");
            System.out.println("around at the university.");
            System.out.println();
            System.out.println("Your command words are:");
            parser.showCommands();
        }
    }


    /**
     * 执行go指令，向房间的指定方向出口移动，如果该出口连接了另一个房间，则会进入该房间， 否则打印输出错误提示信息.
     */
    class CommandGo implements CommandBaseImpl {

        @Override
        public void runCommand(Command command) {
            if (!command.hasSecondWord()) {
                // if there is no second word, we don't know where to go...
                System.out.println("Go where?");
                return;
            }

            String direction = command.getSecondWord();

            // Try to leave current room.
            Room nextRoom = player.getCurrentRoom().getExit(direction);

            if (nextRoom == null) {
                System.out.println("There is no door!");
            } else {
                if (nextRoom.getIsRandomRoom()) {
                    System.out.println("You choosed a random room, next room will be random!");
                    Random random = new Random();
                    List<Integer> keys = new ArrayList<Integer>(rooms.keySet());
                    int randomKey = keys.get(random.nextInt(keys.size()));
                    nextRoom = rooms.get(randomKey);
                }
                visitRoomHistory.push(player.getCurrentRoom());
                player.setCurrentRoom(nextRoom);
                System.out.println(player.getCurrentRoom().getLongDescription());
            }
        }
    }

    /**
     * 执行look指令，查看房间内有哪些物品
     */
    class CommandLook implements CommandBaseImpl {

        @Override
        public void runCommand(Command command) {
            System.out.println(player.getCurrentRoom().getLongDescription());
            if (player.getCurrentRoom().getItems().size() == 0) {
                System.out.println("There are no items in the current room!");
            } else {
                System.out.println("Items in the current room:");
                int num = 0;
                for (Item item : player.getCurrentRoom().getItems()) {
                    num++;
                    System.out.println(
                        num + ". " + item.getItemName() + " (Weight: " + item.getItemWeight()
                            + ")");
                }
            }
            if (player.getCurrentRoom().isHasMagicCookie()) {
                System.out.println("This room has a magic cookie!");
            }
        }
    }

    /**
     * 执行back命令，返回上一个访问的房间
     */
    class CommandBack implements CommandBaseImpl {

        @Override
        public void runCommand(Command command) {
            int goStep;

            // 处理输入的命令，获取要返回几步
            if (command.hasSecondWord()) {
                try {
                    goStep = Integer.parseInt(command.getSecondWord());
                    if (goStep < 1) {
                        System.out.println("Wrong step! Back step must bigger than 1!");
                        return;
                    }
                } catch (Exception e) {
                    System.out.println("Wrong command! Back step must be an integer!");
                    return;
                }
            } else {
                if (visitRoomHistory.empty()) {
                    System.out.println("You have no room to back!");
                    return;
                }
                goStep = 1;
            }

            // 判断能否回退
            if (goStep > visitRoomHistory.size()) {
                System.out.println(
                    "Wrong step! Back step must smaller than the number of rooms visited!");
                return;
            }

            // 执行回退
            while (goStep > 0) {
                goStep--;
                player.setCurrentRoom(visitRoomHistory.peek());
                visitRoomHistory.pop();
            }

            // 输出最后的房间
            System.out.println(player.getCurrentRoom().getLongDescription());
        }
    }

    /**
     * 执行take命令，拿起一件物品
     */
    class CommandTake implements CommandBaseImpl {

        @Override
        public void runCommand(Command command) {
            // 处理输入的命令，获取拿哪个东西
            if (command.hasSecondWord()) {
                try {
                    int takeNum;
                    takeNum = Integer.parseInt(command.getSecondWord());

                    // 判断输入
                    if (takeNum < 1 || takeNum > player.getCurrentRoom().getItems().size()) {
                        System.out.println("Num invalid!");
                        return;
                    }

                    // 拾取物品
                    Item takeItem = player.getCurrentRoom().getItems().get(takeNum - 1);
                    if (player.addItem(takeItem)) { // 成功
                        player.getCurrentRoom().getItems().remove(takeNum - 1);
                        System.out.println("Success take the " + takeItem.getItemName() + "!");
                    } else { // 失败
                        System.out.println(
                            "Failed to take the " + takeItem.getItemName() + "! Your bag is full!");
                    }
                } catch (Exception e) {
                    System.out.println("Wrong num! Your input must be an integer!");
                }
            } else {
                System.out.println("You should input the num of item you want to take!");
            }
        }
    }

    /**
     * 执行drop命令，把一件物品放在背包里
     */
    class CommandDrop implements CommandBaseImpl {

        @Override
        public void runCommand(Command command) {
            // 处理输入的命令，获取放哪个东西
            if (command.hasSecondWord()) {
                try {
                    int takeNum;
                    takeNum = Integer.parseInt(command.getSecondWord());

                    // 判断输入数据
                    if (takeNum < 1 || takeNum > player.getItems().size()) {
                        System.out.println("Wrong num! Num invalid!");
                        return;
                    }

                    // 移出物品
                    Item removedItem = player.getItems().get(takeNum - 1);
                    player.removeItem(takeNum - 1);
                    player.getCurrentRoom().addItem(removedItem);
                    System.out.println("Success to drop the " + removedItem.getItemName() + "!");
                } catch (Exception e) {
                    System.out.println("Wrong num! Num must be an integer!");
                }
            } else {
                System.out.println("You should input the num of item you want to take!");
            }
        }
    }

    /**
     * 执行Item命令，显示玩家当前拥有的物品
     */
    class CommandItem implements CommandBaseImpl {

        @Override
        public void runCommand(Command command) {
            if (player.getItems().size() == 0) {
                System.out.println("You do not have any items!");
            } else {
                System.out.println("Items with you:");
                int num = 0;
                for (Item item : player.getItems()) {
                    num++;
                    System.out.println(
                        num + ". " + item.getItemName() + " (Weight: " + item.getItemWeight()
                            + ")");
                }
            }
        }
    }

    /**
     * 执行Eat命令，用于增加拥有物品重量的上线
     */
    class CommandEat implements CommandBaseImpl {

        @Override
        public void runCommand(Command command) {
            if (player.getCurrentRoom().isHasMagicCookie()) {
                player.getCurrentRoom().setHasMagicCookie(false);
                player.setTotalWeight(player.getTotalWeight() + 5);
                System.out.println("You have ate a magic cookie, now your total weight is " + player
                    .getTotalWeight());
            } else {
                System.out.println("This room does not have anything to eat!");
            }
        }
    }

    /**
     * 执行Save命令，保存游戏数据
     */
    class CommandSave implements CommandBaseImpl {

        @Override
        public void runCommand(Command command) {
            db.save(rooms, player);
        }
    }

    /**
     * 执行Init命令，使用XML文件初始化游戏
     */
    class CommandInit implements CommandBaseImpl {

        @Override
        public void runCommand(Command command) {
            // 询问用户名字
            String playerName;
            Scanner reader = new Scanner(System.in);
            System.out.println("What's your name?");
            System.out.print("> ");
            playerName = reader.nextLine();

            System.out.println("Begin to init...");
            // 初始化变量
            parser = new Parser(commands);
            rooms = new HashMap<Integer, Room>();
            visitRoomHistory = new Stack<Room>();
            player = new Player();
            player.setPlayerName(playerName);

            // 处理用户信息用户
            for (String pName : db.getPlayerList()) {
                db.delPlayer(pName);
            }
            db.addPlayer(playerName);

            // 创建房间
            XMLParser roomsXML = new XMLParser();
            roomsXML.setFilename("rooms.xml");
            try {
                roomsXML.runXMLConvert();
            } catch (Exception e) {
                e.printStackTrace();
            }
            // 创建所有的房间
            Map<Integer, HashMap<String, String>> parentMap = roomsXML.getXMLData();
            for (Map.Entry<Integer, HashMap<String, String>> parentEntry : parentMap.entrySet()) {
                Map<String, String> map = parentEntry.getValue();

                for (Map.Entry<String, String> entry : map.entrySet()) {
                    // 检查哈希表，创建过就不重复了
                    if (!rooms.containsKey(parentEntry.getKey())) {
                        rooms.put(parentEntry.getKey(), new Room());
                    }

                    // 设置房间属性
                    rooms.get(parentEntry.getKey()).setRoomID(parentEntry.getKey());
                    switch (entry.getKey()) {
                        case "room_name":
                            //Set room name
                            rooms.get(parentEntry.getKey()).setRoomName(entry.getValue());
                            break;
                        case "description":
                            //Set description for room
                            rooms.get(parentEntry.getKey()).setDescription(entry.getValue());
                            break;
                        case "is_random_room":
                            //Set is random room
                            if (entry.getValue().equals("1")) {
                                rooms.get(parentEntry.getKey()).setIsRandomRoom(true);
                            }
                            break;
                        case "has_magic_cookie":
                            if (entry.getValue().equals("1")) {
                                rooms.get(parentEntry.getKey()).setHasMagicCookie(true);
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
            // 为房间创建出口
            Map<Integer, HashMap<String, String>> parentExitMap = roomsXML.getXMLData();
            for (Map.Entry<Integer, HashMap<String, String>> parentEntry : parentExitMap
                .entrySet()) {
                Map<String, String> map = parentEntry.getValue();
                for (Map.Entry<String, String> entry : map.entrySet()) {
                    if (entry.getKey().equals("north") || entry.getKey().equals("east") || entry
                        .getKey().equals("south") || entry.getKey().equals("west") || entry.getKey()
                        .equals("up") || entry.getKey().equals("down")) {
                        // 获取并设置出口及方向
                        String direction = entry.getKey();
                        Room exit = rooms.get(Integer.parseInt(entry.getValue()));
                        rooms.get(parentEntry.getKey()).setExit(direction, exit);
                    }
                }
            }

            // 创建物品
            XMLParser itemsXML = new XMLParser();
            itemsXML.setFilename("items.xml");
            try {
                itemsXML.runXMLConvert();
            } catch (Exception e) {
                e.printStackTrace();
            }
            parentMap = itemsXML.getXMLData();

            for (Map.Entry<Integer, HashMap<String, String>> parentEntry : parentMap.entrySet()) {
                Map<String, String> map = parentEntry.getValue();
                Item currentItem = new Item();
                for (Map.Entry<String, String> entry : map.entrySet()) {
                    // 设置ID属性
                    currentItem.setItemID(parentEntry.getKey());

                    // 设置其他属性
                    switch (entry.getKey()) {
                        case "item_room_id":
                            //Set room ID where item is located
                            currentItem.setItemRoomID(Integer.parseInt(entry.getValue()));
                            break;
                        case "item_name":
                            //Set item name
                            currentItem.setItemName(entry.getValue());
                            break;
                        case "item_weight":
                            //Set item weight
                            currentItem.setItemWeight(Integer.parseInt(entry.getValue()));
                            break;
                        default:
                            break;
                    }
                }

                // 添加物品
                if (rooms.containsKey(currentItem.getItemRoomID())) {
                    rooms.get(currentItem.getItemRoomID()).addItem(currentItem);
                } else {
                    System.out.println(
                        "Item: " + currentItem.getItemName() + " can NOT find room when roomID = "
                            + currentItem.getItemRoomID());
                }
            }

            // 设置当前房间
            player.setCurrentRoom(rooms.get(1));
            System.out.println("Init data successfully!");

            // 自动保存
            commands.get("save").runCommand(new Command("save", null));
        }
    }

    /**
     * 执行Load命令，从数据库加载游戏进度
     */
    class CommandLoad implements CommandBaseImpl {

        @Override
        public void runCommand(Command command) {
            System.out.println("Begin to load...");
            visitRoomHistory = new Stack<Room>();
            rooms = db.loadRooms();
            player = db.loadPlayer(rooms);
            db.loadItems(rooms, player);
            System.out.println("Load data successfully!");
        }
    }

    /**
     * 执行ListPlayer命令，显示玩家列表
     */
    class CommandListPlayer implements CommandBaseImpl {

        @Override
        public void runCommand(Command command) {
            ArrayList<String> players = db.getPlayerList();
            System.out.println("The players are as belows:");
            int num = 0;
            for (String player : players) {
                num++;
                System.out.println(num + ". " + player);
            }
        }
    }

    /**
     * 执行AddPlayer命令，增加一个玩家
     */
    class CommandAddPlayer implements CommandBaseImpl {

        @Override
        public void runCommand(Command command) {
            // 获取玩家名称
            String playerName;
            if (command.hasSecondWord()) {
                playerName = command.getSecondWord();
            } else {
                Scanner reader = new Scanner(System.in);
                System.out.println("What's your name?");
                System.out.print("> ");
                playerName = reader.nextLine();
            }

            // 向数据库中添加用户
            db.addPlayer(playerName);
            System.out.println("Add Player successfully!");
        }
    }

    /**
     * 执行DelPlayer命令，删除当前玩家
     */
    class CommandDelPlayer implements CommandBaseImpl {

        @Override
        public void runCommand(Command command) {
            commands.get("save").runCommand(new Command("save", null));

            // 只有不持有任何物品的玩家才能被删除
            if (player.getItems().size() == 0) {
                db.delPlayer(player.getPlayerName());
                System.out.println("Successfully del current player!");
                player = null;
            } else {
                System.out.println("You have items, can not del!");
            }
        }
    }

    /**
     * 执行Switch命令，切换玩家
     */
    class CommandSwitchPlayer implements CommandBaseImpl {

        @Override
        public void runCommand(Command command) {
            // 获取玩家名称
            String playerName;
            if (command.hasSecondWord()) {
                playerName = command.getSecondWord();
            } else {
                Scanner reader = new Scanner(System.in);
                System.out.println("What's the player's name you want to switch?");
                System.out.print("> ");
                playerName = reader.nextLine();
            }

            // 从数据库中得到新玩家
            Player newPlayer = db.switchPlayer(playerName, rooms);

            // 根据得到的结果进行切换
            if (newPlayer == null) {
                System.out.println("Can't find player!");
            } else {
                commands.get("save").runCommand(new Command("save", null));
                player = newPlayer;
                System.out.println("You have successfully switched to " + playerName + "!");
                printWelcome();
            }
        }
    }

    /**
     * 为测试类写的，返回当前玩家对象
     *
     * @return 玩家对象
     */
    public Player getPlayer() {
        return player;
    }

    /**
     * 为测试类写的，返回命令
     *
     * @return 命令列表
     */
    public HashMap<String, CommandBaseImpl> getCommands() {
        return commands;
    }

    public void releaseDB() {
        db.realiseDB();
    }
}