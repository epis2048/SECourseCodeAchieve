package cn.edu.whut.sept.zuul;

public interface CommandBaseImpl {

    /**
     * 运行命令
     * @param command 命令的对象
     */
    void runCommand(Command command);
}
