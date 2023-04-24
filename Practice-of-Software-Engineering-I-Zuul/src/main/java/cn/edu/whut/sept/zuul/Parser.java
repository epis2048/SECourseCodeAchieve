package cn.edu.whut.sept.zuul;

import java.util.HashMap;
import java.util.Scanner;

public class Parser {

    private final CommandWords commands;
    private final Scanner reader;

    /**
     * 初始化该解析器
     */
    public Parser(HashMap<String, CommandBaseImpl> co) {
        commands = new CommandWords(co);
        reader = new Scanner(System.in);
    }

    /**
     * 要求用户输入一个命令
     *
     * @return 用户输入的命令
     */
    public Command getCommand() {
        String inputLine;
        String word1 = null;
        String word2 = null;

        System.out.print("> ");

        inputLine = reader.nextLine();

        Scanner tokenizer = new Scanner(inputLine);
        if (tokenizer.hasNext()) {
            word1 = tokenizer.next();
            if (tokenizer.hasNext()) {
                word2 = tokenizer.next();
            }
        }

        if (commands.isCommand(word1)) {
            return new Command(word1, word2);
        } else {
            return new Command(null, word2);
        }
    }

    /**
     * 显式系统中的所有命令
     */
    public void showCommands() {
        commands.showAll();
    }
}
