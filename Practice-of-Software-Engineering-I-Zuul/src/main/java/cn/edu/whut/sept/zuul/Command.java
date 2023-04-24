package cn.edu.whut.sept.zuul;

public class Command {

    private final String commandWord;
    private final String secondWord;

    /**
     * 初始化内部数据
     *
     * @param firstWord  命令的第一个单词
     * @param secondWord 命令的第二个单词
     */
    public Command(String firstWord, String secondWord) {
        commandWord = firstWord;
        this.secondWord = secondWord;
    }

    /**
     * 获取命令词，即命令
     *
     * @return 命令
     */
    public String getCommandWord() {
        return commandWord;
    }

    /**
     * 获取命令中的第二个单词，即参数
     *
     * @return 参数
     */
    public String getSecondWord() {
        return secondWord;
    }

    /**
     * 判断该命令是否未知
     *
     * @return 该命令是否未知
     */
    public boolean isUnknown() {
        return (commandWord == null);
    }

    /**
     * 该命令是否有参数
     *
     * @return 是否有参数
     */
    public boolean hasSecondWord() {
        return (secondWord != null);
    }
}
