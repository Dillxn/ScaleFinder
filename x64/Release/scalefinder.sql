-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               10.5.4-MariaDB - mariadb.org binary distribution
-- Server OS:                    Win64
-- HeidiSQL Version:             11.0.0.5919
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- Dumping database structure for scalefinder
CREATE DATABASE IF NOT EXISTS `scalefinder` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `scalefinder`;

-- Dumping structure for table scalefinder.chord
CREATE TABLE IF NOT EXISTS `chord` (
  `chordName` varchar(8) DEFAULT NULL,
  `first` varchar(8) DEFAULT NULL,
  `second` varchar(8) DEFAULT NULL,
  `third` varchar(8) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Dumping data for table scalefinder.chord: ~12 rows (approximately)
/*!40000 ALTER TABLE `chord` DISABLE KEYS */;
INSERT INTO `chord` (`chordName`, `first`, `second`, `third`) VALUES
	('C', 'C', 'E', 'G'),
	('C#', 'C#', 'E#', 'G#'),
	('D', 'D', 'F#', 'A'),
	('Eb', 'Eb', 'G', 'Bb'),
	('E', 'E', 'G#', 'B'),
	('F', 'F', 'A', 'C'),
	('F#', 'F#', 'A#', 'C#'),
	('G', 'G', 'B', 'D'),
	('Ab', 'Ab', 'C', 'Eb'),
	('A', 'A', 'C#', 'E'),
	('Bb', 'Bb', 'D', 'F'),
	('B', 'B', 'D#', 'F#');
/*!40000 ALTER TABLE `chord` ENABLE KEYS */;

-- Dumping structure for table scalefinder.scale
CREATE TABLE IF NOT EXISTS `scale` (
  `scaleName` varchar(8) DEFAULT NULL,
  `i` varchar(8) DEFAULT NULL,
  `ii` varchar(8) DEFAULT NULL,
  `iii` varchar(8) DEFAULT NULL,
  `iv` varchar(8) DEFAULT NULL,
  `v` varchar(8) DEFAULT NULL,
  `vi` varchar(8) DEFAULT NULL,
  `vii` varchar(8) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dumping data for table scalefinder.scale: ~12 rows (approximately)
/*!40000 ALTER TABLE `scale` DISABLE KEYS */;
INSERT INTO `scale` (`scaleName`, `i`, `ii`, `iii`, `iv`, `v`, `vi`, `vii`) VALUES
	('C', 'C', 'Dm', 'Em', 'F', 'G', 'Am', 'Bdim'),
	('C#', 'C#', 'D#m', 'E#m', 'F#', 'G#', 'A#m', 'B#dim'),
	('Eb', 'Eb', 'Fm', 'Gm', 'Ab', 'Bb', 'Cm', 'Ddim'),
	('E', 'E', 'F#m', 'G#m', 'A', 'B', 'C#m', 'D#dim'),
	('F', 'F', 'Gm', 'Am', 'Bb', 'C', 'Dm', 'Edim'),
	('F#', 'F#', 'G#m', 'A#m', 'B', 'C#', 'D#m', 'E#dim'),
	('G', 'G', 'Am', 'Bm', 'C', 'D', 'Em', 'F#dim'),
	('Ab', 'Ab', 'Bbm', 'Cm', 'Db', 'Eb', 'Fm', 'Gdim'),
	('Bb', 'Bb', 'Cm', 'Dm', 'Eb', 'F', 'Gm', 'Adim'),
	('A', 'A', 'Bm', 'C#m', 'D', 'E', 'F#m', 'G#dim'),
	('B', 'B', 'C#m', 'D#m', 'E', 'F#', 'G#m', 'A#dim'),
	('D', 'D', 'Em', 'F#m', 'G', 'A', 'Bm', 'C#dim');
/*!40000 ALTER TABLE `scale` ENABLE KEYS */;

-- Dumping structure for table scalefinder.sharp_flat
CREATE TABLE IF NOT EXISTS `sharp_flat` (
  `sharp` varchar(8) DEFAULT NULL,
  `flat` varchar(8) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dumping data for table scalefinder.sharp_flat: ~21 rows (approximately)
/*!40000 ALTER TABLE `sharp_flat` DISABLE KEYS */;
INSERT INTO `sharp_flat` (`sharp`, `flat`) VALUES
	('C#', 'Db'),
	('C#m', 'Dbm'),
	('C#mdim', 'Dbmdim'),
	('D#', 'Eb'),
	('D#m', 'Ebm'),
	('D#mdim', 'Ebmdim'),
	('E#', 'F'),
	('E#m', 'Fm'),
	('E#mdim', 'Fmdim'),
	('F#', 'Gb'),
	('F#m', 'Gbm'),
	('F#mdim', 'Gbmdim'),
	('G#', 'Ab'),
	('G#m', 'Abm'),
	('G#mdim', 'Abmdim'),
	('A#', 'Bb'),
	('A#m', 'Bbm'),
	('A#mdim', 'Bbmdim'),
	('B#', 'C'),
	('B#m', 'Cm'),
	('B#mdim', 'Cmdim');
/*!40000 ALTER TABLE `sharp_flat` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
