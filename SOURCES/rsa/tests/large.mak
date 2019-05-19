
.c.exe:
	cl -c -AL -W3 -I..\ -D ORIGINAL_CODE $&.c
	link /batch $&.obj, $&OLD.EXE,, ..\..\libs.org\rsalarge.lib
	cl -c -AL W3 -I..\ $&.c	
	link /batch $&.obj, $&NEW.EXE,, ..\..\libs\rsalarge.lib
	copy $&NEW.EXE $&.EXE

.asm.exe:
    	\masm51\bin\masm /Ml /D_LLARGE_ /z $&;
	link /batch $&.obj, $&OLD.EXE,, ..\..\libs.org\rsalarge.lib
	link /batch $&.obj, $&NEW.EXE,, ..\..\libs\rsalarge.lib
	copy $&NEW.EXE $&.EXE

all:	  0.exe   1.exe   2.exe   3.exe   4.exe   5.exe   6.exe   7.exe   8.exe   9.exe \
	 10.exe  11.exe  12.exe  13.exe  14.exe  15.exe  16.exe  17.exe  18.exe  19.exe \
	 20.exe  21.exe  22.exe  23.exe  24.exe  25.exe  26.exe  27.exe  28.exe  29.exe \
	 30.exe  31.exe  32.exe  33.exe  34.exe  35.exe  36.exe  37.exe  38.exe  39.exe \
	 40.exe  41.exe  42.exe  43.exe  44.exe  45.exe  46.exe  47.exe  48.exe  49.exe \
	 50.exe  51.exe  52.exe  53.exe  54.exe  55.exe  56.exe  57.exe  58.exe  59.exe \
	 60.exe  61.exe  62.exe  63.exe  64.exe  65.exe  66.exe  67.exe  68.exe  69.exe \
	 70.exe  71.exe  72.exe  73.exe  74.exe  75.exe  76.exe  77.exe  78.exe  79.exe \
	 80.exe  81.exe  82.exe  83.exe  84.exe  85.exe  86.exe  87.exe  88.exe  89.exe \
	 90.exe  91.exe  92.exe  93.exe  94.exe  95.exe  96.exe  97.exe  98.exe  99.exe \
	100.exe 101.exe 102.exe 103.exe 104.exe 105.exe 106.exe 107.exe 108.exe 109.exe \
	110.exe 111.exe 112.exe 113.exe 114.exe 115.exe 116.exe 117.exe 118.exe 119.exe \
	120.exe 121.exe 122.exe 123.exe 124.exe 125.exe 126.exe 127.exe 128.exe 129.exe \
	130.exe 131.exe 132.exe 133.exe 134.exe 135.exe 136.exe 137.exe 138.exe 139.exe \
	140.exe 141.exe 142.exe 143.exe 144.exe 145.exe 146.exe 147.exe 148.exe 149.exe \
	150.exe 151.exe 152.exe 153.exe 154.exe 155.exe 156.exe 157.exe 158.exe 159.exe \
	160.exe 161.exe 162.exe 163.exe 164.exe 165.exe 166.exe 167.exe 

clean:
	-del *.obj
	-del *.map
	-del *.exe

0.exe:		0.c

1.exe:		1.c
2.exe:		2.c
3.exe:		3.c
4.exe:		4.c
5.exe:		5.c
6.exe:		6.c
7.exe:		7.c
8.exe:		8.c
9.exe:		9.c
                
10.exe:		10.c
11.exe:		11.c
12.exe:		12.c
13.exe:		13.c
14.exe:		14.c
15.exe:		15.c
16.exe:		16.c
17.exe:		17.c
18.exe:		18.c
19.exe:		19.c
                
20.exe:		20.c
21.exe:		21.c
22.exe:		22.c
23.exe:		23.c
24.exe:		24.c
25.exe:		25.c
26.exe:		26.c
27.exe:		27.c
28.exe:		28.c
29.exe:		29.c
                
30.exe:		30.c
31.exe:		31.c
32.exe:		32.c
33.exe:		33.c
34.exe:		34.c
35.exe:		35.c
36.exe:		36.c
37.exe:		37.c
38.exe:		38.c
39.exe:		39.c
                
40.exe:		40.c
41.exe:		41.c
42.exe:		42.c
43.exe:		43.c
44.exe:		44.c
45.exe:		45.c
46.exe:		46.c
47.exe:		47.c
48.exe:		48.c
49.exe:		49.c
                
50.exe:		50.c
51.exe:		51.c
52.exe:		52.c
53.exe:		53.c
54.exe:		54.c
55.exe:		55.c
56.exe:		56.c
57.exe:		57.c
58.exe:		58.c
59.exe:		59.c
                
60.exe:		60.c
61.exe:		61.c
62.exe:		62.c
63.exe:		63.c
64.exe:		64.c
65.exe:		65.c
66.exe:		66.c
67.exe:		67.c
68.exe:		68.c
69.exe:		69.c

70.exe:		70.c
71.exe:		71.c
72.exe:		72.c
73.exe:		73.c
74.exe:		74.c
75.exe:		75.c
76.exe:		76.c
77.exe:		77.c
78.exe:		78.c
79.exe:		79.c
         
80.exe:		80.c
81.exe:		81.c
82.exe:		82.c
83.exe:		83.c
84.exe:		84.c
85.exe:		85.c
86.exe:		86.c
87.exe:		87.c
88.exe:		88.c
89.exe:		89.c
         
90.exe:		90.c
91.exe:		91.c
92.exe:		92.c
93.exe:		93.c
94.exe:		94.c
95.exe:		95.c
96.exe:		96.c
97.exe:		97.c
98.exe:		98.c
99.exe:		99.c

100.exe:	100.c
101.exe:	101.c
102.exe:	102.c
103.exe:	103.c
104.exe:	104.c
105.exe:	105.c
106.exe:	106.c
107.exe:	107.c
108.exe:	108.c
109.exe:	109.c
                 
110.exe:	110.c
111.exe:	111.c
112.exe:	112.c
113.exe:	113.c
114.exe:	114.c
115.exe:	115.c
116.exe:	116.c
117.exe:	117.c
118.exe:	118.c
119.exe:	119.c
                 
120.exe:	120.c
121.exe:	121.c
122.exe:	122.c
123.exe:	123.c
124.exe:	124.c
125.exe:	125.c
126.exe:	126.c
127.exe:	127.c
128.exe:	128.c
129.exe:	129.c
                 
130.exe:	130.c
131.exe:	131.c
132.exe:	132.c
133.exe:	133.c
134.exe:	134.c
135.exe:	135.c
136.exe:	136.c
137.exe:	137.c
138.exe:	138.c
139.exe:	139.c
                 
140.exe:	140.c
141.exe:	141.c
142.exe:	142.c
143.exe:	143.c
144.exe:	144.c
145.exe:	145.c
146.exe:	146.c
147.exe:	147.c
148.exe:	148.c
149.exe:	149.c
                 
150.exe:	150.c
151.exe:	151.c
152.exe:	152.c
153.exe:	153.c
154.exe:	154.c
155.exe:	155.c
156.exe:	156.c
157.exe:	157.asm
158.exe:	158.c
159.exe:	159.c
                 
160.exe:	160.c
161.exe:	161.c
162.exe:	162.c
163.exe:	163.c
164.exe:	164.c
165.exe:	165.c
166.exe:	166.c
167.exe:	167.c

