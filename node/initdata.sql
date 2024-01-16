-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               5.7.41-log - MySQL Community Server (GPL)
-- Server OS:                    Win64
-- HeidiSQL Version:             12.5.0.6677
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


-- Dumping database structure for database
DROP DATABASE IF EXISTS `database`;
CREATE DATABASE IF NOT EXISTS `database` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `database`;

-- Dumping structure for table database.sensor
DROP TABLE IF EXISTS `sensor`;
CREATE TABLE IF NOT EXISTS `sensor` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `topic` varchar(50) NOT NULL DEFAULT '',
  `message` text NOT NULL,
  `createddate` datetime DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=latin1;

-- Dumping data for table database.sensor: ~9 rows (approximately)
INSERT IGNORE INTO `sensor` (`id`, `topic`, `message`, `createddate`) VALUES
	(1, 'test', '{"temperature":12}', '2023-09-13 10:11:52'),
	(2, 'test', '{\n  "temperature": 24\n}', '2023-09-13 10:12:12'),
	(3, 'test', '{\n  "temperature": 44\n}', '2023-09-13 13:12:12'),
	(4, 'test', '{\n  "temperature": 54\n}', '2023-09-13 13:22:12'),
	(5, 'test', '{\n  "temperature": 10\n}', '2023-09-13 14:12:12'),
	(6, 'test', '{\n  "temperature": 15\n}', '2023-09-13 14:14:12'),
	(7, 'test', '{"temperature":12}', '2023-09-13 14:20:27'),
	(8, 'test', '{"temperature":12}', '2023-09-13 14:48:00'),
	(9, 'test', '{"temperature":40}', '2023-09-13 14:56:12'),
	(10, 'test', '{"temperature":50}', '2023-09-13 14:59:14');

/*!40103 SET TIME_ZONE=IFNULL(@OLD_TIME_ZONE, 'system') */;
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IFNULL(@OLD_FOREIGN_KEY_CHECKS, 1) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=IFNULL(@OLD_SQL_NOTES, 1) */;
sensor