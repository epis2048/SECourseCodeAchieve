package cn.edu.whut.sept.zuul;

import java.util.HashMap;
import java.util.Map;

public class CommandWords {

    private final HashMap<String, CommandBaseImpl> commands;

    public CommandWords(HashMap<String, CommandBaseImpl> co) {
        commands = co;
    }

    /**
     * 判断输入是否是一个命令
     *
     * @param aString 输出的字符串
     * @return 该字符串是否是命令
     */
    public boolean isCommand(String aString) {
        return (commands.get(aString) != null);
    }

    /**
     * 显式系统中的所有可用命令
     */
    public void showAll() {
        for (Map.Entry<String, CommandBaseImpl> command : commands.entrySet()) {
            System.out.print(command.getKey() + " ");
        }
        System.out.println();
    }
}
