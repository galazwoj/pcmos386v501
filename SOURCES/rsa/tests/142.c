#include "rsa.h"

	struct DATETIME s6 = {2010,1,2,3,4,5,6};	

int main(void)
{
	char		s0 = 'Z';
	int 		s1 = +12;                               
	unsigned int 	s2 = 525;                      
	long 		s3 = -1000000;                              
	unsigned long 	s4 = 20;                     
	float  		s5 = 6.36;                      
	put_field(0, CH_FIELD	       	, 828, 30, _$bcolor,  &s0);
	put_field(0, I2_FIELD           , 928, 30, _$bcolor,  &s1);
	put_field(0, IL_FIELD           ,1028, 30, _$bcolor,  &s3);
	put_field(0, FLOAT_FIELD        ,1128, 30, _$bcolor,  &s5);
	put_field(0, TIME_FIELD         ,1228, 30, _$bcolor,  &s6);
	put_field(0, NUMERIC_DATE_FIELD ,1428, 30, _$bcolor,  &s6);
	put_field(0, STRING_DATE_FIELD  ,1328, 30, _$bcolor,  &s6);
	put_field(0, HX_FIELD           ,1528, 30, _$bcolor,  &s1);
	put_field(0, HL_FIELD           ,1528, 30, _$bcolor,  &s4);
	put_field(0, HASH_FIELD         ,1628, 30, _$bcolor,  &s0);
	put_field(0, U2_FIELD           ,1728, 30, _$bcolor,  &s2);
	put_field(0, UL_FIELD           ,1828, 30, _$bcolor,  &s4);
	put_field(0, 12                 ,1928, 30, _$bcolor,  &s4);
	return 0;
}
