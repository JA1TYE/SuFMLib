#include<cstdint>
#include "table.h"

const std::int16_t sin_table[1024] = {
        0,   201,   402,   603,   804,  1005,  1206,  1407,
    1608,  1809,  2009,  2210,  2410,  2611,  2811,  3012,
    3212,  3412,  3612,  3811,  4011,  4210,  4410,  4609,
    4808,  5007,  5205,  5404,  5602,  5800,  5998,  6195,
    6393,  6590,  6786,  6983,  7179,  7375,  7571,  7767,
    7962,  8157,  8351,  8545,  8739,  8933,  9126,  9319,
    9512,  9704,  9896, 10087, 10278, 10469, 10659, 10849,
    11039, 11228, 11417, 11605, 11793, 11980, 12167, 12353,
    12539, 12725, 12910, 13094, 13279, 13462, 13645, 13828,
    14010, 14191, 14372, 14553, 14732, 14912, 15090, 15269,
    15446, 15623, 15800, 15976, 16151, 16325, 16499, 16673,
    16846, 17018, 17189, 17360, 17530, 17700, 17869, 18037,
    18204, 18371, 18537, 18703, 18868, 19032, 19195, 19357,
    19519, 19680, 19841, 20000, 20159, 20317, 20475, 20631,
    20787, 20942, 21096, 21250, 21403, 21554, 21705, 21856,
    22005, 22154, 22301, 22448, 22594, 22739, 22884, 23027,
    23170, 23311, 23452, 23592, 23731, 23870, 24007, 24143,
    24279, 24413, 24547, 24680, 24811, 24942, 25072, 25201,
    25329, 25456, 25582, 25708, 25832, 25955, 26077, 26198,
    26319, 26438, 26556, 26674, 26790, 26905, 27019, 27133,
    27245, 27356, 27466, 27575, 27683, 27790, 27896, 28001,
    28105, 28208, 28310, 28411, 28510, 28609, 28706, 28803,
    28898, 28992, 29085, 29177, 29268, 29358, 29447, 29534,
    29621, 29706, 29791, 29874, 29956, 30037, 30117, 30195,
    30273, 30349, 30424, 30498, 30571, 30643, 30714, 30783,
    30852, 30919, 30985, 31050, 31113, 31176, 31237, 31297,
    31356, 31414, 31470, 31526, 31580, 31633, 31685, 31736,
    31785, 31833, 31880, 31926, 31971, 32014, 32057, 32098,
    32137, 32176, 32213, 32250, 32285, 32318, 32351, 32382,
    32412, 32441, 32469, 32495, 32521, 32545, 32567, 32589,
    32609, 32628, 32646, 32663, 32678, 32692, 32705, 32717,
    32728, 32737, 32745, 32752, 32757, 32761, 32765, 32766,
    32767, 32766, 32765, 32761, 32757, 32752, 32745, 32737,
    32728, 32717, 32705, 32692, 32678, 32663, 32646, 32628,
    32609, 32589, 32567, 32545, 32521, 32495, 32469, 32441,
    32412, 32382, 32351, 32318, 32285, 32250, 32213, 32176,
    32137, 32098, 32057, 32014, 31971, 31926, 31880, 31833,
    31785, 31736, 31685, 31633, 31580, 31526, 31470, 31414,
    31356, 31297, 31237, 31176, 31113, 31050, 30985, 30919,
    30852, 30783, 30714, 30643, 30571, 30498, 30424, 30349,
    30273, 30195, 30117, 30037, 29956, 29874, 29791, 29706,
    29621, 29534, 29447, 29358, 29268, 29177, 29085, 28992,
    28898, 28803, 28706, 28609, 28510, 28411, 28310, 28208,
    28105, 28001, 27896, 27790, 27683, 27575, 27466, 27356,
    27245, 27133, 27019, 26905, 26790, 26674, 26556, 26438,
    26319, 26198, 26077, 25955, 25832, 25708, 25582, 25456,
    25329, 25201, 25072, 24942, 24811, 24680, 24547, 24413,
    24279, 24143, 24007, 23870, 23731, 23592, 23452, 23311,
    23170, 23027, 22884, 22739, 22594, 22448, 22301, 22154,
    22005, 21856, 21705, 21554, 21403, 21250, 21096, 20942,
    20787, 20631, 20475, 20317, 20159, 20000, 19841, 19680,
    19519, 19357, 19195, 19032, 18868, 18703, 18537, 18371,
    18204, 18037, 17869, 17700, 17530, 17360, 17189, 17018,
    16846, 16673, 16499, 16325, 16151, 15976, 15800, 15623,
    15446, 15269, 15090, 14912, 14732, 14553, 14372, 14191,
    14010, 13828, 13645, 13462, 13279, 13094, 12910, 12725,
    12539, 12353, 12167, 11980, 11793, 11605, 11417, 11228,
    11039, 10849, 10659, 10469, 10278, 10087,  9896,  9704,
    9512,  9319,  9126,  8933,  8739,  8545,  8351,  8157,
    7962,  7767,  7571,  7375,  7179,  6983,  6786,  6590,
    6393,  6195,  5998,  5800,  5602,  5404,  5205,  5007,
    4808,  4609,  4410,  4210,  4011,  3811,  3612,  3412,
    3212,  3012,  2811,  2611,  2410,  2210,  2009,  1809,
    1608,  1407,  1206,  1005,   804,   603,   402,   201,
        0,  -201,  -402,  -603,  -804, -1005, -1206, -1407,
    -1608, -1809, -2009, -2210, -2410, -2611, -2811, -3012,
    -3212, -3412, -3612, -3811, -4011, -4210, -4410, -4609,
    -4808, -5007, -5205, -5404, -5602, -5800, -5998, -6195,
    -6393, -6590, -6786, -6983, -7179, -7375, -7571, -7767,
    -7962, -8157, -8351, -8545, -8739, -8933, -9126, -9319,
    -9512, -9704, -9896,-10087,-10278,-10469,-10659,-10849,
    -11039,-11228,-11417,-11605,-11793,-11980,-12167,-12353,
    -12539,-12725,-12910,-13094,-13279,-13462,-13645,-13828,
    -14010,-14191,-14372,-14553,-14732,-14912,-15090,-15269,
    -15446,-15623,-15800,-15976,-16151,-16325,-16499,-16673,
    -16846,-17018,-17189,-17360,-17530,-17700,-17869,-18037,
    -18204,-18371,-18537,-18703,-18868,-19032,-19195,-19357,
    -19519,-19680,-19841,-20000,-20159,-20317,-20475,-20631,
    -20787,-20942,-21096,-21250,-21403,-21554,-21705,-21856,
    -22005,-22154,-22301,-22448,-22594,-22739,-22884,-23027,
    -23170,-23311,-23452,-23592,-23731,-23870,-24007,-24143,
    -24279,-24413,-24547,-24680,-24811,-24942,-25072,-25201,
    -25329,-25456,-25582,-25708,-25832,-25955,-26077,-26198,
    -26319,-26438,-26556,-26674,-26790,-26905,-27019,-27133,
    -27245,-27356,-27466,-27575,-27683,-27790,-27896,-28001,
    -28105,-28208,-28310,-28411,-28510,-28609,-28706,-28803,
    -28898,-28992,-29085,-29177,-29268,-29358,-29447,-29534,
    -29621,-29706,-29791,-29874,-29956,-30037,-30117,-30195,
    -30273,-30349,-30424,-30498,-30571,-30643,-30714,-30783,
    -30852,-30919,-30985,-31050,-31113,-31176,-31237,-31297,
    -31356,-31414,-31470,-31526,-31580,-31633,-31685,-31736,
    -31785,-31833,-31880,-31926,-31971,-32014,-32057,-32098,
    -32137,-32176,-32213,-32250,-32285,-32318,-32351,-32382,
    -32412,-32441,-32469,-32495,-32521,-32545,-32567,-32589,
    -32609,-32628,-32646,-32663,-32678,-32692,-32705,-32717,
    -32728,-32737,-32745,-32752,-32757,-32761,-32765,-32766,
    -32767,-32766,-32765,-32761,-32757,-32752,-32745,-32737,
    -32728,-32717,-32705,-32692,-32678,-32663,-32646,-32628,
    -32609,-32589,-32567,-32545,-32521,-32495,-32469,-32441,
    -32412,-32382,-32351,-32318,-32285,-32250,-32213,-32176,
    -32137,-32098,-32057,-32014,-31971,-31926,-31880,-31833,
    -31785,-31736,-31685,-31633,-31580,-31526,-31470,-31414,
    -31356,-31297,-31237,-31176,-31113,-31050,-30985,-30919,
    -30852,-30783,-30714,-30643,-30571,-30498,-30424,-30349,
    -30273,-30195,-30117,-30037,-29956,-29874,-29791,-29706,
    -29621,-29534,-29447,-29358,-29268,-29177,-29085,-28992,
    -28898,-28803,-28706,-28609,-28510,-28411,-28310,-28208,
    -28105,-28001,-27896,-27790,-27683,-27575,-27466,-27356,
    -27245,-27133,-27019,-26905,-26790,-26674,-26556,-26438,
    -26319,-26198,-26077,-25955,-25832,-25708,-25582,-25456,
    -25329,-25201,-25072,-24942,-24811,-24680,-24547,-24413,
    -24279,-24143,-24007,-23870,-23731,-23592,-23452,-23311,
    -23170,-23027,-22884,-22739,-22594,-22448,-22301,-22154,
    -22005,-21856,-21705,-21554,-21403,-21250,-21096,-20942,
    -20787,-20631,-20475,-20317,-20159,-20000,-19841,-19680,
    -19519,-19357,-19195,-19032,-18868,-18703,-18537,-18371,
    -18204,-18037,-17869,-17700,-17530,-17360,-17189,-17018,
    -16846,-16673,-16499,-16325,-16151,-15976,-15800,-15623,
    -15446,-15269,-15090,-14912,-14732,-14553,-14372,-14191,
    -14010,-13828,-13645,-13462,-13279,-13094,-12910,-12725,
    -12539,-12353,-12167,-11980,-11793,-11605,-11417,-11228,
    -11039,-10849,-10659,-10469,-10278,-10087, -9896, -9704,
    -9512, -9319, -9126, -8933, -8739, -8545, -8351, -8157,
    -7962, -7767, -7571, -7375, -7179, -6983, -6786, -6590,
    -6393, -6195, -5998, -5800, -5602, -5404, -5205, -5007,
    -4808, -4609, -4410, -4210, -4011, -3811, -3612, -3412,
    -3212, -3012, -2811, -2611, -2410, -2210, -2009, -1809,
    -1608, -1407, -1206, -1005,  -804,  -603,  -402,  -201
};

const std::int8_t NOTE_DEFAULT_OFFSET = 12;
//offset 12
const std::uint32_t delta_table[152]={
    365779,387529,410573,434987,460853,488257,517290,548049,
    580638,615165,651744,690499,731558,775059,821146,869974,
    921706,976513,1034580,1096099,1161276,1230329,1303489,1380998,
    1463116,1550118,1642293,1739948,1843411,1953026,2069159,2192198,
    2322553,2460659,2606977,2761996,2926233,3100236,3284585,3479897,
    3686822,3906052,4138318,4384395,4645105,4921317,5213954,5523992,
    5852466,6200471,6569171,6959794,7373645,7812104,8276636,8768791,
    9290210,9842635,10427908,11047984,11704931,12400943,13138341,13919588,
    14747289,15624209,16553273,17537582,18580420,19685270,20855817,22095968,
    23409863,24801886,26276682,27839175,29494579,31248418,33106545,35075163,
    37160841,39370539,41711633,44191936,46819725,49603771,52553365,55678351,
    58989158,62496836,66213091,70150326,74321681,78741079,83423267,88383872,
    93639451,99207542,105106730,111356701,117978315,124993671,132426182,140300652,
    148643363,157482157,166846534,176767745,187278902,198415085,210213460,222713403,
    235956631,249987342,264852363,280601304,297286726,314964315,333693067,353535490,
    374557804,396830170,420426920,445426805,471913261,499974684,529704726,561202608,
    594573452,629928629,667386135,707070979,749115608,793660340,840853839,890853611,
    943826523,999949368,1059409452,1122405216,1189146904,1259857258,1334772269,1414141959,
    1498231215,1587320679,1681707679,1781707221,1887653046,1999898737,2118818904,2244810433,
};

const std::uint16_t att_table[128]={
    0x34f,0x368,0x381,0x39c,0x3b6,0x3d2,0x3ef,0x40c,
    0x42a,0x44a,0x46a,0x48b,0x4ad,0x4d0,0x4f4,0x519,
    0x53f,0x566,0x58e,0x5b8,0x5e2,0x60e,0x63c,0x66a,
    0x69a,0x6cc,0x6fe,0x733,0x768,0x7a0,0x7d9,0x814,
    0x850,0x88e,0x8ce,0x910,0x954,0x999,0x9e1,0xa2b,
    0xa77,0xac5,0xb16,0xb68,0xbbe,0xc15,0xc70,0xccd,
    0xd2c,0xd8f,0xdf4,0xe5d,0xec8,0xf36,0xfa8,0x101d,
    0x1096,0x1112,0x1191,0x1215,0x129c,0x1327,0x13b6,0x1449,
    0x14e1,0x157d,0x161e,0x16c3,0x176d,0x181c,0x18d1,0x198a,
    0x1a49,0x1b0d,0x1bd8,0x1ca8,0x1d7e,0x1e5b,0x1f3d,0x2027,
    0x2117,0x220f,0x230d,0x2413,0x2521,0x2637,0x2754,0x287a,
    0x29a9,0x2ae0,0x2c21,0x2d6b,0x2ebe,0x301b,0x3183,0x32f5,
    0x3472,0x35fa,0x378e,0x392d,0x3ad8,0x3c90,0x3e55,0x4027,
    0x4206,0x43f4,0x45f0,0x47fb,0x4a15,0x4c3f,0x4e79,0x50c3,
    0x531f,0x558c,0x580c,0x5a9e,0x5d43,0x5ffd,0x62ca,0x65ad,
    0x68a5,0x6bb3,0x6ed8,0x7215,0x7569,0x78d7,0x7c5e,0x8000
};

const std::uint16_t exp_table[257]={
    32768,32679,32591,32502,32415,32327,32239,32152,
    32065,31979,31892,31806,31720,31634,31549,31463,
    31378,31293,31209,31124,31040,30956,30873,30789,
    30706,30623,30540,30457,30375,30293,30211,30129,
    30048,29967,29886,29805,29724,29644,29564,29484,
    29404,29325,29245,29166,29087,29009,28930,28852,
    28774,28696,28619,28541,28464,28387,28310,28234,
    28157,28081,28005,27930,27854,27779,27704,27629,
    27554,27479,27405,27331,27257,27183,27110,27037,
    26964,26891,26818,26745,26673,26601,26529,26457,
    26386,26314,26243,26172,26102,26031,25961,25890,
    25820,25751,25681,25611,25542,25473,25404,25336,
    25267,25199,25131,25063,24995,24927,24860,24793,
    24726,24659,24592,24526,24459,24393,24327,24261,
    24196,24130,24065,24000,23935,23870,23806,23742,
    23677,23613,23549,23486,23422,23359,23296,23233,
    23170,23107,23045,22983,22920,22858,22797,22735,
    22673,22612,22551,22490,22429,22369,22308,22248,
    22188,22128,22068,22008,21949,21889,21830,21771,
    21712,21653,21595,21537,21478,21420,21362,21305,
    21247,21189,21132,21075,21018,20961,20905,20848,
    20792,20735,20679,20623,20568,20512,20457,20401,
    20346,20291,20236,20181,20127,20073,20018,19964,
    19910,19856,19803,19749,19696,19642,19589,19536,
    19483,19431,19378,19326,19274,19221,19169,19118,
    19066,19014,18963,18912,18861,18810,18759,18708,
    18657,18607,18557,18506,18456,18407,18357,18307,
    18258,18208,18159,18110,18061,18012,17963,17915,
    17866,17818,17770,17722,17674,17626,17578,17531,
    17484,17436,17389,17342,17295,17248,17202,17155,
    17109,17063,17016,16970,16925,16879,16833,16788,
    16742,16697,16652,16607,16562,16517,16472,16428,
    16384
};

const std::uint16_t eg_exp_table[258]={
    0x8000,0x7df2,0x7bee,0x79f1,0x77fc,0x7610,0x742b,0x724d,
    0x7077,0x6ea9,0x6ce2,0x6b22,0x6969,0x67b7,0x660c,0x6467,
    0x62ca,0x6132,0x5fa1,0x5e17,0x5c92,0x5b14,0x599c,0x582a,
    0x56bd,0x5557,0x53f5,0x529a,0x5144,0x4ff3,0x4ea8,0x4d62,
    0x4c21,0x4ae5,0x49ae,0x487c,0x474f,0x4626,0x4502,0x43e3,
    0x42c8,0x41b2,0x40a0,0x3f93,0x3e89,0x3d84,0x3c83,0x3b86,
    0x3a8d,0x3998,0x38a7,0x37b9,0x36d0,0x35ea,0x3507,0x3428,
    0x334d,0x3275,0x31a1,0x30d0,0x3002,0x2f37,0x2e70,0x2dac,
    0x2ceb,0x2c2c,0x2b71,0x2ab9,0x2a04,0x2951,0x28a2,0x27f5,
    0x274b,0x26a3,0x25ff,0x255c,0x24bd,0x2420,0x2385,0x22ed,
    0x2257,0x21c3,0x2132,0x20a3,0x2017,0x1f8c,0x1f04,0x1e7e,
    0x1dfa,0x1d78,0x1cf8,0x1c7b,0x1bff,0x1b85,0x1b0d,0x1a97,
    0x1a23,0x19b0,0x1940,0x18d1,0x1864,0x17f8,0x178f,0x1727,
    0x16c0,0x165c,0x15f8,0x1597,0x1537,0x14d8,0x147b,0x141f,
    0x13c5,0x136d,0x1315,0x12bf,0x126b,0x1217,0x11c5,0x1175,
    0x1125,0x10d7,0x108a,0x103f,0x0ff4,0x0fab,0x0f62,0x0f1b,
    0x0ed5,0x0e91,0x0e4d,0x0e0a,0x0dc9,0x0d88,0x0d48,0x0d0a,
    0x0ccc,0x0c90,0x0c54,0x0c19,0x0bdf,0x0ba6,0x0b6e,0x0b37,
    0x0b01,0x0acc,0x0a97,0x0a63,0x0a31,0x09fe,0x09cd,0x099d,
    0x096d,0x093e,0x090f,0x08e2,0x08b5,0x0889,0x085d,0x0833,
    0x0809,0x07df,0x07b6,0x078e,0x0767,0x0740,0x071a,0x06f4,
    0x06cf,0x06aa,0x0687,0x0663,0x0640,0x061e,0x05fd,0x05db,
    0x05bb,0x059b,0x057b,0x055c,0x053d,0x051f,0x0501,0x04e4,
    0x04c7,0x04ab,0x048f,0x0474,0x0459,0x043e,0x0424,0x040a,
    0x03f1,0x03d8,0x03c0,0x03a8,0x0390,0x0378,0x0361,0x034b,
    0x0334,0x031e,0x0309,0x02f4,0x02df,0x02ca,0x02b6,0x02a2,
    0x028e,0x027b,0x0268,0x0255,0x0243,0x0230,0x021f,0x020d,
    0x01fc,0x01eb,0x01da,0x01c9,0x01b9,0x01a9,0x019a,0x018a,
    0x017b,0x016c,0x015d,0x014e,0x0140,0x0132,0x0124,0x0117,
    0x0109,0x00fc,0x00ef,0x00e2,0x00d6,0x00c9,0x00bd,0x00b1,
    0x00a5,0x009a,0x008e,0x0083,0x0078,0x006d,0x0062,0x0058,
    0x004d,0x0043,0x0039,0x002f,0x0025,0x001b,0x0012,0x0009,
    0x0000,0x0000
};

const std::uint16_t pan_table[128]={
    0x8000,0x8000,0x7ffd,0x7ff6,0x7fe9,0x7fd7,0x7fc0,0x7fa4,
    0x7f83,0x7f5d,0x7f32,0x7f02,0x7ecc,0x7e92,0x7e53,0x7e0e,
    0x7dc5,0x7d76,0x7d23,0x7cca,0x7c6d,0x7c0b,0x7ba3,0x7b37,
    0x7ac6,0x7a50,0x79d5,0x7956,0x78d1,0x7848,0x77ba,0x7727,
    0x768f,0x75f3,0x7552,0x74ac,0x7402,0x7353,0x729f,0x71e7,
    0x712b,0x706a,0x6fa4,0x6eda,0x6e0b,0x6d39,0x6c61,0x6b86,
    0x6aa6,0x69c2,0x68da,0x67ee,0x66fd,0x6608,0x6510,0x6413,
    0x6312,0x620e,0x6105,0x5ff9,0x5ee9,0x5dd5,0x5cbd,0x5ba2,
    0x5a82,0x5960,0x583a,0x5710,0x55e3,0x54b2,0x537e,0x5247,
    0x510c,0x4fcf,0x4e8e,0x4d49,0x4c02,0x4ab8,0x496b,0x481b,
    0x46c8,0x4572,0x441a,0x42be,0x4160,0x4000,0x3e9d,0x3d37,
    0x3bcf,0x3a65,0x38f8,0x378a,0x3618,0x34a5,0x3330,0x31b8,
    0x303f,0x2ec3,0x2d46,0x2bc7,0x2a47,0x28c4,0x2740,0x25bb,
    0x2433,0x22ab,0x2121,0x1f96,0x1e09,0x1c7c,0x1aed,0x195d,
    0x17cc,0x163a,0x14a7,0x1314,0x1180,0x0fea,0x0e55,0x0cbf,
    0x0b28,0x0991,0x07f9,0x0661,0x04c9,0x0331,0x0198,0x0000
};

const std::uint16_t cc_lin_table[128]={
    0x0000,0x014a,0x0295,0x03e0,0x052b,0x0676,0x07c1,0x090c,
    0x0a57,0x0ba2,0x0ced,0x0e38,0x0f83,0x10ce,0x1219,0x1364,
    0x14af,0x15fa,0x1745,0x1890,0x19db,0x1b26,0x1c71,0x1dbc,
    0x1f07,0x2052,0x219d,0x22e8,0x2433,0x257e,0x26c9,0x2814,
    0x295f,0x2aaa,0x2bf5,0x2d40,0x2e8b,0x2fd6,0x3121,0x326c,
    0x33b7,0x3502,0x364d,0x3798,0x38e3,0x3a2e,0x3b79,0x3cc4,
    0x3e0f,0x3f5a,0x40a5,0x41f0,0x433b,0x4486,0x45d1,0x471c,
    0x4867,0x49b2,0x4afd,0x4c48,0x4d93,0x4ede,0x5029,0x5174,
    0x52bf,0x540a,0x5555,0x56a0,0x57eb,0x5936,0x5a81,0x5bcc,
    0x5d17,0x5e62,0x5fad,0x60f8,0x6243,0x638e,0x64d9,0x6624,
    0x676f,0x68ba,0x6a05,0x6b50,0x6c9b,0x6de6,0x6f31,0x707c,
    0x71c7,0x7312,0x745d,0x75a8,0x76f3,0x783e,0x7989,0x7ad4,
    0x7c1f,0x7d6a,0x7eb5,0x8000,0x8000,0x8000,0x8000,0x8000,
    0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
    0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
    0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
};

const std::uint16_t cc_exp_table[128]={
    0x0000,0x0027,0x0050,0x007a,0x00a6,0x00d3,0x0102,0x0133,
    0x0165,0x0199,0x01cf,0x0206,0x0240,0x027c,0x02b9,0x02f9,
    0x033b,0x0380,0x03c7,0x0410,0x045c,0x04aa,0x04fc,0x0550,
    0x05a7,0x0601,0x065e,0x06bf,0x0722,0x078a,0x07f5,0x0863,
    0x08d6,0x094d,0x09c7,0x0a46,0x0aca,0x0b52,0x0bdf,0x0c70,
    0x0d07,0x0da3,0x0e45,0x0eec,0x0f99,0x104c,0x1105,0x11c5,
    0x128c,0x1359,0x142e,0x150a,0x15ee,0x16d9,0x17cd,0x18ca,
    0x19cf,0x1add,0x1bf5,0x1d17,0x1e43,0x1f79,0x20ba,0x2207,
    0x235f,0x24c3,0x2633,0x27b0,0x293b,0x2ad3,0x2c7a,0x2e2f,
    0x2ff4,0x31c9,0x33ae,0x35a4,0x37ab,0x39c5,0x3bf1,0x3e31,
    0x4085,0x42ee,0x456c,0x4801,0x4aad,0x4d71,0x504d,0x5343,
    0x5654,0x597f,0x5cc8,0x602e,0x63b2,0x6755,0x6b19,0x6eff,
    0x7308,0x7735,0x7b87,0x8000,0x8000,0x8000,0x8000,0x8000,
    0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
    0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
    0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
};

const std::uint16_t cc_time_table[128]={
    0x0000,0x0002,0x0004,0x0006,0x0008,0x000a,0x000c,0x000e,
    0x0010,0x0012,0x0016,0x001a,0x001e,0x0022,0x0026,0x002a,
    0x002e,0x0032,0x0036,0x003a,0x003c,0x003e,0x0040,0x0042,
    0x0044,0x0046,0x0048,0x004a,0x004c,0x004e,0x005e,0x006e,
    0x007e,0x008e,0x009e,0x00ae,0x00be,0x00ce,0x00de,0x00ee,
    0x010e,0x012e,0x014e,0x016e,0x018e,0x028e,0x038e,0x048e,
    0x058e,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,
    0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,
    0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,
    0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,
    0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,
    0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,
    0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,
    0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,
    0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,
    0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,0x4000,
};

const std::uint16_t mul_frac_table[128]={
    0x0000,0x000a,0x0014,0x001f,0x0029,0x0033,0x003d,0x0048,
    0x0052,0x005c,0x0066,0x0071,0x007b,0x0085,0x008f,0x009a,
    0x00a4,0x00ae,0x00b8,0x00c3,0x00cd,0x00d7,0x00e1,0x00ec,
    0x00f6,0x0100,0x010a,0x0114,0x011f,0x0129,0x0133,0x013d,
    0x0148,0x0152,0x015c,0x0166,0x0171,0x017b,0x0185,0x018f,
    0x019a,0x01a4,0x01ae,0x01b8,0x01c3,0x01cd,0x01d7,0x01e1,
    0x01ec,0x01f6,0x0200,0x020a,0x0214,0x021f,0x0229,0x0233,
    0x023d,0x0248,0x0252,0x025c,0x0266,0x0271,0x027b,0x0285,
    0x028f,0x029a,0x02a4,0x02ae,0x02b8,0x02c3,0x02cd,0x02d7,
    0x02e1,0x02ec,0x02f6,0x0300,0x030a,0x0314,0x031f,0x0329,
    0x0333,0x033d,0x0348,0x0352,0x035c,0x0366,0x0371,0x037b,
    0x0385,0x038f,0x039a,0x03a4,0x03ae,0x03b8,0x03c3,0x03cd,
    0x03d7,0x03e1,0x03ec,0x03f6,0x03f6,0x03f6,0x03f6,0x03f6,
    0x03f6,0x03f6,0x03f6,0x03f6,0x03f6,0x03f6,0x03f6,0x03f6,
    0x03f6,0x03f6,0x03f6,0x03f6,0x03f6,0x03f6,0x03f6,0x03f6,
    0x03f6,0x03f6,0x03f6,0x03f6,0x03f6,0x03f6,0x03f6,0x03f6
};