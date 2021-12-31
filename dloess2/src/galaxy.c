#include <stdio.h>
#include "loess.h"

struct  loess_struct    galaxy;
struct  pred_struct     galaxy_contour, spine_fit, spine_se;
struct  ci_struct	spine_ci;
double	velocity[] = {1769, 1749, 1749, 1758, 1750, 1745, 1750, 1753, 1734, 
		1710, 1711, 1709, 1674, 1665, 1680, 1648, 1626, 1581, 1602, 
		1558, 1538, 1506, 1521, 1498, 1501, 1491, 1481, 1468, 1455, 
		1454, 1456, 1459, 1451, 1465, 1451, 1486, 1433, 1631, 1618, 
		1607, 1608, 1601, 1603, 1612, 1607, 1618, 1649, 1595, 1580, 
		1574, 1574, 1559, 1578, 1591, 1579, 1588, 1581, 1569, 1572, 
		1584, 1565, 1718, 1711, 1710, 1715, 1713, 1717, 1715, 1712, 
		1710, 1692, 1669, 1679, 1691, 1647, 1630, 1616, 1576, 1561, 
		1558, 1538, 1525, 1509, 1501, 1494, 1489, 1493, 1487, 1495, 
		1511, 1505, 1508, 1507, 1513, 1493, 1495, 1736, 1744, 1765, 
		1766, 1764, 1715, 1751, 1761, 1763, 1758, 1743, 1738, 1732, 
		1734, 1723, 1706, 1665, 1677, 1679, 1601, 1629, 1621, 1574, 
		1559, 1540, 1525, 1517, 1506, 1481, 1465, 1468, 1465, 1454,
 		1448, 1441, 1441, 1430, 1434, 1445, 1464, 1471, 1442, 1436, 
		1434, 1428, 1558, 1563, 1581, 1548, 1572, 1574, 1578, 1576, 
		1583, 1584, 1566, 1568, 1577, 1587, 1606, 1593, 1584, 1595, 
		1617, 1552, 1597, 1615, 1626, 1626, 1586, 1624, 1600, 1585, 
		1738, 1690, 1729, 1719, 1702, 1754, 1741, 1736, 1731, 1725, 
		1710, 1673, 1669, 1641, 1675, 1681, 1645, 1594, 1583, 1599, 
		1578, 1548, 1543, 1537, 1543, 1519, 1500, 1488, 1486, 1483, 
		1481, 1485, 1480, 1479, 1505, 1482, 1481, 1489, 1531, 1533, 
		1539, 1526, 1551, 1549, 1532, 1538, 1550, 1536, 1519, 1536, 
		1535, 1536, 1533, 1528, 1539, 1546, 1552, 1557, 1573, 1553, 
		1576, 1591, 1591, 1624, 1633, 1597, 1605, 1629, 1658, 1664, 
		1667, 1671, 1687, 1682, 1668, 1673, 1684, 1668, 1618, 1658, 
		1644, 1647, 1642, 1616, 1629, 1610, 1603, 1613, 1603, 1606, 
		1603, 1608, 1613, 1616, 1615, 1611, 1580, 1580, 1586, 1591, 
		1592, 1562, 1572, 1589, 1588, 1585, 1586, 1573, 1573, 1558, 
		1566, 1740, 1704, 1748, 1757, 1775, 1765, 1762, 1752, 1752, 
		1753, 1753, 1748, 1730, 1709, 1688, 1687, 1678, 1654, 1634, 
		1611, 1590, 1562, 1565, 1541, 1537, 1515, 1498, 1479, 1481, 
		1475, 1466, 1461, 1457, 1455, 1452, 1453, 1448, 1469, 1456, 
		1448, 1409, 1416, 1429};
double	direction[] = {8.46279, 7.96498, 7.46717, 6.96936, 6.47154, 5.97373, 
		5.47592, 4.97811, 4.4803, 3.98249, 3.46303, 2.96522, 
		2.46741, 1.9696, 1.47179, 0.973978, 0.476167, -0.021644,
	        -0.519455, -1.01727, -1.51508, -2.01289, -2.5107, 
 	        -3.00851, -3.52797, -4.02578, -4.52359, -5.0214, 
	        -5.51921, -6.01702, -6.51483, -7.01264, -7.51045, 
	        -8.00827, -8.50608, -9.5017, -11.0168, 27.8244, 21.088,
	        18.8425, 16.597, 14.3516, 12.1061, 9.86059, 7.61511, 
	        5.272, 3.02652, 0.781037, -1.46444, -3.70992, -5.95541, 
	        -8.20089, -10.4464, -12.6918, -14.9373, -17.1828, 
	        -19.4283, -21.6738, -23.9193, -26.2624, -28.5078, 
	        23.8699, 22.3013, 20.7327, 19.1642, 17.5956, 16.027, 
	        14.3902, 12.8216, 11.253, 9.68438, 8.11578, 6.54718, 
	        4.97859, 3.40999, 1.8414, 0.272799, -1.2958, -2.86439, 
	        -4.43299, -6.00159, -7.63838, -9.20698, -10.7756, 
		-12.3442, -13.9128, -15.4814, -17.05, -18.6186, 
	        -20.1872, -21.7557, -23.3243, -24.8929, -26.4615, 
	        -28.0301, -29.6669, 18.4201, 17.5959, 16.7716, 15.9474,
	        14.263, 13.4388, 12.6146, 11.7903, 10.9661, 10.1418, 
	        9.31757, 8.49332, 7.66907, 6.84483, 6.02058, 5.19634, 
	        4.37209, 3.54784, 2.68776, 1.86351, 1.03927, 0.215021,
     	        -0.609226, -1.43347, -2.25772, -3.08196, -3.90621, 
	        -4.73046, -5.5547, -6.37895, -7.2032, -8.02744, 
 	        -8.88752, -9.71177, -10.536, -11.3603, -12.1845, 
	        -13.0088, -13.833, -14.6572, -15.4815, -16.3057, 
	        -17.13, -17.9542, -18.7785, 25.8899, 24.2078, 22.4526, 
	        20.8436, 19.1615, 17.4794, 15.7972, 14.1151, 12.433, 
	        10.7509, 9.06879, 7.31354, 5.70456, 3.94931, 2.19406, 
		0.511948, -1.09703, -2.77914, -4.46126, -6.07024, 
	        -7.82548, -9.5076, -11.1897, -12.8718, -14.5539, 
	        -16.2361, -23.1108, -24.7198, 1.97596, 1.77531, 1.67498,
	        1.57466, 1.47434, 1.37401, 1.27369, 1.17336, 1.07304, 
	        0.972712, 0.872388, 0.767701, 0.667377, 0.567052, 
   	        0.466727, 0.366403, 0.266078, 0.165754, 0.0654291, 
	        -0.0348955, -0.13522, -0.235545, -0.335869, -0.436194, 
	        -0.536518, -0.636843, -0.74153, -0.841854, -0.942179, 
	        -1.0425, -1.14283, -1.24315, -1.34348, -1.4438, 
	        -1.54413, -1.64445, -1.74478, -1.8451, 24.8532, 23.827,
	        22.8007, 21.7298, 20.7036, 19.6773, 18.6511, 16.5539, 
	        15.5723, 14.546, 13.4752, 12.4489, 11.4227, 10.3964, 
	        9.37015, 8.3439, 7.31764, 6.29139, 5.26513, 4.23888, 
	        3.21262, 2.18637, 1.16011, 0.133859, -0.937015, 
	        -1.96327, -2.98953, -4.01578, -5.04204, -6.06829, 
	        -7.04993, -8.07618, -9.14706, -10.1733, -11.1996, 
	        -12.2258, -13.2521, -14.2783, -15.3046, -16.3308, 
	        -17.3571, -18.3834, -19.4096, -20.4359, -21.4621, 
	        -22.4884, 29.4841, 27.0434, 25.0908, 22.6501, 20.4046, 
	        18.1591, 15.9136, 13.7658, 11.4227, 9.17718, 6.9317, 
	        4.58859, 2.44074, 0.0976296, -2.05022, -4.19807, 
	        -6.63881, -8.88429, -11.1298, -13.2776, -15.5231, 
	        -17.8662, -20.1117, -22.3572, -24.6027, -26.8481, 
	        -29.0936, 10.8869, 9.39348, 8.91731, 8.39786, 7.92169, 
	        7.42388, 6.92607, 6.42826, 5.9088, 5.41099, 4.91318, 
   	        4.41537, 3.91756, 3.44139, 2.92193, 2.42412, 1.92631, 
	        1.4285, 0.93069, 0.432879, -0.0649319, -0.562743, 
	        -1.06055, -1.55837, -2.07782, -2.55399, -3.07344, 
	        -3.57125, -4.06906, -4.56688, -5.06469, -5.5625, 
	        -6.06031, -6.55812, -7.05593, -7.57539, -8.0732, 
	        -8.54937, -9.09046, -9.58827, -10.0428, -10.5406, 
	        -11.0601,
		-38.1732, -35.9277, -33.6822, -31.4367, -29.1912, 
		-26.9458, -24.7003, -22.4548, -20.2093, -17.9638, -15.6207, 
		-13.3753, -11.1298, -8.88429, -6.63881, -4.39333, -2.14785, 
		0.0976296, 2.34311, 4.58859, 6.83407, 9.07955, 11.325, 
		13.5705, 15.9136, 18.1591, 20.4046, 22.6501, 24.8955,
		27.141, 29.3865, 31.632, 33.8775, 36.123, 38.3684, 42.8594, 
		49.6935, 6.16853, 4.6751, 4.17728, 3.67947, 3.18166, 2.68385,
		2.18604, 1.68823, 1.16877, 0.670963, 0.173152, -0.324659, 
		-0.822471, -1.32028, -1.81809, -2.3159, -2.81371, -3.31153, 
		-3.80934, -4.30715, -4.80496, -5.30277, -5.82223, -6.32004, 
		-25.5974, -23.9153, -22.2332, -20.551, -18.8689, -17.1868, 
		-15.4316, -13.7494, -12.0673, -10.3852, -8.70311, -7.021, 
		-5.33888, -3.65677, -1.97466, -0.292541, 1.38957, 3.07169, 
		4.7538, 6.43591, 8.19116, 9.87327, 11.5554, 13.2375, 14.9196,
		16.6017, 18.2838, 19.966, 21.6481, 23.3302, 25.0123, 26.6944, 
		28.3765, 30.0586, 31.8139, -47.986, -45.8388, -43.6916, 
		-41.5443, -37.1565, -35.0093, -32.862, -30.7148, -28.5676, 
		-26.4203, -24.2731, -22.1259, -19.9786, -17.8314, -15.6842, 
		-13.5369, -11.3897, -9.24245, -7.00185, -4.85462, -2.70738, 
		-0.560148, 1.58709, 3.73432, 5.88156, 8.02879, 10.176, 
		12.3233, 14.4705, 16.6177, 18.765, 20.9122, 23.1528, 25.3, 
		27.4473, 29.5945, 31.7417, 33.889, 36.0362, 38.1834, 40.3307, 
		42.4779, 44.6251, 46.7724, 48.9196, 24.1427, 22.5741, 20.9373,
		19.437, 17.8684, 16.2998, 14.7312, 13.1626, 11.594, 10.0254, 
		8.45678, 6.81998, 5.31959, 3.68279, 2.04599, 0.477399, -1.023,
		-2.59159, -4.16019, -5.66059, -7.29738, -8.86598, -10.4346, 
		-12.0032, -13.5718, -15.1404, -21.5511, -23.0515, -45.2569, 
		-40.6613, -38.3635, -36.0656, -33.7678, -31.47, -29.1722, 
		-26.8744, -24.5766, -22.2788, -19.981, -17.5832, -15.2854, 
		-12.9876, -10.6898, -8.392, -6.09419, -3.79638, -1.49857, 
		0.799239, 3.09705, 5.39486, 7.69267, 9.99048, 12.2883, 
		14.5861, 16.9838, 19.2816, 21.5794, 23.8773, 26.1751, 28.4729,
		30.7707, 33.0685, 35.3663, 37.6641, 39.9619, 42.2597, 49.8478,
		47.7895, 45.7311, 43.5833, 41.525, 39.4666, 37.4083, 33.2021,
		31.2332, 29.1749, 27.027, 24.9687, 22.9103, 20.852, 18.7936, 
		16.7353, 14.6769, 12.6186, 10.5602, 8.50188, 6.44353, 4.38518,
		2.32683, 0.26848, -1.87936, -3.93771, -5.99606, -8.05441, 
		-10.1128, -12.1711, -14.14, -16.1983, -18.3462, -20.4045, 
		-22.4629, -24.5212, -26.5796, -28.6379, -30.6962, -32.7546, 
		-34.8129, -36.8713, -38.9296, -40.988, -43.0463, -45.1047, 
		6.53648, 5.99538, 5.5625, 5.0214, 4.52359, 4.02578, 3.52797, 
		3.0518, 2.53234, 2.03453, 1.53672, 1.01727, 0.541099, 
		0.021644, -0.454523, -0.93069, -1.47179, -1.9696, -2.46741, 
		-2.94358, -3.44139, -3.96084, -4.45866, -4.95647, -5.45428, 
		-5.95209, -6.4499, -49.1077, -42.3712, -40.2234, -37.8803, 
		-35.7324, -33.487, -31.2415, -28.996, -26.6529, -24.4074, 
		-22.1619, -19.9164, -17.671, -15.5231, -13.18, -10.9345, 
		-8.68903, -6.44355, -4.19807, -1.95259, 0.292889, 2.53837, 
		4.78385, 7.02933, 9.37244, 11.5203, 13.8634, 16.1089, 18.3544,
		20.5998, 22.8453, 25.0908, 27.3363, 29.5818, 31.8272, 34.1704,
		36.4158, 38.5637, 41.0044, 43.2499, 45.3001, 47.5456, 
		49.8887};
double	ew[59], ns[99], grid[11682], fit_eval[200], ci_eval[30];
double	tmp, range = 98, coverage = .99;
int32_t	n = 323, p = 2, m, se_fit = FALSE;
int	i, j, k;

int
main() {
        printf("\nloess(&galaxy):\n");
        loess_setup(direction, velocity, n, p, &galaxy);
        galaxy.model.span = 0.35;
	galaxy.model.normalize = FALSE;
	galaxy.model.family = "symmetric";
        loess(&galaxy);
        loess_summary(&galaxy);

	m = 5841;
	tmp = -29.0;
        for(i = 0; i < 59; i++) 
                ew[i] = tmp++;
	tmp = -49.0;
        for(i = 0; i < 99; i++)
		ns[i] = tmp++;
        for(i = 0; i < 99; i++) {
                k = i * 59;
                for(j = 0; j < 59; j++) {
                        grid[k + j] = ew[j];
                        grid[m + k + j] = ns[i];
                }
        }
        predict(grid, m, &galaxy, &galaxy_contour, se_fit);

	m = 100;
        tmp = range / 99;
        for(i = 0; i < 100; i++) {
                fit_eval[i + 100] = -49 + tmp * i;
		fit_eval[i] = fit_eval[i + 100] / (-3.7);
	}
	predict(fit_eval, m, &galaxy, &spine_fit, se_fit);

	m = 15; 
	se_fit = TRUE;
        tmp = range / 14;
        for(i = 0; i < m; i++) {
                ci_eval[i + m] = -49 + tmp * i;
		ci_eval[i] = fit_eval[i + 100] / (-3.7);
	}
	predict(ci_eval, m, &galaxy, &spine_se, se_fit);
        pointwise(&spine_se, m, coverage, &spine_ci);

        loess_free_mem(&galaxy);
	pred_free_mem(&galaxy_contour);
	pred_free_mem(&spine_fit);
	pred_free_mem(&spine_se);
        return 0;
}
