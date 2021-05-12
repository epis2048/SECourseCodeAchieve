package com.qst.dms.service;
import java.io.EOFException;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;

import com.qst.dms.db.DBUtil;
import com.qst.dms.entity.AppendObjectOutputStream;
import com.qst.dms.entity.DataBase;
import com.qst.dms.entity.LogRec;
import com.qst.dms.entity.MatchedLogRec;
import com.qst.dms.entity.MatchedTransport;
import com.qst.dms.entity.Transport;
//日志业务类
public class LogRecService {
	// 日志数据采集
	public LogRec inputLog() {
		LogRec log = null;
		// 建立一个从键盘接收数据的扫描器
		Scanner scanner = new Scanner(System.in);
		try {
			// 提示用户输入ID标识
			System.out.println("请输入ID标识：");
			// 接收键盘输入的整数
			int id = scanner.nextInt();
			// 获取当前系统时间
			Date nowDate = new Date();
			// 提示用户输入地址
			System.out.println("请输入地址：");
			// 接收键盘输入的字符串信息
			String address = scanner.next();
			// 数据状态是“采集”
			int type = DataBase.GATHER;
			// 提示用户输入登录用户名
			System.out.println("请输入登陆用户名：");
			// 接收键盘输入的字符串信息
			String user= scanner.next();
			// 提示用户输入主机IP
			System.out.println("请输入主机IP：");
			// 接收键盘输入的字符串信息
			String ip = scanner.next();
			// 提示用户输入登录状态、登出状态
			System.out.println("请输入登录状态:1是登录，0是登出");
			int logType = scanner.nextInt();
			// 创建日志对象
			log = new LogRec(id, nowDate, address, type, user, ip, logType);
		} catch (Exception e) {
			System.out.println("采集的日志信息不合法");
		}
		// 返回日志对象
		return log;
	}

	// 日志信息输出
	public void showLog(LogRec... logRecs) {
		for (LogRec e : logRecs) {
			if (e != null) {
				System.out.println(e.toString());
			}
		}
	}

	// 匹配日志信息输出，可变参数
	public void showMatchLog(MatchedLogRec... matchLogs) {
		for (MatchedLogRec e : matchLogs) {
			if (e != null) {
				System.out.println(e.toString());
			}
		}
	}

	// 匹配日志信息输出,参数是集合
	public void showMatchLog(ArrayList<MatchedLogRec> matchLogs) {
		for (MatchedLogRec e : matchLogs) {
			if (e != null) {
				System.out.println(e.toString());
			}
		}
	}
	
	public void saveMatchLog(ArrayList<MatchedLogRec> matchLogs) {
		try (ObjectOutputStream obs = new ObjectOutputStream(
				new FileOutputStream("MatchedLogs.txt", true))) {
			// 循环保存对象数据
			for (MatchedLogRec e : matchLogs) {
				if (e != null) {
					// 把对象写入到文件中
					obs.writeObject(e);
					obs.flush();
				}
			}
			// 文件末尾保存一个null对象，代表文件结束
			obs.writeObject(null);
			obs.close();
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
	
	public void saveAndAppendMatchLog(ArrayList<MatchedLogRec> matchLogs) {
		AppendObjectOutputStream aoos = null;
		File file = new File("MatchedLogs.txt");
		try {
			AppendObjectOutputStream.file = file;
			aoos = new AppendObjectOutputStream(file);
			for(MatchedLogRec e : matchLogs) {
				if(e != null) {
					aoos.writeObject(e);
					aoos.flush();
				}
			}
		}
		catch (Exception ex) {
			
		}
		finally {
			if(aoos != null) {
				try {
					aoos.close();
				}
				catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
	}
	
	//存匹配登录信息到数据库
	public void saveMatchLogToDB(ArrayList<MatchedLogRec> matchLogs) {
		DBUtil db = new DBUtil();
		try {
			db.getConnection();
			for(MatchedLogRec matchedLog : matchLogs) {
				//获取匹配的登录
				LogRec login = matchedLog.getLogin();
				//获取匹配的登出
				LogRec logout = matchedLog.getLogout();
				//保存匹配记录中的登录
				String sql = "insert into gather_logrec (id, time, address, type, username, ip, logtype) values (?, ?, ?, ?, ?, ?, ?)";
				Object[] param = new Object[] {
						login.getId(),
						new Timestamp(login.getTime().getTime()),
						login.getAddress(),
						login.getType(),
						login.getUser(),
						login.getIp(),
						login.getLogType()
				};
				db.executeUpdate(sql, param);
				//保存匹配记录中的登出
				param = new Object[] {
						logout.getId(),
						new Timestamp(logout.getTime().getTime()),
						logout.getAddress(),
						logout.getType(),
						logout.getUser(),
						logout.getIp(),
						logout.getLogType()
				};
				db.executeUpdate(sql, param);
				//保存匹配日志的ID
				sql = "insert into matched_logrec (loginid, logoutid) values (?, ?)";
				param = new Object[] {
						login.getId(),
						logout.getId(),
				};
				db.executeUpdate(sql, param);
			}
			db.closeAll();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	//从数据库中读匹配登录信息
		public ArrayList<MatchedLogRec> readMatchedLogFromDB(){
			ArrayList<MatchedLogRec> matchedLogs = new ArrayList<MatchedLogRec>();
			DBUtil db = new DBUtil();
			try {
				db.getConnection();
				String sql = "select i.ID, i.TIME, i.ADDRESS, i.TYPE, i.username, i.ip, i.logtype,"
						+ "o.ID, o.TIME, o.ADDRESS, o.TYPE, o.username, o.ip, o.logtype"
						+ " from matched_logrec m, gather_logrec i, gather_logrec o "
						+ " where m.loginid=i.id and m.logoutid=o.id";
				ResultSet rs = db.executeQuery(sql, null);
				while(rs.next()) {
					//获取登录记录
					LogRec login = new LogRec( rs.getInt(1), rs.getDate(2),
							rs.getString(3), rs.getInt(4), rs.getString(5),
							rs.getString(6), rs.getInt(7) );
					//获取登出记录
					LogRec logout = new LogRec( rs.getInt(8), rs.getDate(9),
							rs.getString(10), rs.getInt(11), rs.getString(12),
							rs.getString(13), rs.getInt(14) );
					//添加匹配登录信息到匹配集合
					MatchedLogRec matchedLog = new MatchedLogRec(login, logout);
					matchedLogs.add(matchedLog);
				}
				db.closeAll();
			} catch (Exception e) {
				e.printStackTrace();
			}
			//返回
			return matchedLogs;
		}
	
	public ArrayList<MatchedLogRec> readMatchLog() {
		ArrayList<MatchedLogRec> matchLogs = new ArrayList<>();
		// 创建一个ObjectInputStream对象输入流，并连接文件输入流，读MatchedTransports.txt文件中
		try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(
				"MatchedLogs.txt"))) {
			MatchedLogRec matchLog;
			/*
			// 循环读文件中的对象
			while ((matchLog = (MatchedLogRec) ois.readObject()) != null) {
				// 将对象添加到泛型集合中
				matchLogs.add(matchLog);
			}
			*/
			while(true) {
				try {
					matchLog = (MatchedLogRec) ois.readObject();
					matchLogs.add(matchLog);
				}
				catch (EOFException ex) {
					break;
				}
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		return matchLogs;
	}
	//获取数据库中的所有匹配的日志信息，返回一个ResultSet
	public ResultSet readLogResult() {		
		DBUtil db = new DBUtil();
		ResultSet rs=null;
		try {
			// 获取数据库链接
			Connection conn=db.getConnection();
			// 查询匹配日志，设置ResultSet可以使用除了next()之外的方法操作结果集
			Statement st=conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE,ResultSet.CONCUR_UPDATABLE);
				
			String sql = "SELECT l.id, l.time, l.address, l.username, l.ip, k.svalue logtype FROM gather_logrec l INNER JOIN system_key k where k.skey = l.logtype and k.stype = 'log_logtype'";
			rs = st.executeQuery(sql);
		}catch (Exception e) {
			e.printStackTrace();
		}
		return rs;
	}
	
	public int getLogMaxID() {
		int maxID = 1;
		DBUtil db = new DBUtil();
		try {
			db.getConnection();
			String sql = "select ID from gather_logrec order by ID desc limit 1";
			ResultSet rs = db.executeQuery(sql, null);
			while(rs.next()) {
				//获取登录记录
				maxID = rs.getInt(1);
			}
			db.closeAll();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return maxID;
	}

}
