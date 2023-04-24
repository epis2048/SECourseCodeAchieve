-- Adminer 4.6.3 MySQL dump

SET NAMES utf8;
SET time_zone = '+00:00';
SET foreign_key_checks = 0;
SET sql_mode = 'NO_AUTO_VALUE_ON_ZERO';

DROP DATABASE IF EXISTS `zuul`;
CREATE DATABASE `zuul` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `zuul`;

DROP TABLE IF EXISTS `zuul_accessToken`;
CREATE TABLE `zuul_accessToken` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `uid` int(11) NOT NULL,
  `token` varchar(256) NOT NULL,
  `createTime` timestamp NOT NULL ON UPDATE CURRENT_TIMESTAMP,
  `isExpired` int(11) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=25 DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `zuul_admin`;
CREATE TABLE `zuul_admin` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(100) NOT NULL,
  `casid` varchar(100) NOT NULL,
  `lastlogin` datetime NOT NULL ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `zuul_item`;
CREATE TABLE `zuul_item` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `description` text,
  `weight` int(11) NOT NULL,
  `locateType` int(11) NOT NULL,
  `locateID` int(11) NOT NULL,
  `url` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `zuul_log`;
CREATE TABLE `zuul_log` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `uid` int(11) NOT NULL,
  `msg` text NOT NULL,
  `createTime` timestamp NOT NULL ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=248 DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `zuul_player`;
CREATE TABLE `zuul_player` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(100) NOT NULL,
  `nickname` varchar(100) NOT NULL,
  `password` varchar(100) NOT NULL,
  `email` varchar(100) NOT NULL,
  `currentRoom` int(11) NOT NULL DEFAULT '0',
  `totalWeight` int(11) NOT NULL DEFAULT '0',
  `weightUpline` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`),
  UNIQUE KEY `username` (`username`),
  UNIQUE KEY `email` (`email`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `zuul_room`;
CREATE TABLE `zuul_room` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `description` text,
  `northExit` int(11) NOT NULL DEFAULT '0',
  `southExit` int(11) NOT NULL DEFAULT '0',
  `eastExit` int(11) NOT NULL DEFAULT '0',
  `westExit` int(11) NOT NULL DEFAULT '0',
  `isRandomRoom` int(11) NOT NULL DEFAULT '0',
  `hasMagicCookie` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;


-- 2023-04-24 09:08:08
