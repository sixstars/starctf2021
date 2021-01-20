create database `ctf` default character set utf8 collate utf8_general_ci;

use ctf;

DROP TABLE IF EXISTS `users`;

CREATE TABLE `users` (
  `id` int AUTO_INCREMENT,
  `username` varchar(255) DEFAULT NULL,
  `password` varchar(255) DEFAULT NULL,
  `avatar` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;