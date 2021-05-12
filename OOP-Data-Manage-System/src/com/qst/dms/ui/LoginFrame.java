package com.qst.dms.ui;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

import com.qst.dms.entity.User;
import com.qst.dms.service.UserService;

import javax.swing.JLabel;
import javax.swing.JOptionPane;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.CardLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Font;

public class LoginFrame extends JFrame{
	// 标签
	private JLabel lblName, lblPwd, lblWel;
	// 用户名，文本框
	private JTextField txtName;
	// 密码和确认密码，密码框
	private JPasswordField txtPwd;
	// 用户业务类
	private UserService userService;
	private JButton btnOk, btnToReg;
	// 主面板
	private JPanel p;	
	
	public LoginFrame() {
		super("用户登录");

		// 实例化用户业务类对象
		userService = new UserService();
		
		// 设置窗体的icon
		ImageIcon icon = new ImageIcon("images\\dms.png");
		this.setIconImage(icon.getImage());
		// 设置面板布局，网格布局
		p = new JPanel(new GridLayout(4, 1));
		// 实例化组件
		lblName = new JLabel("用  户  名：");
		lblPwd = new JLabel("密      码：");
		lblWel = new JLabel("欢迎使用本系统！");
		lblWel.setFont(new Font("宋体", Font.PLAIN, 20));
		txtName = new JTextField(16);
		txtPwd = new JPasswordField(16);
		btnOk = new JButton("登录");
		btnToReg = new JButton("注册");
		btnToReg.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				new RegistFrame();
				dispose();
			}
		});
		btnOk.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// 获取用户输入的数据
				String userName = txtName.getText().trim();
				String password = new String(txtPwd.getPassword());
				if(userName.equals("") || password.equals("")) {
					JOptionPane.showMessageDialog(null,"用户名和密码均不能为空！","错误提示",JOptionPane.ERROR_MESSAGE);
				} else {
					userService = new UserService();
					User user;
					user = userService.findUserByName(userName);
					if(user == null) {
						JOptionPane.showMessageDialog(null,"用户名或密码错误！","错误提示",JOptionPane.ERROR_MESSAGE);
					} else {
						if(user.getPassword().equals(password)) {
							JOptionPane.showMessageDialog(null,"登录成功！","成功提示",JOptionPane.PLAIN_MESSAGE);
							new MainFrame();
							dispose();
						} else {
							JOptionPane.showMessageDialog(null,"用户名或密码错误！","错误提示",JOptionPane.ERROR_MESSAGE);
						}
					}
				}
			}
		});

		// 将组件分组放入面板，然后将小面板放入主面板
		JPanel p0 = new JPanel(new FlowLayout(FlowLayout.CENTER));
		p0.add(lblWel);
		p.add(p0);
		JPanel p1 = new JPanel(new FlowLayout(FlowLayout.CENTER));
		p1.add(lblName);
		p1.add(txtName);
		p.add(p1);
		JPanel p2 = new JPanel(new FlowLayout(FlowLayout.CENTER));
		p2.add(lblPwd);
		p2.add(txtPwd);
		p.add(p2);
		JPanel p3 = new JPanel(new FlowLayout(FlowLayout.CENTER));
		p3.add(btnOk);
		p3.add(btnToReg);
		p.add(p3);
		// 主面板放入窗体中
		getContentPane().add(p);
		// 设置窗体大小和位置
		this.setSize(310, 200);
		this.setLocation(300, 300);
		// 设置窗体不可改变大小
		this.setResizable(false);

		// 设置窗体初始可见
		this.setVisible(true);
		
	}
	
	public static void main(String[] args) {
		new LoginFrame();
	}
	
}
