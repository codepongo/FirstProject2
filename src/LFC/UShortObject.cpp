#include "stdafx.h"
#include "LFC.h"

namespace System
{

// static
UShortObject UShortObject::s_values[258] =
{
	UShortObject(0xffff),
	UShortObject(0),
	UShortObject(1),
	UShortObject(2),
	UShortObject(3),
	UShortObject(4),
	UShortObject(5),
	UShortObject(6),
	UShortObject(7),
	UShortObject(8),
	UShortObject(9),
	UShortObject(10),
	UShortObject(11),
	UShortObject(12),
	UShortObject(13),
	UShortObject(14),
	UShortObject(15),
	UShortObject(16),
	UShortObject(17),
	UShortObject(18),
	UShortObject(19),
	UShortObject(20),
	UShortObject(21),
	UShortObject(22),
	UShortObject(23),
	UShortObject(24),
	UShortObject(25),
	UShortObject(26),
	UShortObject(27),
	UShortObject(28),
	UShortObject(29),
	UShortObject(30),
	UShortObject(31),
	UShortObject(32),
	UShortObject(33),
	UShortObject(34),
	UShortObject(35),
	UShortObject(36),
	UShortObject(37),
	UShortObject(38),
	UShortObject(39),
	UShortObject(40),
	UShortObject(41),
	UShortObject(42),
	UShortObject(43),
	UShortObject(44),
	UShortObject(45),
	UShortObject(46),
	UShortObject(47),
	UShortObject(48),
	UShortObject(49),
	UShortObject(50),
	UShortObject(51),
	UShortObject(52),
	UShortObject(53),
	UShortObject(54),
	UShortObject(55),
	UShortObject(56),
	UShortObject(57),
	UShortObject(58),
	UShortObject(59),
	UShortObject(60),
	UShortObject(61),
	UShortObject(62),
	UShortObject(63),
	UShortObject(64),
	UShortObject(65),
	UShortObject(66),
	UShortObject(67),
	UShortObject(68),
	UShortObject(69),
	UShortObject(70),
	UShortObject(71),
	UShortObject(72),
	UShortObject(73),
	UShortObject(74),
	UShortObject(75),
	UShortObject(76),
	UShortObject(77),
	UShortObject(78),
	UShortObject(79),
	UShortObject(80),
	UShortObject(81),
	UShortObject(82),
	UShortObject(83),
	UShortObject(84),
	UShortObject(85),
	UShortObject(86),
	UShortObject(87),
	UShortObject(88),
	UShortObject(89),
	UShortObject(90),
	UShortObject(91),
	UShortObject(92),
	UShortObject(93),
	UShortObject(94),
	UShortObject(95),
	UShortObject(96),
	UShortObject(97),
	UShortObject(98),
	UShortObject(99),
	UShortObject(100),
	UShortObject(101),
	UShortObject(102),
	UShortObject(103),
	UShortObject(104),
	UShortObject(105),
	UShortObject(106),
	UShortObject(107),
	UShortObject(108),
	UShortObject(109),
	UShortObject(110),
	UShortObject(111),
	UShortObject(112),
	UShortObject(113),
	UShortObject(114),
	UShortObject(115),
	UShortObject(116),
	UShortObject(117),
	UShortObject(118),
	UShortObject(119),
	UShortObject(120),
	UShortObject(121),
	UShortObject(122),
	UShortObject(123),
	UShortObject(124),
	UShortObject(125),
	UShortObject(126),
	UShortObject(127),
	UShortObject(128),
	UShortObject(129),
	UShortObject(130),
	UShortObject(131),
	UShortObject(132),
	UShortObject(133),
	UShortObject(134),
	UShortObject(135),
	UShortObject(136),
	UShortObject(137),
	UShortObject(138),
	UShortObject(139),
	UShortObject(140),
	UShortObject(141),
	UShortObject(142),
	UShortObject(143),
	UShortObject(144),
	UShortObject(145),
	UShortObject(146),
	UShortObject(147),
	UShortObject(148),
	UShortObject(149),
	UShortObject(150),
	UShortObject(151),
	UShortObject(152),
	UShortObject(153),
	UShortObject(154),
	UShortObject(155),
	UShortObject(156),
	UShortObject(157),
	UShortObject(158),
	UShortObject(159),
	UShortObject(160),
	UShortObject(161),
	UShortObject(162),
	UShortObject(163),
	UShortObject(164),
	UShortObject(165),
	UShortObject(166),
	UShortObject(167),
	UShortObject(168),
	UShortObject(169),
	UShortObject(170),
	UShortObject(171),
	UShortObject(172),
	UShortObject(173),
	UShortObject(174),
	UShortObject(175),
	UShortObject(176),
	UShortObject(177),
	UShortObject(178),
	UShortObject(179),
	UShortObject(180),
	UShortObject(181),
	UShortObject(182),
	UShortObject(183),
	UShortObject(184),
	UShortObject(185),
	UShortObject(186),
	UShortObject(187),
	UShortObject(188),
	UShortObject(189),
	UShortObject(190),
	UShortObject(191),
	UShortObject(192),
	UShortObject(193),
	UShortObject(194),
	UShortObject(195),
	UShortObject(196),
	UShortObject(197),
	UShortObject(198),
	UShortObject(199),
	UShortObject(200),
	UShortObject(201),
	UShortObject(202),
	UShortObject(203),
	UShortObject(204),
	UShortObject(205),
	UShortObject(206),
	UShortObject(207),
	UShortObject(208),
	UShortObject(209),
	UShortObject(210),
	UShortObject(211),
	UShortObject(212),
	UShortObject(213),
	UShortObject(214),
	UShortObject(215),
	UShortObject(216),
	UShortObject(217),
	UShortObject(218),
	UShortObject(219),
	UShortObject(220),
	UShortObject(221),
	UShortObject(222),
	UShortObject(223),
	UShortObject(224),
	UShortObject(225),
	UShortObject(226),
	UShortObject(227),
	UShortObject(228),
	UShortObject(229),
	UShortObject(230),
	UShortObject(231),
	UShortObject(232),
	UShortObject(233),
	UShortObject(234),
	UShortObject(235),
	UShortObject(236),
	UShortObject(237),
	UShortObject(238),
	UShortObject(239),
	UShortObject(240),
	UShortObject(241),
	UShortObject(242),
	UShortObject(243),
	UShortObject(244),
	UShortObject(245),
	UShortObject(246),
	UShortObject(247),
	UShortObject(248),
	UShortObject(249),
	UShortObject(250),
	UShortObject(251),
	UShortObject(252),
	UShortObject(253),
	UShortObject(254),
	UShortObject(255),
	UShortObject(256),
};

String UShortObject::ToString()
{
	return String::FromNumber(m_value);
}

UShortObject* UShortObject::GetObject(unsigned short value)
{
	if (value <= 256 || value == 0xffff)
	{
		ASSERT(s_values[value+1].m_value == value);
		return &s_values[value+1];
	}

	return new UShortObject(value);
}

}	// System