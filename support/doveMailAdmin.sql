CREATE DATABASE `mail`;

USE `mail`;

DROP TABLE IF EXISTS `domains`;
CREATE TABLE `domains` (
  `domain` varchar(50) NOT NULL,
  PRIMARY KEY (`domain`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

LOCK TABLES `domains` WRITE;
/*!40000 ALTER TABLE `domains` DISABLE KEYS */;
INSERT INTO `domains` VALUES ('testme.com');
/*!40000 ALTER TABLE `domains` ENABLE KEYS */;
UNLOCK TABLES;

DROP TABLE IF EXISTS `doveMailAdminCFG`;
CREATE TABLE `doveMailAdminCFG` (
  `id` smallint(255) NOT NULL DEFAULT '0',
  `authMode` varchar(127) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

LOCK TABLES `doveMailAdminCFG` WRITE;
INSERT INTO `doveMailAdminCFG` VALUES (0,'PLAIN');
UNLOCK TABLES;

DROP TABLE IF EXISTS `forwardings`;
CREATE TABLE `forwardings` (
  `source` varchar(80) NOT NULL,
  `destination` text NOT NULL,
  PRIMARY KEY (`source`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `email` varchar(512) NOT NULL DEFAULT '',
  `password` varchar(512) DEFAULT NULL,
  PRIMARY KEY (`email`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

LOCK TABLES `users` WRITE;
-- User: test@testme.com Pass: 123456
-- Use 'doveadm pw -s ssha256' to create your own password...
INSERT INTO `users` VALUES ('test@testme.com','{SSHA256}18cNpakSeF3q3NiNgd8CCgbgpkrhmOogdqGrdMRjiQfbQ2ZF');
UNLOCK TABLES;
