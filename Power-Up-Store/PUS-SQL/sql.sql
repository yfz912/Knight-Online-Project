-- phpMyAdmin SQL Dump
-- version 2.10.3
-- http://www.phpmyadmin.net
-- 
-- Anamakine: localhost
-- Üretim Zamanı: 09 Aralık 2015 saat 21:42:30
-- Sunucu sürümü: 5.0.51
-- PHP Sürümü: 5.2.6

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- 
-- Veritabanı: `powerupstore1`
-- 

-- --------------------------------------------------------

-- 
-- Tablo yapısı: `esn_list`
-- 

CREATE TABLE `esn_list` (
  `sIndex` int(11) NOT NULL auto_increment,
  `ESN` varchar(200) NOT NULL,
  `Owner` varchar(200) NOT NULL,
  `Used` int(11) NOT NULL default '0',
  `Cash` int(11) NOT NULL,
  PRIMARY KEY  (`sIndex`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=172 ;

-- 
-- Tablo döküm verisi `esn_list`
-- 

INSERT INTO `esn_list` VALUES (162, '9890346-t1i6-3t4i-vnvj-5k9w-g6kr-jg32', 'iso', 1, 10);
INSERT INTO `esn_list` VALUES (163, '8018142-u2m0-9t8k-etux-0l3d-k4rr-fx87', 'iso', 0, 10);
INSERT INTO `esn_list` VALUES (164, '3894619-x9g4-0f1w-miri-2t6n-t0wm-se48', 'iso', 0, 10);
INSERT INTO `esn_list` VALUES (165, '6425997-u9q0-3r1o-qotk-8x1n-n9om-kj54', 'iso', 0, 10);
INSERT INTO `esn_list` VALUES (166, '7990480-h6w8-6i5t-thko-5g5q-r0oh-mw59', 'iso', 0, 10);
INSERT INTO `esn_list` VALUES (167, '9748797-t1l7-0f9p-wsti-3j4u-x0vo-jj52', 'iso', 0, 10);
INSERT INTO `esn_list` VALUES (168, '8213193-v7n3-5n4m-ekhv-6o1d-l1fi-sl62', 'iso', 0, 10);
INSERT INTO `esn_list` VALUES (169, '1283693-x8g4-1q9q-fdxk-8p9e-p3ir-px21', 'iso', 0, 10);
INSERT INTO `esn_list` VALUES (170, '1140500-x0v1-4e7m-swmr-3k2h-m8os-of74', 'iso', 0, 10);
INSERT INTO `esn_list` VALUES (171, '6281341-j4h2-5r3k-gejp-7p9d-u4vk-fm51', 'iso', 0, 10);

-- --------------------------------------------------------

-- 
-- Tablo yapısı: `mall_list`
-- 

CREATE TABLE `mall_list` (
  `sIndex` int(11) NOT NULL auto_increment,
  `view_type` varchar(100) NOT NULL,
  `view_rank` int(11) NOT NULL,
  `goodsno` varchar(100) NOT NULL,
  `name` varchar(100) NOT NULL,
  `smallimage` varchar(100) NOT NULL,
  `bigimage` varchar(100) NOT NULL,
  `mainicon` varchar(100) NOT NULL,
  `subicon` varchar(100) NOT NULL,
  `price` int(11) NOT NULL,
  `event_price` int(11) NOT NULL,
  `dtype` int(11) NOT NULL,
  `buytype` int(11) NOT NULL,
  `invencnt` int(11) NOT NULL,
  `explain1` varchar(100) NOT NULL,
  `explain2` varchar(100) NOT NULL,
  `item_type` int(11) NOT NULL,
  `limit_type` int(11) NOT NULL,
  `limit_total` int(11) NOT NULL,
  `limit_remain` int(11) NOT NULL,
  `limit_sdate` datetime NOT NULL,
  `limit_edate` datetime NOT NULL,
  `limit_age` int(11) NOT NULL,
  `issue_check` int(11) NOT NULL,
  `issue_image` varchar(100) NOT NULL,
  `char_sex` int(11) NOT NULL,
  `item_property` varchar(100) NOT NULL,
  `addhour` int(11) NOT NULL,
  `sellCount` int(11) NOT NULL default '0',
  PRIMARY KEY  (`sIndex`),
  UNIQUE KEY `sIndex` (`sIndex`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=125 ;

-- 
-- Tablo döküm verisi `mall_list`
-- 

INSERT INTO `mall_list` VALUES (1, '', 1, '800200000', 'Menissiah Transform Scroll(Karus)', '800200000_32.gif', '800200000.gif', '', '', 199, 0, 4, 0, 1, 'Transforms your character to look like   NPC Mennissiah(Karus) ', '', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (2, '', 1, '800110000', 'Menissiah Transform Scroll(El Morad)', '800110000_32.gif', '800110000.gif', '', '', 199, 0, 4, 0, 1, 'Transforms your character to look like   NPC Mennissiah(El Morad) ', '', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (3, '', 1, '800220000', 'Hera Transform Scroll(Karus)', '800220000_32.gif', '800220000.gif', '', '', 199, 0, 4, 0, 1, 'Transforms your character to look like   NPC Hera(Karus) ', '', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (4, '', 1, '800130000', 'Hera Transform Scroll(El Morad)', '800130000_32.gif', '800130000.gif', '', '', 199, 0, 4, 0, 1, 'Transforms your character to look like   NPC Hera(El Morad) ', '', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (5, '', 1, '800190000', 'Patrick Transform Scroll(Karus)', '800190000_32.gif', '800190000.gif', '', '', 149, 0, 4, 0, 1, 'Transforms your character to look like   NPC Patrick(Karus) ', '', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (6, '', 1, '800100000', 'Patrick Transform Scroll(El Morad)', '800100000_32.gif', '800100000.gif', '', '', 149, 0, 4, 0, 1, 'Transforms your character to look like   NPC Patrick(El Morad) ', '', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (7, '', 1, '800210000', 'Cougar Transform Scroll (Karus)', '800210000_32.gif', '800210000.gif', '', '', 149, 0, 4, 0, 1, 'Transforms your character to look like   NPC Cougar(Karus) ', '', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (8, '', 1, '800120000', 'Cougar Transform Scroll(El Morad)', '800120000_32.gif', '800120000.gif', '', '', 149, 0, 4, 0, 1, 'Transforms your character to look like   NPC Cougar(El Morad) ', '', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (9, '', 1, '810340000(Disable)', 'Appearance Change', '810340000_32.gif', '810340000.gif', '', '', 1, 0, 4, 0, 1, 'Modifies features. It will last 30 days. [Makeup Specialist] Ulku. ', 'Changes face, hair, and hair color. ', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (10, '', 1, '508117000', 'Yeniceri Armor', '32_itemicon_5_0811_70_0.gif', '1itemicon_5_0811_70_0.gif', '', '', 429, 0, 4, 0, 2, 'It allows you to obtain a Yenieri Armor piece that changes your characters body appearance while add', 'Yenieri Armor -ONE ITEM SLOTS must be available when visiting NPC Kayra or you will lose the Minerva', 0, 0, 0, 0, '2011-11-07 00:00:00', '2011-11-07 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (11, '', 1, '800170000', 'Valkyrie Helmet Certificate', '214.gif', '', '', '', 349, 0, 4, 0, 1, 'It allows you to obtain a Valkyrie Helmet piece that changes your characters body appearance while a', 'Valkyrie Helmet ', 0, 0, 0, 0, '2011-11-07 00:00:00', '2011-11-07 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (12, '', 1, '800180000', 'Valkyrie Armor Certificate', '213.gif', '', '', '', 429, 0, 4, 0, 2, 'It allows you to obtain a Valkyrie Armor piece that changes your characters body appearance while ad', 'Valkyrie Armor ', 0, 0, 0, 0, '2011-11-07 00:00:00', '2011-11-07 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (13, 'BESTBUY', 1, '800230000', 'Gryphon Helmet Certificate', '800230000e.gif', '800230000e.gif', '', '', 349, 0, 4, 0, 1, 'Allows you to obtain a Gryphon Helmet piece that changes your characters body appearance while addin', 'Go to NPC [Peddler] Hemes- select cospre item- select existing Minerva clothing - select Gryphon Hel', 0, 0, 0, 0, '2012-10-24 00:00:00', '2012-10-31 18:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (14, 'BESTBUY', 1, '800240000', 'Gryphon Armor Certificate', '800240000e.gif', '800240000e.gif', '', '', 429, 0, 4, 0, 1, 'Allows you to obtain a Gryphon Armor piece that changes your characters body appearance while adding', 'Go to NPC [Peddler] Hemes- select cospre item- select existing Minerva clothing - select Gryphon Arm', 0, 0, 0, 0, '2011-11-07 00:00:00', '2011-11-07 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (15, '', 1, '508116000', 'Yeniceri Helmet', 'yeni_helmat_32.gif', 'yeni_helmat.gif', '', '', 349, 0, 4, 0, 1, 'It allows you to obtain a Yenieri Helmetpiece that changes your characters body appearance while add', 'Yenieri Helmet-ONE ITEM SLOTS must be available when visiting NPC Kayra or you will lose the Minerva', 0, 0, 0, 0, '2012-03-08 00:00:00', '2012-03-08 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (16, 'MYSTERY', 1, '900189000', 'Crisis(El Morad)', 'itemicon_8_0012_20_0.gif', 'itemicon_8_0012_20_0.gif', '', '', 289, 0, 4, 0, 1, 'Transforms your character to look like NPC Crisis(ElMorad) ', 'Register the item on a short cut key window and use it as same as using a skill. ', 0, 0, 0, 0, '2012-05-14 00:00:00', '2012-05-14 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (17, '', 1, '800270000', 'Bahamut Armor Certificate', '800270000e.gif', '800270000e.gif', '', '', 429, 0, 4, 0, 1, 'It allows you to obtain a Valkyrie Helmet piece that changes your characters body appearance while a', 'Visit the NPC [Peddler] Hemes in Moradon to obtain your Valkyrie Items.  After you receive your item', 0, 0, 0, 0, '2012-05-14 00:00:00', '2012-05-14 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (18, 'MYSTERY', 1, '800260000', 'Bahamut Helmet Certificate', '800260000e.gif', '800260000e.gif', '', '', 349, 0, 4, 0, 1, 'It allows you to obtain a Valkyrie Helmet piece that changes your characters body appearance while a', 'Visit the NPC [Peddler] Hemes in Moradon to obtain your Valkyrie Items.  After you receive your item', 0, 0, 0, 0, '2012-05-14 00:00:00', '2012-05-14 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (19, 'MYSTERY', 1, '900190000 ', 'Ibex(Karus)', 'itemicon_8_0012_30_0.gif', 'itemicon_8_0012_30_0.gif', '', '', 289, 0, 4, 0, 1, 'Transforms your character to look like NPC Ibex(Karus).', 'Register the item on a short cut key window and use it as same as using a skill. ', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (20, 'MYSTERY', 1, '508112000', 'Minerva Package', '1016_32.gif', '1016.gif', '', '', 729, 0, 4, 0, 1, 'It allows you to obtain a Minerva piece that changes your characters body appearance while adding on', 'Visit the NPC [Peddler] Kaira in Moradon to obtain your Minerva Items.  After you receive your item,', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (21, 'MYSTERY', 1, '518011000', 'Magpie (ElMorad)', 'itemicon_el.gif', 'itemicon_el.gif', '', '', 289, 0, 4, 0, 1, 'Transforms your character to look like the cute NPC Magpie. Transforms your character to look like N', 'Register the item on a short cut key on window and use it as a same as using a skill.  Condition: Th', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (22, 'MYSTERY', 1, '518012000', 'Magpie (Karus)', 'itemicon_ka .gif', 'itemicon_ka .gif', '', '', 289, 0, 4, 0, 1, 'Transforms your character to look like the cute NPC Magpie. Transforms your character to look like N', 'Register the item on a short cut key on window and use it as a same as using a skill.  Condition: Th', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Costumes', 0, 0);
INSERT INTO `mall_list` VALUES (31, '', 1, '800032000', 'Name Change Scroll', '800032000_32.gif', '800032000.gif', '', '', 1499, 0, 3, 0, 1, 'A scroll to change the character name.', 'Go to [Peddler] Hemes in Moradon. You can change your name there.', 0, 0, 0, 0, '2011-12-09 00:00:00', '2011-12-09 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (32, '', 1, '800077000', '400 Defense+ Scroll(L)', '800076000_32.gif', '800076000.gif', '', '', 299, 0, 3, 0, 1, 'It increases the characters max defense ', 'A scroll to increase max defense by 400', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 3, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (33, '', 1, '800013000', '1500 Health+ Scroll(L)', '800013000_32.gif', '800013000.gif', '', '', 149, 0, 3, 0, 1, 'Increases maximum Health ', 'Increases maximum Health by 1500 ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 3, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (34, '', 1, '800012000', '1000 Health+ Scroll(L)', '800013000_32.gif', '800013000.gif', '', '', 99, 0, 3, 0, 1, 'Increases maximum Health ', 'Increases maximum Health by 1000 ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 3, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (35, '', 1, '800011000', '500 Health+ Scroll(L)', '800013000_32.gif', '800013000.gif', '', '', 49, 0, 3, 0, 1, 'Increases maximum Health ', 'Increases maximum Health by 500 ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 3, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (36, '', 1, '800010000', '300 Defense+ Scroll(L)', '800010000_32.gif', '800010000.gif', '', '', 199, 0, 3, 0, 1, 'Increases Defense. ', 'Increases Defense by 300. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 3, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (37, 'BESTGIF', 1, '800009000', '150 Defense+ Scroll(L)', '800010000_32.gif', '800010000.gif', '', '', 79, 0, 3, 0, 1, 'Increases Defense. ', 'Increases Defense by 150. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 3, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (38, '', 1, '800015000', 'Speed+ Potion', '800015000_32.gif', '800015000.gif', '', '', 79, 0, 3, 0, 1, 'It increases characters speed.  It increases chracters speed. ', 'It increases chracters speed by 150%. It is same speed as swift. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (39, '', 1, '800014000', 'Attack Damage+ Scroll', '800014000_32.gif', '800014000.gif', '', '', 159, 0, 3, 0, 1, 'It increases attack damage. ', 'A scroll to increase max attack damage by 20%. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (40, '', 1, '800008000', 'Power of Lion Scroll(Stat)(L)', '800008000_32.gif', '800008000.gif', '', '', 229, 0, 3, 0, 1, 'It increases the characters STR, HP, DEX, INT, MP stats. ', 'A scroll to increase the characters STR, HP, DEX, INT, MP stats by 10. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (41, '', 1, '800028000', 'Power of Lion Scroll(Stat)(S)', '800008000_32.gif', '800028000.gif', '', '', 129, 0, 3, 0, 1, 'It increases the characters STR, HP, DEX, INT, MP stats. ', 'A scroll to increase the characters STR, HP, , DEX ,INT, MP stats by 10. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (42, '', 1, '800003000', 'STR+ Scroll(Stat)(L)', '800003000_32.gif', '800023000.gif', '', '', 169, 0, 3, 0, 1, 'Increases STR. ', 'Increases STR by 15. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (43, '', 1, '800023000', 'STR+ Scroll(Stat)(S)', '800032000_32.gif', '800032000.gif', '', '', 69, 0, 3, 0, 1, 'Increases STR. ', 'Increases STR by 15. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (44, '', 1, '800004000', 'HP+ Scroll(Stat)(L)', '800004000_32.gif', '800004000.gif', '', '', 159, 0, 3, 0, 1, 'Increases HP. ', 'Increases HP by 15 ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (45, '', 1, '800024000', 'HP+ Scroll(Stat)(S)', '800004000_32.gif', '800004000.gif', '', '', 69, 0, 3, 0, 1, 'Increases HP. ', 'Increases HP by 15 ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (46, '', 1, '800005000', 'DEX+ Scroll(Stat)(L)', '800005000_32.gif', '800005000.gif', '', '', 169, 0, 3, 0, 1, 'Increases DEX. ', 'Increases DEX by 15 ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (47, '', 1, '800025000', 'DEX+ Scroll(Stat)(S)', '800005000_32.gif', '800005000.gif', '', '', 69, 0, 3, 0, 1, 'Increases DEX. ', 'Increases DEX by 15 ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (48, '', 1, '800006000', 'INT+ Scroll(Stat)(L)', '800006000_32.gif', '800006000.gif', '', '', 69, 0, 3, 0, 1, 'Increases INT. ', 'Increases INT by 15.  More mana points. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (49, '', 1, '800026000', 'INT+ Scroll(Stat)(S)', '800006000_32.gif', '800006000.gif', '', '', 29, 0, 3, 0, 1, 'Increases INT. ', 'Increases INT by 15.  More mana points. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (50, '', 1, '800007000', 'MP+ Scroll(Stat)(L)', '800007000_32.gif', '800007000.gif', '', '', 69, 0, 3, 0, 1, 'It increases the characters MP ', 'It increases the characters MP by 15. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (51, 'BESTGIF', 1, '800027000', 'MP+ Scroll(Stat)(S)', '800007000_32.gif', '800007000.gif', '', '', 39, 0, 3, 0, 1, 'It increases the characters MP ', 'It increases the characters MP by 15. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (52, '', 1, '379258000', 'Tears of Karivdis', '32_itemicon_3_7925_80_0.gif', '1itemicon_3_7925_80_0.gif', '', '', 400, 0, 3, 1, 1, 'Item used in weapon and armor upgrading. This does not guarantee that the item will not be destroyed', 'Increase 30% rebirth upgrade success rate. -Not Purchasable with Gift Cash. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (53, 'BESTGIF', 1, '700001000', 'Redistribution Item', '700001000_32.gif', '700001000.gif', '', '', 799, 0, 3, 0, 1, 'Item to redistribute stats. ', 'Allows you to redistribute your stats. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (54, '', 1, '800036000', '60% Re-Spawn scroll', '800036000_32.gif', '800036000.gif', '', '', 69, 0, 3, 0, 1, '60% of EXP is recovered when re-spawning. ', 'A scroll that recovers 60% when re-spawning ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (55, 'BESTGIF', 1, '800021000', 'Teleportation Item', '800021000_32.gif', '800021000.gif', '', '', 99, 0, 3, 0, 1, 'You can teleport to your friend. ', 'You can teleport to your friend with one scroll. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (56, '', 1, '800022000', 'Duration Item', '800022000_32.gif', '800022000.gif', '', '', 149, 0, 3, 0, 1, 'It increases the duration on the skills cast on you by other players. ', 'It is an item that doubles the duration of beneficial skills cast on you by other players. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (57, '', 1, '700004000', 'Monster Summon Staff(Disabled)', '700004000_32.gif', '700004000.gif', '', '', 0, 0, 3, 0, 1, 'Summons Unique Monster to Kill. ', 'Summons Unique Monster to Kill. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (58, '', 1, '810075000', 'Symbol of Gladiator[10 ea]', '810060000_32.gif', '810060000.gif', '', '', 769, 0, 3, 0, 1, 'Increases experience gain by 70%  - The level requirement is between 1 to 50 Only.', 'A scroll that increase 70% EXP ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (59, 'BESTGIF', 1, '810073000', 'Symbol of Gladiator [5 ea]', '810060000_32.gif', '810060000.gif', '', '', 499, 0, 3, 0, 1, 'Increases experience gain by 70% - The level requirement is between 1 to 50 Only.', 'A scroll that increase 70% EXP ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (60, '', 1, '810060000', 'Symbol of Gladiator', '810060000_32.gif', '810060000.gif', '', '', 109, 0, 3, 0, 1, 'Increases experience gain by 70%  - The level requirement is between 1 to 50 Only.', 'A scroll that increase 70% EXP ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (61, '', 1, '810061000', 'Symbol of Warrior', '810061000_32.gif', '810061000.gif', '', '', 109, 0, 3, 0, 1, 'Increases experience gain by 40% For Levels 1  60 only', 'A scroll that increases experience gain by 40% ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (62, '', 1, '810074000', 'Symbol of Warrior[5 ea]', '810061000_32.gif', '810061000.gif', '', '', 499, 0, 3, 0, 1, 'Increases experience gain by 40%  - The level requirement is between 1 to 60 Only.', 'A scroll that increases experience gain by 40% ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (63, '', 1, '800440000', 'Voucher for Magic Bag', '800440000_32.gif', '800440000.gif', '', '', 0, 0, 3, 0, 1, 'This voucher can be turned in for a Magic Bag that can be used to carry more items on your character', '119kc', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (64, '', 1, '800111000', 'Character Seal Scroll', '800111000_32.gif', '800111000.gif', '', '', 0, 0, 3, 0, 1, 'Scroll for sealing a character. 2800kc', 'Used for sealing one character becomes a Cypher Ring upon use. ', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (65, '', 1, '810150000', 'Chaos Map Coupon ', '810150000_32.gif', '810150000.gif', '', '', 35, 0, 3, 0, 1, 'Map of Chaos. Sends the user to Chaos. [White Shadow Commander] Sirin. ', 'A coupon to exchange for a Map of Chaos item. ', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (66, '', 1, '810160000', 'Ancient Text', '810160000_32.gif', '810160000.gif', '', '', 25, 0, 3, 0, 1, 'Contains clues to deciphering the ancient tongue. A good wing can be received by interpreting the Vo', 'Increases the chances of receiving a high level Wing item with better attributes. ', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (67, '', 1, '800250000', 'Voucher for a Pathos Glove', '508060000_32.gif', '508060000.gif', '', '', 395, 0, 3, 0, 1, 'Allows you to obtain a Pathos Glove that changes your characters body appearance while adding one ch', 'Go to NPC [Peddler] Hemes- select cospre item- select Pathos Gloves ', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (68, '', 1, '800450000', 'Voucher for Automatic Pet Looting', '800450000_32.gif', '800450000.gif', 'icon_new_64.gif', 'icon_new_32.gif', 0, 0, 3, 0, 1, 'This voucher can be turned in for the ability to have your pet automatically loot fallen enemies for', 'Automatic Pet Looting 248kc', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (69, 'NEW', 1, '800078000', '2000 Health+ Scroll', 'itemicon_8_0007_90_0_s.gif', 'itemicon_8_0007_90_0.gif', '', '', 199, 0, 3, 0, 1, 'It increases the characters max Health ', 'A scroll to increase max Health by 2000 ', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (70, '', 1, '800076000', 'Scroll of Armor 350', '800010000.gif', '800010000_32.gif', '', '', 249, 0, 3, 0, 1, 'Increase Defense ', 'Increase Defense by 350 ', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (71, '', 1, '900045000', 'Nation Transfer', '800360000_32.gif', '800360000.gif', '', '', 999, 0, 3, 0, 1, 'When used, a player may switch nations and reconfigure the appearance of characters on the server, w', 'Bring the item to[Grand Merchant] Kaishan ', 0, 0, 0, 0, '2011-11-07 00:00:00', '2011-11-07 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (72, '', 1, '810076000', 'Symbol of Warrior[10 ea]', '810076000_32.gif', '810061000.gif', '', '', 769, 0, 3, 0, 1, 'Increases experience gain by 40%   - The level requirement is between 1 to 60 Only.', 'A scroll that increases experience gain by 40% ', 0, 0, 0, 0, '2011-11-07 00:00:00', '2011-11-07 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (73, 'RECOM', 1, '700035017', 'Cuff Binder Pet', '7_0_003_30_32.gif', '7_0_003_30.gif', '', '', 0, 0, 3, 0, 1, 'Transforms pets appearance into Cuff binder.299kc', 'Transforming pets appearance into cuff binder.', 0, 0, 0, 0, '2011-11-07 00:00:00', '2011-11-07 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (74, '', 1, '800090000', 'Familiar Name Change', '800032000_32.gif', '800032000.gif', '', '', 0, 0, 3, 0, 1, '1. A scroll to change the Familiar Name. 2.Item CANNOT be traded or sold. ', 'A scroll to change the Familiar Name. 349kc', 0, 0, 0, 0, '2011-11-07 00:00:00', '2011-11-07 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (75, 'RECOM', 1, '800074000', 'NP increase item', 'itemicon_8_0007_40_0.gif', 'itemicon_8_0007_40_0.gif', '', '', 999, 0, 3, 0, 1, 'Increase Nation Point gain by 50% ', 'Increase Nation Points gain by 50% ', 0, 0, 0, 0, '2011-11-07 00:00:00', '2011-11-07 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (76, '', 1, '800087000', 'Merchant Concentration', 'itemicon_8_0008_70_0.gif', 'itemicon_8_0008_70_0.gif', '', '', 159, 0, 3, 0, 1, 'Utilize a special merchant table to sell items.  More item slots so you can have more stock. ', 'Utilize a special merchant table to sell items ', 0, 0, 0, 0, '2011-11-07 00:00:00', '2011-11-07 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (77, '', 1, '820100000', 'Symbol of Growth', '810082000_32.gif', '810061000.gif', '', '', 0, 0, 3, 0, 1, 'Increases experience gain by 400%. Not Purchasable with Gift Cash. ', 'A scroll that increases experience gain by 400% 249kc. -Not Purchasable with Gift Cash.  Can be used', 0, 0, 0, 0, '2011-11-07 00:00:00', '2011-11-07 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (78, '', 1, '508070000', 'Pathos Package', '1015_32.gif', '1015.gif', '', '', 749, 0, 3, 0, 1, 'Allows you to obtain a Pathos Glove that changes your characters body appearance while adding one ch', 'Pathos Glove Package -TWO ITEM SLOTS must be available when visiting NPC Kayra or you will lose the ', 0, 0, 0, 0, '2011-11-07 00:00:00', '2011-11-07 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (79, 'RECOM', 1, '700033015', 'Giga Hammer Pet', '32_itemicon_7_0003_30_0.gif', '1itemicon_7_0003_30_0.gif', '', '', 349, 0, 3, 0, 1, 'Transforms pets appearance  in to Giga Hammer.', 'Go to [Familiar Tamer]Kate in Moradon to change appearance. ', 0, 0, 0, 0, '2012-03-08 00:00:00', '2012-03-08 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (80, 'BESTBUY CHARACTER', 1, '800079000', 'HP Scroll 60%', 'itemicon_hp60.gif', 'itemicon_hp60.gif', '', '', 349, 0, 3, 0, 1, 'Scroll which will increase health by 60%. ', 'After purchasing, just drag the potion in your inventory to your shortcut key bar to use.', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (81, 'CHARACTER', 1, '810051000', 'Hyper Noah Scroll', 'itemicon_8_1005_10_0.gif', 'itemicon_8_1005_10_0.gif', '', '', 149, 0, 3, 0, 1, 'Increases Noah (in-game coin) drop amount by 100%.', 'Register the item on a short cut key window and use it the same as using a skill. Can be used by lev', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (82, '', 1, '900435000', 'Lesson of Master', 'itemicon_lesmaster.gif', 'itemicon_lesmaster.gif', '', '', 0, 0, 3, 0, 1, 'Increases the characters STR, HP, DEX, INT, MP stats. ', 'Equip to skill bar and consume. 859kc', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (83, 'CHARACTER RECOM', 1, '700034016', 'Krowaz Pet', '32_itemicon_7_0003_40_0.gif', '1itemicon_7_0003_40_0.gif', '', '', 0, 0, 3, 0, 1, 'Transforms pets appearance in to Krowaz. 499kc', 'Go to [Familiar Tamer]Kate in Moradon to change appearance. ', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (84, 'CHARACTER', 1, '889310000', 'Voucher for 100 Health Potions', 'itemicon_8_8931_00_0.gif', 'itemicon_8_8931_00_0.gif', '', '', 49, 0, 3, 0, 1, 'This voucher can be turned in for Health Potions. This voucher can be turned in for Health Potions t', 'This item needs to be turned in to [Peddler] Hemes to receive the Health Potions.  The item then nee', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (85, 'CHARACTER', 1, '889340000', 'Voucher for 100 Magic Potions', 'itemicon_8_8934_00_0.gif', 'itemicon_8_8934_00_0.gif', '', '', 49, 0, 3, 0, 1, 'This voucher can be turned in for Magic Potions. This voucher can be turned in for Magic Potions tha', 'This item needs to be turned in to [Peddler] Hemes to receive the Magic Potions.  The item then need', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (86, 'CHARACTER', 1, '889320000', 'Voucher for 300 Health Potions', 'itemicon_8_8932_00_0.gif', 'itemicon_8_8932_00_0.gif', '', '', 89, 0, 3, 0, 1, 'This voucher can be turned in for Health Potions.This voucher can be turned in for Health Potions th', 'This item needs to be turned in to [Peddler] Hemes to receive the Health Potions. All levels apply. ', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (87, '', 1, '889350000', 'Voucher for 300 Magic Potions', 'itemicon_8_8935_00_0.gif', 'itemicon_8_8935_00_0.gif', '', '', 89, 0, 3, 0, 1, 'This voucher can be turned in for Magic Potions.  Memorial Day Weekend Sale. This voucher can be tur', 'This item needs to be turned in to [Peddler] Hemes to receive the Magic Potions.  The item then need', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (88, '', 1, '900129000', 'Red Potion(Disabled)', 'itemicon_redpot.gif', 'itemicon_redpot.gif', '', '', 9, 0, 3, 0, 1, 'Increases attack by 10% Attack Increase by 10%. Can be stacked with Cospre Gear and Dragon Wings. ', 'Apply to skillbar and consume. Cannot be traded, sold or stored at Inn Hostess. ', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (89, '', 1, '900128000', 'Blue Potion(Disabled)', 'itemicon_bluepot.gif', 'itemicon_bluepot.gif', '', '', 9, 0, 3, 0, 1, 'Potion that will increase defense by 60 points. Increases defense by 60 points. Can be stacked with ', 'Apply to skillbar and consume. Item cannot be traded, sold or stored at Inn Hostess. ', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (90, 'BESTBUY', 1, '810115000', 'HP Maestro Voucher', '810115000_32.gif', '810115000_64.gif', 'icon_new_64.gif', 'icon_new_32.gif', 200, 0, 3, 0, 1, 'With [Familir Trainer] Kate, exchange it for an item that will allow recovery of HP 720 for the cost', 'Visit [Trainer] Kate, exchange it for an item that will allow recovery of HP 720 for the cost of 4,9', 0, 0, 0, 0, '2013-02-28 00:00:00', '2013-02-28 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (91, 'BESTBUY', 1, '810116000', 'MP Maestro Voucher', '810116000_32.gif', '810116000_64.gif', '', '', 200, 0, 3, 0, 1, 'With [Familir Trainer] Kate, exchange it for an item that will allow recovery of MP 1920for the cost', 'Visit [Trainer] Kate, exchange it for an item that will allow recovery of MP 1920for the cost of 10,', 0, 0, 0, 0, '2013-02-28 00:00:00', '2013-02-28 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (92, '', 1, '900385000', 'Dryad Voucher (30 days)', '900385000_32.gif', '900385000_64.gif', 'icon_new_64.gif', 'icon_new_32.gif', 369, 0, 3, 0, 1, 'Exchange it with [Merchant] Kayra for [Dryad spirit] which will increase Noah Drop 100%. <br><br> *C', 'Through Kayra, exchange it with [Dryad Spirit] for [Noah Drop 100% Increase] ', 0, 0, 0, 0, '2013-04-02 00:00:00', '2013-04-02 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (93, '', 1, '900386000', 'Oreads Voucher (30 days)', '900386000_32.gif', '900386000_64.gif', 'icon_new_64.gif', 'icon_new_32.gif', 369, 0, 3, 0, 1, 'Exchange it with [Merchant] Kayra for Automatic looting. <br><br> *Cannot be traded and can only be ', 'Through Kayra, exchange it with [Oreads Voucher] for [Auto Looting]. ', 0, 0, 0, 0, '2013-04-02 00:00:00', '2013-04-02 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (94, 'NEW RECOM', 1, '800442000', 'VIP Vault Key [30days]', '800442000_32.gif', '800442000_64.gif', 'icon_new_64.gif', 'icon_new_32.gif', 0, 0, 3, 1, 1, 'With Inn Hostess register [VIP Storage Key] for additional 48 slots of storage. You can have your ow', 'With Inn Hostess register [VIP Storage Key] for additional 48 slots of storage. You can have your ow', 0, 0, 0, 0, '2013-05-07 00:00:00', '2013-05-07 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (95, 'NEW', 1, '800444000', 'Arrange Line', '800444000_32.gif', '800444000_64.gif', 'icon_new_64.gif', 'icon_new_32.gif', 0, 0, 3, 1, 1, 'At [Trainer] Kate, permanently change character''s location on character selection window. <br><br> *', 'Visit [Trainer] Kate, item will permanently change character''s location on character selection windo', 0, 0, 0, 0, '2013-05-07 00:00:00', '2013-05-07 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (96, '', 1, '810520000', 'Seal Exchange Voucher', '810520000_32.gif', '810520000_64.gif', 'icon_new_64.gif', 'icon_new_32.gif', 79, 0, 3, 1, 1, 'It''s an exchange to receive 10 seal items. Seal item will seal character''s attributed item.  ', 'Receive the exchange voucher from Kayra, use [Item Sealing] option from Inn Hostess. ', 0, 0, 0, 0, '2013-06-18 00:00:00', '2013-06-18 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (97, 'NEW', 1, '810700000', 'Medium Level Seal Exchange ', '810700000_32.gif', '810700000_64.gif', 'icon_new_64.gif', 'icon_new_32.gif', 0, 0, 3, 1, 1, 'It''s an exchange to receive 50 seal items. Seal item will seal character''s attributed item.  ', 'Receive the exchange voucher from Kayra, use [Item Sealing] option from Inn Hostess. 379kc ', 0, 0, 0, 0, '2013-06-18 00:00:00', '2013-06-18 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (98, 'NEW', 1, '900705000', 'Punishment Stick + Wing', 'dwing_pstick_32.gif', 'dwing_pstick_64.gif', 'icon_new_64.gif', 'icon_new_32.gif', 0, 0, 3, 1, 1, 'Wield the mighty Punishment Stick plus a little more! Wings are always a nice touch of the latest Kn', 'Once in the Discipline Dungeon, you will need to purchase the Punishment Stick. Purchase this bundle', 0, 0, 0, 0, '2013-06-18 00:00:00', '2013-06-18 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (99, '', 1, '810377000', 'Dragon Box', '810341000_32.gif', '810341000.gif', 'icon_new_64.gif', 'icon_new_32.gif', 0, 0, 3, 0, 1, 'Exchange the item with [Merchant] Kaira in Moradon. ', 'Exchange the item with [Merchant] Kaira in Moradon. 280kc ', 0, 0, 0, 0, '2014-04-18 00:00:00', '2014-04-18 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (100, '', 1, '810378000', 'Spirit of Genie (10ea)', '32_itemicon_9_0056_00_0.gif', '64_itemicon_9_0056_00_0.gif', 'icon_sale_64.gif', 'icon_sale_32.gif', 149, 0, 3, 0, 1, 'After 1st Job Change (at Lv 10) you will be able to hunt automatically.', 'When 1 Spirit of Genie is used, 120 points will be available for use. 1 pt = 1 min. ', 0, 0, 0, 0, '2014-12-23 00:00:00', '2014-12-23 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (101, 'NEW', 1, '399282686', 'EXP Premium ', '399282686_32.gif', '399282686.gif', 'icon_best_64.gif', 'icon_best_32.gif', 1955, 0, 2, 1, 1, ' 1. Preferred game access 24/7<br>  2. 300% EXP boost for levels 1-80<br>      120% EXP gaining for ', 'The EXP Premium is the premium service of choice for players who wish to level up their characters a', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Specials', 0, 0);
INSERT INTO `mall_list` VALUES (102, '', 1, '399281685', 'DISC Premium', '399281685_32.gif', '399281685.gif', 'icon_best_64.gif', 'icon_best_32.gif', 2955, 0, 2, 1, 1, '  1. Preferred game access 24/7<br>  2. 30% EXP Boost for levels 1-83<br>  3. Item drop rate increas', 'DISC Premium is the most discounted choice of all premium services. This Premium grants you to acces', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Specials', 0, 0);
INSERT INTO `mall_list` VALUES (103, 'ISSUE NEW', 1, '399292764', 'WAR Premium', '399292764_32.gif', '399292764.gif', 'icon_new_64.gif', 'icon_new_32.gif', 0, 0, 2, 1, 1, '1. 100% EXP boost for levels 1-83.<br> 2. Item drop rate increased.<br> 3. Experience loss on death ', 'The War Premium is the premium of choice for the PvP Fanatic. The premium gives you the largest NP b', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, 'banner_437_127_2.gif', 0, 'Specials', 0, 0);
INSERT INTO `mall_list` VALUES (105, '', 1, '700002000', 'Trinas Piece', '700002000_32.gif', '700002000.gif', '', '', 559, 0, 2, 1, 1, 'Item used in weapon and armor upgrading. This does not guarantee that the item will not be destroyed', 'Increases chance of successfully upgrading a weapon. -Not Purchasable with Gift Cash. ', 0, 0, 0, 0, '2011-11-03 00:00:00', '2011-11-03 00:00:00', 0, 0, '', 0, 'Specials', 0, 0);
INSERT INTO `mall_list` VALUES (106, 'RECOM', 1, '700009000', 'Shadow Piece(Disabled)', '700009000_32.gif', '700009000.gif', '', '', 0, 0, 2, 1, 1, 'Item used in weapon and armor crafting. This does not guarantee that the item will not be destroyed.', '30% increase to crafting success rate. ', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Specials', 0, 0);
INSERT INTO `mall_list` VALUES (109, 'ABILITY', 1, '810164000', 'Dragons Wing', '810164000_32_32.gif', '810164000.gif', 'icon_best_64.gif', 'icon_best_32.gif', 859, 0, 2, 1, 1, 'Allows you to obtain a Dragons Wing item which changes your characters appearance while adding one c', 'Visit [Vendor] Kayra in Moradon to obtain your Dragons Wing item. Applies to all levels. Cannot be t', 0, 0, 0, 0, '2012-05-14 00:00:00', '2012-05-14 00:00:00', 0, 0, '', 0, 'Specials', 0, 0);
INSERT INTO `mall_list` VALUES (110, 'ABILITY BESTBUY', 1, '389390000', 'Premium Potion HP', 'itemicon_3_8937_00_0_s.gif', 'itemicon_3_8937_00_0.gif', '', '', 192, 0, 2, 1, 1, 'Premium Potion Voucher HP 5000.', 'After purchasing, just drag the potion in your inventory to your shortcut key bar to use.', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Specials', 0, 0);
INSERT INTO `mall_list` VALUES (111, 'ABILITY BESTBUY', 1, '389400000', 'Premium Potion MP', 'itemicon_3_8938_00_0_s.gif', 'itemicon_3_8938_00_0.gif', '', '', 192, 0, 2, 1, 1, 'Premium Potion Voucher MP 5000.', 'After purchasing, just drag the potion in your inventory to your shortcut key bar to use.', 0, 0, 0, 0, '2012-05-15 00:00:00', '2012-05-15 00:00:00', 0, 0, '', 0, 'Specials', 0, 0);
INSERT INTO `mall_list` VALUES (112, '', 1, '810227000', 'Genie Hammer', '32_itemicon_3_7909_90_0.gif', '64_itemicon_3_7909_90_0.gif', 'icon_new_64.gif', 'icon_new_32.gif', 99, 0, 2, 0, 1, 'All of the equipments that need reparing will be repaired. (available with Knight Genie) ', '', 0, 0, 0, 0, '2012-09-27 00:00:00', '2012-09-27 00:00:00', 0, 0, '', 0, 'Specials', 0, 0);
INSERT INTO `mall_list` VALUES (113, 'ABILITY', 1, '800086000', 'Clan Name Change Scroll(Disabled)', '800086000_32.gif', '800086000_64.gif', 'icon_new_64.gif', 'icon_new_32.gif', 0, 0, 2, 1, 1, 'Allows Clan''s name to be changed.  2499kc', 'Visit [Peddler] Hemes to use the item and change the Clan ID. ', 0, 0, 0, 0, '2013-05-07 00:00:00', '2013-05-07 00:00:00', 0, 0, '', 0, 'Specials', 0, 0);
INSERT INTO `mall_list` VALUES (114, '', 1, '810537000', 'Special Monster Staff', '810234000_32.gif', '810234000.gif', 'icon_new_64.gif', 'icon_new_32.gif', 0, 0, 2, 1, 1, '[During the Event Period, monsters summoned by this special staff will drop Dragon Marbles as well a', 'To use, place the [Special Monster Staff] in the quick bar. When you click on the shortcut key, the ', 0, 0, 0, 0, '2014-03-27 00:00:00', '2014-03-27 00:00:00', 0, 0, '', 0, 'Specials', 0, 0);
INSERT INTO `mall_list` VALUES (115, 'NEW', 1, '810594000', 'Gender Change', '810594000_32.gif', '810594000_64.gif', 'icon_new_64.gif', 'icon_new_32.gif', 349, 0, 2, 0, 1, 'Current characters gender and appearance will be changed.  Cannot be used by Portu, Kurian, Ark Tuar', 'Exchange item with [makeup artist] Ulku.  ', 0, 0, 0, 0, '2015-07-02 00:00:00', '2015-07-02 00:00:00', 0, 0, '', 0, 'Specials', 0, 0);
INSERT INTO `mall_list` VALUES (116, '', 1, '900028683', 'Beyaz Kanat (30 days)', 'beyazkanat.png', 'beyazkanat.png', 'icon_new_64.gif', 'icon_new_32.gif', 1049, 0, 3, 0, 1, 'increase Atack Power by 3%. ', 'Through Kayra, ', 0, 0, 0, 0, '2013-04-02 00:00:00', '2013-04-02 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (117, '', 1, '900030684', 'Mor Kanat (30 days)', 'morkanat.png', 'morkanat.png', 'icon_new_64.gif', 'icon_new_32.gif', 1049, 0, 3, 0, 1, 'increase Atack Power by 3%. ', 'Through Kayra, ', 0, 0, 0, 0, '2013-04-02 00:00:00', '2013-04-02 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (118, '', 1, '900767867', 'Alencia Wings(30 days)', 'beyazkanat.png', 'beyazkanat.png', 'icon_new_64.gif', 'icon_new_32.gif', 0, 0, 3, 0, 1, 'increase Resistant point +10. ', 'Through Kayra, ', 0, 0, 0, 0, '2013-04-02 00:00:00', '2013-04-02 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);
INSERT INTO `mall_list` VALUES (119, '', 1, '389221000', 'Emblem Of Honor', '389221000_32.gif', '389221000.gif', 'icon_best_64.gif', 'icon_best_32.gif', 999, 0, 2, 1, 1, ' ', '', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Specials', 0, 0);
INSERT INTO `mall_list` VALUES (120, 'ABILITY', 1, '389222000', 'Royal Emblem', '389222000.gif', '389222000.gif', 'icon_best_64.gif', 'icon_best_32.gif', 1999, 0, 2, 1, 1, ' ', '', 0, 0, 0, 0, '2012-05-14 00:00:00', '2012-05-14 00:00:00', 0, 0, '', 0, 'Specials', 0, 0);
INSERT INTO `mall_list` VALUES (121, '', 1, '910045000', 'Brain of Centaur', '389221000_32.gif', '389221000.gif', 'icon_best_64.gif', 'icon_best_32.gif', 1, 0, 2, 1, 1, ' ', '', 0, 0, 0, 0, '2011-11-05 00:00:00', '2011-11-05 00:00:00', 0, 0, '', 0, 'Specials', 0, 0);
INSERT INTO `mall_list` VALUES (124, '', 1, '810638730', 'Wing of Hellfire Dragon(30 days)', 'beyazkanat.png', 'beyazkanat.png', 'icon_new_64.gif', 'icon_new_32.gif', 0, 0, 3, 0, 1, '300HP+', 'Through Kayra, ', 0, 0, 0, 0, '2013-04-02 00:00:00', '2013-04-02 00:00:00', 0, 0, '', 0, 'Power-Up', 0, 0);

-- --------------------------------------------------------

-- 
-- Tablo yapısı: `mall_main_category`
-- 

CREATE TABLE `mall_main_category` (
  `sIndex` int(11) NOT NULL,
  `main_type` int(11) NOT NULL,
  `name` varchar(100) NOT NULL,
  `menu_type` varchar(100) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- 
-- Tablo döküm verisi `mall_main_category`
-- 

INSERT INTO `mall_main_category` VALUES (3, 4, 'Costumes', 'normal');
INSERT INTO `mall_main_category` VALUES (2, 3, 'Power-Up', 'normal');
INSERT INTO `mall_main_category` VALUES (1, 2, 'Specials', 'normal');
INSERT INTO `mall_main_category` VALUES (4, 5, 'Bundles', 'package');
INSERT INTO `mall_main_category` VALUES (5, 7, 'On Sale', 'event');

-- --------------------------------------------------------

-- 
-- Tablo yapısı: `purchase_history`
-- 

CREATE TABLE `purchase_history` (
  `sIndex` int(11) unsigned NOT NULL auto_increment,
  `strAccountID` varchar(30) NOT NULL,
  `mc_gross` varchar(10) NOT NULL,
  `payer_id` varchar(100) NOT NULL,
  `address_street` text NOT NULL,
  `payment_date` varchar(100) NOT NULL,
  `payment_status` varchar(100) NOT NULL,
  `address_zip` varchar(100) NOT NULL,
  `first_name` varchar(100) NOT NULL,
  `last_name` varchar(100) NOT NULL,
  `business` varchar(100) NOT NULL,
  `txn_id` varchar(100) NOT NULL,
  `payer_email` varchar(100) NOT NULL,
  `mc_currency` varchar(10) NOT NULL,
  `cash` varchar(100) NOT NULL,
  UNIQUE KEY `sIndex` (`sIndex`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=85 ;

-- 
-- Tablo döküm verisi `purchase_history`
-- 

INSERT INTO `purchase_history` VALUES (25, 'iyiservis2', '50.00', 'RHAMSXGJ9YHP6', 'Giresun Espiye Arydurak köyü', '13:22:40 Nov 04, 2013 PST', 'Completed', '28300', 'Ysmail', 'Abanoz', 'ko100gaming@hotmail.com', '7RE26818MB765183K', 'fragmachinee@msn.com', 'USD', '5000');
INSERT INTO `purchase_history` VALUES (24, 'maxell', '15.00', 'EZT4JGFCJT2T4', '1.Organize Sanayi Bölgesi . Osmanli Cd. No 3 Sincan', '12:28:16 Nov 04, 2013 PST', 'Completed', '06930', 'Ömer', 'Yerli', 'ko100gaming@hotmail.com', '67C83202CA3371823', 'anksncnomr@hotmail.com', 'USD', '1500');
INSERT INTO `purchase_history` VALUES (23, 'kasapoglu55', '30.00', 'TR2ZU2RKNG76U', 'selahyye mah', '12:12:49 Nov 04, 2013 PST', 'Completed', '55100', 'sanyye', 'yylmaz', 'ko100gaming@hotmail.com', '2UY3661876746412P', 'mustyxxx49@gmail.com', 'USD', '3000');
INSERT INTO `purchase_history` VALUES (22, 'kasapoglu55', '15.00', 'TR2ZU2RKNG76U', 'SELAHIYE', '12:08:30 Nov 04, 2013 PST', 'Completed', '55100', 'SANIYE', 'YILMAZ', 'ko100gaming@hotmail.com', '8YP104858K691530G', 'mustyxx49@gmail.com', 'USD', '1500');
INSERT INTO `purchase_history` VALUES (21, 'kasapoglu55', '5.00', 'TR2ZU2RKNG76U', 'SELAHIYE MAH', '12:01:54 Nov 04, 2013 PST', 'Completed', '55100', 'SANIYE', 'YILMAZ', 'ko100gaming@hotmail.com', '70G50914JB505322F', 'mustyxxx49@gmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (20, 'heaven859', '5.00', 'H2GURLZQE74N6', '361.sok.karapürçek ankara', '11:38:02 Nov 04, 2013 PST', 'Completed', '', 'Hamdi', 'Demirparmak', 'ko100gaming@hotmail.com', '452049857E7649507', 'mrcnr06@gmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (19, '0sk1', '5.00', '268X6AQ2DBXNQ', 'CAC', '07:00:01 Nov 04, 2013 PST', 'Completed', '', 'CAN', 'CACAC', 'ko100gaming@hotmail.com', '7MK00606XC993005A', 'sikotur25@hotmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (18, '0sk1', '1.00', 'VW5ADJBXJ3RWU', '-', '12:52:44 Oct 08, 2013 PDT', 'Completed', '', 'ali', 'Çaly?an', 'ko100gaming@hotmail.com', '3T277713XN455893D', 'sikotur25@hotmail.com', 'USD', '9999');
INSERT INTO `purchase_history` VALUES (17, '0sk1', '42.00', 'DRJVKG82EVFMC', '1 Main St', '07:26:55 Oct 01, 2013 PDT', 'Completed', '95131', 'Alican', 'Çal\Z\Zan', 'ko100gaming-facilitator@hotmail.com', '8LP41594P54302818', 'zzztt@tt.com', 'USD', '3000');
INSERT INTO `purchase_history` VALUES (16, '', '7', 'TESTBUYERID01', '123, any street', '07:14:19 1 Oct 2013 PDT', 'Completed', '95131', 'John', 'Smith', 'seller@paypalsandbox.com', '5SP14459CD289915J', 'buyer@paypalsandbox.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (26, 'iyiservis2', '50.00', 'RHAMSXGJ9YHP6', 'Giresun Espiye Arydurak köyü', '13:26:55 Nov 04, 2013 PST', 'Completed', '28300', 'Ysmail', 'Abanoz', 'ko100gaming@hotmail.com', '7MM10645FN395523L', 'fragmachinee@msn.com', 'USD', '5000');
INSERT INTO `purchase_history` VALUES (27, 'iyiservis2', '50.00', 'RHAMSXGJ9YHP6', 'Giresun Espiye Arydurak köyü', '13:29:16 Nov 04, 2013 PST', 'Completed', '28300', 'Ysmail', 'Abanoz', 'ko100gaming@hotmail.com', '3UG289820E6269313', 'fragmachinee@msn.com', 'USD', '5000');
INSERT INTO `purchase_history` VALUES (28, 'iyiservis2', '50.00', 'RHAMSXGJ9YHP6', 'Giresun Espiye Arydurak köyü', '13:58:32 Nov 04, 2013 PST', 'Completed', '28300', 'Ysmail', 'Abanoz', 'ko100gaming@hotmail.com', '2YS648256L869704L', 'fragmachinee@msn.com', 'USD', '5000');
INSERT INTO `purchase_history` VALUES (29, 'iyiservis2', '50.00', 'RHAMSXGJ9YHP6', 'Giresun Espiye Arydurak köyü', '13:59:38 Nov 04, 2013 PST', 'Completed', '28300', 'Ysmail', 'Abanoz', 'ko100gaming@hotmail.com', '6G3396315G285691S', 'fragmachinee@msn.com', 'USD', '5000');
INSERT INTO `purchase_history` VALUES (30, 'kasapoglu55', '5.00', 'TR2ZU2RKNG76U', 'SELAHIYE MAH', '23:07:42 Nov 04, 2013 PST', 'Completed', '55100', 'SANIYE', 'YILMAZ', 'ko100gaming@hotmail.com', '7UB26887ER935583K', 'mustyxxx49@gmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (31, 'kasapoglu55', '5.00', 'TR2ZU2RKNG76U', 'SELAHIYE MAH', '00:44:49 Nov 05, 2013 PST', 'Completed', '55100', 'SANIYE', 'YILMAZ', 'ko100gaming@hotmail.com', '77C750849H943810C', 'mustyxxx49@gmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (32, 'kasapoglu55', '5.00', 'TR2ZU2RKNG76U', 'SELAHIYE MAH', '00:48:53 Nov 05, 2013 PST', 'Completed', '55100', 'SANIYE', 'YILMAZ', 'ko100gaming@hotmail.com', '56F927763B781101L', 'mustyxxx49@gmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (33, 'kasapoglu55', '5.00', 'TR2ZU2RKNG76U', 'SELAHIYE MAH', '00:55:34 Nov 05, 2013 PST', 'Completed', '55100', 'SANIYE', 'YILMAZ', 'ko100gaming@hotmail.com', '3KJ95637805322116', 'mustyxxx49@gmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (34, 'cazablanka', '10.00', '2JCTHJQ7HJ63Q', 'x', '05:00:46 Nov 05, 2013 PST', 'Completed', '34295', 'kadir melih', 'gulec', 'ko100gaming@hotmail.com', '8FN202560X486452E', 'kadirmelih.gulec@gmail.com', 'USD', '1000');
INSERT INTO `purchase_history` VALUES (35, 'cazablanka', '5.00', '2JCTHJQ7HJ63Q', 'x', '05:13:41 Nov 05, 2013 PST', 'Completed', '34295', 'kadir melih', 'gulec', 'ko100gaming@hotmail.com', '8MN16451L3786473B', 'kadirmelih.gulec@gmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (36, 'iyiservis2', '50.00', 'RHAMSXGJ9YHP6', 'Giresun Espiye Arydurak köyü', '06:04:42 Nov 05, 2013 PST', 'Completed', '28300', 'Ysmail', 'Abanoz', 'ko100gaming@hotmail.com', '1MT11458U8648671D', 'fragmachinee@msn.com', 'USD', '5000');
INSERT INTO `purchase_history` VALUES (37, 'paster1', '50.00', 'BC8GWTSTELLAQ', 'Atadan Caddesi Mühendisler Sokak 36/9 Ankara/Etlik', '06:41:49 Nov 05, 2013 PST', 'Completed', '', 'Sefa', 'Karayol', 'ko100gaming@hotmail.com', '26892952SB6789229', 'sefakarayol@hotmail.com', 'USD', '5000');
INSERT INTO `purchase_history` VALUES (38, 'paster1', '50.00', 'BC8GWTSTELLAQ', 'Atadan Caddesi Mühendisler Sokak 36/9 Ankara/Etlik', '06:50:53 Nov 05, 2013 PST', 'Completed', '', 'Sefa', 'Karayol', 'ko100gaming@hotmail.com', '9HM95580E7783450X', 'sefakarayol@hotmail.com', 'USD', '5000');
INSERT INTO `purchase_history` VALUES (39, 'paster1', '50.00', 'BC8GWTSTELLAQ', 'Atadan Caddesi Mühendisler Sokak 36/9 Ankara/Etlik', '06:58:59 Nov 05, 2013 PST', 'Completed', '', 'Sefa', 'Karayol', 'ko100gaming@hotmail.com', '8KE60696GR5895748', 'sefakarayol@hotmail.com', 'USD', '5000');
INSERT INTO `purchase_history` VALUES (40, 'jasoon', '5.00', 'MLJEN8WCMVC36', 'Elmaly Kent Mah. Adem yavuz Cad. Melekler Sok. No :4/4', '07:46:53 Nov 05, 2013 PST', 'Completed', '34100', 'Ali', 'SARI', 'ko100gaming@hotmail.com', '9XU15403G6856491L', 'ammoniaaaaaa@gmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (41, 'maxell', '5.00', 'EZT4JGFCJT2T4', '1.Organize Sanayi Bölgesi Osmanly Cd No.3 Sincan', '07:54:12 Nov 05, 2013 PST', 'Completed', '06930', 'Ömer', 'Yerli', 'ko100gaming@hotmail.com', '5SU89741LC205873T', 'anksncnomr@hotmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (42, 'maxell', '40.00', 'EZT4JGFCJT2T4', '1.Organize Sanayi Bölgesi Osmanli Cd No3', '08:13:27 Nov 05, 2013 PST', 'Completed', '06930', 'Ömer', 'Yerli', 'ko100gaming@hotmail.com', '6VN825474X8269605', 'anksncnomr@hotmail.com', 'USD', '4000');
INSERT INTO `purchase_history` VALUES (43, 'paster1', '50.00', 'THD5PQ8Z7V4PA', 'atadan Caddesi Mühendisler Sokak 36/9', '08:29:15 Nov 05, 2013 PST', 'Completed', '', 'sefa', 'Karayol', 'ko100gaming@hotmail.com', '61K4204460082335R', 'fry-28@hotmail.com', 'USD', '5000');
INSERT INTO `purchase_history` VALUES (44, 'rewq1', '30.00', 'JMPKHU5CHNGLS', 'asdfasdf', '09:10:06 Nov 05, 2013 PST', 'Completed', '06170', 'canberk', 'akta?', 'ko100gaming@hotmail.com', '60F07548VV991430W', 'canberk.aktas@hotmail.com', 'USD', '3000');
INSERT INTO `purchase_history` VALUES (45, 'maxell', '30.00', 'EZT4JGFCJT2T4', 'organize sanayi bölgesi sincan', '09:17:55 Nov 05, 2013 PST', 'Completed', '06930', 'Ömer', 'yerli', 'ko100gaming@hotmail.com', '778099755K947510M', 'anksncnomr@hotmail.com', 'USD', '3000');
INSERT INTO `purchase_history` VALUES (46, 'maxell', '15.00', 'EZT4JGFCJT2T4', '1.organize sanayi bölgesi osmanli cd no 3', '09:25:06 Nov 05, 2013 PST', 'Completed', '06930', 'ömer', 'yerli', 'ko100gaming@hotmail.com', '4NA10039EB590553J', 'anksncnomr@hotmail.com', 'USD', '1500');
INSERT INTO `purchase_history` VALUES (47, 'paster1', '45.00', 'HAVLE2BZ7GQJQ', 'Atadan Caddesi Mühendisler Sokak 36/9', '12:23:32 Nov 05, 2013 PST', 'Completed', '', 'Sefa', 'Karayol', 'ko100gaming@hotmail.com', '6NX36446MT571031K', 'DarkOfAnqel.1990@gmail.com', 'USD', '4500');
INSERT INTO `purchase_history` VALUES (48, 'kasapoglu55', '5.00', 'TQYDM3NNCG54N', 'SELAHYYE MAH', '12:36:03 Nov 05, 2013 PST', 'Completed', '55100', 'SINAN', 'YILMAZ', 'ko100gaming@hotmail.com', '17B45445UP078081S', 'mustyxxx49@gmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (49, 'kasapoglu55', '35.00', 'TQYDM3NNCG54N', 'SELAHIYE MAH', '12:38:00 Nov 05, 2013 PST', 'Completed', '55100', 'SINAN', 'YILMAZ', 'ko100gaming@hotmail.com', '20A129683T619012H', 'mustyxxx49@gmail.com', 'USD', '3500');
INSERT INTO `purchase_history` VALUES (50, 'REPLAY55', '15.00', 'QZBUNTQ8MUNZE', 'fatih mahallesi türkoca?y sokak no 19/3', '15:39:03 Nov 05, 2013 PST', 'Completed', '55850', 'Kemalettin', 'KUNDUZ', 'ko100gaming@hotmail.com', '0JB07623BJ992133Y', 'gerilim8210@hotmail.com', 'USD', '1500');
INSERT INTO `purchase_history` VALUES (51, 'ahmtre433', '50.00', 'TX27GR2Q7QEML', 'Ye?ilova mahallesi Fetih Caddesi no :2 \nKütahya/Simav', '02:34:36 Nov 06, 2013 PST', 'Completed', '43500', 'Ahmet Ra?it', 'Ertürk', 'ko100gaming@hotmail.com', '77H72877TL763610L', 'ahmtre@hotmail.co.uk', 'USD', '5000');
INSERT INTO `purchase_history` VALUES (52, 'ahmtre433', '50.00', 'TX27GR2Q7QEML', 'Ye?ilova mahallesi Fetih Caddesi no :2 \nKütahya/Simav', '02:54:13 Nov 06, 2013 PST', 'Completed', '43500', 'Ahmet Ra?it', 'Ertürk', 'ko100gaming@hotmail.com', '0TV19007FW082903E', 'ahmtre@hotmail.co.uk', 'USD', '5000');
INSERT INTO `purchase_history` VALUES (53, 'justsay2yea', '5.00', 'DFC4UD5YUYDDU', 'çiftlikköy sahil mahallesi barbaros bulvary murat apartmany no:69/4', '03:45:01 Nov 06, 2013 PST', 'Completed', '77000', 'yusuf berk', 'karaku?', 'ko100gaming@hotmail.com', '89085817M1114220A', 'fre3d00m@gmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (54, 'caner3516', '5.00', '9RBQCVR6KZLLU', '1620/23 sokak No : 34 Cengizhan Mah. / Bayrakly / YZMYR', '06:28:49 Nov 06, 2013 PST', 'Completed', '', 'Caner', 'Gürcan', 'ko100gaming@hotmail.com', '13P16347J45997830', 'aslavazgecmem35ten@hotmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (55, 'caner3516', '5.00', '9RBQCVR6KZLLU', '1620/23 sokak No : 34 Cengizhan Mah. / Bayrakly / YZMYR', '06:30:21 Nov 06, 2013 PST', 'Completed', '', 'Caner', 'Gürcan', 'ko100gaming@hotmail.com', '9A73573122204622X', 'aslavazgecmem35ten@hotmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (56, 'maxell', '40.00', 'FXTF4PF8RNC42', '1 . Organize Sanayi Bölgesi Osmanli Cd No3', '08:11:56 Nov 06, 2013 PST', 'Completed', '06930', 'Vergül', 'Yerli', 'ko100gaming@hotmail.com', '4YK89146NG217943K', 'anksncnomr@hotmail.com', 'USD', '4000');
INSERT INTO `purchase_history` VALUES (57, 'nafaso1', '10.00', 'CD93TQ7JBR252', 'cumhuriyet mah. kazym pa?a cad. no:55', '15:53:24 Nov 06, 2013 PST', 'Completed', '59800', 'hüseyin caner', 'karayer', 'ko100gaming@hotmail.com', '77W34116RL314670L', 'majestelry@hotmail.com', 'USD', '1000');
INSERT INTO `purchase_history` VALUES (58, 'umut52', '5.00', 'S4WCL2G3NMZEE', 'tandogan mahallesi ?ehit mehmet metin sokak 3/9', '00:50:35 Nov 07, 2013 PST', 'Completed', '', 'umut', 'altun', 'ko100gaming@hotmail.com', '2ME878213F114343T', 'umut_00052@hotmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (59, 'justsay2yea', '5.00', 'DFC4UD5YUYDDU', 'çiftlikköy sahil mahallesi barbaros bulvary murat apartmany no:69/4', '04:18:51 Nov 07, 2013 PST', 'Completed', '77000', 'yusuf berk', 'karaku?', 'ko100gaming@hotmail.com', '9GB54850KK547834L', 'fre3d00m@gmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (60, 'ammonia', '10.00', 'MLJEN8WCMVC36', 'Elmaly Kent Mah. Adem yavuz Cad. Melekler Sok. No :4/4', '06:27:38 Nov 07, 2013 PST', 'Completed', '34100', 'Ali', 'SARI', 'ko100gaming@hotmail.com', '8AE104051B2344237', 'ammoniaaaaaa@gmail.com', 'USD', '1000');
INSERT INTO `purchase_history` VALUES (61, 'marreg5959', '10.00', 'PMCU5RW88N55S', 'Ystasyon Kazymlar', '07:35:47 Nov 07, 2013 PST', 'Completed', '59880', 'Ramazan', 'I?IK', 'ko100gaming@hotmail.com', '53Y55481G0930974C', 'bypatronn21@hotmail.com', 'USD', '1000');
INSERT INTO `purchase_history` VALUES (62, 'ilkanx33', '5.00', 'QS4SKMW9PAVJQ', 'ORTA MAHALLE KIPÇAK SOKAK NO 67 DAYRE 9', '08:33:00 Nov 07, 2013 PST', 'Completed', '34030', 'AYFER', 'SAYDAN', 'ko100gaming@hotmail.com', '9GY30657WB640420E', 'ayfer_saydan@hotmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (63, 'justsay2yea', '10.00', 'DFC4UD5YUYDDU', 'çiftlikköy sahil mahallesi barbaros bulvary murat apartmany no:69/4', '14:18:17 Nov 07, 2013 PST', 'Completed', '77000', 'yusuf berk', 'karaku?', 'ko100gaming@hotmail.com', '3CX263047D734952X', 'fre3d00m@gmail.com', 'USD', '1000');
INSERT INTO `purchase_history` VALUES (64, 'wariorgoko', '5.00', 'K3UCK4QPYXGPG', 'sisli ayazag istabul', '15:57:35 Nov 07, 2013 PST', 'Completed', '', 'halil', 'bayik', 'ko100gaming@hotmail.com', '38D477677Y625672H', 'halilbayik01@gmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (65, 'wariorgoko', '10.00', 'U3TF8LCU26P4N', 'istanbul sisli beykent', '16:20:02 Nov 07, 2013 PST', 'Completed', '', 'halil', 'bayik', 'ko100gaming@hotmail.com', '2UP32478AA7758535', 'halilbayik@gmail.com', 'USD', '1000');
INSERT INTO `purchase_history` VALUES (66, 'wariorgoko', '10.00', 'U3TF8LCU26P4N', 'istanbul sisli beykent', '16:35:35 Nov 07, 2013 PST', 'Completed', '', 'halil', 'bayik', 'ko100gaming@hotmail.com', '6KC96195MB9451128', 'halilbayik01@gmail.com', 'USD', '1000');
INSERT INTO `purchase_history` VALUES (67, 'iyiservis2', '10.00', 'RHAMSXGJ9YHP6', 'Giresun Espiye Arydurak köyü', '07:07:22 Nov 08, 2013 PST', 'Completed', '28300', 'Ysmail', 'Abanoz', 'ko100gaming@hotmail.com', '9GW03480Y57466643', 'fragmachinee@msn.com', 'USD', '1000');
INSERT INTO `purchase_history` VALUES (68, 'kahraman1', '50.00', '4EBQFVMHM6XSS', 'merkez mah. çynar sok.', '07:14:52 Nov 08, 2013 PST', 'Completed', '34406', 'olcay', 'yildiz', 'ko100gaming@hotmail.com', '8C884596YN063891C', 'olcaybaskanadream@hotmail.com', 'USD', '5000');
INSERT INTO `purchase_history` VALUES (69, 'ltorbaci34', '5.00', 'QS4SKMW9PAVJQ', 'YENY DOGAN MAHALLE A?ÇIOGLU CIKMAZI NO : 11 KAT : 2 DAYRE : 3', '08:22:37 Nov 08, 2013 PST', 'Completed', '34030', 'AYFER', 'SAYDAN', 'ko100gaming@hotmail.com', '1AX87813LN2850812', 'ayfer_saydan@hotmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (70, 'iyiservis2', '50.00', 'RHAMSXGJ9YHP6', 'Giresun Espiye Arydurak köyü', '08:27:28 Nov 08, 2013 PST', 'Completed', '28300', 'Ysmail', 'Abanoz', 'ko100gaming@hotmail.com', '27W49529FK015305H', 'fragmachinee@msn.com', 'USD', '5000');
INSERT INTO `purchase_history` VALUES (71, 'kahraman1', '30.00', '4EBQFVMHM6XSS', 'merkez mah. çynar sok.', '08:49:27 Nov 08, 2013 PST', 'Completed', '34406', 'olcay', 'yildiz', 'ko100gaming@hotmail.com', '87K30020M4389935A', 'olcaybaskanadream@hotmail.com', 'USD', '3000');
INSERT INTO `purchase_history` VALUES (72, 'decoys0603', '10.00', 'RWY6PZCER98QJ', 'akdeniz mah. aypek sitesi \nbelek/antalya', '09:46:10 Nov 08, 2013 PST', 'Completed', '07506', 'umut', 'gur', 'ko100gaming@hotmail.com', '3PB12904NX720123Y', 'decoys0601@gmail.com', 'USD', '1000');
INSERT INTO `purchase_history` VALUES (73, '0sk1', '', '', '', '', '', '', '', '', '', '9890346-t1i6-3t4i-vnvj-5k9w-g6kr-jg32', '', '', '10');
INSERT INTO `purchase_history` VALUES (74, 'rasgele', '5.00', 'Z2N6NC7L7N7K6', 'sefa apt daire 1 bostancy', '13:22:11 Nov 13, 2013 PST', 'Completed', '', 'Ozan', 'HIZAL', 'buyko100@mail.com', '6WT50843JV251463U', 'omerozanhizal@gmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (75, 'maxell', '5.00', 'EZT4JGFCJT2T4', 'organiza sanayi bölgesi', '13:37:09 Nov 15, 2013 PST', 'Completed', '06930', 'ömer', 'yerli', 'buyko100@mail.com', '2DF28458M4302024H', 'anksncnomr@hotmail.com', 'USD', '500');
INSERT INTO `purchase_history` VALUES (76, '', '40.00', 'RW74Z8H6SG8VC', '', '09:14:47 Dec 12, 2013 PST', 'Completed', '', 'murat', 'kocacy', 'yatagankc@hotmail.com', '0XX12971VY341012B', 'murat_34@besiktas.ws', 'TRY', '4000');
INSERT INTO `purchase_history` VALUES (77, '', '50.00', 'XZMZDVHFPBSG8', '', '06:00:04 Dec 13, 2013 PST', 'Completed', '', 'özkan', 'türen', 'yatagankc@hotmail.com', '41025060FD324282S', 'ozkan_turen@hotmail.com', 'TRY', '5000');
INSERT INTO `purchase_history` VALUES (78, '', '25.00', 'QZ42XASGNCGXL', 'Obere Rainstr. 12', '10:50:14 Dec 28, 2013 PST', 'Completed', '73235', 'Derya', 'Aker', 'yatagankc@hotmail.com', '9JK955722X7249137', 'son_nefes_d_b@hotmail.de', 'EUR', '2500');
INSERT INTO `purchase_history` VALUES (79, '', '20.00', 'RW74Z8H6SG8VC', '', '11:35:27 Dec 31, 2013 PST', 'Completed', '', 'murat', 'kocacy', 'yatagankc@hotmail.com', '6GR38542KW464721X', 'murat_34@besiktas.ws', 'TRY', '2000');
INSERT INTO `purchase_history` VALUES (80, '', '50.00', 'XZMZDVHFPBSG8', 'asdasdasd', '08:05:50 Jan 19, 2014 PST', 'Completed', '35000', 'özkan', 'türen', 'yatagankc@hotmail.com', '6F227976M4054984K', 'ozkan_turen@hotmail.com', 'TRY', '5000');
INSERT INTO `purchase_history` VALUES (81, '', '30.00', 'PXGVZ7UK3Z6Q8', '', '06:32:12 Jan 23, 2014 PST', 'Completed', '', 'ula?', 'tunç', 'yatagankc@hotmail.com', '0M9539375L8197004', 'jamrockpack@gmail.com', 'TRY', '3000');
INSERT INTO `purchase_history` VALUES (82, '', '30.00', 'PXGVZ7UK3Z6Q8', '', '09:26:41 Jan 29, 2014 PST', 'Completed', '', 'ula?', 'tunç', 'yatagankc@hotmail.com', '5VB97289XH7940638', 'jamrockpack@gmail.com', 'TRY', '3000');
INSERT INTO `purchase_history` VALUES (83, '', '30.00', 'XZMZDVHFPBSG8', 'asdasdasd', '06:44:16 Feb 06, 2014 PST', 'Completed', '35000', 'özkan', 'türen', 'yatagankc@hotmail.com', '02K16419XN625854P', 'ozkan_turen@hotmail.com', 'TRY', '3000');
INSERT INTO `purchase_history` VALUES (84, '', '20.00', 'XZMZDVHFPBSG8', 'asdasdasd', '08:40:53 Feb 07, 2014 PST', 'Completed', '35000', 'özkan', 'türen', 'yatagankc@hotmail.com', '0LJ77460FT843451L', 'ozkan_turen@hotmail.com', 'TRY', '2000');

-- --------------------------------------------------------

-- 
-- Tablo yapısı: `pus_purchase_history`
-- 

CREATE TABLE `pus_purchase_history` (
  `sIndex` int(11) NOT NULL auto_increment,
  `nItemID` int(11) NOT NULL,
  `strItem` varchar(100) NOT NULL,
  `nPrice` int(11) NOT NULL,
  `nCash` int(11) NOT NULL,
  `strDate` varchar(50) NOT NULL,
  PRIMARY KEY  (`sIndex`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- 
-- Tablo döküm verisi `pus_purchase_history`
-- 


-- --------------------------------------------------------

-- 
-- Tablo yapısı: `user_info`
-- 

CREATE TABLE `user_info` (
  `sIndex` int(10) unsigned NOT NULL auto_increment,
  `strAccountID` varchar(100) NOT NULL,
  `nCash` int(11) NOT NULL default '0',
  `nBonusCash` int(11) NOT NULL default '0',
  PRIMARY KEY  (`sIndex`),
  UNIQUE KEY `sIndex` (`sIndex`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=79386 ;

-- 
-- Tablo döküm verisi `user_info`
-- 

INSERT INTO `user_info` VALUES (79385, 'admin', 500, 0);
